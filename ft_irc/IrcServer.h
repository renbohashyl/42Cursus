#ifndef IRC_SERVER_H
#define IRC_SERVER_H

#include <set>
#include <string>
#include "SessionManager.h"
#include "ChannelCollection.h"
#include "NonuserCollection.h"
#include "UserCollection.h"
#include "ParamCollection.h"

class IrcMessage;

class IrcServer
{
public:
	enum eErr
	{
		ERR_NONE = 0,
		ERR_LISTEN_FAIL,
		ERR_DISPATCH_FAIL,
		ERR_INVALID_MESSAGE,
		ERR_WRONG_PASSWORD,
		ERR_USERS_FAIL
	};
public:
	IrcServer(const unsigned short port, const std::string& hostname, const std::string& password, const std::string& operatorUsername, const std::string& operatorPassword);
	virtual ~IrcServer();

	int Run();

private:
	IrcServer();
	IrcServer(const IrcServer&);
	IrcServer& operator=(const IrcServer&);

	int processNonuserMessage(const IrcMessage& message, Nonuser* pNonuser);
	int processUserMessage(const IrcMessage& message, User* pUser);

	int processNonuserMessagePass(const IrcMessage& message, Nonuser* pNonuser);
	int processNonuserMessageNick(const IrcMessage& message, Nonuser* pNonuser);
	int processNonuserMessageUser(const IrcMessage& message, Nonuser* pNonuser);
	int processNonuserMessageQuit(Nonuser* pNonuser);

	int processUserMessagePass(const IrcMessage& message, User* pUser);
	int processUserMessageNick(const IrcMessage& message, User* const pUser);
	int processUserMessageUser(const IrcMessage& message, User* pUser);
	int processUserMessageNames(const IrcMessage& message, User* pUser);
	int processUserMessageJoin(const IrcMessage& message, User* const pUser);
	int processUserMessagePart(const IrcMessage& message, User* pUser);
	int processUserMessageMode(const IrcMessage& message, User* pUser);
	int processUserMessageTopic(const IrcMessage& message, User* pUser);
	int processUserMessageInvite(const IrcMessage& message, User* pUser);
	int processUserMessageKick(const IrcMessage& message, User* pUser);
	int processUserMessagePrivmsg(const IrcMessage& message, User* pUser);
	int processUserMessageQuit(const IrcMessage& message, User* pUser);
	int processUserMessageList(const IrcMessage& message, User* pUser);
		
	/*
	//yoseo need command
	int processUserMessageOper(const IrcMessage& message, User* pUser);
	int processUserMessageKill(const IrcMessage& message, User* pUser);	
	*/
	int processUserMessagePing(User* pUser);
	
	int processCommandMode(User* pUser, Channel* pChannel, const std::string& modes, ParamCollection::ConstIterator it, ParamCollection::ConstIterator endIt);
	int processCommandModePlusI(User* pUser, Channel* pChannel);
	int processCommandModePlusT(User* pUser, Channel* pChannel);
	int processCommandModePlusK(User* pUser, Channel* pChannel);
	int processCommandModePlusK(User* pUser, Channel* pChannel, const std::string& arg);
	int processCommandModePlusO(User* pUser, Channel* pChannel);
	int processCommandModePlusO(User* pUser, Channel* pChannel, const std::string& arg);
	int processCommandModePlusL(User* pUser, Channel* pChannel);
	int processCommandModePlusL(User* pUser, Channel* pChannel, const std::string& arg);
	int processCommandModeMinusI(User* pUser, Channel* pChannel);
	int processCommandModeMinusT(User* pUser, Channel* pChannel);
	int processCommandModeMinusK(User* pUser, Channel* pChannel);
	int processCommandModeMinusO(User* pUser, Channel* pChannel);
	int processCommandModeMinusO(User* pUser, Channel* pChannel, const std::string& arg);
	int processCommandModeMinusL(User* pUser, Channel* pChannel);
	int processCommandModeUnknown(User* pUser, Channel* pChannel, char c);

	int createUser(Nonuser* pNonuser);
	bool isSpecialChar(char ch);
	bool isChanStringChar(char ch);
	bool isValidNickname(const std::string& nickname);
	bool isValidChannelname(const std::string& channelname);
	std::string addressToString(const unsigned long address);

	bool isOperator(const User* pUser);
	bool isOperatorPassword(const std::string& password);
	void addOperator(const User* pUser);
	void removeOperator(const User* pUser);

	int messageChannelHelloWorld(const IrcMessage& message, User* pUser, Channel* channel);

private:
	unsigned short mPort;
	std::string mHostname; //i.love.de.......
	std::string mPassword;

	SessionManager mSessionManager;
	NonuserCollection mNonusers;
	UserCollection mUsers;
	ChannelCollection mChannels;

	std::set<const User*> mOperators;
	std::string mOperatorUsername;
	std::string mOperatorPassword;
};

#endif /* IRC_SERVER_H */
