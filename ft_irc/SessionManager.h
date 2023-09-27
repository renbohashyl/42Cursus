#ifndef __IRC_SESSION_MANAGER_H__
# define __IRC_SESSION_MANAGER_H__

#include <string>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>

#include <sys/socket.h>
#include <sys/time.h>
#include <sys/event.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

class Session;

class SessionManager
{
public:
	enum eERR {
		ERR_NONE = 0,
		ERR_READ_FAILURE = 1 << 1,
		ERR_SEND_FAILURE = 1 << 2,
		ERR_NULL = 1 << 3,
		ERR_ALREADY_CLOSED = 1 << 4,
		ERR_FATAL = 1 << 5,
		ERR_COMMON = 1 << 6,
		ERR_SENDBUFFER_IS_ALIVE = 1 << 7
	};

	enum eSessionLimits {
		LISTEN_LIMIT = 128,
		READ_LIMIT = 1024
	};

public:
	SessionManager();
	virtual ~SessionManager();

	int MakeListen(const char * ListenPort);
	int MakeListen(const unsigned short ListenPort);
	int Dispatch();
	int Close(Session *);

	Session * GetNextSessionOrNull();

	int GetListeningSocket() const;

private:
	SessionManager(const SessionManager & copy);
	SessionManager & operator=(const SessionManager & operland);

	int makeListenAux(const unsigned short ListenPort);
	int acceptNewClient();
	int readData(Session *);
	int sendToClient(Session *);
	int closeAux(Session *);

	int getKqueueFD() const;

	void changeEvent(const int ChangeSocket, const int RWFlag, const int IO);
	void disconnect(Session *);

	struct kevent * getChangeList();
	size_t getChangeLen() const;

	Session * getCurrentSession(const int);

private:
	int mListeningSocket;
	int mKqueueFD;
	int mNewEventLen;
	struct kevent mEventList[LISTEN_LIMIT];
	std::queue<Session *> mNewSessions;
	std::vector<Session *> mDisconnectedSessions;
	std::map<int, Session *> mSessions;
	std::vector<struct kevent> mChangeList;
};

#endif
