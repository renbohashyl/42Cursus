#ifndef CHANNEL_COLLECTION_H
#define CHANNEL_COLLECTION_H

#include <vector>
#include <string>

class Channel;
class User;

class ChannelCollection
{
public:
    typedef  std::vector<Channel*> Container;
	typedef  Container::iterator Iterator;

enum eERR 
    {
		ERR_NONE = 0,
		ERR_MEM,		
    	ERR_SAME_NAME
	};


private:
	ChannelCollection(const ChannelCollection&);
	ChannelCollection& operator=(const ChannelCollection&);
public:
	ChannelCollection();  	
	virtual ~ChannelCollection();
	Iterator Begin();
	Iterator End();

	Channel* CreateChannel(const std::string& name, User* const pUser);
	Iterator FindByName(const std::string& name);
	int Flush();

private:
    Container mCollection;
};
#endif
