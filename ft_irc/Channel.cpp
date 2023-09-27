#include "Channel.h"
#include "User.h"

Channel::Channel()
    : mName("")
    , mbDead(false)
    , mMode(Channel::NONE)
    , mTopic("")
    , mKey("")
    , mlimit(0)    
{
}

Channel::Channel(const std::string& name)
    : mName(name)
    , mbDead(false)
    , mMode(Channel::TOPIC)
    , mTopic("")
    , mKey("")
    , mlimit()    
{
    mCollection.reserve(100);
    mOperator.reserve(10);
    mInvite.reserve(10);
}


Channel::Channel(const Channel& other)
{
    (void)other;
}

Channel& Channel::operator=(const Channel& other)
{
    (void)other;
    return *this;
}

Channel::~Channel()
{
}

Channel::Iterator Channel::Begin()
{
    return mCollection.begin();
}
Channel::Iterator Channel::End()
{
    return mCollection.end();
}

const std::string& Channel::GetName() const
{
    return mName;
}

const std::string& Channel::GetTopic() const
{
    return mTopic;
}

int	Channel::GetUserCount() const
{
    return mCollection.size();
}

void  Channel::SetTopic(const std::string& topic)
{
    mTopic = topic;
}

void  Channel::SetKey(const std::string& key)
{
    mKey = key;
}

void Channel::SetLimit(int limit)
{
    mlimit = limit;
}

void Channel::SetMode(const char c)
{
    switch (c)
    {
    case 'i' :
        mMode = mMode | static_cast<int>(Channel::INVIE);
        break;
    case 'l' :
        mMode = mMode | static_cast<int>(Channel::LMT);
        break;
    case 't' :
        mMode = mMode | static_cast<int>(Channel::TOPIC);
        break;
    case 'k' :
        mMode = mMode | static_cast<int>(Channel::KEY);
        break;
    case 'o' :
        mMode = mMode | static_cast<int>(Channel::OPER);
        break;
    default:        
        break;
    }
}
void Channel::SetMode(const Channel::eMODE mode)
{    
    mMode = mMode | static_cast<int>(mode);
}

void Channel::RemoveMode(const char c)
{    
    switch (c)
    {
    case 'i':
        mMode = mMode & ~(static_cast<int>(Channel::INVIE));
        break;
    case 'l':
        mMode = mMode & ~(static_cast<int>(Channel::LMT));
        break;
    case 't':
        mMode = mMode & ~(static_cast<int>(Channel::TOPIC));
        break;
    case 'k':
        mMode = mMode & ~(static_cast<int>(Channel::KEY));
        break;
    case 'o':
        mMode = mMode & ~(static_cast<int>(Channel::OPER));
        break;
    default:        
        break;
    }
}

void Channel::RemoveMode(const Channel::eMODE mode)
{
    mMode = mMode & ~(static_cast<int>(mode));
}



bool Channel::IsInviteMode() const
{
    return mMode & Channel::INVIE;
}
bool Channel::IsTopicMode() const
{
    return mMode & Channel::TOPIC;
}
bool Channel::IsKeyeMode() const
{
    return mMode & Channel::KEY;
}
bool Channel::IsLimitMode() const
{
    return mMode & Channel::LMT;
}

bool Channel::IsFull() const
{
    return mlimit <= mCollection.size();
}

bool Channel::IsKeySame(const std::string& key) const
{
    return key == mKey;
}

bool Channel::IsValidOption(char c)
{
    switch (c)
    {
    case 'i':                
    case 'l':        
    case 't':
    case 'k':        
    case 'o':
        return true;    
    }
    return false;
}

bool Channel::IsInviteUser(const User* const user) const
{
    ConstIterator inviteIter = mInvite.begin();

    for ( ;inviteIter != mInvite.end(); )    
    {
        if ((*inviteIter) == user)
        {
            return true;
        }
        ++inviteIter;
    }
    return false;
}

bool Channel::IsOperator(const User* const user)
{
    ConstIterator operatorIter = mOperator.begin();     

    for ( ;operatorIter != mOperator.end(); )
    {
        if ((*operatorIter) == user)
        {
            return true;            
        }

        ++operatorIter;
    }
    return false;
}

bool Channel::IsUser(const User* const user)
{
    ConstIterator iter = mCollection.begin();     

    for ( ;iter != mCollection.end(); )
    {
        if ((*iter) == user)
        {
            return true;            
        }

        ++iter;
    }
    return false;
}

User* Channel::GetUserOrNull(const std::string& userNickname)
{
    Iterator iter = mCollection.begin();

    for ( ;iter != mCollection.end(); )
    {
        if ((*iter)->GetNickname() == userNickname)
        {
            return *iter;            
        }

        ++iter;
    }
    
    return NULL;
}

int Channel::AddUser(User* const user)
{
    user->mOnlineChannel.push_back(this);

    if (mCollection.empty())
    {
        AddOperator(user);        
    }

    mCollection.push_back(user);

    //접속할때 초대목록에서 제거
    RemoveInviteUser(user);

    if (IsTopicMode())
    {
        //reply
    }

    //reply
    return Channel::ERR_NONE;
}

int Channel::AddInviteUser(User* const user)
{
    //채널에 없을때!
    if (NULL == GetUserOrNull(user->GetNickname()))
    {
        mInvite.push_back(user);
    }

    return ERR_NONE;
}

int Channel::AddOperator(User* const user)
{
    if (IsOperator(user))
    {
        return ERR_NONE;
    }

    mOperator.push_back(user);
    return ERR_NONE;
}

int Channel::RemoveUser(User* const user)
{
    //Remove User
    Iterator iter = mCollection.begin();
    
    for (; iter != mCollection.end(); )
    {
        if (user == *iter)
        {            
            mCollection.erase(iter);
            break ;
        }
        ++iter;
    }

    //Remove Operator
    RemoveOerator(user);

    //Remove InviteUser
    RemoveInviteUser(user);
    
    //user remvoe channel
    user->RemoveChannel(this);
    return Channel::ERR_NONE;        
}

int	Channel::RemoveInviteUser(const User* const pUser)
{
    Iterator iter = mInvite.begin();
    for (; iter != mInvite.end(); )
    {
        if (pUser == *iter)
        {
            mInvite.erase(iter);
            break ;
        }
        ++iter;
    }
    
    return Channel::ERR_NONE;        
}

int Channel::RemoveOerator(const User* const pUser)
{
    Iterator iter = mOperator.begin();

    for (; iter != mOperator.end(); )
    {
        if (pUser == *iter)
        {
            mOperator.erase(iter);
            break ;
        }        
        ++iter;
    }
    
    return Channel::ERR_NONE;        
}

int Channel::ForwardMessage(const char* pMessage, const size_t size)
{
    Iterator iter = mCollection.begin();

    for (; iter != mCollection.end(); )
    {
        (*iter)->ForwardMessage(pMessage, size);
        ++iter;
    }

    return 0;
}

int Channel::ForwardMessageExceptFor(const char* pMessage, const size_t size, const User& userExcepted)
{
    Iterator iter = mCollection.begin();

    for (; iter != mCollection.end(); )
    {
        if (*iter != &userExcepted)
        {
            (*iter)->ForwardMessage(pMessage, size);            
        }

        ++iter;
    }
    return 0;
}

int Channel::ForwardMessage(const IrcMessage& message)
{
    Iterator iter = mCollection.begin();

    for (; iter != mCollection.end(); )
    {
        (*iter)->ForwardMessage(message);
        ++iter;
    }

    return ERR_NONE;
}

int Channel::ForwardMessageExceptFor(const IrcMessage& message, const User& userExcepted)
{
    Iterator iter = mCollection.begin();

    for (; iter != mCollection.end(); )
    {
        if (*iter != &userExcepted)
        {
            (*iter)->ForwardMessage(message);            
        }

        ++iter;
    }
    return ERR_NONE;
}

std::string Channel::GetUsersSepSpace(const User* const pUser)
{
    std::string str;
    str.reserve(100);

    //first self...
    str = pUser->GetNickname();
    if (IsOperator(pUser))
    {
        str = "@";
        str += pUser->GetNickname();        
    }

    for (size_t i = 0; i < mCollection.size(); ++i)
    {
        if (mCollection[i] == pUser)
        {
            continue;
        }

        str += " ";
        if (IsOperator(mCollection[i]))
        {
            str += "@";
        }
        str += mCollection[i]->GetNickname();
    }
    return str;
}

std::string Channel::GetChannelOption()
{
    std::string str = "+";
    str.reserve(100);

    


    if (mMode & Channel::INVIE)
    {
        str += "i";
    }

    if (mMode & Channel::TOPIC)
    {
        str += "t";
    }

    if (mMode & Channel::LMT)
    {
        str += "l";       
    }

    if (mMode & Channel::KEY)
    {
        str += "k";
    }

    if (mMode & Channel::OPER)
    {
        str += "o";
    }



    //k > l > i
    //유저 컬렉션에서 같은 채널에있는 유저들에게 메세지발사 (범용메세지?)
    //nick topic등 채널에서 일어나는 명령어들 문서참조.
    //nick prepix 확인
    return str;
}

std::string Channel::GetModePrams()
{
    std::string str("");

    if (IsLimitMode())
    {
        str += std::to_string(mlimit);
    }

    return str;
}

std::string Channel::GetOperatorModePrams()
{
    std::string str("");

    if (IsLimitMode())
    {
        str += std::to_string(mlimit);
        str += " ";
    }

    if (IsKeyeMode())
    {
        str += mKey;        
    }

    return str;
}


