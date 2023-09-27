#ifndef __IRC_SESSION_H__
# define __IRC_SESSION_H__

#include <time.h>
#include <limits.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/socket.h>

#include <map>
#include <utility>
#include <string>
#include <vector>
#include <deque>

#define ALPHANUM "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"

class SessionManager;

class Session
{
friend
	class SessionManager;

public:
	enum eERR {
		ERR_NONE = 0,
		ERR_MESSAGE_QUE_EMPTY,
		ERR_MESSAGE_NO_CRLF,
		ERR_MESSAGE_SINGLE_CR,
		ERR_MESSAGE_SINGLE_LF,
		ERR_MESSAGE_NUL_CHAR,
		ERR_MESSAGE_TOO_LONG,
		ERR_DISCONNECTED,
		ERR_NULL,
		ERR_UNAVAILABLE,
		ERR_COMMON
	};

	enum eLIMITS{
		MESSAGE_LIMIT = 512
	};

public:
	bool IsConnected();
	int GetSocket() const;
	unsigned short GetPort() const;
	unsigned long GetAddress() const;
	int GetNextMessage(std::string *);
	int Send(const char *, size_t);

private:
	static Session * CreateSessionPointer(const int, std::vector<struct kevent> *, struct sockaddr_in *);
	static const std::deque<char>::size_type npos = -1;

	Session();
	Session(const int, std::vector<struct kevent> *, struct sockaddr_in *);
	Session(const Session& copy);
	Session& operator= (const Session& copy);
	virtual ~Session();

//member functions
private:
	bool getReserveDeath() const;
	size_t getSizeOfSendMSG() const;
	size_t getSendMessage(char *);

	void setCurrentStatus(const bool);
	void setReserveDeath();

	void addRecvMSG(const char *, size_t);

//member variables
private:
	const int mSocket;
	bool mbAvailable;
	bool mbDeathReservation;
	const unsigned short mPort;
	const unsigned long mAddress;
	std::vector<struct kevent> * mChangeList;
	std::deque<char> mRecvMSG;
	std::deque<char> mSendMSG;
};

#endif
