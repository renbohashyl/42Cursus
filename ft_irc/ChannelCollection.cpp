#include "ChannelCollection.h"
#include "Channel.h"
#include "User.h"

ChannelCollection::ChannelCollection()
{
}

ChannelCollection::~ChannelCollection()
{
    Iterator iter = mCollection.begin();

    for(; iter != mCollection.end(); )
    {
        delete (*iter);            
        ++iter;        
    }
}

ChannelCollection& ChannelCollection::operator=(const ChannelCollection& other)
{
    (void)other;
    return *this;
}

ChannelCollection::ChannelCollection(const ChannelCollection&)
{
}

ChannelCollection::Iterator ChannelCollection::Begin()
{
    return mCollection.begin();
}

ChannelCollection::Iterator ChannelCollection::End()
{
    return mCollection.end();    
}

Channel* ChannelCollection::CreateChannel(const std::string& name, User* const pUser)
{    
    ChannelCollection::Iterator iterator = FindByName(name);
    if (iterator != End())
    {
        return *iterator;
    }

    Channel* channel = new Channel(name);
    mCollection.push_back(channel);

	channel->AddUser(pUser);
    return channel;
}

ChannelCollection::Iterator ChannelCollection::FindByName(const std::string& name)
{
    Iterator iter = mCollection.begin();

    for (; iter != mCollection.end(); )
    {
        if ((*iter)->GetName() == name)        
        {
            break;
        }
        ++iter;
    }

    return iter;
}

int ChannelCollection::Flush()
{
    Iterator iter = mCollection.begin();

    for(; iter != mCollection.end(); )
    {
        if ((*iter)->GetUserCount() == 0)
        {
            delete (*iter);
            iter = mCollection.erase(iter);
        }
        else
        {
            ++iter;
        }
    }

    return 0;
}
