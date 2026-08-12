#include "StdAfx.h"
#include "CandList.h"

/** @name 构造和虚构函数 */////////////////////////////////////////////////////
/// @{

/**********************************************************************
* 函数名称： CCandList
* 功能描述： 
* 输入参数： 
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/03/26		V1.0	    huanggenping	创建版本
***********************************************************************/
CCandList::CCandList(void)
{
	m_nMaxCandNum = 0;
	m_pVectorCandInfo = NULL;
	m_pTestCandInfo = NULL;
}

/**********************************************************************
* 函数名称： ~CCandList
* 功能描述： 
* 输入参数： 
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/03/26		V1.0	    huanggenping	创建版本
***********************************************************************/
CCandList::~CCandList(void)
{
	if (m_pVectorCandInfo != NULL)
	{
		for (CVectorCandInfo::iterator iter =  m_pVectorCandInfo->begin(); iter != m_pVectorCandInfo->end(); iter++)
		{
			CCandInfo *pCandInfo = *iter;
			delete pCandInfo;
			pCandInfo = NULL;
		}
		delete m_pVectorCandInfo;
		m_pVectorCandInfo = NULL;
	}
	SAFE_DELETE(m_pTestCandInfo);
}

/// @}


/** @name 公用成员函数 */////////////////////////////////////////////////////
/// @{

/**********************************************************************
* 函数名称： Init
* 功能描述： 
* 输入参数： 
* 输出参数：
* 返 回 值： 执行成功，返回TRUE；执行失败，返回FALSE
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/03/25		V1.0	    huanggenping	创建版本
***********************************************************************/
BOOL CCandList::Init(void)
{
	m_nChooseCandNum = -1;
	m_nRealCandNum = 0;
	m_nDrawCandNum = 0;
	m_nMaxCandNum = 9;
	m_pVectorCandInfo = new CVectorCandInfo();
	m_nCandInfoNum = 0;
	// 预先定义9个候选词
	CCandInfo * pCandInfo = NULL;
	// 预先定义1
	pCandInfo = new CCandInfo();
	pCandInfo->Init();
	m_pVectorCandInfo->push_back(pCandInfo);
	// 预先定义2
	pCandInfo = new CCandInfo();
	pCandInfo->Init();
	m_pVectorCandInfo->push_back(pCandInfo);
	// 预先定义3
	pCandInfo = new CCandInfo();
	pCandInfo->Init();
	m_pVectorCandInfo->push_back(pCandInfo);
	// 预先定义4
	pCandInfo = new CCandInfo();
	pCandInfo->Init();
	m_pVectorCandInfo->push_back(pCandInfo);
	// 预先定义5
	pCandInfo = new CCandInfo();
	pCandInfo->Init();
	m_pVectorCandInfo->push_back(pCandInfo);
	// 预先定义6
	pCandInfo = new CCandInfo();
	pCandInfo->Init();
	m_pVectorCandInfo->push_back(pCandInfo);
	// 预先定义7
	pCandInfo = new CCandInfo();
	pCandInfo->Init();
	m_pVectorCandInfo->push_back(pCandInfo);
	// 预先定义8
	pCandInfo = new CCandInfo();
	pCandInfo->Init();
	m_pVectorCandInfo->push_back(pCandInfo);
	// 预先定义9
	pCandInfo = new CCandInfo();
	pCandInfo->Init();
	m_pVectorCandInfo->push_back(pCandInfo);
	// 预先定义测试用的
	m_pTestCandInfo = new CCandInfo();
	m_pTestCandInfo->Init();
	m_pTestCandInfo->m_strWord =  _T("测试");
	return TRUE;
}

/**********************************************************************
* 函数名称： InsertData
* 功能描述： 
* 输入参数： 
* <param name="pCandInfo"></param>
* 输出参数：
* 返 回 值： 执行成功，返回TRUE；执行失败，返回FALSE
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/03/18		V1.0	    huanggenping	创建版本
***********************************************************************/
BOOL CCandList::InsertData(CCandInfo * pCandInfo)
{
	int nShowNum = 6;
	if (nShowNum < 1 || nShowNum > 9)
	{
		nShowNum = 6;
	}
	CCandInfo* pThisCandInfo = GetCurCandInfo();
	if (pThisCandInfo == NULL)
	{
		return FALSE;
	}
	// 上个的地址
	CCandInfo* pPravCandInfo = NULL;
	if (m_nCandInfoNum > 0)
	{
		pPravCandInfo = GetCandInfo(m_nCandInfoNum - 1);
	}
	pThisCandInfo->m_strOriginal = pCandInfo->m_strWord;
	pThisCandInfo->m_strWord = pCandInfo->m_strWord;
	if (pCandInfo->m_mbType == WB_SYS || pCandInfo->m_mbType == WB_USR || pCandInfo->m_mbType == GBK_SYS)
	{
		if (pCandInfo->m_nType == 0)
		{
			pThisCandInfo->m_strWbCode = pCandInfo->m_strIndex.c_str();
		}
	}
	else if (pCandInfo->m_mbType == PY_SYS || pCandInfo->m_mbType == PY_SYS_SINGLE || pCandInfo->m_mbType == PY_USR || pCandInfo->m_mbType == PY_MAKE)
	{
		if (pCandInfo->m_nType == 0)
		{
			pThisCandInfo->m_strWbCode = pCandInfo->m_strWbCode;
			pThisCandInfo->m_strPyCode = pCandInfo->m_strPyCode;
		}
	}
	else if (pCandInfo->m_mbType == BH_SYS || pCandInfo->m_mbType == BH_USR)
	{
		if (pCandInfo->m_nType == 0)
		{
			pThisCandInfo->m_strBhCode = pCandInfo->m_strIndex.c_str();
		}
	}
	else
	{
		pThisCandInfo->m_strWbCode = _T("");
	}
	pThisCandInfo->m_strOriginal = pCandInfo->m_strOriginal;
	pThisCandInfo->m_nType = pCandInfo->m_nType;
	pThisCandInfo->m_mbType = pCandInfo->m_mbType;
	pThisCandInfo->m_mbChildType = pCandInfo->m_mbChildType;
	pThisCandInfo->m_strIndex = pCandInfo->m_strIndex;
	pThisCandInfo->m_wPos = pCandInfo->m_wPos;
	pThisCandInfo->m_wOrgFre = pCandInfo->m_wOrgFre;
	pThisCandInfo->m_wUsrFre = pCandInfo->m_wUsrFre;
	pThisCandInfo->m_bStep = pCandInfo->m_bStep;
	pThisCandInfo->m_nFixed = pCandInfo->m_nFixed;
	pThisCandInfo->m_nNum = m_nCandInfoNum + 1;
	pThisCandInfo->m_pExtraData = pCandInfo->m_pExtraData;
	pThisCandInfo->m_strExtra = pCandInfo->m_strExtra;
	pThisCandInfo->m_nID = pCandInfo->m_nID;
	AddCandInfoNum();

	return TRUE;
}

/**********************************************************************
* 函数名称： GetCandInfo
* 功能描述： 
* 输入参数： 
* <param name="nNum"></param>
* 输出参数：
* 返 回 值： 返回CCandInfo的指针
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/03/18		V1.0	    huanggenping	创建版本
***********************************************************************/
CCandInfo* CCandList::GetCandInfo(int nNum)
{
	if (nNum < 0)
	{
		return NULL;
	}
	if (nNum >= m_nCandInfoNum)
	{
		return NULL;
	}
	return m_pVectorCandInfo->at(nNum);
}

/**********************************************************************
* 函数名称： GetDrawCand
* 功能描述： 
* 输入参数： 
* <param name="nNum"></param>
* 输出参数：
* 返 回 值： 返回CCandInfo的指针
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/03/18		V1.0	    huanggenping	创建版本
***********************************************************************/
CCandInfo* CCandList::GetDrawCand(int nNum)
{
	if (nNum < 0)
	{
		return NULL;
	}
	if (m_nDrawCandNum > 0)
	{
		if (nNum >= m_nDrawCandNum)
		{
			return NULL;
		}
	}
	else
	{
		if (nNum >= m_nCandInfoNum)
		{
			return NULL;
		}
	}
	return m_pVectorCandInfo->at(nNum);
}

/**********************************************************************
* 函数名称： GetMaxCandInfoRight
* 功能描述： 
* 输入参数： 
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/03/27		V1.0	    huanggenping	创建版本
***********************************************************************/
int CCandList::GetMaxCandInfoRight()
{
	int nMaxRight = 0;
	for (int i = 0 ; i < m_nCandInfoNum; i++)
	{
		CCandInfo* pCandInfo = m_pVectorCandInfo->at(i);
		if (nMaxRight < pCandInfo->m_nRight)
		{
			nMaxRight = pCandInfo->m_nRight;
		}
	}
	return nMaxRight;
}

/**********************************************************************
* 函数名称： GetCurCandInfo
* 功能描述： 
* 输入参数： 
* 输出参数：
* 返 回 值： 返回CCandInfo的指针
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/03/26		V1.0	    huanggenping	创建版本
***********************************************************************/
CCandInfo* CCandList::GetCurCandInfo()
{
	if (m_nCandInfoNum >= 9)
	{
		return NULL;
	}
	CCandInfo* pCandInfo = m_pVectorCandInfo->at(m_nCandInfoNum);
	return pCandInfo;
}

/**********************************************************************
* 函数名称： GetPrevCandInfo
* 功能描述： 
* 输入参数： 
* 输出参数：
* 返 回 值： 返回CCandInfo的指针
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/03/26		V1.0	    huanggenping	创建版本
***********************************************************************/
CCandInfo* CCandList::GetPrevCandInfo()
{
	if (m_nCandInfoNum < 1)
	{
		return NULL;
	}
	CCandInfo* pCandInfo = m_pVectorCandInfo->at(m_nCandInfoNum - 1);
	return pCandInfo;
}

/**********************************************************************
* 函数名称： GetTestCandInfo
* 功能描述： 
* 输入参数： 
* 输出参数：
* 返 回 值： 返回CCandInfo的指针
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/03/26		V1.0	    huanggenping	创建版本
***********************************************************************/
CCandInfo* CCandList::GetTestCandInfo()
{
	if (m_pTestCandInfo == NULL)
	{
		return NULL;
	}
	return m_pTestCandInfo;
}

/**********************************************************************
* 函数名称： RemoveAll
* 功能描述： 
* 输入参数： 
* 输出参数：
* 返 回 值： 返回CCandInfo的指针
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/03/18		V1.0	    huanggenping	创建版本
***********************************************************************/
BOOL CCandList::RemoveAll()
{
	if(m_pVectorCandInfo != NULL)
	{
		for(CVectorCandInfo::iterator iter = m_pVectorCandInfo->begin(); iter != m_pVectorCandInfo->end(); iter++)
		{
			CCandInfo * pCandInfo = *iter;
			pCandInfo->Clear();
		}
	}
	m_nChooseCandNum = -1;
	m_nMouseCandNum = -1;
	m_nCandInfoNum = 0;
	m_nRealCandNum = 0;
	m_nDrawCandNum = 0;
	/*CBaseImePlugin *pWnBaseImePlugin = g_pWnUIGlbas->GetWnBasePlugin()->GetWnBaseImePlugin();
	if (pWnBaseImePlugin != NULL)
	{
		pWnBaseImePlugin->ClearCand(0);
	}*/
	return TRUE;
}

/**********************************************************************
* 函数名称： AddCandInfoNum
* 功能描述： 
* 输入参数： 
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/03/18		V1.0	    huanggenping	创建版本
***********************************************************************/
void CCandList::AddCandInfoNum()
{
	m_nCandInfoNum++;
	m_nRealCandNum++;
}

/**********************************************************************
* 函数名称： SetCandInfoNum
* 功能描述： 
* 输入参数： 
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/03/18		V1.0	    huanggenping	创建版本
***********************************************************************/
void CCandList::SetCandInfoNum(int nCandInfoNum)
{
	m_nCandInfoNum = nCandInfoNum;
}

/**********************************************************************
* 函数名称： GetCandInfoNum
* 功能描述： 
* 输入参数： 
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/03/18		V1.0	    huanggenping	创建版本
***********************************************************************/
int CCandList::GetCandInfoNum()
{
	return m_nCandInfoNum;
}

/**********************************************************************
* 函数名称： GetRealCandNum
* 功能描述： 
* 输入参数： 
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/03/18		V1.0	    huanggenping	创建版本
***********************************************************************/
int CCandList::GetRealCandNum()
{
	return m_nRealCandNum; 
}

/**********************************************************************
* 函数名称： GetChooseCandNum
* 功能描述： 
* 输入参数： 
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/03/18		V1.0	    huanggenping	创建版本
***********************************************************************/
int CCandList::GetChooseCandNum()
{
	return m_nChooseCandNum;
}


/**********************************************************************
* 函数名称： SetMaxCandNum
* 功能描述： 
* 输入参数： 
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/03/25		V1.0	    huanggenping	创建版本
***********************************************************************/
void CCandList::SetMaxCandNum(int nMaxCandNum)
{
	if (nMaxCandNum > m_nMaxCandNum)
	{
		m_nMaxCandNum = nMaxCandNum;
		//RealseBuffer();
		for (CVectorCandInfo::iterator iter =  m_pVectorCandInfo->begin(); iter != m_pVectorCandInfo->end(); iter++)
		{
			CCandInfo *pCandInfo = *iter;
			delete pCandInfo;
			pCandInfo = NULL;
		}
		m_pVectorCandInfo->clear();
		CCandInfo * pCandInfo = NULL;
		CCandInfo myCandInfo;
		for (int i = 0; i < m_nMaxCandNum; i++)
		{
			// 预先定义1
			pCandInfo = new CCandInfo();
			m_pVectorCandInfo->push_back(pCandInfo);
		}
	}
}


/**********************************************************************
* 函数名称： SetChooseCandNum
* 功能描述： 
* 输入参数： 
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/03/18		V1.0	    huanggenping	创建版本
***********************************************************************/
void CCandList::SetChooseCandNum(int nChooseCandNum)
{
	m_nChooseCandNum = nChooseCandNum;
}

/**********************************************************************
* 函数名称： GetChooseCandNum
* 功能描述： 
* 输入参数： 
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/03/18		V1.0	    huanggenping	创建版本
***********************************************************************/
int CCandList::GetMouseCandNum()
{
	return m_nMouseCandNum;
}

/**********************************************************************
* 函数名称： SetChooseCandNum
* 功能描述： 
* 输入参数： 
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/03/18		V1.0	    huanggenping	创建版本
***********************************************************************/
void CCandList::SetMouseCandNum(int nMouseCandNum)
{
	m_nMouseCandNum = nMouseCandNum;
}

/**********************************************************************
* 函数名称： GetDrawCandNum
* 功能描述： 
* 输入参数： 
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/03/18		V1.0	    huanggenping	创建版本
***********************************************************************/
int CCandList::GetDrawCandNum()
{
	return m_nDrawCandNum;
}

/**********************************************************************
* 函数名称： SetChooseCandNum
* 功能描述： 
* 输入参数： 
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/03/18		V1.0	    huanggenping	创建版本
***********************************************************************/
void CCandList::SetDrawCandNum(int nDrawCandNum)
{
	m_nDrawCandNum = nDrawCandNum;
}

/**********************************************************************
* 函数名称： DeleteThis
* 功能描述： 
* 输入参数： 
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/03/18		V1.0	    huanggenping	创建版本
***********************************************************************/
void CCandList::DeleteThis()
{
	delete this;
}

/// @}
