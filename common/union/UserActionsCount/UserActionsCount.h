#pragma once


enum User_Action
{
	Status_Actions_Begin = 0,								//状态栏相关操作开始

	Status_Actions_Mouse_Cn_En_Switch,						//鼠标点击中英文切换
	Status_Actions_Key_Cn_En_Switch,						//快捷键中英文切换
	Status_Actions_Mouse_Biao_Dian_Switch,					//鼠标点击标点切换
	Status_Actions_Key_Biao_Dian_Switch,					//快捷键标点切换
	Status_Actions_Mouse_Quan_Jiao_Switch,					//鼠标点击半全角切换
	Status_Actions_Key_Quan_Jiao_Switch,					//快捷键半全角切换
	Status_Actions_Mouse_Jian_Fan_Switch,					//鼠标点击简繁体切换
	Status_Actions_Key_Jian_Fan_Switch,						//快捷键简繁体切换
	Status_Actions_Mouse_SoftKeyBoard,						//鼠标点击软键盘弹出
	Status_Actions_Key_SoftKeyBoard,						//快捷键软键盘弹出

	Status_Actions_End,										//状态栏相关操作结束

};

class CUserActionsCount
{
public:
	CUserActionsCount(void);
public:
	~CUserActionsCount(void);

public:
	BOOL Init();

	void AddUserActionsCount(User_Action action);

private:
	void AddStatusActionsConfig(User_Action action);

	void AddActionsConfig(const TCHAR* szAppName, const TCHAR* szKeyName);
private:
	// 保存用户操作行为的统计相关文件
	TCHAR m_strCfgFileName[MAX_PATH];
};
