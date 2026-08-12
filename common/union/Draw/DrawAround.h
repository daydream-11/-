#pragma once

#include "DrawStruct.h"

class CItemAround
{
public:
	// 顶部左边
	CDrawRect m_rectAroundUpLeft;
	// 顶部中间
	CDrawRect m_rectAroundUpMiddle;
	// 顶部右边
	CDrawRect m_rectAroundUpRight;
	// 中间左边
	CDrawRect m_rectAroundMiddleLeft;
	// 中间中间
	CDrawRect m_rectAroundMiddleMiddle;
	// 中间右边
	CDrawRect m_rectAroundMiddleRight;
	// 底部左边
	CDrawRect m_rectAroundDownLeft;
	// 底部中间
	CDrawRect m_rectAroundDownMiddle;
	// 底部右边
	CDrawRect m_rectAroundDownRight;
	//
	CImgInfo *m_pImgInfo;
public:
	CItemAround()
	{
		m_pImgInfo = NULL;
	}
public:
	// 设置m_pImgInfo
	void SetImgInfo(CImgInfo *pImgInfo)
	{
		m_pImgInfo = pImgInfo;
	}
	// 获取m_pImgInfo
	CImgInfo* GetImgInfo(void)
	{
		return m_pImgInfo;
	}
	// 顶部左边
	CDrawRect* GetRectAroundUpLeft()
	{
		return &m_rectAroundUpLeft;
	}
	// 顶部中间
	CDrawRect* GetRectAroundUpMiddle()
	{
		return &m_rectAroundUpMiddle;
	}
	// 顶部右边
	CDrawRect* GetRectAroundUpRight()
	{
		return &m_rectAroundUpRight;
	}
	// 中间左边
	CDrawRect* GetRectAroundMiddleLeft()
	{
		return &m_rectAroundMiddleLeft;
	}
	// 中间中间
	CDrawRect* GetRectAroundMiddleMiddle()
	{
		return &m_rectAroundMiddleMiddle;
	}
	// 中间右边
	CDrawRect* GetRectAroundMiddleRight()
	{
		return &m_rectAroundMiddleRight;
	}
	// 底部左边
	CDrawRect* GetRectAroundDownLeft()
	{
		return &m_rectAroundDownLeft;
	}
	// 底部中间
	CDrawRect* GetRectAroundDownMiddle()
	{
		return &m_rectAroundDownMiddle;
	}
	// 底部右边
	CDrawRect* GetRectAroundDownRight()
	{
		return &m_rectAroundDownRight;
	}
	// 查找CDrawRect
	CDrawRect* GetFindRectAround(int nHorWay, int nVerWay)
	{
		switch (nVerWay)
		{
			case 0:
				{
					switch (nHorWay)
					{
						case 0:
							{
								return GetRectAroundUpLeft();
							}
						case 1:
							{
								return GetRectAroundUpMiddle();
							}
						case 2:
							{
								return GetRectAroundUpRight();
							}
					}
					break;
				}
			case 1:
				{
					switch (nHorWay)
					{
						case 0:
							{
								return GetRectAroundMiddleLeft();
							}
						case 1:
							{
								return GetRectAroundMiddleMiddle();
							}
						case 2:
							{
								return GetRectAroundMiddleRight();
							}
					}
					break;
				}
			case 2:
				{
					switch (nHorWay)
					{
						case 0:
							{
								return GetRectAroundDownLeft();
							}
						case 1:
							{
								return GetRectAroundDownMiddle();
							}
						case 2:
							{
								return GetRectAroundDownRight();
							}
					}
					break;
				}
		}
		return NULL;
	}
};

class CDrawAround
{
public:

	/** @name 公共成员变量 */////////////////////////////////////////////////////
	/// @{

	CMapSingleSkinParameter *m_pAroundMapSingleSkinParameter;
	CMapSingleImgParameter *m_pAroundMapSingleImgParameter;
	// 正常状态下
	CItemAround *m_pItemAroundHover;
	// 按下状态下
	CItemAround *m_pItemAroundDown;
	// 选择状态下
	CItemAround *m_pItemAroundChoose;
	// 无效状态下
	CItemAround *m_pItemAroundDisable;
	//
	CImgInfo *m_pAroundImgInfo;

	/// @}

public:
	CDrawAround(void);
	~CDrawAround(void);

public:

	/** @name 公共成员变量 */////////////////////////////////////////////////////
	/// @{
	
	//
	void SetAroundMapSingleSkinParameter(CMapSingleSkinParameter *pAroundMapSingleSkinParameter);
	//
	void SetAroundMapSingleImgParameter(CMapSingleImgParameter *pAroundMapSingleImgParameter);
	// 初始化绘制周围
	BOOL InitDrawAround(void);
	// 加载绘制周围
	BOOL LoadDrawAround(void);
	//
	CItemAround* GetItemAroundHover(void);
	//
	CItemAround* GetItemAroundDown(void);
	//
	CItemAround* GetItemAroundChoose(void);
	//
	CItemAround* GetItemAroundDisable(void);
	//
	CImgInfo* GetAroundImgInfo();
	
	/// @}
};
