#ifndef __BASE_PUSH_SYSTEM_MANAGER_H__
#define __BASE_PUSH_SYSTEM_MANAGER_H__

#include "DLL.h"

class CBasePushSystemManager : public CDllClass
{
public:
	virtual void Init(const TCHAR * lpszCmdLine, HWND hMainWnd) = 0;
	// 
	virtual void DoRunLoadDataEngineDll(const TCHAR *lpszDataEngineDll) = 0;
};

#endif	// __BASE_ADV_SYSTEM_MANAGER_H__
