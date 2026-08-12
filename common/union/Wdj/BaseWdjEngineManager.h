#ifndef __BASE_WDJ_ENGINE_MANAGER_H__
#define __BASE_WDJ_ENGINE_MANAGER_H__

#include "DLL.h"

class CBaseWdjEngineManager : public CDllClass
{
public:
	virtual ~CBaseWdjEngineManager(){}
public:
	// ³õÊ¼»¯
	virtual BOOL Init(const TCHAR * lpszCmdLine, HWND hMainWnd) = 0;
	// ÍË³ö
	virtual BOOL Exit() = 0;
};

#endif	// __BASE_WDJ_ENGINE_MANAGER_H__
