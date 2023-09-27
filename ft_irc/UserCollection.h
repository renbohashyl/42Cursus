#ifndef USERCOLLECTION_H
#define USERCOLLECTION_H

#include <vector>
#include <string>

class User;
class Session;
class SessionManager;

class UserCollection
{
public:    
	typedef  std::vector<User*> Container;    
	typedef  Container::iterator Iterator;

	enum eERR {
		ERR_NONE = 0,
		ERR_MEM, //new error
		ERR_DEAD
	};

public:
	UserCollection();
	virtual ~UserCollection();
private:
	UserCollection& operator=(const UserCollection& other);
	UserCollection(const UserCollection& other);
	
public:
	int CreateUser(  
				SessionManager* sessionManager,
				Session* session, 
                const std::string& nickName, 
                const std::string& userName,
                const std::string& hostName,
                const std::string& serverName,
                const std::string& realName);
	
	Iterator	Begin();
	Iterator	End();

	Iterator	FindByNickname(const std::string nickName);
	Iterator	FindBySession(const Session* const session);

	bool		Empty() const;
	int			Size() const;

	int			RegisterToFlush(Iterator iterator);
	int			RegisterToFlush(User* user);
	int			Flush();

protected:
private:
    Container	mCollection;
	bool		mbFlush;

protected:
private:
};

#endif
