#ifndef __CAND_NODE_ORDER_H__
#define __CAND_NODE_ORDER_H__

#include "CandNode.h"

// 按照词频排序
bool MatchCandNodeOrder(CCandNode *pCandNode1, CCandNode *pCandNode2);
// 按照五笔词频排序
bool MatchWuBiCandNodeOrder(CCandNode *pCandNode1, CCandNode *pCandNode2);
// 按照累计排序
bool MatchCandNodeAddupOrder(CCandNode *pCandNode1, CCandNode *pCandNode2);
// 拼音候选字排序
bool MatchPinYinCandNodeOrder(CCandNode *pCandNode1, CCandNode *pCandNode2);
// 拼音候选字排序按照频率
bool MatchSimpleFrePinYinCandNodeOrder(CCandNode *pCandNode1, CCandNode *pCandNode2);
// 拼音候选字排序
bool MatchPinYinCandNodeOriginalOrder(CCandNode *pCandNode1, CCandNode *pCandNode2);
// 单子和词组混合在一起排序
bool MatchPinYinSinglePhraseCandNodeOrder(CCandNode *pCandNode1, CCandNode *pCandNode2);
// 简单拼音单字排序
bool MatchSimplenessPinYinSingleCandNodeOrder(CCandNode *pCandNode1, CCandNode *pCandNode2);
// 英语词组排序
bool MatchYingYuPhraseCandNodeOrder(CCandNode *pCandNode1, CCandNode *pCandNode2);
// 按照拆分多少排序
bool MatchPinYinPowerWeightOrder(CCandNode *pCandNode1, CCandNode *pCandNode2);
// 按字符串排序
bool MatchPinYinCodeOrder(CCandNode *pCandNode1, CCandNode *pCandNode2);

#endif	// __CAND_NODE_ORDER_H__
