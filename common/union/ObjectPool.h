#ifndef __OBJECT_POOL_H__
#define __OBJECT_POOL_H__

#include "BaseType.h"

template <typename T>
class ObjectPool
{
private:
	typedef T* PointerT;
	typedef vector<PointerT> TVectorPointerT;
	typedef typename TVectorPointerT::iterator TVectorPointerTIterator;
public:
	ObjectPool();
	~ObjectPool();
public:
	BOOL Init(UINT uSize);	//初始化,设定对象池大小和是否多线程
	UINT GetSize();
	UINT GetNoUseSize();

public:	
	// 得到一个对象
	T* GetNewT();
	//收回一个对象
	void RemoveT(T *pT);
	// 按索引得到一个对象
	T* GetIndex(UINT uIndex);
private:
	void Clear();
private:
	UINT m_uAllSize;
	TVectorPointerT m_vectorPointerT;
	PointerT *m_pNoUsePool;
	UINT m_uNoUseSize;
	// 单个大小
	UINT m_uSingleSize;
private:
	MyLock m_Lock;
};

template <typename T>
ObjectPool<T>::ObjectPool()
{
	m_pNoUsePool = NULL;
	m_uAllSize = 0;
	m_uNoUseSize = 0;
	m_uSingleSize = 0;
}

template <typename T>
ObjectPool<T>::~ObjectPool()
{
	Clear();
}

template <typename T>
BOOL ObjectPool<T>::Init(UINT uSize)
{
	Clear();
	if (uSize < 1)
	{
		return FALSE;
	}
	m_uSingleSize = uSize;
	m_uAllSize = uSize;
	T *pTArray = new T[uSize];
	m_vectorPointerT.push_back(pTArray);
	m_pNoUsePool = new PointerT[uSize];
	if ((pTArray == NULL) || (m_pNoUsePool == NULL))
	{
		return FALSE;
	}
	m_uNoUseSize = uSize;
	for(UINT i = 0; i < uSize; i++)
	{
		T *pT = &(pTArray[i]);
		pT->Init(i);
		m_pNoUsePool[i] = pT;
	}
	return TRUE;
}

template <typename T>
void ObjectPool<T>::Clear()
{
	for (TVectorPointerTIterator iter = m_vectorPointerT.begin(); iter != m_vectorPointerT.end(); iter++)
	{
		PointerT pPointerT = *iter;
		delete[] pPointerT;
		pPointerT = NULL;
	}
	if (m_pNoUsePool != NULL)
	{
		delete[] m_pNoUsePool;
		m_pNoUsePool = NULL;
	}
	m_uAllSize = 0;
	m_uNoUseSize = 0;
}

template <typename T>
T* ObjectPool<T>::GetNewT()
{
	AutoLockT myAutoLockT(m_Lock);
	T* pT = NULL;
	if (m_uNoUseSize == 0)
	{
		UINT uStartIndex = m_uAllSize;
		m_uAllSize += m_uSingleSize;
		T *pTArray = new T[m_uSingleSize];
		m_vectorPointerT.push_back(pTArray);
		PointerT *pTempPointerT = new PointerT[m_uAllSize];
		memset(pTempPointerT, 0, sizeof(PointerT) * m_uAllSize);
		for(UINT i = 0; i < m_uSingleSize; i++)
		{
			pT = &(pTArray[i]);
			pT->Init(uStartIndex + i);
			pTempPointerT[i] = pT;
		}
		delete[] m_pNoUsePool;
		m_pNoUsePool = pTempPointerT;
		m_uNoUseSize = m_uSingleSize;
		pT = m_pNoUsePool[m_uNoUseSize - 1];
		m_pNoUsePool[m_uNoUseSize - 1] = NULL;
		m_uNoUseSize--;
		return pT;
	}
	pT = m_pNoUsePool[m_uNoUseSize - 1];
	m_pNoUsePool[m_uNoUseSize - 1] = NULL;
	m_uNoUseSize--;
	//
	return pT;
}

template <typename T>
void ObjectPool<T>::RemoveT(T *pT)
{
	AutoLockT myAutoLockT(m_Lock);
	if (m_uNoUseSize >= m_uAllSize)
	{
		return;
	}
	m_pNoUsePool[m_uNoUseSize] = pT;
	m_uNoUseSize++;
}

template <typename T>
T* ObjectPool<T>::GetIndex(UINT uIndex)
{
	AutoLockT myAutoLockT(m_Lock);
	if (m_uAllSize <= uIndex)
	{
		return NULL;
	}
	UINT uVectorPostion = uIndex / m_uSingleSize;
	T* pTArray = m_vectorPointerT.at(uVectorPostion);
	UINT uTempIndex = uIndex - (uVectorPostion * m_uSingleSize);
	return &(pTArray[uTempIndex]);
}

template <typename T>
UINT ObjectPool<T>::GetSize(void)
{
	return m_uAllSize;
}

template <typename T>
UINT ObjectPool<T>::GetNoUseSize()
{
	return m_uNoUseSize;
}

#endif // __OBJECT_POOL_H__