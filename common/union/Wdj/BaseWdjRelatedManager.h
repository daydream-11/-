#ifndef __BASE_WDJ_ENGINE_MANAGER_H__
#define __BASE_WDJ_ENGINE_MANAGER_H__

#include "DLL.h"

class CBaseWdjRelatedManager : public CDllClass
{
public:
	// ≥ı ºªØ
	virtual BOOL Init(const TCHAR * lpszCmdLine, HWND hMainWnd) = 0;
};

#endif	// __BASE_WDJ_ENGINE_MANAGER_H__
