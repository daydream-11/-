#include "StdAfx.h"
#include "DrawAround.h"

CDrawAround::CDrawAround(void)
{
	m_pAroundImgInfo = NULL;
	m_pItemAroundHover = NULL;
	m_pItemAroundDown = NULL;
	m_pItemAroundChoose = NULL;
	m_pItemAroundDisable = NULL;
}

CDrawAround::~CDrawAround(void)
{
	if (m_pItemAroundHover != NULL)
	{
		delete m_pItemAroundHover;
		m_pItemAroundHover = NULL;
	}
	if (m_pItemAroundDown != NULL)
	{
		delete m_pItemAroundDown;
		m_pItemAroundDown = NULL;
	}
	//
	if (m_pItemAroundChoose != NULL)
	{
		delete m_pItemAroundChoose;
		m_pItemAroundChoose = NULL;
	}
	//
	if (m_pItemAroundDisable != NULL)
	{
		delete m_pItemAroundDisable;
		m_pItemAroundDisable = NULL;
	}
}

/** @name 公共成员变量 */////////////////////////////////////////////////////
/// @{

// 初始化绘制周围
BOOL CDrawAround::InitDrawAround(void)
{
	m_pAroundMapSingleSkinParameter = NULL;
	m_pItemAroundHover = new CItemAround();
	if (m_pItemAroundHover == NULL)
	{
		return FALSE;
	}
	m_pItemAroundDown = new CItemAround();
	if (m_pItemAroundDown == NULL)
	{
		return FALSE;
	}
	m_pItemAroundChoose = new CItemAround();
	if (m_pItemAroundChoose == NULL)
	{
		return FALSE;
	}
	m_pItemAroundDisable = new CItemAround();
	if (m_pItemAroundDisable == NULL)
	{
		return FALSE;
	}
	return TRUE;
}

//
CItemAround* CDrawAround::GetItemAroundHover(void)
{
	if (m_pItemAroundHover == NULL)
	{
		return NULL;
	}
	return m_pItemAroundHover;
}

//
CItemAround* CDrawAround::GetItemAroundDown(void)
{
	if (m_pItemAroundDown == NULL)
	{
		return NULL;
	}
	return m_pItemAroundDown;
}

//
CItemAround* CDrawAround::GetItemAroundChoose(void)
{
	if (m_pItemAroundChoose == NULL)
	{
		return NULL;
	}
	return m_pItemAroundChoose;
}

//
CItemAround* CDrawAround::GetItemAroundDisable(void)
{
	if (m_pItemAroundDisable == NULL)
	{
		return NULL;
	}
	return m_pItemAroundDisable;
}


//
CImgInfo* CDrawAround::GetAroundImgInfo()
{
	return m_pAroundImgInfo;
}
//
void CDrawAround::SetAroundMapSingleSkinParameter(CMapSingleSkinParameter *pAroundMapSingleSkinParameter)
{
	m_pAroundMapSingleSkinParameter = pAroundMapSingleSkinParameter;
}

//
void CDrawAround::SetAroundMapSingleImgParameter(CMapSingleImgParameter *pAroundMapSingleImgParameter)
{
	m_pAroundMapSingleImgParameter = pAroundMapSingleImgParameter;
}

// 读取绘制周围
BOOL CDrawAround::LoadDrawAround(void)
{
	if (m_pAroundMapSingleImgParameter == NULL)
	{
		return FALSE;
	}
	m_pAroundImgInfo = m_pAroundMapSingleImgParameter->GetParameterValue(_T("image"));

	const xstring * pString = NULL;
	
	if (m_pAroundMapSingleSkinParameter != NULL)
	{
		int nUpLeft_LeftSrc = 0;
		int nUpLeft_TopSrc = 0;
		int nUpLeft_WidthSrc = 0;
		int nUpLeft_HeightSrc = 0;
		int nUpMid_WidthSrc = 0;
		int nUpRight_WidthSrc = 0;
		int nMidLeft_HeightSrc = 0;
		int nDownLeft_HeightSrc = 0;
		//
		pString = m_pAroundMapSingleSkinParameter->GetParameterPointer(_T("upLeft_LeftSrc"));
		if (pString != NULL)
		{
			nUpLeft_LeftSrc = _ttoi(pString->c_str());
		}
		//
		pString = m_pAroundMapSingleSkinParameter->GetParameterPointer(_T("upLeft_TopSrc"));
		if (pString != NULL)
		{
			nUpLeft_TopSrc = _ttoi(pString->c_str());
		}
		//
		pString = m_pAroundMapSingleSkinParameter->GetParameterPointer(_T("upLeft_WidthSrc"));
		if (pString != NULL)
		{
			nUpLeft_WidthSrc = _ttoi(pString->c_str());
		}
		//
		pString = m_pAroundMapSingleSkinParameter->GetParameterPointer(_T("upLeft_HeightSrc"));
		if (pString != NULL)
		{
			nUpLeft_HeightSrc = _ttoi(pString->c_str());
		}
		//
		pString = m_pAroundMapSingleSkinParameter->GetParameterPointer(_T("upMid_WidthSrc"));
		if (pString != NULL)
		{
			nUpMid_WidthSrc = _ttoi(pString->c_str());
		}
		//
		pString = m_pAroundMapSingleSkinParameter->GetParameterPointer(_T("upRight_WidthSrc"));
		if (pString != NULL)
		{
			nUpRight_WidthSrc = _ttoi(pString->c_str());
		}
		//
		pString = m_pAroundMapSingleSkinParameter->GetParameterPointer(_T("midLeft_HeightSrc"));
		if (pString != NULL)
		{
			nMidLeft_HeightSrc = _ttoi(pString->c_str());
		}
		//
		pString = m_pAroundMapSingleSkinParameter->GetParameterPointer(_T("downLeft_HeightSrc"));
		if (pString != NULL)
		{
			nDownLeft_HeightSrc = _ttoi(pString->c_str());
		}
		//
		CItemAround* pItemAround = NULL;
		CDrawRect* pRectAround = NULL;
		CDrawRect* pHoverRectAround = NULL;
		//
		pItemAround = m_pItemAroundHover;
		// UpLeft
		pRectAround = pItemAround->GetRectAroundUpLeft();
		pRectAround->m_nLeft = nUpLeft_LeftSrc;
		pRectAround->m_nTop = nUpLeft_TopSrc;
		pRectAround->m_nWidth = nUpLeft_WidthSrc;
		pRectAround->m_nHeight = nUpLeft_HeightSrc;
		// UpMid
		pRectAround = pItemAround->GetRectAroundUpMiddle();
		pRectAround->m_nLeft = nUpLeft_LeftSrc + nUpLeft_WidthSrc;
		pRectAround->m_nTop = nUpLeft_TopSrc;
		pRectAround->m_nWidth = nUpMid_WidthSrc;
		pRectAround->m_nHeight = nUpLeft_HeightSrc;
		// UpRight
		pRectAround = pItemAround->GetRectAroundUpRight();
		pRectAround->m_nLeft = nUpLeft_LeftSrc + nUpLeft_WidthSrc + nUpMid_WidthSrc;
		pRectAround->m_nTop = nUpLeft_TopSrc;
		pRectAround->m_nWidth = nUpRight_WidthSrc;
		pRectAround->m_nHeight = nUpLeft_HeightSrc;
		// MidLeft
		pRectAround = pItemAround->GetRectAroundMiddleLeft();
		pRectAround->m_nLeft = nUpLeft_LeftSrc;
		pRectAround->m_nTop = nUpLeft_TopSrc + nUpLeft_HeightSrc;
		pRectAround->m_nWidth = nUpLeft_WidthSrc;
		pRectAround->m_nHeight = nMidLeft_HeightSrc;
		// MidMid
		pRectAround = pItemAround->GetRectAroundMiddleMiddle();
		pRectAround->m_nLeft = nUpLeft_LeftSrc + nUpLeft_WidthSrc;
		pRectAround->m_nTop = nUpLeft_TopSrc + nUpLeft_HeightSrc;
		pRectAround->m_nWidth = nUpMid_WidthSrc;
		pRectAround->m_nHeight = nMidLeft_HeightSrc;
		// MidRight
		pRectAround = pItemAround->GetRectAroundMiddleRight();
		pRectAround->m_nLeft = nUpLeft_LeftSrc + nUpLeft_WidthSrc + nUpMid_WidthSrc;
		pRectAround->m_nTop = nUpLeft_TopSrc + nUpLeft_HeightSrc;
		pRectAround->m_nWidth = nUpRight_WidthSrc;
		pRectAround->m_nHeight = nMidLeft_HeightSrc;
		// DownLeft
		pRectAround = pItemAround->GetRectAroundDownLeft();
		pRectAround->m_nLeft = nUpLeft_LeftSrc;
		pRectAround->m_nTop = nUpLeft_TopSrc + nUpLeft_HeightSrc + nMidLeft_HeightSrc;
		pRectAround->m_nWidth = nUpLeft_WidthSrc;
		pRectAround->m_nHeight = nDownLeft_HeightSrc;
		// DownMid
		pRectAround = pItemAround->GetRectAroundDownMiddle();
		pRectAround->m_nLeft = nUpLeft_LeftSrc + nUpLeft_WidthSrc;
		pRectAround->m_nTop = nUpLeft_TopSrc + nUpLeft_HeightSrc + nMidLeft_HeightSrc;
		pRectAround->m_nWidth = nUpMid_WidthSrc;
		pRectAround->m_nHeight = nDownLeft_HeightSrc;
		// DownRight
		pRectAround = pItemAround->GetRectAroundDownRight();
		pRectAround->m_nLeft = nUpLeft_LeftSrc + nUpLeft_WidthSrc + nUpMid_WidthSrc;
		pRectAround->m_nTop = nUpLeft_TopSrc + nUpLeft_HeightSrc + nMidLeft_HeightSrc;
		pRectAround->m_nWidth = nUpRight_WidthSrc;
		pRectAround->m_nHeight = nDownLeft_HeightSrc;
		int nSingleAroundWidth = nUpLeft_LeftSrc + nUpLeft_WidthSrc + nUpMid_WidthSrc + nUpRight_WidthSrc;
		for (int i = 1; i < 4; i++)
		{
			if (i == 1)
			{
				pItemAround = m_pItemAroundDown;
			}
			else if (i == 2)
			{
				pItemAround = m_pItemAroundChoose;
			}
			else if (i == 3)
			{
				pItemAround = m_pItemAroundDisable;
			}
			for (int j = 0; j < 3; j++)
			{
				for (int k = 0; k < 3; k++)
				{
					pRectAround = pItemAround->GetFindRectAround(k, j);
					pHoverRectAround = m_pItemAroundHover->GetFindRectAround(k, j);
					pRectAround->m_nLeft = pHoverRectAround->m_nLeft + nSingleAroundWidth * i;
					pRectAround->m_nTop = pHoverRectAround->m_nTop;
					pRectAround->m_nWidth = pHoverRectAround->m_nWidth;
					pRectAround->m_nHeight = pHoverRectAround->m_nHeight;
				}
			}
		}
	}
	return TRUE;
}

/// @}