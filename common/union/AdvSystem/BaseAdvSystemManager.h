#ifndef __BASE_ADV_SYSTEM_MANAGER_H__
#define __BASE_ADV_SYSTEM_MANAGER_H__

#include "DLL.h"

class CBaseAdvSystemManager : public CDllClass
{
public:
	virtual VOID Init(const TCHAR * lpszCmdLine, HWND hMainWnd) = 0;
};

#endif	// __BASE_ADV_SYSTEM_MANAGER_H__
