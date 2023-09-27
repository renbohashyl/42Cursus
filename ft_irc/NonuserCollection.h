#ifndef NONUSER_COLLECTION_H
#define NONUSER_COLLECTION_H

#include <set>
#include <string>
#include <vector>

class Nonuser;
class SessionManager;
class Session;

class NonuserCollection
{
friend
	class Nonuser;
public:
	typedef std::vector<Nonuser*> Container;
	typedef Container::iterator Iterator;

	NonuserCollection();
	virtual ~NonuserCollection();

	bool IsReservedNickname(const std::string& nickname);

	Iterator Begin();
	Iterator End();

	Nonuser* CreateNonuser(SessionManager* pSessionManager, Session* pSession);
	void Flush();
private:
	NonuserCollection(const NonuserCollection&);
	NonuserCollection& operator=(const NonuserCollection&);

	void reserveNickname(const std::string& nickname);
	void unreserveNickname(const std::string& nickname);

private:
	Container mNonusers;
	std::set<std::string> mNicknames;
};

#endif /* NONUSER_COLLECTION_H */
