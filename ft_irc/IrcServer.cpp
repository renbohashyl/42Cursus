#include <cctype>
#include <sstream>
#include "IrcServer.h"
#include "IrcMessage.h"
#include "Nonuser.h"
#include "Session.h"
#include "User.h"

IrcServer::IrcServer(const unsigned short port, const std::string& hostname, const std::string& password, const std::string& operatorUsername, const std::string& operatorPassword)
	: mPort(port)
	, mHostname(hostname)
	, mPassword(password)
	, mSessionManager()
	, mNonusers()
	, mUsers()
	, mChannels()
	, mOperators()
	, mOperatorUsername(operatorUsername)
	, mOperatorPassword(operatorPassword)
{
	if (mOperatorPassword == "")
	{
		mOperatorPassword = "topsecret";
	}
}
IrcServer::~IrcServer()
{
}

int IrcServer::Run()
{
	int err;
	err = mSessionManager.MakeListen(mPort);
	if (err != SessionManager::ERR_NONE)
	{
		return ERR_LISTEN_FAIL;
	}
	while(1)
	{
		err = mSessionManager.Dispatch();
		if (err != SessionManager::ERR_NONE)
		{
			return ERR_DISPATCH_FAIL;
		}

		while (1)
		{
			Session* pNewSession = mSessionManager.GetNextSessionOrNull();
			if (pNewSession == NULL)
			{
				break;
			}
			mNonusers.CreateNonuser(&mSessionManager, pNewSession);
		}
		
		for (NonuserCollection::Iterator it = mNonusers.Begin();
				it != mNonusers.End();
				++it)
		{
			Nonuser& nonuser = **it;
			while (1)
			{
				std::string rawMessage;
				err = nonuser.GetNextMessage(&rawMessage);
				if (err != Nonuser::ERR_NONE)
				{
					break;
				}

				IrcMessage message(rawMessage);
				err = processNonuserMessage(message, &nonuser);
				if (err != ERR_NONE)
				{
					//something
				}
			}
			if (err != Nonuser::ERR_MESSAGE_QUE_EMPTY)
			{
				nonuser.RegisterToFlush();
			}
		}
		mNonusers.Flush();
	
		for (UserCollection::Iterator it = mUsers.Begin();
				it != mUsers.End();
				++it)
		{
			User& user = **it;
			while(1)
			{
				std::string rawMessage;
				err = user.GetNextMessage(&rawMessage);
				if (err != User::ERR_NONE)
				{
					break;
				}

				IrcMessage message(rawMessage);
				err = processUserMessage(message, &user);
				if (err != ERR_NONE)
				{
					//something
				}
			}
			if (err != User::ERR_MESSAGE_QUE_EMPTY)
			{
				IrcMessage quitMessage;
				quitMessage.SetCommand(IrcMessage::COMMAND_QUIT);
				switch (err)
				{
					case User::ERR_SESSION_DISCONNECTED:
						quitMessage.AddParam("Remote host closed the connection");
						break;
					case User::ERR_INVALID_MESSAGE:
						quitMessage.AddParam("Remote host send invalid message");
						break;
					case User::ERR_UNKNOWN:
						quitMessage.AddParam("Unknown error occuered. Plz send msg to op");
						break;
					default:
						quitMessage.AddParam("Critical unknown error occured. Pls send msg to op");
						break;
				}
				processUserMessageQuit(quitMessage, &user);
			}
		}
		mUsers.Flush();
		mChannels.Flush();
	}
	return ERR_NONE;
}

int IrcServer::createUser(Nonuser* pNonuser)
{
	if (mPassword != "")
	{
		if (pNonuser->IsPassworded() == false || pNonuser->mPassword != mPassword)
		{
			IrcMessage response;
			response.SetCommand(IrcMessage::COMMAND_ERROR);
			response.AddParam(std::string("Bad Password"));
			pNonuser->ForwardMessage(response);
			pNonuser->RegisterToFlush();
			return ERR_NONE;
		}
	}
	int err
		= mUsers.CreateUser(
				pNonuser->mpSessionManager,
				pNonuser->mpSession,
				pNonuser->mNickname,
				pNonuser->mUsername,
				addressToString(pNonuser->mpSession->GetAddress()),
				mHostname,
				pNonuser->mRealname
			);
	if (err != UserCollection::ERR_NONE)
	{
		return ERR_USERS_FAIL;
	}

	std::stringstream sstream;
	IrcMessage welcomeMsg;
	welcomeMsg.SetPrefix(mHostname);
	welcomeMsg.SetCommand(IrcMessage::NUMERIC_RPL_WELCOME);
	welcomeMsg.AddParam(pNonuser->mNickname);
	sstream << "Welcome to the 42 Internet Relaychat Network "
		<< pNonuser->mNickname
		<< '!' << pNonuser->mUsername
		<< '@' << addressToString(pNonuser->mpSession->GetAddress());
	welcomeMsg.AddParam(sstream.str());
	sstream.str("");
	ForwardIrcMessage(welcomeMsg, pNonuser->mpSession);

	IrcMessage yourhostMsg;
	yourhostMsg.SetPrefix(mHostname);
	yourhostMsg.SetCommand(IrcMessage::NUMERIC_RPL_YOURHOST);
	yourhostMsg.AddParam(pNonuser->mNickname);
	sstream << "Your host is " << mHostname << ", running version ftircd 1.0";
	yourhostMsg.AddParam(sstream.str());
	sstream.str("");
	ForwardIrcMessage(yourhostMsg, pNonuser->mpSession);

	IrcMessage createdMsg;
	createdMsg.SetPrefix(mHostname);
	createdMsg.SetCommand(IrcMessage::NUMERIC_RPL_CREATED);
	createdMsg.AddParam(pNonuser->mNickname);
	createdMsg.AddParam("This server was created 2022.06.01");
	ForwardIrcMessage(createdMsg, pNonuser->mpSession);

	pNonuser->BePromoted();
	return ERR_NONE;
}

bool IrcServer::isSpecialChar(char ch)
{
	return ( ch == '-' || ch == '[' || ch == ']' || ch == '\\'
			|| ch == '`' || ch == '^' || ch == '{' || ch == '}');
}

bool IrcServer::isChanStringChar(char ch)
{
	return !( ch == '\0' || ch == 0xA || ch == '\r' || ch == '\n'
			|| ch == ' ' || ch == ',' || ch == ':');
}

bool IrcServer::isValidNickname(const std::string& nickname)
{
	if (nickname.size() == 0)
	{
		return false;
	}
	if (isalpha(nickname[0]) == false)
	{
		return false;
	}
	for (size_t pos = 1; pos < nickname.size(); ++pos)
	{
		if (isalpha(nickname[pos]) == false
				&& isdigit(nickname[pos]) == false
				&& isSpecialChar(nickname[pos]) == false)
		{
			return false;
		}
	}
	return true;
}

bool IrcServer::isValidChannelname(const std::string& channelname)
{
	if (channelname.size() < 2)
	{
		return false;
	}
	if (channelname[0] != '#' && channelname[0] != '&')
	{
		return false;
	}
	for (size_t pos = 1; pos < channelname.size(); ++pos)
	{
		if (isChanStringChar(channelname[pos]) == false)
		{
			return false;
		}
	}
	return true;
}

bool IrcServer::isOperatorPassword(const std::string& password)
{
if (password == "pass")
	{
		return true;
	}
	
	return false;
}

std::string IrcServer::addressToString(const unsigned long address)
{
	std::stringstream sstream;
	sstream << (address >> 24 & 0x000000FF);
	sstream << '.';
	sstream << (address >> 16 & 0x000000FF);
	sstream << '.';
	sstream << (address >> 8 & 0x000000FF);
	sstream << '.';
	sstream << (address & 0x000000FF);
	return sstream.str();
}

bool IrcServer::isOperator(const User* pUser)
{
	if (mOperators.find(pUser) == mOperators.end())	
	{
		return false;
	}
	return true;
}
void IrcServer::addOperator(const User* pUser)
{
	mOperators.insert(pUser);
	return;
}
void IrcServer::removeOperator(const User* pUser)
{
	mOperators.erase(pUser);
	return;
}
