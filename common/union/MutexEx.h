#ifndef __METEXEX_H__
#define __METEXEX_H__

class CMutexEx
{
private:
	HANDLE	m_hMutex;
	BOOL m_IsMutex;
public:
	CMutexEx();
	CMutexEx(const TCHAR * szMutexName);
	~CMutexEx(void);
public:
	// 创建互斥对象
	VOID Create(const TCHAR *lpszMutexName);
	// 是否存在互斥
	BOOL IsMutex();
};

#endif	// __METEXEX_H__
