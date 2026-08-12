#include "StdAfx.h"
#include "CandNode.h"

CCandNode::CCandNode(void)
{
	Clear();
}

CCandNode::~CCandNode(void)
{
	this->ClearExtraData();
}
// 相等操作符
bool CCandNode::operator == (const CCandNode& lhs) const
{
	if ( this->m_strIndex == lhs.m_strIndex)
	{
		if ( this->m_strCode == lhs.m_strCode)
		{
			if(this->m_strWord == lhs.m_strWord)
			{
				return true;
			}
		}
	}
	return false;
}
// 不等操作符
bool CCandNode::operator != (const CCandNode& lhs) const
{
	if ( this->m_strIndex == lhs.m_strIndex)
	{
		if ( this->m_strCode == lhs.m_strCode)
		{
			if(this->m_strWord == lhs.m_strWord)
			{
				return false;
			}
		}
	}
	return true;
}


// 清空
void CCandNode::Clear()
{
	// 与候选词对应的索引
	m_strIndex = _T("");
	// 候选词
	m_strWord = _T("");;
	// 候选编码
	m_strCode = _T("");
	// 原始词频
	m_wOrgFre = 0;
	// 用户词频
	m_wUsrFre = 0;
	// 排序词频
	m_wAdjFre = 0;
	// 比对词频
	m_nCompFre = 0;
	// 位置号
	m_wPos = 0;
	// 是否步步提示候选词
	m_bStep = FALSE;
	// 固定位置
	m_cPos = 255;
	// 权重
	m_wPowerWeight = 0;
	// 码表类型
	m_mbType = UN_SYS_MB;
	// 子码表类型
	m_mbChildType = UN_SYS_MB;
	//
	m_pExtraData = NULL;
	m_nID = 0;
}
// 退出
void CCandNode::ClearExtraData()
{
	// 附加数据
	if (m_mbType == PY_MAKE)
	{
		if (m_pExtraData != NULL)
		{
			TVectorCandNode *pVectorCandNode = (TVectorCandNode*)m_pExtraData;
			//
			DeleteVectorObject<CCandNode*, TVectorCandNode>(pVectorCandNode);
			m_pExtraData = NULL;
		}
	}
}
// 拷贝数据
void CCandNode::Copy(CCandNode *pCandNode)
{
	// 码表类型
	m_mbType = pCandNode->m_mbType;
	// 子码表类型
	m_mbChildType = pCandNode->m_mbChildType;
	// 与候选词对应的索引
	m_strIndex = pCandNode->m_strIndex;
	// 候选词
	m_strWord = pCandNode->m_strWord;
	// 候选编码
	m_strCode = pCandNode->m_strCode;
	// 原始词频
	m_wOrgFre = pCandNode->m_wOrgFre;
	// 用户词频
	m_wUsrFre = pCandNode->m_wUsrFre;
	// 排序词频
	m_wAdjFre = pCandNode->m_wAdjFre;
	// 比对词频
	m_nCompFre = pCandNode->m_nCompFre;
	// 位置号
	m_wPos = pCandNode->m_wPos;
	// 权重
	m_wPowerWeight = pCandNode->m_wPowerWeight;
	// 是否步步提示候选词
	m_bStep = pCandNode->m_bStep;
	// 固定位置
	m_cPos = pCandNode->m_cPos;
	//
	if (m_mbType == PY_MAKE)
	{
		if (pCandNode->m_pExtraData != NULL)
		{
			//
			TVectorCandNode *pNewVectorCandNode = new TVectorCandNode();
			TVectorCandNode *pCopyVectorCandNode = (TVectorCandNode*)pCandNode->m_pExtraData;
			//
			for (TVectorCandNode::iterator iter = pCopyVectorCandNode->begin(); iter != pCopyVectorCandNode->end(); iter++)
			{
				CCandNode *pCopyCandNode = *iter;
				CCandNode *pNewCandNode = new CCandNode();
				pNewCandNode->Copy(pCopyCandNode);
				pNewVectorCandNode->push_back(pNewCandNode);
			}
			this->m_pExtraData = pNewVectorCandNode;
		}
	}
	else
	{
		// 附加数据
		m_pExtraData = pCandNode->m_pExtraData;
	}
}
// 获取最大词频
INT CCandNode::GetMaxFre()
{
	if (m_mbType == PY_SYS_SINGLE )
	{
		return 0;
	}
	int maxComFre = m_nCompFre;
	if ( m_pExtraData != NULL && m_mbType == PY_MAKE)
	{
		TVectorCandNode* pVectorCandNode = (TVectorCandNode*)this->m_pExtraData;
		foreach_pointer(TVectorCandNode, pVectorCandNode, itor)
		{
			maxComFre =maxComFre + (*itor)->GetMaxFre();
		}
	}
	return maxComFre;
}