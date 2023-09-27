#include "ParamCollection.h"

ParamCollection::ParamCollection()
	: mParams()
{
}
ParamCollection::ParamCollection(const ParamCollection& other)
	:mParams(other.mParams)
{
}
ParamCollection::~ParamCollection()
{
}

ParamCollection& ParamCollection::operator=(const ParamCollection& other)
{
	mParams = other.mParams;
	return *this;
}

ParamCollection::Iterator ParamCollection::Begin()
{
	return mParams.begin();
}
ParamCollection::Iterator ParamCollection::End()
{
	return mParams.end();
}

size_t ParamCollection::GetSize() const
{
	return mParams.size();
}
ParamCollection::ConstIterator ParamCollection::ParamCollection::Begin() const
{
	const Container& ref = mParams;
	return ref.begin();
}
ParamCollection::ConstIterator ParamCollection::End() const
{
	const Container& ref = mParams;
	return ref.end();
}

void ParamCollection::Add(const std::string& param)
{
	mParams.push_back(param);
	return;
}

void ParamCollection::Add(const char* pParam, size_t size)
{
	/* FIXME
	 * use ReversIterator...?
	 */
	std::string str;
	mParams.push_back(str);
	Iterator it = mParams.end();
	--it;
	it->assign(pParam, size);
	return;
}
