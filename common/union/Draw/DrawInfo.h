#ifndef __DRAW_INFO_H__
#define __DRAW_INFO_H__

#include "DrawDest.h"
#include "AroundRect.h"
#include "DrawText.h"
#include "DrawArrow.h"

class CDrawInfo
{

public:

	
	/** @name 私有成员变量 *///////////////////////////////////////////////
    /// @{

	// 是否显示
	int m_nIsVisible;
	int m_nIsAround;
	int m_nIsRetainAround;
	int m_nIsBtnArrow;
	int m_nIsBtnStatus;
	int m_nIsDisable;
	int m_nIsDefault;
	int m_nSaveBtnMode;
	// 按钮模式
	int m_nBtnMode;
	// 绘制左边坐标
	int m_nLeftDest;
	// 绘制顶部坐标
	int m_nTopDest;
	// 绘制宽度
	int m_nWidthDest;
	// 绘制高度
	int m_nHeightDest;
	// 绘制周围的左边坐标
	int m_nAroundLeft;
	// 绘制周围的顶部坐标
	int m_nAroundTop;
	// 绘制周围的宽度
	int m_nAroundWidth;
	// 绘制周围的高度
	int m_nAroundHeight;
	// 绘制周围的左边坐标
	int m_nArrowLeft;
	// 绘制周围的顶部坐标
	int m_nArrowTop;
	// 绘制周围的宽度
	int m_nArrowWidth;
	// 绘制周围的高度
	int m_nArrowHeight;
	//
	int m_nLeftSrc;
	int m_nTopSrc;
	int m_nWidthSrc;
	int m_nHeightSrc;
	//
	int m_nHaveHover;
	int m_nLeftSrcHover;
	int m_nTopSrcHover;
	int m_nWidthSrcHover;
	int m_nHeightSrcHover;
	//
	int m_nHaveDown;
	int m_nLeftSrcDown;
	int m_nTopSrcDown;
	int m_nWidthSrcDown;
	int m_nHeightSrcDown;
	//
	int m_nHaveDisable;
	int m_nLeftSrcDisable;
	int m_nTopSrcDisable;
	int m_nWidthSrcDisable;
	int m_nHeightSrcDisable;
	//
	int m_nTextTop;
	int m_nTextLeft;
	int m_nTextWidth;
	int m_nTextHeight;
	//
	// 主要是是否横向拉伸
	int m_nHorizontalAlignment;
	// 主要是是否纵向拉伸
	int m_nVerticalAlignment;
	xstring m_strBtnText;
	int m_nBtnTextLen;
	TCHAR * m_strTipName;
	int m_nTipNameLen;
	//
	HFONT m_hBtnTextFont;
	// 按钮颜色
	COLORREF m_btnTextColor;

	/// @}

public:
	CDrawInfo(void);
	~CDrawInfo(void);

public:
	virtual xstring GetBtnText() const;
	virtual BOOL SetDrawInfo(const TCHAR * strName, const TCHAR * strValue);
	virtual void SetBtnText(const TCHAR * strBtnText);
	virtual void SetTipName(const TCHAR * strTipName);
	virtual void SetWidthHeightDest();
	virtual void SetHoverDownInfo();
	virtual void SetHoverDownDisableInfo();

};

#endif	// __DRAW_INFO_H__