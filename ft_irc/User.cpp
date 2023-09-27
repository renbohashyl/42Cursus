#include "User.h"
#include "SessionManager.h"
#include "Session.h"
#include "Channel.h"
#include "IrcMessage.h"



#include <set>

//debug
#include <iostream>


User::User()
{
}

User::User(const User& other)
{
    (void)other;
}

User& User::operator=(const User& other)
{
    (void)other;
    return *this;
}

User::~User()
{
    
    std::vector<Channel*>::iterator iterator = mOnlineChannel.begin();        
     for (; iterator != mOnlineChannel.end(); )
     {
        if (NULL != *iterator)
        {            
            (*iterator)->RemoveUser(this);
        }
     }     

     mSessionManager->Close(mSession);
}
User::User( SessionManager* sessionManager
            ,Session* session
            ,const std::string& nickName
			,const std::string& userName 
			,const std::string& hostName 
			,const std::string& serverName            
			,const std::string& realName)
    : mSessionManager(sessionManager)    
    , mSession(session)
    , mNickName(nickName)
    , mUserName(userName)
    , mHostName(hostName)
    , mServerName(serverName)
    , mRealName(realName)
    , mbDead(false)
    , mbServerOerater(false)
{
}

Session* User::GetSession() const
{
    return mSession;    
}

const std::string& User::GetNickname() const
{
    return mNickName;
}

const std::string& User::GetUserName() const
{
    return mUserName;
}

const std::string& User::GetHostName() const
{
    return mHostName;
}

const std::string& User::GetServerName() const
{
    return mServerName;
}

const std::string& User::GetRealName() const
{
    return mRealName;
}

bool User::IsDead() const
{
    return mbDead;
}

bool User::IsServerOperator() const
{
    //return mbServerOerater;
    return true;
}

int	User::GetChannelCount() const
{
    return mOnlineChannel.size();
}

Channel* User::GetChannelOrNullByName(const std::string& channelName) const
{
    std::vector<Channel*>::const_iterator channelIter = mOnlineChannel.begin();

    for (; channelIter != mOnlineChannel.end(); )
    {
        if ((*channelIter)->GetName() == channelName)
        {
            return *channelIter;        
        }
        ++channelIter;
    }
    
    return NULL;
}

void User::SetNickName(const std::string& nickname)
{
    mNickName = nickname;
}

void User::SetServerOperator(bool boper)
{
    mbServerOerater = boper;
}



int User::RemoveChannel(Channel* const channel)
{
    std::vector<Channel*>::const_iterator channelIter = mOnlineChannel.begin();

    for (; channelIter != mOnlineChannel.end(); )
    {
        if ((*channelIter) == channel)
        {
            mOnlineChannel.erase(channelIter);            
            return ERR_NONE;
        }
        ++channelIter;
    }
    
    std::cout << "User::RemoveChannel" << std::endl;
    return ERR_NOT_FOUND_CHANNEL;
}



int User::GetNextMessage(std::string* const pMessage)
{
	int err;
	err = mSession->GetNextMessage(pMessage);
	if (err != Session::ERR_NONE)
	{
		switch(err)
		{
			case Session::ERR_MESSAGE_QUE_EMPTY:
				return ERR_MESSAGE_QUE_EMPTY;
				break;
			case Session::ERR_DISCONNECTED:
				return ERR_SESSION_DISCONNECTED;
				break;
			case Session::ERR_MESSAGE_TOO_LONG:
			case Session::ERR_MESSAGE_NUL_CHAR:
			case Session::ERR_MESSAGE_SINGLE_CR:
			case Session::ERR_MESSAGE_SINGLE_LF:
				return ERR_INVALID_MESSAGE;
				break;
			default:
				return ERR_UNKNOWN;
		}
	}
	return ERR_NONE;
}

int User::ForwardMessage(const char* const pMessage, const size_t size)
{
    int err = mSession->Send(pMessage, size);    
		if (err != Session::ERR_NONE)
		{
			return ERR_FORWARD_FAIL;
		}
		return ERR_NONE;
}

int User::ForwardMessageFriends(const IrcMessage& message)
{
    std::set<User*> setUser;

    for (size_t i = 0; i < mOnlineChannel.size(); ++i)
    {
        Channel* channel = mOnlineChannel[i];
        Channel::Iterator userIter = channel->Begin();
    
        for (;channel->End() != userIter; ++userIter)
        {
            if (this != *userIter)
            {
                setUser.insert(*userIter);
            }                        
        }
    }

    std::set<User*>::iterator userIter = setUser.begin();
    for (;setUser.end() != userIter; ++userIter)
    {
        int err = (*userIter)->ForwardMessage(message);

        if (err != IrcMessage::ERR_NONE)
        {
            return ERR_FORWARD_FAIL;
        }        
    }
    return ERR_NONE;
}

int User::ForwardMessageFriendsAndMe(const IrcMessage& message)
{
    std::set<User*> setUser;

    setUser.insert(this);

    for (size_t i = 0; i < mOnlineChannel.size(); ++i)
    {
        Channel* channel = mOnlineChannel[i];
        Channel::Iterator userIter = channel->Begin();
    
        for (;channel->End() != userIter; ++userIter)
        {
            std::cout << "insert" << std::endl;
            setUser.insert(*userIter);
        }
    }

    std::set<User*>::iterator userIter = setUser.begin();
    for (;setUser.end() != userIter; ++userIter)
    {
        std::cout << "ForwardMessage" << std::endl;
        int err = (*userIter)->ForwardMessage(message);
        if (err != IrcMessage::ERR_NONE)
        {
            return ERR_FORWARD_FAIL;
        }
    }

    return ERR_NONE;
}

int User::ForwardMessage(const IrcMessage& message)
{
	int err = ForwardIrcMessage(message, mSession);
	if (err != IrcMessage::ERR_NONE)
	{
		return ERR_FORWARD_FAIL;
	}
	return ERR_NONE;
}
