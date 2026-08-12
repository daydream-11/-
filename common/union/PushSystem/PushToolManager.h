#ifndef __PUSH_TOOL_MANAGER_H__
#define __PUSH_TOOL_MANAGER_H__


class CPushToolManager
{
private:

public:
	CPushToolManager(void);
	~CPushToolManager(void);

public:
	// ³õÊ¼»¯
	virtual void Init(const TCHAR * lpszCmdLine, HWND hMainWnd);
	// ÍË³ö
	virtual void Exit();
};

#endif	// __PUSH_SYSTEM_MANAGER_H__
