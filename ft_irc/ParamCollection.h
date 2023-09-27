#ifndef PARAM_COLLECTION_H
#define PARAM_COLLECTION_H

#include <string>
#include <vector>

class ParamCollection
{
public:
	typedef std::vector<std::string> Container;
	typedef Container::iterator Iterator;
	typedef Container::const_iterator ConstIterator;
public:
	ParamCollection();
	ParamCollection(const ParamCollection& other);
	virtual ~ParamCollection();

	ParamCollection& operator=(const ParamCollection& other);

	size_t GetSize() const;
	ConstIterator Begin() const;
	ConstIterator End() const;

	Iterator Begin();
	Iterator End();

	void Add(const std::string& param);
	void Add(const char* pParam, size_t size);
private:

private:
	Container mParams;
};

#endif
