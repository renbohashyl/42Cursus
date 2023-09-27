#include "IrcMessage.h"
#include "Nonuser.h"
#include "SessionManager.h"
#include "Session.h"

Nonuser::Nonuser(NonuserCollection* pCollection, SessionManager* pSessionManager, Session* pSession)
	: mpCollection(pCollection)
	, mpSession(pSession)
	, mpSessionManager(pSessionManager)
	, mbPromoted(false)
	, mbRegiterdToFlush(false)
	, mPassword()
	, mNickname()
	, mUsername()
	, mHostname()
	, mRealname()
	, mbPassworded(false)
	, mbNicknamed(false)
	, mbUsernamed(false)
{
}
Nonuser::~Nonuser()
{
	if (mbPromoted == false)
	{
		mpSessionManager->Close(mpSession);
	}
	if (mbNicknamed == true)
	{
		mpCollection->unreserveNickname(mNickname);
	}
}

bool Nonuser::IsPromoted() const
{
	return mbPromoted;
}
bool Nonuser::IsRegisterdToFlush() const
{
	return mbRegiterdToFlush;
}
bool Nonuser::IsPassworded() const
{
	return mbPassworded;
}
bool Nonuser::IsNicknamed() const
{
	return mbNicknamed;
}
bool Nonuser::IsUsernamed() const
{
	return mbUsernamed;
}

void Nonuser::RegisterToFlush()
{
	mbRegiterdToFlush = true;
	return;
}
void Nonuser::BePromoted()
{
	if (mbNicknamed == true)
	{
		mpCollection->unreserveNickname(mNickname);
	}
	mbPromoted = true;
	mbRegiterdToFlush = true;
	return;
}
void Nonuser::SetPassword(const std::string& password)
{
	mbPassworded = true;
	mPassword = password;
	return; 
}
void Nonuser::SetNickname(const std::string& nickname)
{
	if (mbNicknamed == true)
	{
		mpCollection->unreserveNickname(mNickname);
	}
	mbNicknamed = true;
	mNickname = nickname;
	mpCollection->reserveNickname(mNickname);
	return;
}
void Nonuser::SetUsername(const std::string& username)
{
	mbUsernamed = true;
	mUsername = username;
	return;
}
void Nonuser::SetRealname(const std::string& realname)
{
	mRealname = realname;
	return;
}

int Nonuser::GetNextMessage(std::string* pMessage)
{
	if (mbPromoted)
	{
		return ERR_IS_PROMOTED;
	}
	if (mbRegiterdToFlush)
	{
		return ERR_REGISTERED_TO_FLUSH;
	}
	int err;
	err = mpSession->GetNextMessage(pMessage);
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

int Nonuser::ForwardMessage(const char* pMessage, size_t size)
{
	int err;
	err = mpSession->Send(pMessage, size);
	if (err != Session::ERR_NONE)
	{
		return ERR_UNKNOWN;
	}
	return ERR_NONE;
}

int Nonuser::ForwardMessage(const IrcMessage& message)
{
	ForwardIrcMessage(message, mpSession);
	return ERR_NONE;
}
