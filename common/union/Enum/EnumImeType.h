#ifndef __ENUM_IME_H__
#define __ENUM_IME_H__

#include <vector>
#include <map>
using namespace std;

// 用户词库操作类型
enum EUserMBOperateType
{
	// 添加用户词库
	ADD_USER_MB_OPERATE = 0,
	// 编辑用户词库
	EDIT_USER_MB_OPERATE = 1,
};

// 五笔重码字词排序（0：默认排序；1：单字优先；2：词组优先）
enum EWbSameCodeCandidateWordSortMode
{
	// 默认排序
	WB_SAME_CODE_DEFAULT_SORT = 0,
	// 单字优先
	WB_SAME_CODE_SINGLE_PRIOR = 1,
	// 词组优先
	WB_SAME_CODE_PHRASE_PRIOR = 2,
};


// 不同窗口显示编码和候选模式
enum EDiffWndShowCompAndCandMode
{
	// 不启用不同窗口显示编码窗口和候选窗口
	NOT_DIFF_WND_SHOW_COMP_AND_CAND = 0,
	// 启用不同窗口显示编码窗口和候选窗口
	YES_DIFF_WND_SHOW_COMP_AND_CAND = 1,
};


// 候选窗口位于编码窗口
enum ECandWndOfCompPos
{
	// 位于编码窗口下方
	CandWndOfCompBottomPos = 0,
	// 位于编码窗口右边
	CandWndOfCompRightPos = 1,
};

#endif	// __ENUM_IME_H__
