#include "StdAfx.h"
#include "BaseGlobals.h"
#if defined (__DB_SYSTEM__)
#include "DBSystemManager.h"
#endif

CBaseGlobals::CBaseGlobals(void)
{
	m_hInstance = NULL;
	m_pFunction = NULL;
	m_pConfigure = NULL;
	m_pCommonVariable = NULL;
#if defined (__UI_SYSTEM__)
	m_pUIApp = NULL;
	m_pUIImeProc = NULL;
#endif

#if defined (__KB_SYSTEM__)
	m_pKBInterface = NULL;
#endif

#if defined (__FN_SYSTEM__)
	m_pFNInterface = NULL;
#endif

#if defined (__GS_USER_COUNT__)
	m_pUserActionsCount = NULL;
#endif

}


CBaseGlobals::~CBaseGlobals(void)
{
	Exit();
}

/** @name 公共成员函数 *///////////////////////////////////////////////////
/// @{

/**********************************************************************
* 函数名称： Init
* 功能描述： 
* 输入参数： 
* 输出参数：
* 返 回 值： 执行成功，返回true；执行失败，返回false
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/03/16		V1.0	    huanggenping	创建版本
***********************************************************************/
BOOL CBaseGlobals::Init(HINSTANCE hInstance)
{
	BOOL bReturn = FALSE;
	//
	m_hInstance = hInstance;
	//
	return TRUE;
}

/**********************************************************************
* 函数名称： NewObject
* 功能描述： 
* 输入参数： 
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/03/17		V1.0	    huanggenping	创建版本
***********************************************************************/
BOOL CBaseGlobals::NewObject(void)
{
#if defined (__UI_SYSTEM__)
	//
	m_pUIImeProc = new CUIImeProc();
	if (m_pUIImeProc == NULL)
	{
		return FALSE;
	}
#endif
	//
	m_pFunction = new CFunction();
	if (m_pFunction == NULL)
	{
		return FALSE;
	}
	// 
	m_pConfigure = new CConfigure();
	if (m_pConfigure == NULL)
	{
		return FALSE;
	}
	//
	m_pCommonVariable = new CCommonVariable();
	if (m_pCommonVariable == NULL)
	{
		return FALSE;
	}
#if defined (__UI_SYSTEM__)
	//
	g_pSkinStyle = new CSkinStyle();
	if (g_pSkinStyle == NULL)
	{
		return FALSE;
	}
	//
	g_pSkinData = new CSkinData();
	if (g_pSkinData == NULL)
	{
		return FALSE;
	}
	//
	m_pUIApp = new CUIApp();
	if (m_pUIApp == NULL)
	{
		return FALSE;
	}
#endif
#if defined (__DB_SYSTEM__)
	//
/*	m_pDBInterface = new CDBInterface();
	if (m_pDBInterface == NULL)
	{
		return FALSE;
	}*/
#endif
#if defined (__KB_SYSTEM__)
	//
	m_pKBInterface = new CKBInterface();
	if (m_pKBInterface == NULL)
	{
		return FALSE;
	}
#endif

#if defined (__FN_SYSTEM__)
	//
	m_pFNInterface = new CFNInterface();
	if (m_pFNInterface == NULL)
	{
		return FALSE;
	}
#endif

#if defined (__GS_USER_COUNT__)
	m_pUserActionsCount = new CUserActionsCount();
	if (m_pUserActionsCount == NULL)
	{
		return FALSE;
	}
#endif

	return TRUE;
}

/**********************************************************************
* 函数名称： ExitGlobals
* 功能描述： 
* 输入参数： 
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/03/17		V1.0	    huanggenping	创建版本
***********************************************************************/
BOOL CBaseGlobals::InitObject(void)
{
	BOOL bReturn = FALSE;
#if defined (__UI_SYSTEM__)
	bReturn =m_pUIImeProc->Init();
	if (!bReturn)
	{
		return FALSE;
	}
#endif
	//
	bReturn = m_pConfigure->Init();
	if (!bReturn)
	{
		return FALSE;
	}
	//
	bReturn = m_pCommonVariable->Init();
	if (!bReturn)
	{
		return FALSE;
	}
	//
#if defined (__IME_SYSTEM__)

	m_pCommonVariable->Load(FALSE);

#elif defined (__CONFIG_SYSTEM__)

	m_pCommonVariable->Load(TRUE);

#elif defined (__SKINEDITOR_SYSTEM__)
	//
	g_pSkinStyle->m_bTempDrawUI = TRUE;
	//
	m_pCommonVariable->Load(TRUE);

#elif defined (__WIZARD_SYSTEM__)

	m_pCommonVariable->Load(FALSE);

#elif defined (__MB_MANAGER_SYSTEM__)

	m_pCommonVariable->Load(FALSE);

#elif defined (__USERPAGE_SYSTEM__)

	m_pCommonVariable->Load(FALSE);

#elif defined (__MAIN_EXE_DEFINE_H__)

	m_pCommonVariable->Load(FALSE);
	
#endif


#if defined (__UI_SYSTEM__)
	//
	bReturn = g_pSkinData->Init();
	if (!bReturn)
	{
		return FALSE;
	}
	//
	bReturn = g_pSkinStyle->Init();
	if (!bReturn)
	{
		return FALSE;
	}
	bReturn = m_pUIApp->Init();
	if (!bReturn)
	{
		return FALSE;
	}
#endif

#if defined (__DB_SYSTEM__)
	TCHAR szSysMBPath[MAX_PATH] = {'\0'};
	_stprintf(szSysMBPath, _T("%s%s\\"), m_pConfigure->GetInstallPath(), SYSTEM_MB_PATH);
	CDBSystemManagerInstance::Singleton()->Init();
	CDBSystemManagerInstance::Singleton()->Load(
		m_hInstance
		, m_pConfigure->GetInstallPath()
		, szSysMBPath
		, m_pConfigure->GetCfgRootPath()
		, m_pConfigure->GetCfgUserPath()
		);
	if (m_pCommonVariable->GetShareParameterValue(IS_USE_PIN_YIN_ERROR_RECOVERY))
	{
		CDBSystemManagerInstance::Singleton()->SetPYErrorRecoveryConfig
			(
				m_pCommonVariable->GetShareParameterValue(IS_USE_ERROR_RECOVERY_MG_TO_NG),
				m_pCommonVariable->GetShareParameterValue(IS_USE_ERROR_RECOVERY_GN_TO_NG),
				m_pCommonVariable->GetShareParameterValue(IS_USE_ERROR_RECOVERY_IOU_TO_IU),
				m_pCommonVariable->GetShareParameterValue(IS_USE_ERROR_RECOVERY_UEI_TO_UI),
				m_pCommonVariable->GetShareParameterValue(IS_USE_ERROR_RECOVERY_UEN_TO_UN)
			);
	}
	else
	{
		CDBSystemManagerInstance::Singleton()->SetPYErrorRecoveryConfig
			(
				FALSE,
				FALSE,
				FALSE,
				FALSE,
				FALSE
			);
	}
#endif

#if defined (__KB_SYSTEM__)
	bReturn = m_pKBInterface->Init();
	if (!bReturn)
	{
		return FALSE;
	}
#endif

#if defined (__FN_SYSTEM__)
	bReturn = m_pFNInterface->Init();
	if (!bReturn)
	{
		return FALSE;
	}
#endif

#if defined (__GS_USER_COUNT__)
	bReturn = m_pUserActionsCount->Init();
	if (!bReturn)
	{
		return FALSE;
	}
#endif
	return TRUE;
}

/**********************************************************************
* 函数名称： ExitGlobals
* 功能描述： 
* 输入参数： 
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/03/17		V1.0	    huanggenping	创建版本
***********************************************************************/
BOOL CBaseGlobals::Exit(void)
{
#if defined (__UI_SYSTEM__)
	SAFE_DELETE(m_pUIApp);
#endif
#if defined (__UI_SYSTEM__)
	SAFE_DELETE(m_pUIImeProc);
#endif
#if defined (__DB_SYSTEM__)
	CDBSystemManagerInstance::Release();
#endif
#if defined (__KB_SYSTEM__)
	SAFE_DELETE(m_pKBInterface);
#endif
#if defined (__FN_SYSTEM__)
	SAFE_DELETE(m_pFNInterface);
#endif

#if defined (__UI_SYSTEM__)
	SAFE_DELETE(g_pSkinData);
	SAFE_DELETE(g_pSkinStyle);
#endif

#if defined (__GS_USER_COUNT__)
	SAFE_DELETE(m_pUserActionsCount);
#endif

	SAFE_DELETE(m_pCommonVariable);
	SAFE_DELETE(m_pFunction);
	SAFE_DELETE(m_pConfigure);
	return TRUE;
}


/**********************************************************************
* 函数名称： GetInstance
* 功能描述： 用于获取程序的句柄
* 输入参数： 
* 输出参数：
* 返 回 值： 执行成功，返回true；执行失败，返回false
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/03/16		V1.0	    huanggenping	创建版本
***********************************************************************/
HINSTANCE CBaseGlobals::GetInstance(void)
{
	return m_hInstance;
}

/**********************************************************************
* 函数名称： GetConfigure
* 功能描述： 
* 输入参数： 
* 输出参数：
* 返 回 值： 返回CConfigure的指针
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/05/06		V1.0	    huanggenping	创建版本
***********************************************************************/
CConfigure* CBaseGlobals::GetConfigure(void)
{
	if (m_pConfigure == NULL)
	{
		return NULL;
	}
	return m_pConfigure;
}

/**********************************************************************
* 函数名称： GetFunction
* 功能描述： 
* 输入参数： 
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/03/26		V1.0	    huanggenping	创建版本
***********************************************************************/
CFunction* CBaseGlobals::GetFunction(void)
{
	if (m_pFunction == NULL)
	{
		return NULL;
	}
	return m_pFunction;
}


#if defined (__UI_SYSTEM__)

/**********************************************************************
* 函数名称： GetUIApp
* 功能描述： 
* 输入参数： 
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/03/26		V1.0	    huanggenping	创建版本
***********************************************************************/
CUIApp* CBaseGlobals::GetUIApp(void)
{
	if (m_pUIApp == NULL)
	{
		return NULL;
	}
	return m_pUIApp;
}

#endif

/**********************************************************************
* 函数名称： GetCommonVariable
* 功能描述： 
* 输入参数： 
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/03/26		V1.0	    huanggenping	创建版本
***********************************************************************/
CCommonVariable* CBaseGlobals::GetCommonVariable(void)
{
	if (m_pCommonVariable == NULL)
	{
		return NULL;
	}
	return m_pCommonVariable;
}

#if defined (__UI_SYSTEM__)

/**********************************************************************
* 函数名称： GetUIImeProc
* 功能描述： 
* 输入参数： 
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/03/26		V1.0	    huanggenping	创建版本
***********************************************************************/
CUIImeProc* CBaseGlobals::GetUIImeProc(void)
{
	if (m_pUIImeProc == NULL)
	{
		return NULL;
	}
	return m_pUIImeProc;
}

#endif

#if defined (__DB_SYSTEM__)

/**********************************************************************
* 函数名称： GetDBInterface
* 功能描述： 
* 输入参数： 
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/03/26		V1.0	    huanggenping	创建版本
***********************************************************************/
/*CDBInterface* CBaseGlobals::GetDBInterface(void)
{
	if (m_pDBInterface == NULL)
	{
		return NULL;
	}
	return m_pDBInterface;
}*/

#endif

#if defined (__KB_SYSTEM__)

/**********************************************************************
* 函数名称： GetKBInterface
* 功能描述： 
* 输入参数： 
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/03/26		V1.0	    huanggenping	创建版本
***********************************************************************/
CKBInterface* CBaseGlobals::GetKBInterface(void)
{
	if (m_pKBInterface == NULL)
	{
		return NULL;
	}
	return m_pKBInterface;
}

#endif


#if defined (__FN_SYSTEM__)

/**********************************************************************
* 函数名称： GetFNInterface
* 功能描述： 
* 输入参数： 
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/03/26		V1.0	    huanggenping	创建版本
***********************************************************************/
CFNInterface* CBaseGlobals::GetFNInterface(void)
{
	if (m_pFNInterface == NULL)
	{
		return NULL;
	}
	return m_pFNInterface;
}
#endif

#if defined (__GS_USER_COUNT__)

/**********************************************************************
* 函数名称： GetUserActionsCount
* 功能描述： 
* 输入参数： 
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/03/26		V1.0	    huanggenping	创建版本
***********************************************************************/
CUserActionsCount* CBaseGlobals::GetUserActionsCount()
{
	return m_pUserActionsCount;
}
#endif



/// @}