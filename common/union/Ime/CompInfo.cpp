/*********************************************************************
* 版权所有 (C)2008
* 
* 文件名称： CompInfo.h
* 文件标识： 
* 内容摘要： 提供给单个候选词的管理类，包括主要模块、函数及其功能的说明
* 其它说明： 
* 当前版本： 1.0.20090319
* 作    者： huanggenping
* 完成日期： 2009-03-19
* 
* 修改记录1：
*    修改日期：
*    版 本 号：
*    修 改 人：
*    修改内容： 
* 修改记录2：…
**********************************************************************/
#include "Stdafx.h"
#include "CompInfo.h"

/** @name 构造和虚构函数 */////////////////////////////////////////////////////
/// @{

/**********************************************************************
* 函数名称： CCompInfo
* 功能描述： 
* 输入参数： 
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/03/17		V1.0	    huanggenping	创建版本
***********************************************************************/
CCompInfo::CCompInfo()
{
	m_pVectorPyPartCand = NULL;
#if defined (__UI_SYSTEM__)
	m_pPartCandDrawPaint = NULL;
	m_pPrevDrawPaint = NULL;
	m_pBackDrawPaint = NULL;
	m_pHintDrawPaint = NULL;
	m_pCursorDrawPaint = NULL;
#endif
	Clear();
}

/**********************************************************************
* 函数名称： ~CCompInfo
* 功能描述： 
* 输入参数： 
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/03/17		V1.0	    huanggenping	创建版本
***********************************************************************/
CCompInfo::~CCompInfo()
{
	if (m_pVectorPyPartCand != NULL)
	{
		m_pVectorPyPartCand->clear();
		delete m_pVectorPyPartCand;
		m_pVectorPyPartCand = NULL;
	}
#if defined (__UI_SYSTEM__)
	SAFE_DELETE(m_pPartCandDrawPaint);
	SAFE_DELETE(m_pPrevDrawPaint);
	SAFE_DELETE(m_pBackDrawPaint);
	SAFE_DELETE(m_pHintDrawPaint);
	SAFE_DELETE(m_pCursorDrawPaint);
#endif
}

/// @}

/** @name 公共成员函数 */////////////////////////////////////////////////////
/// @{

/**********************************************************************
* 函数名称： Init
* 功能描述： 
* 输入参数： 
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/03/17		V1.0	    huanggenping	创建版本
***********************************************************************/
BOOL CCompInfo::Init()
{
	BOOL bReturn = FALSE;
	m_pVectorPyPartCand = new CVectorPyPartCand();
	if (m_pVectorPyPartCand == NULL)
	{
		return FALSE;
	}
#if defined (__UI_SYSTEM__)
	//
	m_pPartCandDrawPaint = new CDrawPaint();
	if (m_pPartCandDrawPaint == NULL)
	{
		return FALSE;
	}
	//
	bReturn = m_pPartCandDrawPaint->InitDrawPaint();
	if (!bReturn)
	{
		return FALSE;
	}
	//
	bReturn = m_pPartCandDrawPaint->Create(0, 0);
	if (!bReturn)
	{
		return FALSE;
	}
	//
	m_pPrevDrawPaint = new CDrawPaint();
	if (m_pPrevDrawPaint == NULL)
	{
		return FALSE;
	}
	//
	bReturn = m_pPrevDrawPaint->InitDrawPaint();
	if (!bReturn)
	{
		return FALSE;
	}
	//
	bReturn = m_pPrevDrawPaint->Create(0, 0);
	if (!bReturn)
	{
		return FALSE;
	}
	//
	m_pBackDrawPaint = new CDrawPaint();
	if (m_pBackDrawPaint == NULL)
	{
		return FALSE;
	}
	//
	bReturn = m_pBackDrawPaint->InitDrawPaint();
	if (!bReturn)
	{
		return FALSE;
	}
	//
	bReturn = m_pBackDrawPaint->Create(0, 0);
	if (!bReturn)
	{
		return FALSE;
	}
	//
	m_pHintDrawPaint = new CDrawPaint();
	if (m_pHintDrawPaint == NULL)
	{
		return FALSE;
	}
	//
	bReturn = m_pHintDrawPaint->InitDrawPaint();
	if (!bReturn)
	{
		return FALSE;
	}
	//
	bReturn = m_pHintDrawPaint->Create(0, 0);
	if (!bReturn)
	{
		return FALSE;
	}
	//
	m_pCursorDrawPaint = new CDrawPaint();
	if (m_pCursorDrawPaint == NULL)
	{
		return FALSE;
	}
	//
	bReturn = m_pCursorDrawPaint->InitDrawPaint();
	if (!bReturn)
	{
		return FALSE;
	}
	//
	bReturn = m_pCursorDrawPaint->Create(0, 0);
	if (!bReturn)
	{
		return FALSE;
	}
#endif
	return TRUE;
}

/**********************************************************************
* 函数名称： Clear
* 功能描述： 
* 输入参数： 
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/03/17		V1.0	    huanggenping	创建版本
***********************************************************************/
void CCompInfo::Clear()
{
	memset(m_strOriginalComp, 0, sizeof(m_strOriginalComp));
	memset(m_strAnalyzeComp, 0, sizeof(m_strAnalyzeComp));
	if (m_pVectorPyPartCand != NULL)
	{
		m_pVectorPyPartCand->clear();
	}
	m_bTestComp = FALSE;
	m_bChooseHint = FALSE;
	m_bPySplitComp = FALSE;
	m_nType = 0;
	m_rectPartCand.left = 0;
	m_rectPartCand.top = 0;
	m_rectPartCand.right = 0;
	m_rectPartCand.bottom = 0;
	m_nCursorPos = 0;
	m_nPrevLeft = 0;
	m_nPrevTop = 0;
	m_nPrevRight = 0;
	m_nPrevBottom = 0;
	m_nBackLeft = 0;
	m_nBackTop = 0;
	m_nBackRight = 0;
	m_nBackBottom = 0;
	// 光标的起始位置的左坐标
	m_nCursorLeft1 = 0;
	// 光标的起始位置的上坐标
	m_nCursorTop1 = 0;
	// 光标的结束位置的左坐标
	m_nCursorLeft2 = 0;
	// 光标的结束位置的上坐标
	m_nCursorTop2 = 0;
	// 编码区提示文字最左边坐标
	m_nHintLeft = 0;
	// 编码区提示文字最上变坐标
	m_nHintTop = 0;
	// 编码区提示文字最右边坐标
	m_nHintRight = 0;
	// 编码区提示文字最下边坐标
	m_nHintBottom = 0;
	// 编码区最右边坐标
	m_nRight = 0;
	// 编码区最下边坐标
	m_nBottom = 0;
	// 是否网址补全（0：正常模式，-1：网址不补全，1：网址补全）
	m_nWebSiteMatch = 0;
	// 是否网址直达
	m_nWebSiteNonstop = 0;
	// 打字速度
	m_nOutputSpeed = -1;
	// 网址直达名字
	m_strWebSiteNonstopName = _T("");
	// 网址直达信息
	m_strWebSiteNonstopInfo = _T("");
	// 网址直达Url
	m_strWebSiteNonstopUrl = _T("");
}


/**********************************************************************
* 函数名称： Clear
* 功能描述： 
* 输入参数： 
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/03/17		V1.0	    huanggenping	创建版本
***********************************************************************/
void CCompInfo::SetTempCompInfo()
{
	_stprintf(m_strOriginalComp, _T("%s"), _T("temp"));
	_stprintf(m_strAnalyzeComp, _T("%s"), _T("temp"));
	m_nType = -1;
	m_nOutputSpeed = -1;
	m_nCursorPos = 0;
	m_nOutputSpeed = -1;
}



// 设置网址直达名字
void CCompInfo::SetWebSiteNonstopInfo(const TCHAR *lpszWebSiteNonstopName, const TCHAR *lpszWebSiteNonstopUrl, const TCHAR *lpszWebSiteNonstopHotKey)
{
	TCHAR szWebSiteNonstopInfo[MAX_PATH] = {'\0'};
	_stprintf(szWebSiteNonstopInfo, _T("%s. 网址直达:%s"), lpszWebSiteNonstopHotKey, lpszWebSiteNonstopName);
	m_nWebSiteNonstop = 1;
	m_strWebSiteNonstopName = lpszWebSiteNonstopName;
	m_strWebSiteNonstopUrl = lpszWebSiteNonstopUrl;
	m_strWebSiteNonstopInfo = szWebSiteNonstopInfo;
}

// 清空网址直达
void CCompInfo::ClearWebSiteNonstopInfo()
{
	m_nWebSiteNonstop = 0;
	m_strWebSiteNonstopName = _T("");
	m_strWebSiteNonstopInfo = _T("");
	m_strWebSiteNonstopUrl = _T("");
}

// 部分已经上屏的候选汉字
INT CCompInfo::GetVectorPyPartCandSize()
{
	if (m_pVectorPyPartCand == NULL)
	{
		return 0;
	}
	return m_pVectorPyPartCand->size();
}
/// @}