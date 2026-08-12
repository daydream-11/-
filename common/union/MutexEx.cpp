#include "framework.h"
#include "MutexEx.h"

//构造互斥对象
CMutexEx::CMutexEx()
: m_hMutex(NULL)
, m_IsMutex(FALSE)
{

}

// 构造互斥对象
CMutexEx::CMutexEx(const TCHAR * szMutexName)
{
	m_hMutex = CreateMutex(0, TRUE, szMutexName);
	m_IsMutex = (GetLastError() != ERROR_ALREADY_EXISTS);
}


//释放互斥对象
CMutexEx::~CMutexEx(void)
{
	if (m_hMutex != NULL)
	{
		ReleaseMutex(m_hMutex);
		CloseHandle(m_hMutex);
	}
}


// 创建互斥对象
VOID CMutexEx::Create(const TCHAR *lpszMutexName)
{
	m_hMutex = CreateMutex(0, TRUE, lpszMutexName);
	m_IsMutex = (GetLastError() != ERROR_ALREADY_EXISTS);
}

//判断互斥
BOOL CMutexEx::IsMutex()
{
	return m_IsMutex;
}