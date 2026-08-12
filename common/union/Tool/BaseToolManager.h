#ifndef __BASE_TOOL_MANAGER_H__
#define __BASE_TOOL_MANAGER_H__

#include "DLL.h"

class CBaseToolManager : public CDllClass
{
public:
	// 打开迷你窗口
	virtual VOID OpenMiNiExe() = 0;
	// 卸载服务
	virtual VOID UnInstallTool() = 0;
	// 开始运行服务
	virtual VOID StartTool() = 0;
};

#endif	// __BASE_TOOL_MANAGER_H__


