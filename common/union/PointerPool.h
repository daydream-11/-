#ifndef __POINTER_POOL_H__
#define __POINTER_POOL_H__

#include "BaseType.h"

template <typename T>
class PointerPool
{
public:
	PointerPool();
	~PointerPool();
public:

	// 初始化,设定对象池大小和是否多线程
	BOOL Init(UINT uSize);
	UINT GetSize();
	UINT GetNoUseSize();

public:	
	// 得到一个对象
	T GetNewT();
	//收回一个对象
	VOID RemoveT(T myT);
	// 按索引得到一个对象
	T GetIndex(UINT uIndex);
	// 按索引得到一个对象
	VOID InitValue(UINT uIndex, T myT);
private:
	void Clear();
private:
	// 对象池大小
	UINT m_uSize;
	T *m_pPointerPool;
	T *m_pNoUsePool;
	UINT m_uNoUseSize;
private:
	MyLock m_Lock;
};

template <typename T>
PointerPool<T>::PointerPool()
{
	m_pPointerPool = NULL;
	m_pNoUsePool = NULL;
	m_uSize = 0;
	m_uNoUseSize = 0;
}

template <typename T>
PointerPool<T>::~PointerPool()
{
	Clear();
}

template <typename T>
BOOL PointerPool<T>::Init(UINT uSize)
{
	Clear();
	if (uSize < 1)
	{
		return FALSE;
	}
	m_pPointerPool = new T[uSize];
	m_pNoUsePool = new T[uSize];

	if ((m_pPointerPool == NULL) || (m_pNoUsePool == NULL))
	{
		return FALSE;
	}
	m_uSize = uSize;
	m_uNoUseSize = uSize;
	return TRUE;
}

template <typename T>
void PointerPool<T>::Clear()
{
	if (m_pPointerPool != NULL)
	{
		delete[] m_pPointerPool;
		m_pPointerPool = NULL;
	}
	if (m_pNoUsePool != NULL)
	{
		delete[] m_pNoUsePool;
		m_pNoUsePool = NULL;
	}
	m_uSize = 0;
	m_uNoUseSize = 0;
}

template <typename T>
T PointerPool<T>::GetNewT()
{
	AutoLockT myAutoLockT(m_Lock);
	if (m_uNoUseSize == 0)
	{
		return NULL;
	}
	T myT = m_pNoUsePool[m_uNoUseSize - 1];
	m_pNoUsePool[m_uNoUseSize - 1] = NULL;
	m_uNoUseSize--;
	//
	return myT;
}

template <typename T>
void PointerPool<T>::RemoveT(T myT)
{
	AutoLockT myAutoLockT(m_Lock);
	if (m_uNoUseSize >= m_uSize)
	{
		return;
	}
	m_pNoUsePool[m_uNoUseSize] = myT;
	m_uNoUseSize++;
}

template <typename T>
T PointerPool<T>::GetIndex(UINT uIndex)
{
	AutoLockT myAutoLockT(m_Lock);
	if (m_uSize <= uIndex)
	{
		return NULL;
	}
	return m_pPointerPool[uIndex];
}

template <typename T>
VOID PointerPool<T>::InitValue(UINT uIndex, T myT)
{
	AutoLockT myAutoLockT(m_Lock);
	if (m_uSize <= uIndex)
	{
		return;
	}
	m_pPointerPool[uIndex] = myT;
	m_pNoUsePool[uIndex] = myT;
}

template <typename T>
UINT PointerPool<T>::GetSize(void)
{
	return m_uSize;
}

template <typename T>
UINT PointerPool<T>::GetNoUseSize()
{
	return m_uNoUseSize;
}


#endif // __POINTER_POOL_H__