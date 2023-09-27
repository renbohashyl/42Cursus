#include "UserCollection.h"
#include "SessionManager.h"
#include "User.h"

UserCollection::UserCollection()
    : mbFlush(false)
{
    mCollection.reserve(100);
}

UserCollection::UserCollection(const UserCollection& other)
{
    (void)other;
}

UserCollection& UserCollection::operator=(const UserCollection& other)
{
    (void)other;
    return *this;    
}

UserCollection::~UserCollection()
{
    UserCollection::Iterator iter = mCollection.begin();

    for (; iter != mCollection.end(); )
    {
        if ((*iter) != NULL)
        {
            delete (*iter);
        }
          
        ++iter;
    }
}

int UserCollection::CreateUser(
                SessionManager* sessionManager,
                Session* session, 
                const std::string& nickName, 
                const std::string& userName,
                const std::string& hostName,
                const std::string& serverName,
                const std::string& realName)
{
    User* user = new User(sessionManager, session, nickName, userName, hostName, serverName, realName);    
    if (NULL == user)
    {        
        return UserCollection::ERR_MEM;
    }

    mCollection.push_back(user);    
    return UserCollection::ERR_NONE;
}

UserCollection::Iterator UserCollection::Begin()
{
    return mCollection.begin();
}

UserCollection::Iterator UserCollection::End()
{
    return mCollection.end();
}

UserCollection::Iterator UserCollection::FindByNickname(const std::string nickName)
{
    Iterator iter = Begin();    

    for (; iter != End(); )
    {
        if ((*iter)->GetNickname() == nickName)
        {
            break;
        }
        ++iter;
    }

    return iter;    
}

UserCollection::Iterator UserCollection::FindBySession(const Session* const session)
{
    Iterator iter = Begin();    

    for (; iter != End(); )
    {
        if ((*iter)->GetSession() == session)
        {
            break;
        }

        ++iter;
    }

    return iter;    
}

bool UserCollection::Empty() const
{
    return mCollection.empty();
}

int UserCollection::Size() const
{
    return mCollection.size();
}

int UserCollection::RegisterToFlush(Iterator user)
{    

    if ((*user)->mbDead)
    {
        // Aready register to flush
        return UserCollection::ERR_DEAD;        
    }
    
    (*user)->mbDead = true;    
    mbFlush = true;
    return UserCollection::ERR_NONE;
}

int UserCollection::RegisterToFlush(User* user)
{    
    if (user->mbDead)
    {
        // Aready register to flush
        return UserCollection::ERR_DEAD;        
    }

    user->mbDead = true;    
    mbFlush = true;
    return UserCollection::ERR_NONE;
}

int UserCollection::Flush()
{
    if (false == mbFlush)
    {
        return UserCollection::ERR_NONE;
    }
    
    UserCollection::Iterator iter = mCollection.begin();   
    for (; iter != mCollection.end(); )
    {
        if ((*iter)->mbDead)        
        {
            delete (*iter);
            iter = mCollection.erase(iter);
        }
        else
        {
            ++iter;
        }
    }

    mbFlush = false;
    return UserCollection::ERR_NONE;        
}
