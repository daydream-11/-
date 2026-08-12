#ifndef __OBJECT_LIST_H__
#define __OBJECT_LIST_H__

#include "BaseType.h"

template <typename T>
class ObjectList
{
private:
	typedef T* PointerT;
public:
	ObjectList();
	~ObjectList();

public:
	BOOL Init(UINT uSize);	//初始化,设定对象池大小和是否多线程
	UINT GetSize();

public:	
	// 得到一个对象
	T* GetNewT();
	//收回一个对象
	void RemoveT(T *pT);
private:
	void Clear();
private:
	T* m_pObjectPool;
	T* m_pHead;
	T* m_pTail;
	UINT m_uSize;
private:
	MyLock m_Lock;
};

template <typename T>
ObjectList<T>::ObjectList()
{
	m_pObjectPool = NULL;
	m_pHead = NULL;
	m_pTail = NULL;
	m_uSize = 0;
}

template <typename T>
ObjectList<T>::~ObjectList()
{
	Clear();
}

template <typename T>
BOOL ObjectList<T>::Init(UINT uSize)	//初始化,设定对象池大小和是否多线程
{
	Clear();
	if (uSize < 1)
	{
		return FALSE;
	}

	m_pObjectPool = new T[uSize];

	if (m_pObjectPool == NULL)
	{
		return FALSE;
	}
	m_uSize = uSize;
	T *pTempT = NULL;
	for (INT i = 0; i < m_uSize; i++)
	{
		if (NULL == m_pHead)
		{
			m_pHead = &(m_pObjectPool[i]);
			pTempT = m_pHead;
		}
		else
		{
			pTempT->pNext = &(m_pObjectPool[i]);
			pTempT = pTempT->pNext;
		}
	}

	m_pTail = pTempT;

	m_pTail->pNext = NULL;

}

// 得到一个对象
template <typename T>
T* ObjectList<T>::GetNewT()
{
	AutoLockT myAutoLockT(m_Lock);
	if ( m_pHead == m_pTail )
	{
		return NULL;
	}

	T *pTempT = m_pHead;

	m_pHead = m_pHead->pNext;

	return pTempT;

}

//收回一个对象
template <typename T>
void ObjectList<T>::RemoveT(T *pT)
{
	AutoLockT myAutoLockT(m_Lock);
	pT->pNext = NULL;
	m_pTail->pNext = pT;
	m_pTail = m_pTail->pNext;
}

template <typename T>
void ObjectList<T>::Clear()
{
	if (m_pObjectPool != NULL)
	{
		delete[] m_pObjectPool;
		m_pObjectPool = NULL;
	}

	m_pHead = NULL;
	m_pTail = NULL;
	m_uSize = 0;
}

#endif  //__OBJECT_LIST_H__