#ifndef NONUSER_H
#define NONUSER_H

#include <string>

#include "IrcServer.h"

class IrcMessage;
class NonuserCollection;
class Session;
class SessionManager;

class Nonuser
{
friend
	class IrcServer;
friend
	class NonuserCollection;
public:
	enum eErr
	{
		ERR_NONE,
		ERR_MESSAGE_QUE_EMPTY,
		ERR_SESSION_DISCONNECTED,
		ERR_INVALID_MESSAGE,
		ERR_IS_PROMOTED,
		ERR_REGISTERED_TO_FLUSH,
		ERR_UNKNOWN
	};

	bool IsPromoted() const;
	bool IsRegisterdToFlush() const;
	bool IsPassworded() const;
	bool IsNicknamed() const;
	bool IsUsernamed() const;

	void BePromoted();
	void RegisterToFlush();
	void SetPassword(const std::string& password);
	void SetNickname(const std::string& nickname);
	void SetUsername(const std::string& username);
	void SetHostname(const std::string& hostname);
	void SetRealname(const std::string& realname);

	int GetNextMessage(std::string* pMessage);
	int ForwardMessage(const char* pMessage, size_t size);
	int ForwardMessage(const IrcMessage& message);
private:
	Nonuser();
	Nonuser(const Nonuser&);
	Nonuser& operator=(const Nonuser&);

	Nonuser(NonuserCollection* pCollection, SessionManager* pSessionManager, Session* pSession);
	virtual ~Nonuser();

private:
	NonuserCollection* mpCollection;
	Session* mpSession;
	SessionManager* mpSessionManager;

	bool mbPromoted;
	bool mbRegiterdToFlush;

	std::string mPassword;
	std::string mNickname;
	std::string mUsername;
	std::string mHostname;
	std::string mRealname;

	bool mbPassworded;
	bool mbNicknamed;
	bool mbUsernamed;
};

#endif /* NONUSER_H */
