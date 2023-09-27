#include "NonuserCollection.h"
#include "Nonuser.h"

NonuserCollection::NonuserCollection()
	: mNonusers()
{
}
NonuserCollection::~NonuserCollection()
{
}

bool NonuserCollection::IsReservedNickname(const std::string& nickname)
{
	if (mNicknames.find(nickname) == mNicknames.end())
	{
		return false;
	}
	return true;
}

NonuserCollection::Iterator NonuserCollection::Begin()
{
	return mNonusers.begin();
}
NonuserCollection::Iterator NonuserCollection::End()
{
	return mNonusers.end();
}

Nonuser* NonuserCollection::CreateNonuser(SessionManager* pSessionManager, Session* pSession)
{
	Nonuser* pNonuser = new Nonuser(this, pSessionManager, pSession);
	mNonusers.push_back(pNonuser);
	return pNonuser;
}

void NonuserCollection::Flush()
{
	Iterator it = mNonusers.begin();
	while (it != mNonusers.end())
	{
		if ((**it).IsRegisterdToFlush())
		{
			delete *it;
			it = mNonusers.erase(it);
			continue;
		}
		++it;
	}
}

void NonuserCollection::reserveNickname(const std::string& nickname)
{
	mNicknames.insert(nickname);
	return;
}

void NonuserCollection::unreserveNickname(const std::string& nickname)
{
	mNicknames.erase(nickname);
	return;
}
