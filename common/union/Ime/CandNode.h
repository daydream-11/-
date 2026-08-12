#pragma once

/*********************************************************************
* 版权所有 (C)2008
* 
* 文件名称： WnCandNode.h
* 文件标识： 
* 内容摘要： 候选词的节点数据类
* 其它说明： 
* 当前版本： 1.0.20090527
* 作    者： liangshouchang
* 完成日期： 2009-05-27
* 
* 修改记录1：
*    修改日期：
*    版 本 号：
*    修 改 人：
*    修改内容： 
* 修改记录2：…
**********************************************************************/

#ifndef __CAND_NODE_H__
#define __CAND_NODE_H__

#include "Public.h"
#include "Enum.h"


// 候选词节点类
class CCandNode
{
public:

	// 固定位置
	BYTE m_cPos;

	// 是否步步提示候选词
	BYTE m_bStep;

	// 位置号
	WORD m_wPos;

	// 权重
	WORD m_wPowerWeight;

	// 码表类型
	EnumMBType m_mbType;

	// 子码表类型
	EnumMBType m_mbChildType;

	// 原始词频
	INT m_wOrgFre;

	//用户词频
	INT m_wUsrFre;

	// 排序词频
	INT m_wAdjFre;
	// 比对词频
	INT m_nCompFre;

	// 附加数据
	VOID *m_pExtraData;

	// 与候选词对应的索引
	xstring	m_strIndex;

	// 候选词
	xstring m_strWord;

	// 候选编码
	xstring m_strCode;

	// 额外数据
	xstring m_strExtra;

	// 数据库索引
	INT m_nID;

public:
	CCandNode(void);
	~CCandNode(void);
private:
	bool operator == (const CCandNode& lhs) const;
	bool operator != (const CCandNode& lhs) const;

public:

	// 清空
	void Clear();

	// 退出
	void ClearExtraData();

	// 拷贝数据
	void Copy(CCandNode *pCandNode);
	// 获取最大词频
	INT GetMaxFre();
};

//用户自造词节点类
class CUsrNode
{
public:
	CUsrNode(void)
	{
		//m_strIndex.resize(4);
		memset(m_strIndex, 0 , 5 * sizeof(TCHAR));
		m_dwAddr  = 0;
		m_cDatlen = 0;
		m_dwNext  = 0;
		m_bAvail  = TRUE;
		m_wUsrFre = 0;
	}
	~CUsrNode(void){}

public:
	//xstring	m_strIndex;		//索引
	TCHAR	m_strIndex[5];
	DWORD	m_dwAddr;		//汉字索引地址
	BYTE	m_cDatlen;		//数据长度
	DWORD	m_dwNext;		//指向下一个节点
	BOOL	m_bAvail;		//是否有效节点
	DWORD	m_wUsrFre;		//用户词频
};


//用户自造词节点类
//主要用于拼音用户词库
class CUsrNodeExt
{
public:
	CUsrNodeExt(void)
	{
		m_dwAddr = 0;
		m_cDatlen = 0;
		m_dwNext = 0;
		m_bAvail = TRUE;
		m_wUsrFre = 0;
	}

	~CUsrNodeExt(void){}

public:
	WORD	m_wIndex[10];	//索引
	DWORD	m_dwAddr;		//汉字索引地址
	BYTE	m_cDatlen;		//数据长度
	DWORD	m_dwNext;		//指向下一个节点
	BOOL	m_bAvail;		//是否有效节点J
	DWORD	m_wUsrFre;		//用户词频
};

typedef vector<CCandNode*> TVectorCandNode;

#endif	// __CAND_NODE_H__