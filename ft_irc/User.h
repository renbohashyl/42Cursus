#ifndef USER_H
#define USER_H

#include <string>
#include <vector>

class Channel;
class IrcMessage;
class Session;
class SessionManager;

class User
{
public:
	friend class UserCollection;
	friend class Channel;

	enum eErr
	{
		ERR_NONE = 0,
		ERR_NOT_FOUND_CHANNEL = 1,
		ERR_FORWARD_FAIL,
		ERR_MESSAGE_QUE_EMPTY,
		ERR_SESSION_DISCONNECTED,
		ERR_INVALID_MESSAGE,
		ERR_UNKNOWN
	};

private:
	User();
	User(const User&);
	User& operator=(const User&);

public:
	User(	SessionManager* sessionManager
			,Session* session
			,const std::string& nickName            
			,const std::string& userName 
			,const std::string& hostName 
			,const std::string& serverName            
			,const std::string& realName            
			);
	virtual ~User();
	


public:
	//Getters
	Session*				GetSession()	const;
    const std::string&		GetNickname()	const;
    const std::string&		GetUserName()	const;
    const std::string&		GetHostName()	const;
    const std::string&		GetServerName()	const;
    const std::string&		GetRealName()	const;		
	int						GetChannelCount() const;
	Channel*				GetChannelOrNullByName(const std::string& channelName) const;	

	void					SetNickName(const std::string& nickname);
	void					SetServerOperator(bool boper);

	bool 					IsDead()		const;
	bool					IsServerOperator() const;

	int 					GetNextMessage(std::string* const pMessage);

	int 					ForwardMessage(const char* const pMessage, const size_t size);
	int						ForwardMessageFriends(const IrcMessage& message);
	int						ForwardMessageFriendsAndMe(const IrcMessage& message);
	int           			ForwardMessage(const IrcMessage& message);	

public:	
	//bool					IsOperator();//??	

private:
	int						RemoveChannel(Channel* const channel);

protected:
private:
	SessionManager*			mSessionManager;
	Session* 				mSession;	
    std::string 			mNickName;
    std::string 			mUserName;
    std::string 			mHostName;
    std::string 			mServerName;
    std::string				mRealName;

	bool					mbDead;
	bool					mbServerOerater;
	
	//유저는 동시에 채널 10개에 입장할수있다.
	std::vector<Channel*>	mOnlineChannel;	

	
};

#endif
