#ifndef __RESOURCE_STRUCT_H__
#define __RESOURCE_STRUCT_H__

#include "VectorParameter.h"
#include "MapParameter.h"
#include "ImgInfo.h"
#include "DrawInfo.h"

// 单个参数MAP
typedef MapParameter<xstring, xstring> CMapSingleParameter;
// 多个向量参数列表
typedef VectorParameter<CMapSingleParameter*> CVectorMultiParameter;
// MAP装置向量列表参数
typedef MapParameter<xstring, CVectorMultiParameter*> CMapMultiVectorParameter;

// 单个风格配置参数
typedef MapParameter<xstring, xstring> CMapSingleSkinParameter;
// 多个风格配置参数
typedef VectorParameter<CMapSingleSkinParameter*> CVectorMultiSkinParameter;
// 一个窗口风格参数
typedef VectorParameter<CVectorMultiSkinParameter*> CVectorSingleWndParameter;
// 皮肤按钮配置参数
typedef MapParameter<xstring, CVectorSingleWndParameter*> CMapMultiWndParameter;

// 单个图片句柄配置参数
typedef MapParameter<xstring, CImgInfo*> CMapSingleImgParameter;
// 多个图片句柄配置参数
typedef MapParameter<xstring, CMapSingleImgParameter*> CMapMultiImgParameter;
// 一个窗口的图片句柄参数
typedef MapParameter<xstring, CMapMultiImgParameter*> CMapSingleWndImgParameter;
// 多个窗口的图片句柄参数
typedef MapParameter<xstring, CMapSingleWndImgParameter*> CMapMultiWndImgParameter;


// 单个绘制配置参数
// 多个绘制配置参数
typedef MapParameter<xstring, CDrawInfo*> CMapMultiDrawParameter;
// 一个窗口的绘制参数
typedef MapParameter<xstring, CMapMultiDrawParameter*> CMapSingleWndDrawParameter;
// 多个窗口的绘制参数
typedef MapParameter<xstring, CMapSingleWndDrawParameter*> CMapMultiWndDrawParameter;

//
static const TCHAR pszLowercaseRouteWay[4][10] = 
{
	_T("left"),
	_T("top"),
	_T("width"),
	_T("height")
};
//
static const TCHAR pszFMBackWay[3][10] = 
{
	_T("front"),
	_T("mid"),
	_T("back")
};
//
static const TCHAR pszNHDownWay[3][10] = 
{
	_T("Normal"),
	_T("Hover"),
	_T("Down")
};


class CDrawRect
{
public:
	int m_nLeft;
	int m_nTop;
	int m_nWidth;
	int m_nHeight;
	CImgInfo *m_pImgInfo;
public:
	CDrawRect()
	{
		m_nLeft = 0;
		m_nTop = 0;
		m_nWidth = 0;
		m_nHeight = 0;
		m_pImgInfo = NULL;
	}
	void SetValue(int nIndex, int nValue)
	{
		switch (nIndex)
		{
		case 0:
			{
				m_nLeft = nValue;
				break;
			}
		case 1:
			{
				m_nTop = nValue;
				break;
			}
		case 2:
			{
				m_nWidth = nValue;
				break;
			}
		case 3:
			{
				m_nHeight = nValue;
				break;
			}
		}
	}
	void SetImgInfo(CImgInfo *pImgInfo)
	{
		m_pImgInfo = pImgInfo;
	}
	CImgInfo* GetImgInfo(void)
	{
		if (m_pImgInfo == NULL)
		{
			return NULL;
		}
		return m_pImgInfo;
	}
};

class CItemFMBack
{
public:
	CDrawRect m_drawRectFront;
	CDrawRect m_drawRectMiddle;
	CDrawRect m_drawRectBack;
	//
	CImgInfo *m_pImgInfo;
public:
	CItemFMBack()
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
	// 获取前部分图片
	CDrawRect* GetDrawRectFront(void)
	{
		return &m_drawRectFront;
	}
	// 获取中间部分图片
	CDrawRect* GetDrawRectMiddle(void)
	{
		return &m_drawRectMiddle;
	}
	// 获取后面部分图片
	CDrawRect* GetDrawRectBack(void)
	{
		return &m_drawRectBack;
	}
};

class CDrawFMBack
{
public:
	// 正常状态下
	CItemFMBack *m_pNormalItemFMBack;
	// 移动状态下
	CItemFMBack *m_pHoverItemFMBack;
	// 按下状态下
	CItemFMBack *m_pDownItemFMBack;
	// 默认状态下
	CItemFMBack *m_pDefaultItemFMBack;
	// 无效状态下
	CItemFMBack *m_pDisableItemFMBack;
	//
	CImgInfo *m_pImgInfo;
public:
	CDrawFMBack()
	{
		m_pImgInfo = NULL;
		m_pNormalItemFMBack = NULL;
		m_pHoverItemFMBack = NULL;
		m_pDownItemFMBack = NULL;
		m_pDefaultItemFMBack = NULL;
		m_pDisableItemFMBack = NULL;
	}
	~CDrawFMBack()
	{
		//
		if (m_pNormalItemFMBack != NULL)
		{
			delete m_pNormalItemFMBack;
			m_pNormalItemFMBack = NULL;
		}
		//
		if (m_pHoverItemFMBack != NULL)
		{
			delete m_pHoverItemFMBack;
			m_pHoverItemFMBack = NULL;
		}
		//
		if (m_pDownItemFMBack != NULL)
		{
			delete m_pDownItemFMBack;
			m_pDownItemFMBack = NULL;
		}
		//
		if (m_pDefaultItemFMBack != NULL)
		{
			delete m_pDefaultItemFMBack;
			m_pDefaultItemFMBack = NULL;
		}
		//
		if (m_pDisableItemFMBack != NULL)
		{
			delete m_pDisableItemFMBack;
			m_pDisableItemFMBack = NULL;
		}
	}
	// 
	BOOL CDrawFMBack::InitDrawFMBack(void)
	{
		//
		m_pNormalItemFMBack = new CItemFMBack();
		if (m_pNormalItemFMBack == NULL)
		{
			return FALSE;
		}
		//
		m_pHoverItemFMBack = new CItemFMBack();
		if (m_pHoverItemFMBack == NULL)
		{
			return FALSE;
		}
		//
		m_pDownItemFMBack = new CItemFMBack();
		if (m_pDownItemFMBack == NULL)
		{
			return FALSE;
		}
		//
		m_pDisableItemFMBack = new CItemFMBack();
		if (m_pDisableItemFMBack == NULL)
		{
			return FALSE;
		}
		//
		m_pDefaultItemFMBack = new CItemFMBack();
		if (m_pDefaultItemFMBack == NULL)
		{
			return FALSE;
		}
		return TRUE;
	}
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
	// 获取正常状态下
	CItemFMBack* GetNormalItemFMBack()
	{
		if (m_pNormalItemFMBack == NULL)
		{
			return NULL;
		}
		return m_pNormalItemFMBack;
	}
	// 获取移动状态下
	CItemFMBack* GetHoverItemFMBack()
	{
		if (m_pHoverItemFMBack == NULL)
		{
			return NULL;
		}
		return m_pHoverItemFMBack;
	}

	// 获取按下状态下
	CItemFMBack* GetDownItemFMBack()
	{
		if (m_pDownItemFMBack == NULL)
		{
			return NULL;
		}
		return m_pDownItemFMBack;
	}

	// 获取无效状态下
	CItemFMBack* GetDisableItemFMBack()
	{
		if (m_pDisableItemFMBack == NULL)
		{
			return NULL;
		}
		return m_pDisableItemFMBack;
	}

	// 获取默认状态下
	CItemFMBack* GetDefaultItemFMBack()
	{
		if (m_pDefaultItemFMBack == NULL)
		{
			return NULL;
		}
		return m_pDefaultItemFMBack;
	}

};

class CDrawNHDRect
{
public:
	// 正常状态下
	CDrawRect m_normalWnDrawRect;
	// 移动状态下
	CDrawRect m_hoverWnDrawRect;
	// 按下状态下
	CDrawRect m_downWnDrawRect;
	//
	CImgInfo *m_pImgInfo;
public:
	CDrawNHDRect()
	{
		m_pImgInfo = NULL;
	}
	~CDrawNHDRect()
	{

	}
	// 获取m_pImgInfo
	CImgInfo* GetImgInfo(void)
	{
		return m_pImgInfo;
	}
	// 获取m_pImgInfo
	void SetImgInfo(CImgInfo *pImgInfo)
	{
		m_pImgInfo = pImgInfo;
	}
	// 获取正常状态下
	CDrawRect* GetNormalWnDrawRect()
	{
		return &m_normalWnDrawRect;
	}
	// 获取移动状态下
	CDrawRect* GetHoverWnDrawRect()
	{
		return &m_hoverWnDrawRect;
	}
	// 获取按下状态下
	CDrawRect* GetDownWnDrawRect()
	{
		return &m_downWnDrawRect;
	}
};

#endif	// __RESOURCE_STRUCT_H__