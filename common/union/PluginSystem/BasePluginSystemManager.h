#ifndef __BASE_PLUGIN_SYSTEM_MANAGER_H__
#define __BASE_PLUGIN_SYSTEM_MANAGER_H__

#include "DLL.h"

class CBasePluginSystemManager : public CDllClass
{
public:
	virtual void Init(const TCHAR * lpszCmdLine) = 0;
	// ÍË³ö
	virtual void Exit() = 0;
};

#endif	// __BASE_PLUGIN_SYSTEM_MANAGER_H__
