#include "SessionManager.h"
#include "Session.h"

SessionManager::SessionManager()
 : mListeningSocket(-1), mKqueueFD(-1), mNewEventLen(0), mEventList() { }
SessionManager::~SessionManager() {
	std::map<int, Session *>::iterator map_it = mSessions.begin();
	std::map<int, Session *>::iterator map_ite = mSessions.end();
	std::vector<Session *>::iterator vec_it = mDisconnectedSessions.begin();
	std::vector<Session *>::iterator vec_ite = mDisconnectedSessions.end();

	for (; map_it != map_ite; ++map_it)
		delete (map_it->second);
	for (; vec_it != vec_ite; ++vec_it)
		delete (*vec_it);
	close(GetListeningSocket());
}

int SessionManager::makeListenAux(const unsigned short ListenPort)
{
	struct sockaddr_in serverAddr;

	mListeningSocket = socket(AF_INET, SOCK_STREAM, 0);
	mKqueueFD = kqueue();

	if (mListeningSocket == -1 || mKqueueFD == -1)
		return (ERR_FATAL);

	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddr.sin_port = htons(ListenPort);

	if (bind(mListeningSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) || \
		listen(mListeningSocket, LISTEN_LIMIT) || \
		fcntl(mListeningSocket, F_SETFL, O_NONBLOCK))
		return (ERR_FATAL);
	changeEvent(mListeningSocket, EVFILT_READ, EV_ADD | EV_ENABLE);

	return (ERR_NONE);
}

int SessionManager::acceptNewClient()
{
	struct sockaddr_in clientAddr;
	socklen_t sockLen = sizeof(clientAddr);
	memset(&clientAddr, 0, sizeof(clientAddr));
	const int clientSocket = accept(GetListeningSocket(), (struct sockaddr *)&clientAddr, &sockLen);
	if (clientSocket == -1)
		return (ERR_FATAL);
	if (fcntl(clientSocket, F_SETFL, O_NONBLOCK))
		return (close(clientSocket));

	Session * tempSession = Session::CreateSessionPointer(clientSocket, &mChangeList, &clientAddr);
	std::pair<const int, Session *>toInsert(clientSocket, tempSession);

	mSessions.insert(toInsert);
	mNewSessions.push(tempSession);
	changeEvent(clientSocket, EVFILT_READ, EV_ADD | EV_ENABLE);
	changeEvent(clientSocket, EVFILT_WRITE, EV_ADD | EV_DISABLE);
	return (ERR_NONE);
}

int SessionManager::readData(Session * session)
{
	char buf[READ_LIMIT + 1];
	ssize_t readSize = recv(session->GetSocket(), buf, READ_LIMIT, 0);

	if (readSize < 0) {
		if (errno == EAGAIN || errno == EWOULDBLOCK)
			return (ERR_NONE);
	} else {
		while (readSize > 0) {
			session->addRecvMSG(buf, readSize);
			readSize = recv(session->GetSocket(), buf, READ_LIMIT, 0);
		}
		if (readSize != 0 && (errno == EAGAIN || errno == EWOULDBLOCK))
			return (ERR_NONE);
	}

	disconnect(session);
	return (readSize == 0 ? ERR_NONE : ERR_READ_FAILURE);
}

int SessionManager::sendToClient(Session * session)
{
	std::deque<char>::iterator it = session->mSendMSG.begin();
	char buf[READ_LIMIT];
	size_t bufSize = session->getSendMessage(buf);
	it += bufSize;

	ssize_t	writeSize = send(session->GetSocket(), buf, bufSize, 0);

	if (writeSize == -1) {
		if (errno == EAGAIN || errno == EWOULDBLOCK)
			return (ERR_NONE);
	} else {
		if ((std::deque<char>::size_type)writeSize < bufSize) {
			while (writeSize != -1) {
				session->mSendMSG.erase(session->mSendMSG.begin(), it);
				it = session->mSendMSG.begin() + session->getSendMessage(buf);
				writeSize = send(session->GetSocket(), buf, READ_LIMIT, 0);
			}
			if (errno == EAGAIN || errno == EWOULDBLOCK)
				return (ERR_NONE);
		} else if (session->getReserveDeath()) {
			return (Close(session));
		} else {
			session->mSendMSG.erase(session->mSendMSG.begin(), it);
			changeEvent(session->GetSocket(), EVFILT_WRITE, EV_DISABLE);
			return (ERR_NONE);
		}
	}

	disconnect(session);
	return (ERR_SEND_FAILURE);
}

int SessionManager::getKqueueFD() const { return (mKqueueFD); }

void SessionManager::changeEvent(const int ChangeSocket, const int RWFlag, const int IO)
{
	struct kevent tempEvent;

	EV_SET(&tempEvent, ChangeSocket, RWFlag, IO, 0, 0, NULL);
	mChangeList.push_back(tempEvent);
}

void SessionManager::disconnect(Session * ToCloseSession)
{
	ToCloseSession->setCurrentStatus(false);
	mDisconnectedSessions.push_back(ToCloseSession);
	mSessions.erase(ToCloseSession->GetSocket());
}

struct kevent * SessionManager::getChangeList() { return (&(mChangeList[0])); }
size_t SessionManager::getChangeLen() const { return (mChangeList.size()); }

Session * SessionManager::getCurrentSession(const int customNumber)
{
	Session * tempSession = mSessions[customNumber];

	if (tempSession == NULL)
	{
		std::vector<Session *>::iterator it = mDisconnectedSessions.begin();
		std::vector<Session *>::iterator ite = mDisconnectedSessions.end();
		for (; it != ite; ++it) {
			if ((*it)->mSocket == customNumber) {
				tempSession = *it;
				break ;
			}
		}
	}
	return (tempSession);
}

int SessionManager::MakeListen(const char * ListenPort) { return(makeListenAux(atoi(ListenPort))); }
int SessionManager::MakeListen(const unsigned short ListenPort) { return(makeListenAux(ListenPort)); }

int SessionManager::Dispatch()
{
	mNewEventLen = kevent(mKqueueFD, getChangeList(), getChangeLen(), mEventList, LISTEN_LIMIT, NULL);

	if (mNewEventLen == -1)
		return (ERR_FATAL);
	mChangeList.clear();

	for (int i = 0; i < mNewEventLen; i++)
	{
		if ((mEventList[i]).flags & EV_ERROR) {
			if ((mEventList[i]).ident == (uintptr_t)GetListeningSocket()) {
				return (ERR_FATAL);
			} else {
				getCurrentSession(mEventList[i].ident);
			}
		}
		else if ((mEventList[i]).filter == EVFILT_WRITE) {
			sendToClient(getCurrentSession(mEventList[i].ident));
		}
		else if ((mEventList[i]).filter == EVFILT_READ) {
			if ((mEventList[i]).ident == (uintptr_t)GetListeningSocket()) {
				if (acceptNewClient() == ERR_FATAL)
					return (ERR_FATAL);
			}
			else if (mSessions.find((mEventList[i]).ident) != mSessions.end()) {
				readData(getCurrentSession(mEventList[i].ident));
			}
		}
	}
	return (ERR_NONE);
}

int SessionManager::closeAux(Session * ToCloseSession)
{
	Session * tempSession = ToCloseSession;
	const int keyOfSession = ToCloseSession->GetSocket();

	if (mSessions.erase(keyOfSession) == 0) {
		std::vector<Session *>::iterator it = mDisconnectedSessions.begin();
		std::vector<Session *>::iterator ite = mDisconnectedSessions.end();
		for (; it != ite; ++it) {
			if (*it == tempSession)
				break ;
		}
		mDisconnectedSessions.erase(it);
	}
	close(keyOfSession);
	delete (tempSession);
	return (ERR_NONE);
}

int SessionManager::Close(Session * ToCloseSession)
{
	if (ToCloseSession == NULL)
		return (ERR_NULL);
	else if (ToCloseSession->getReserveDeath() || ToCloseSession->mSendMSG.empty() == true) {
		return (closeAux(ToCloseSession));
	}
	ToCloseSession->setReserveDeath();
	disconnect(ToCloseSession);
	return (ERR_SENDBUFFER_IS_ALIVE);
}

Session * SessionManager::GetNextSessionOrNull()
{
	Session * tempSession = NULL;

	if (!(mNewSessions.empty())) {
		tempSession = mNewSessions.front();
		mNewSessions.pop();
	}
	return (tempSession);
}

int SessionManager::GetListeningSocket() const { return (mListeningSocket); }
