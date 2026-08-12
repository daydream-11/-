#ifndef __REGISTER_TEMPLATE_H__
#define __REGISTER_TEMPLATE_H__

#include <vector>
using namespace std;

// ÏòÁ¿×¢²áÆ÷
template<typename RegT>
class VectorRegister
{
public:
	typedef vector<RegT*> TVectorRegContainer;
public:
	VectorRegister()
	{

	}
	virtual ~VectorRegister() 
	{

	}
public:

	// ×¢²á¼àÌý
	bool RegListener(RegT *pRegT);

	// ·´×¢²á¼àÌý
	bool UnRegListener(RegT *pRegT);

protected:
	TVectorRegContainer m_vectorRegContainer;
};

template<typename RegT>
bool VectorRegister<RegT>::UnRegListener(RegT *pRegT) 
{
	bool bFind = false;
	TVectorRegContainer::iterator iter = m_vectorRegContainer.begin();
	while (iter != m_vectorRegContainer.end())
	{
		if ((*iter) == pRegT)
		{
			bFind = true;
			iter = m_vectorRegContainer.erase(iter);
		}
		else
		{
			++iter;
		}
	}
    return bFind;
}

template<typename RegT>
bool VectorRegister<RegT>::RegListener(RegT *pRegT) 
{
	bool bFind = false;
	TVectorRegContainer::iterator iter = m_vectorRegContainer.begin();
	while (iter != m_vectorRegContainer.end())
	{
		if ((*iter) == pRegT)
		{
			bFind = true;
			break;
		}
		else
		{
			++iter;
		}
	}
	if (!bFind)
	{
		m_vectorRegContainer.push_back(pRegT);
	}
	return bFind;
}

#endif // __REGISTER_TEMPLATE_H__