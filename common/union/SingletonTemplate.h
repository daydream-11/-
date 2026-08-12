#ifndef __SINGLETON_TEMPLATE_H__
#define __SINGLETON_TEMPLATE_H__

template <typename T>
class CiaSingleton : public T
{
public:
	typedef T SingletonType;

public:
	// 获取单例
	static CiaSingleton* Singleton();
	// 释放单例
	static void Release();

private:
	// 单例实体指针
	static CiaSingleton *m_pSingleInstance;

private:
	// 此类不可继承，不可实例化
	CiaSingleton(){}
	~CiaSingleton(){}
};

template <typename T>
class ChaSingleton
{
public:
	typedef T SingletonType;
public:
	// 获取单例
	static SingletonType *Singleton();
	// 释放单例
	static void Release();

private:
	// 单例实体指针
	static SingletonType *m_pSingleInstance;

private:
	// 此类不可继承，不可实例化
	ChaSingleton() {}
	~ChaSingleton() {}	
};

// 类CiaSingleInstance的定义

template<typename T>
CiaSingleton<T>* CiaSingleton<T>::m_pSingleInstance = nullptr;

template<typename T>
CiaSingleton<T>* CiaSingleton<T>::Singleton() 
{
	if (m_pSingleInstance == NULL)
	{
		m_pSingleInstance = new CiaSingleton<T>();
	}
	return m_pSingleInstance;
}

template <typename T>
void CiaSingleton<T>::Release()
{
	delete m_pSingleInstance;
	m_pSingleInstance = nullptr;
}


template<typename T>
typename ChaSingleton<T>::SingletonType* ChaSingleton<T>::m_pSingleInstance = NULL;

template <typename T>
typename ChaSingleton<T>::SingletonType* ChaSingleton<T>::Singleton()
{
	if (m_pSingleInstance == NULL) 
	{
		m_pSingleInstance = new SingletonType();
	}
	return m_pSingleInstance;
}

template <typename T>
void ChaSingleton<T>::Release() 
{
	delete m_pSingleInstance;
	m_pSingleInstance = NULL;
}

#endif	// __SINGLETON_TEMPLATE_H__
