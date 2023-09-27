#ifndef CHANNEL_H
#define CHANNEL_H

#include <string>
#include <vector>

class User;
class IrcMessage;

class Channel
{
public:
	friend class ChannelCollection;

public:    
	typedef  std::vector<User*> Container;
	typedef  Container::iterator Iterator;
	typedef  Container::const_iterator ConstIterator;

	enum eERR 
    {
		ERR_NONE = 0,
		ERR_MEM,
		ERR_ALREADY_ONLINE,
		ERR_DEAD,
		ERR_SAME_NAME
	};

	enum eMODE
	{
		NONE  = 0x00,
		INVIE = 0x01, // -i
		TOPIC = 0x02, // -t
		KEY   = 0x04, // -k
		OPER  = 0x08, // -o
		LMT   = 0x10 // -l
	};

private:
	Channel();
	Channel& operator=(const Channel&);
	Channel(const Channel&);

public:
	Channel(const std::string& name);	
	virtual ~Channel();

	Iterator Begin();
	Iterator End();

	const std::string& GetName() const;
	const std::string& GetTopic() const;
	int	GetUserCount() const;
	void SetTopic(const std::string& topic);

	void SetMode(const char c);
	void SetMode(const Channel::eMODE mode);
	void SetKey(const std::string& key);
	void SetLimit(int limit);

	void RemoveMode(const char c);
	void RemoveMode(const Channel::eMODE mode);

	//Mode
	bool IsInviteMode() const;
	bool IsTopicMode() const;
	bool IsKeyeMode() const;
	bool IsLimitMode() const;
	bool IsFull() const;
	bool IsKeySame(const std::string& key) const;
	bool IsInviteUser(const User* const user) const;
	bool IsOperator(const User* const user); 
	bool IsUser(const User* const user);
	bool IsValidOption(char c);

	User* GetUserOrNull(const std::string& userNickname);
	
	int AddUser(User* const user);
	int AddInviteUser(User* const user);
	int AddOperator(User* const user);
	
	int RemoveUser(User* const pUser);
	int	RemoveInviteUser(const User* const pUser);
	int RemoveOerator(const User* const pUser);
		
	int ForwardMessage(const char* pMessage, const size_t size);
	int ForwardMessageExceptFor(const char* pMessage, const size_t size, const User& userExcepted);

	int ForwardMessage(const IrcMessage& message);
	int ForwardMessageExceptFor(const IrcMessage& message, const User& userExcepted);

	//const IrcMessage& message
	std::string GetUsersSepSpace(const User* const pUser);
	std::string GetChannelOption();
	std::string GetModePrams();
	std::string GetOperatorModePrams();

private:
	


protected:
private:	
	std::string mName;	
	bool		mbDead;
	int			mMode;
	std::string mTopic;
	std::string mKey;
	size_t		mlimit;
	Container	mCollection;	
	Container	mOperator;	
	Container	mInvite;	

protected:
private:
};

#endif
