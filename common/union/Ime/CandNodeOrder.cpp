
#include "stdafx.h"
#include "CandNodeOrder.h"

// 按照词频排序
bool MatchCandNodeOrder(CCandNode *pCandNode1, CCandNode *pCandNode2)
{
	if (pCandNode1->m_wAdjFre < pCandNode2->m_wAdjFre)
	{
		// 词频低的放后面
		return false;
	}
	else if (pCandNode1->m_wAdjFre > pCandNode2->m_wAdjFre)
	{
		// 词频高的放前面
		return true;
	}
	return false;
}

// 按照五笔词频排序
bool MatchWuBiCandNodeOrder(CCandNode *pCandNode1, CCandNode *pCandNode2)
{
	if (pCandNode1->m_wUsrFre < pCandNode2->m_wUsrFre)
	{
		// 用户词频低的放后面
		return false;
	}
	else if (pCandNode1->m_wUsrFre > pCandNode2->m_wUsrFre)
	{
		// 用户词频高的放前面
		return true;
	}
	if (pCandNode1->m_wAdjFre < pCandNode2->m_wAdjFre)
	{
		// 词频低的放后面
		return false;
	}
	else if (pCandNode1->m_wAdjFre > pCandNode2->m_wAdjFre)
	{
		// 词频高的放前面
		return true;
	}
	return false;
}

// 按照累计排序
bool MatchCandNodeAddupOrder(CCandNode *pCandNode1, CCandNode *pCandNode2)
{
	if (pCandNode1->m_wPos < pCandNode2->m_wPos)
	{
		// 位置低的放前面
		return true;
	}
	else if (pCandNode1->m_wPos > pCandNode2->m_wPos)
	{
		// 位置高的放后面
		return false;
	}
	if (pCandNode1->m_wOrgFre < pCandNode2->m_wOrgFre)
	{
		// 词频低的放后面
		return false;
	}
	else if (pCandNode1->m_wOrgFre > pCandNode2->m_wOrgFre)
	{
		// 词频高的放后面
		return true;
	}
	return false;
}


// 拼音候选字排序
bool MatchPinYinCandNodeOrder(CCandNode *pCandNode1, CCandNode *pCandNode2)
{
	int nTextLen = (int)pCandNode1->m_strWord.size();
	int nTempTextLen = (int)pCandNode2->m_strWord.size();
	if (nTextLen < nTempTextLen)
	{
		// 拼音字短的放后面
		return false;
	}
	if (nTextLen > nTempTextLen)
	{
		// 拼音字长的放前面
		return true;
	}
	if (pCandNode1->m_wUsrFre < pCandNode2->m_wUsrFre)
	{
		// 用户词频低的放后面
		return false;
	}
	else if (pCandNode1->m_wUsrFre > pCandNode2->m_wUsrFre)
	{
		// 用户词频高的放前面
		return true;
	}
	if (pCandNode1->m_wAdjFre < pCandNode2->m_wAdjFre)
	{
		// 词频低的放后面
		return false;
	}
	else if (pCandNode1->m_wAdjFre > pCandNode2->m_wAdjFre)
	{
		// 词频高的前后面
		return true;
	}
	return false;
}


// 拼音候选字排序按照频率
bool MatchSimpleFrePinYinCandNodeOrder(CCandNode *pCandNode1, CCandNode *pCandNode2)
{
	if (pCandNode1->m_wUsrFre < pCandNode2->m_wUsrFre)
	{
		// 用户词频低的放后面
		return false;
	}
	else if (pCandNode1->m_wUsrFre > pCandNode2->m_wUsrFre)
	{
		// 用户词频高的放前面
		return true;
	}
	if (pCandNode1->m_wAdjFre < pCandNode2->m_wAdjFre)
	{
		// 词频低的放后面
		return false;
	}
	else if (pCandNode1->m_wAdjFre > pCandNode2->m_wAdjFre)
	{
		// 词频高的前后面
		return true;
	}
	return false;
}


// 拼音候选字排序
bool MatchPinYinCandNodeOriginalOrder(CCandNode *pCandNode1, CCandNode *pCandNode2)
{
	// 长句联想
	if (pCandNode1->m_strIndex.length() < pCandNode2->m_strIndex.length())
	{
		return true;
	}
	else if (pCandNode1->m_strIndex.length() > pCandNode2->m_strIndex.length())
	{
		return false;
	}
	if (pCandNode1->m_wUsrFre < pCandNode2->m_wUsrFre)
	{
		// 用户词频低的放后面
		return false;
	}
	else if (pCandNode1->m_wUsrFre > pCandNode2->m_wUsrFre)
	{
		// 用户词频高的放前面
		return true;
	}
	if (pCandNode1->m_wAdjFre < pCandNode2->m_wAdjFre)
	{
		// 词频低的放后面
		return false;
	}
	else if (pCandNode1->m_wAdjFre > pCandNode2->m_wAdjFre)
	{
		// 词频高的前后面
		return true;
	}
	return false;
}


// 单字和词组混合在一起排序
bool MatchPinYinSinglePhraseCandNodeOrder(CCandNode *pCandNode1, CCandNode *pCandNode2)
{
	if (pCandNode1->m_wUsrFre < pCandNode2->m_wUsrFre)
	{
		// 用户词频低的放后面
		return false;
	}
	else if (pCandNode1->m_wUsrFre > pCandNode2->m_wUsrFre)
	{
		// 用户词频高的放后面
		return true;
	}
	if (pCandNode1->m_wAdjFre < pCandNode2->m_wAdjFre)
	{
		// 词频低的放后面
		return false;
	}
	else if (pCandNode1->m_wAdjFre > pCandNode2->m_wAdjFre)
	{
		// 词频高的放后面
		return true;
	}
	return false;
};


// 简单拼音单字排序
bool MatchSimplenessPinYinSingleCandNodeOrder(CCandNode *pCandNode1, CCandNode *pCandNode2)
{
	int nTextLen = (int)pCandNode1->m_strWord.size();
	int nTempTextLen = (int)pCandNode2->m_strWord.size();
	if (nTextLen < nTempTextLen)
	{
		return true;
	}
	if (nTextLen > nTempTextLen)
	{
		return false;
	}
	if (pCandNode1->m_wAdjFre < pCandNode2->m_wAdjFre)
	{
		// 词频低的放后面
		return false;
	}
	else if (pCandNode1->m_wAdjFre > pCandNode2->m_wAdjFre)
	{
		// 词频高的放前面
		return true;
	}
	return false;
}

// 英语词组排序
bool MatchYingYuPhraseCandNodeOrder(CCandNode *pCandNode1, CCandNode *pCandNode2)
{
	int nTextLen = (int)pCandNode1->m_strWord.size();
	int nTempTextLen = (int)pCandNode2->m_strWord.size();
	if (nTextLen < nTempTextLen)
	{
		return true;
	}
	if (nTextLen > nTempTextLen)
	{
		return false;
	}
	if (pCandNode1->m_wAdjFre < pCandNode2->m_wAdjFre)
	{
		// 词频低的放后面
		return false;
	}
	else if (pCandNode1->m_wAdjFre > pCandNode2->m_wAdjFre)
	{
		// 词频高的放前面
		return true;
	}
	return false;
}
// 按照拆分多少排序
bool MatchPinYinPowerWeightOrder(CCandNode *pCandNode1, CCandNode *pCandNode2)
{
	int powerWeight1 = pCandNode1->m_wPowerWeight * 100 / pCandNode1->m_strWord.length();
	int powerWeight2 = pCandNode2->m_wPowerWeight * 100 / pCandNode2->m_strWord.length();
	return powerWeight1 < powerWeight2;
}
// 按字符串排序
bool MatchPinYinCodeOrder(CCandNode *pCandNode1, CCandNode *pCandNode2)
{
	if (pCandNode1->m_strCode == _T(""))
	{
		if (pCandNode1->m_strIndex < pCandNode2->m_strIndex)
		{
			return true;
		}
		return false;
	}
	if (pCandNode1->m_strCode < pCandNode2->m_strCode)
	{
		return true;
	}
	return false;
}