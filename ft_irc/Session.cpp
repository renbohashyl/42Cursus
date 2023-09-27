#include "Session.h"
#include "SessionManager.h"

Session::Session(const int ClientSocket, std::vector<struct kevent> *managerChangeList, struct sockaddr_in *address)
	: mSocket(ClientSocket), mbAvailable(true), mbDeathReservation(false), 
	  mPort(ntohs(address->sin_port)), mAddress(ntohl(address->sin_addr.s_addr)), mChangeList(managerChangeList)
{ }
Session * Session::CreateSessionPointer(const int clientSocket, std::vector<struct kevent> *mChangeList, struct sockaddr_in *address) {
	return (new Session(clientSocket, mChangeList, address));
}

Session::~Session() {}

bool Session::getReserveDeath() const { return (mbDeathReservation); }
size_t Session::getSizeOfSendMSG() const { return (mSendMSG.size()); }
size_t Session::getSendMessage(char * buffer)
{
	std::deque<char>::iterator it = mSendMSG.begin();
	std::deque<char>::iterator ite = mSendMSG.end();
	const size_t len = mSendMSG.size();
	size_t i = 0;

	if (len > 0) {
		for (i = 0; it != ite && i < len; ++i, ++it)
			buffer[i] = *it;
		buffer[i] = '\0';
	}
	return (i);
}

void Session::setCurrentStatus(const bool whenEOF) { (mbAvailable = whenEOF); }
void Session::setReserveDeath() { mbDeathReservation = true; }

void Session::addRecvMSG(const char * buffer, size_t size)
{
	for (size_t i = 0; i < size; ++i)
		mRecvMSG.push_back(buffer[i]);
}

bool Session::IsConnected() { return (mbAvailable); }

int Session::GetSocket() const { return (mSocket); }
unsigned short Session::GetPort() const { return (mPort); }
unsigned long Session::GetAddress() const { return (mAddress); }
int Session::GetNextMessage(std::string * output)
{
	if (output == NULL)
		return (ERR_NULL);

	if (mRecvMSG.size() == 0) {
		if (IsConnected() == true)
			return (ERR_MESSAGE_QUE_EMPTY);
		else
			return (ERR_DISCONNECTED);
	}

	std::deque<char>::iterator it = mRecvMSG.begin();
	std::deque<char>::iterator ite = mRecvMSG.end();
	bool cr = false;
	int errorCode = ERR_NONE;

	for (; it != ite; ++it)
	{
		if (*it == '\r' && cr == false) {
			cr = true;
		} else if (*it == '\n') {
			if (cr) {
				*output += *it;
				break ;
			} else {
				errorCode = ERR_MESSAGE_SINGLE_LF;
				break ;
			}
		} else if (*it == '\0') {
			errorCode = ERR_MESSAGE_NUL_CHAR;
			break ;
		} else if (cr) {
			errorCode = ERR_MESSAGE_SINGLE_CR;
			break ;
		}
		*output += *it;
	}

	if (output && output->empty() == false && output->size() > MESSAGE_LIMIT)
		errorCode = ERR_MESSAGE_TOO_LONG;
	else if (it == ite) {
		if (IsConnected() == true)
			return (ERR_MESSAGE_QUE_EMPTY);
		else
			errorCode = ERR_DISCONNECTED;
	}

	if (errorCode == ERR_NONE)
		++it;
	mRecvMSG.erase(mRecvMSG.begin(), it);

	return (errorCode);
}

int Session::Send(const char * buffer, size_t len)
{
	if (buffer == NULL)
		return (ERR_NULL);

	for (size_t i = 0; i < len; i++)
		mSendMSG.push_back(buffer[i]);

	{
	struct kevent tempEvent;

	EV_SET(&tempEvent, GetSocket(), EVFILT_WRITE, EV_ENABLE, 0, 0, NULL);
	mChangeList->push_back(tempEvent);
	}

	return (ERR_NONE);
}
