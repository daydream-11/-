#include "StdAfx.h"
#include "UserActionsCount.h"

CUserActionsCount::CUserActionsCount(void)
{
	memset(m_strCfgFileName, 0, MAX_PATH);
}

CUserActionsCount::~CUserActionsCount(void)
{
}

void CUserActionsCount::AddUserActionsCount( User_Action action )
{
	
	if ((Status_Actions_Begin < action) && (action < Status_Actions_End))
	{
		AddStatusActionsConfig(action);
	}
}

BOOL CUserActionsCount::Init()
{
	_stprintf(m_strCfgFileName, _T("%sConfig\\UseActions.ini"), g_pGlobals->GetConfigure()->GetCfgRootPath());
	return TRUE;
}

void CUserActionsCount::AddStatusActionsConfig( User_Action action )
{
	TCHAR szAppName[MAX_PATH] = _T("StatusActions");
	TCHAR szKeyName[MAX_PATH] = _T("");
	switch(action)
	{
	case Status_Actions_Mouse_Cn_En_Switch:
		{
			_stprintf(szKeyName, _T("%s"), _T("Mouse_Cn_En_Switch"));
			break;
		}
	case Status_Actions_Key_Cn_En_Switch:
		{
			_stprintf(szKeyName, _T("%s"), _T("Key_Cn_En_Switch"));
			break;
		}
	case Status_Actions_Mouse_Biao_Dian_Switch:
		{
			_stprintf(szKeyName, _T("%s"), _T("Mouse_Biao_Dian_Switch"));
			break;
		}
	case Status_Actions_Key_Biao_Dian_Switch:
		{
			_stprintf(szKeyName, _T("%s"), _T("Key_Biao_Dian_Switch"));
			break;
		}
	case Status_Actions_Mouse_Quan_Jiao_Switch:
		{
			_stprintf(szKeyName, _T("%s"), _T("Mouse_Quan_Jiao_Switch"));
			break;
		}
	case Status_Actions_Key_Quan_Jiao_Switch:
		{
			_stprintf(szKeyName, _T("%s"), _T("Key_Quan_Jiao_Switch"));
			break;
		}
	case Status_Actions_Mouse_Jian_Fan_Switch:
		{
			_stprintf(szKeyName, _T("%s"), _T("Mouse_Jian_Fan_Switch"));
			break;
		}
	case Status_Actions_Key_Jian_Fan_Switch:
		{
			_stprintf(szKeyName, _T("%s"), _T("Key_Jian_Fan_Switch"));
			break;
		}
	case Status_Actions_Mouse_SoftKeyBoard:
		{
			_stprintf(szKeyName, _T("%s"), _T("Mouse_SoftKeyBoard"));
			break;
		}
	case Status_Actions_Key_SoftKeyBoard:
		{
			_stprintf(szKeyName, _T("%s"), _T("Key_SoftKeyBoard"));
			break;
		}
	}
	AddActionsConfig(szAppName, szKeyName);
}

void CUserActionsCount::AddActionsConfig( const TCHAR* szAppName, const TCHAR* szKeyName )
{
	int count = GetPrivateProfileInt(szAppName, szKeyName, 0, m_strCfgFileName);
	count++;
	TCHAR szMsg[MAX_PATH] = {'\0'};
	_stprintf(szMsg, _T("%d"), count);
	WritePrivateProfileString(szAppName, szKeyName, szMsg, m_strCfgFileName);
}
