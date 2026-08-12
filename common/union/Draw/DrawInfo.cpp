#include "StdAfx.h"
#include "DrawInfo.h"

CDrawInfo::CDrawInfo(void)
{
	m_nSaveBtnMode = 0;
	// 按钮模式
	m_nBtnMode = 0;
	m_strBtnText.clear();
	m_nBtnTextLen = 0;
	m_strTipName = NULL;
	m_nTipNameLen = 0;
	m_nLeftDest = 0;
	m_nTopDest = 0;
	m_nWidthDest = 0;
	m_nHeightDest = 0;
	// 绘制周围的左边坐标
	m_nAroundLeft = 0;
	// 绘制周围的顶部坐标
	m_nAroundTop = 0;
	// 绘制周围的宽度
	m_nAroundWidth = 0;
	// 绘制周围的高度
	m_nAroundHeight = 0;
	// 绘制周围的左边坐标
	m_nArrowLeft = 0;
	// 绘制周围的顶部坐标
	m_nArrowTop = 0;
	// 绘制周围的宽度
	m_nArrowWidth = 0;
	// 绘制周围的高度
	m_nArrowHeight = 0;
	//
	m_nLeftSrc = 0;
	m_nTopSrc = 0;
	m_nWidthSrc = 0;
	m_nHeightSrc = 0;
	//
	m_nHaveHover = 0;
	m_nLeftSrcHover = 0;
	m_nTopSrcHover = 0;
	m_nWidthSrcHover = 0;
	m_nHeightSrcHover = 0;
	//
	m_nHaveDown = 0;
	m_nLeftSrcDown = 0;
	m_nTopSrcDown = 0;
	m_nWidthSrcDown = 0;
	m_nHeightSrcDown = 0;
	m_nHaveDisable = 0;
	m_nLeftSrcDisable = 0;
	m_nTopSrcDisable = 0;
	m_nWidthSrcDisable = 0;
	m_nHeightSrcDisable = 0;
	//
	m_nIsVisible = 1;
	m_nIsAround = 0;
	m_nIsRetainAround = 0;
	m_nIsBtnArrow = 0;
	m_nIsDisable = 0;
	m_nIsDefault = 0;
	m_nTextTop = 0;
	m_nTextLeft = 0;
	m_nTextWidth = 0;
	m_nTextHeight = 0;
	m_nHorizontalAlignment = -1;
	m_nVerticalAlignment = -1;
	m_nIsBtnStatus = 0;
	m_hBtnTextFont = NULL;
	// 按钮颜色
	m_btnTextColor = RGB(255, 255, 255);
}

CDrawInfo::~CDrawInfo(void)
{
	if (m_strTipName != NULL)
	{
		delete[] m_strTipName;
		m_strTipName = NULL;
	}
	//
	if (m_hBtnTextFont != NULL)
	{
		::DeleteObject(m_hBtnTextFont);
		m_hBtnTextFont = NULL;
	}
}

BOOL CDrawInfo::SetDrawInfo(const TCHAR * strName, const TCHAR * strValue)
{
	//
	if (_tcscmp(strName, _T("widthSrc")) == 0)
	{
		m_nWidthSrc = _ttoi(strValue);
		return TRUE;
	}
	//
	if (_tcscmp(strName, _T("heightSrc")) == 0)
	{
		m_nHeightSrc = _ttoi(strValue);
		return TRUE;
	}
	//
	if (_tcscmp(strName, _T("leftSrc")) == 0)
	{
		m_nLeftSrc = _ttoi(strValue);
		return TRUE;
	}
	if (_tcscmp(strName, _T("topSrc")) == 0)
	{
		m_nTopSrc = _ttoi(strValue);
		return TRUE;
	}
	//
	if (_tcscmp(strName, _T("widthDest")) == 0)
	{
		m_nWidthDest = _ttoi(strValue);
		return TRUE;
	}
	//
	if (_tcscmp(strName, _T("heightDest")) == 0)
	{
		m_nHeightDest = _ttoi(strValue);
		return TRUE;
	}
	//
	if (_tcscmp(strName, _T("leftDest")) == 0)
	{
		m_nLeftDest = _ttoi(strValue);
		return TRUE;
	}
	if (_tcscmp(strName, _T("topDest")) == 0)
	{
		m_nTopDest = _ttoi(strValue);
		return TRUE;
	}
	//
	if ((_tcscmp(strName, _T("btnText")) == 0))
	{
		SetBtnText(strValue);
		return TRUE;
	}
	//
	if ((_tcscmp(strName, _T("tipName")) == 0))
	{
		SetTipName(strValue);
		return TRUE;
	}
	if ((_tcscmp(strName, _T("btnTextColor")) == 0))
	{
		TCHAR szValue[MAX_PATH] = {'\0'};
		TCHAR szColor[MAX_PATH] = {'\0'};
		int nR = 255;
		int nG = 255;
		int nB = 255;
		_stprintf(szValue, _T("%s"), strValue);
		_tcscpy(szColor, _T("0x"));
		_tcsncat(szColor, szValue + 1, 2);
		nR = (int)_tcstol(szColor, NULL, 16);
		_tcscpy(szColor, _T("0x"));
		_tcsncat(szColor, szValue + 3, 2);
		nG = (int)_tcstol(szColor, NULL, 16);
		_tcscpy(szColor, _T("0x"));
		_tcsncat(szColor, szValue + 5, 2);
		nB = (int)_tcstol(szColor, NULL, 16);
		//m_btnTextColor = RGB(nR, nG, nB);
		return TRUE;
	}
	if ((_tcscmp(strName, _T("btnTextStyle")) == 0))
	{
		m_hBtnTextFont = ::CreateFont(12, 0, 0, 0, FW_NORMAL, 0, 0, 0, 0, 0, 0, 0, 0, _T("宋体"));
	}
	return FALSE;
}

void CDrawInfo::SetBtnText(const TCHAR * strBtnText)
{
	m_strBtnText = strBtnText;
}

xstring CDrawInfo::GetBtnText() const
{
	return m_strBtnText;
}

void CDrawInfo::SetTipName(const TCHAR * strTipName)
{
	int nTextLen = (int)_tcslen(strTipName);
	if (m_strTipName == NULL)
	{
		m_nTipNameLen = nTextLen;
		m_strTipName = new TCHAR[nTextLen + 1];
		_tcscpy(m_strTipName, strTipName);
		return;
	}
	if (nTextLen < m_nTipNameLen)
	{
		_tcscpy(m_strTipName, strTipName);
		return;
	}
	delete[] m_strTipName;
	m_nTipNameLen = nTextLen;
	m_strTipName = new TCHAR[nTextLen + 1];
	_tcscpy(m_strTipName, strTipName);
}

void CDrawInfo::SetWidthHeightDest()
{
	m_nWidthDest = m_nWidthSrc;
	m_nHeightDest = m_nHeightSrc;
}

void CDrawInfo::SetHoverDownInfo()
{
	m_nLeftSrcHover = m_nWidthSrc;
	m_nTopSrcHover = m_nTopSrc;
	m_nWidthSrcHover = m_nWidthSrc;
	m_nHeightSrcHover = m_nHeightSrc;
	m_nHaveHover = 1;
	//
	m_nLeftSrcDown = m_nWidthSrc + m_nWidthSrcHover;
	m_nTopSrcDown = m_nTopSrc;
	m_nWidthSrcDown = m_nWidthSrc;
	m_nHeightSrcDown = m_nHeightSrc;
	m_nHaveDown = 1;
}

void CDrawInfo::SetHoverDownDisableInfo()
{
	SetHoverDownInfo();
	//
	m_nLeftSrcDisable = m_nWidthSrc + m_nWidthSrcHover + m_nWidthSrcDown;
	m_nTopSrcDisable = m_nTopSrc;
	m_nWidthSrcDisable = m_nWidthSrc;
	m_nHeightSrcDisable = m_nHeightSrc;
	m_nHaveDisable = 1;
}

