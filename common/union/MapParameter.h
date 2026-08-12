#ifndef __MAP_PARAMETER_H__
#define __MAP_PARAMETER_H__

#include <map>
using namespace std;

template <typename Key, typename Value>
class MapParameter
{
public:

	typedef map<Key, Value> TMapParameter;
	typedef typename TMapParameter::iterator TMapIterator;
	typedef typename TMapParameter::value_type TMapValueType;
	TMapParameter *m_pMapParameter;

public:

	MapParameter();
	
	~MapParameter();

public:

	virtual bool AppendParameter(const Key & myKey, const Value & myValue);
	virtual bool ModifyParameter(const Key & myKey, const Value & myValue);
	virtual VOID SettingParameter(const Key & myKey, const Value & myValue);
    virtual bool DeleteParameter(const Key & myKey);
    virtual bool IsExistParameter(const Key & myKey);
    virtual bool DeleteAllParameter();
    virtual const Value GetParameterValue(const Key & strParamName);
    virtual const Value* GetParameterPointer(const Key & strParamName);
	virtual const Value* operator[](const Key & _strParamName);
	virtual int GetParameterCount();

};


template <typename Key, typename Value>
MapParameter<Key, Value>::MapParameter()
{
	m_pMapParameter = new TMapParameter();
}

template <typename Key, typename Value>
MapParameter<Key, Value>::~MapParameter()
{
	if (m_pMapParameter != NULL)
	{
		TMapIterator iter;
		for (iter = m_pMapParameter->begin(); iter != m_pMapParameter->end();)
		{
			TMapIterator currentIter = iter;
			TMapIterator nextIter = ++iter;
			m_pMapParameter->erase(currentIter);
			iter = nextIter;
		}
		delete m_pMapParameter;
		m_pMapParameter = NULL;
	}

}

template <typename Key, typename Value>
bool MapParameter<Key, Value>::AppendParameter(const Key & myKey, const Value & myValue)
{
	TMapIterator iter = m_pMapParameter->find(myKey); 
	if (iter != m_pMapParameter->end())
	{
		// 参数已经存在
		return false;
	}
	m_pMapParameter->insert(TMapValueType(myKey, myValue));
	return true;
}

template <typename Key, typename Value>
bool MapParameter<Key, Value>::ModifyParameter(const Key & myKey, const Value & myValue)
{
	TMapIterator iter = m_pMapParameter->find(myKey);
	if (iter != m_pMapParameter->end())
	{
		// 有此参数存在
		iter->second = myValue;
		return true;
	}
	return false;
}

template <typename Key, typename Value>
void MapParameter<Key, Value>::SettingParameter(const Key & myKey, const Value & myValue)
{
	TMapIterator iter = m_pMapParameter->find(myKey);
	if (iter != m_pMapParameter->end())
	{
		// 有此参数存在
		iter->second = myValue;
		return;
	}
	m_pMapParameter->insert(TMapValueType(myKey, myValue));
}

template <typename Key, typename Value>
bool MapParameter<Key, Value>::DeleteParameter(const Key & myKey)
{
	TMapIterator iter = m_pMapParameter->find(myKey);
	if (iter != m_pMapParameter->end())
	{
		// 有此参数存在
		m_pMapParameter->erase(iter);
	}
	return false;
}

template <typename Key, typename Value>
bool MapParameter<Key, Value>::IsExistParameter(const Key & myKey)
{
	TMapIterator iter = m_pMapParameter->find(myKey);
	if (iter != m_pMapParameter->end())
	{
		// 有此参数存在
		return true;
	}
	return false;
}

template <typename Key, typename Value>
bool MapParameter<Key, Value>::DeleteAllParameter()
{
	m_pMapParameter->clear();
	return true;
}

template <typename Key, typename Value>
const Value MapParameter<Key, Value>::GetParameterValue(const Key & strParamName)
{
	TMapIterator iter = m_pMapParameter->find(strParamName);
	if (iter != m_pMapParameter->end())
	{
		return iter->second;
	}
	return NULL;
}

template <typename Key, typename Value>
const Value* MapParameter<Key, Value>::GetParameterPointer(const Key & strParamName)
{
	Value * pT = NULL;
	TMapIterator iter = m_pMapParameter->find(strParamName);
	if (iter != m_pMapParameter->end())
	{
		pT = &iter->second;
		return pT;
	}
	return NULL;
}

template <typename Key, typename Value>
const Value* MapParameter<Key, Value>::operator[](const Key & strParamName)
{
	Value * pT = NULL;
	TMapIterator iter = m_pMapParameter->find(strParamName);
	if (iter != m_pMapParameter->end())
	{
		pT = &iter->second;
		return pT;
	}
	return NULL;
}

template <typename Key, typename Value>
int MapParameter<Key, Value>::GetParameterCount()
{
	return (int)m_pMapParameter->size();
}


#endif	//__MAP_PARAMETER_H__