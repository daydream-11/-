// WndShadow.h : header file
//
// Version 0.1
//
// Copyright (c) 2006 Perry Zhu, All Rights Reserved.
//
// mailto:perry@live.com
//
//
// This source file may be redistributed unmodified by any means PROVIDING 
// it is NOT sold for profit without the authors expressed written 
// consent, and providing that this notice and the author's name and all 
// copyright notices remain intact. This software is by no means to be 
// included as part of any third party components library, or as part any
// development solution that offers MFC extensions that are sold for profit. 
// 
// If the source code is used in any commercial applications then a statement 
// along the lines of:
// 
// "Portions Copyright (c) 2006 Perry Zhu" must be included in the "Startup 
// Banner", "About Box" or "Printed Documentation". This software is provided 
// "as is" without express or implied warranty. Use it at your own risk! The 
// author accepts no liability for any damage/loss of business that this 
// product may cause.
//
/////////////////////////////////////////////////////////////////////////////
//****************************************************************************

#include "StdAfx.h"
#include "WndShadow.h"
#include "math.h"
#include "crtdbg.h"

// Some extra work to make this work in VC++ 6.0

// walk around the for iterator scope bug of VC++6.0
#ifdef _MSC_VER
#if _MSC_VER == 1200
#define for if(false);else for
#endif
#endif

// Some definitions for VC++ 6.0 without newest SDK
#ifndef WS_EX_LAYERED
#define WS_EX_LAYERED 0x00080000
#endif

#ifndef AC_SRC_ALPHA
#define AC_SRC_ALPHA 0x01
#endif

#ifndef ULW_ALPHA
#define ULW_ALPHA 0x00000002
#endif

CWndShadow::pfnUpdateLayeredWindow CWndShadow::s_UpdateLayeredWindow = NULL;

const TCHAR *strWndClassName = _T("PerryShadowWnd");

HINSTANCE CWndShadow::s_hInstance = (HINSTANCE)INVALID_HANDLE_VALUE;

std::map<HWND, CWndShadow *> CWndShadow::s_Shadowmap;

CWndShadow::CWndShadow(void)
: m_hWnd((HWND)INVALID_HANDLE_VALUE)
, m_OriParentProc(NULL)
, m_nSize(5)
, m_WndSize(0)
, m_bUpdate(false)
, m_pShadowDrawImage(NULL)
{
}

CWndShadow::~CWndShadow(void)
{
}

bool CWndShadow::Initialize(HINSTANCE hInstance)
{
	// Should not initiate more than once
	if (NULL != s_UpdateLayeredWindow)
		return false;

	HMODULE hUser32 = GetModuleHandle(_T("USER32.DLL"));
	s_UpdateLayeredWindow = 
		(pfnUpdateLayeredWindow)GetProcAddress(hUser32, 
		"UpdateLayeredWindow");
	
	// If the import did not succeed, make sure your app can handle it!
	if (NULL == s_UpdateLayeredWindow)
		return false;

	// Store the instance handle
	s_hInstance = hInstance;

	//

	// Register window class for shadow window
	WNDCLASSEX wcex;

	memset(&wcex, 0, sizeof(wcex));

	wcex.cbSize = sizeof(WNDCLASSEX); 
	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= DefWindowProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= NULL;
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= strWndClassName;
	wcex.hIconSm		= NULL;

	RegisterClassEx(&wcex);

	return true;
}

void CWndShadow::Create(HWND hParentWnd)
{
	// Do nothing if the system does not support layered windows
	if(NULL == s_UpdateLayeredWindow)
		return;

	m_pShadowDrawImage = new CDrawImage();
	m_pShadowDrawImage->InitDrawImage();
	m_pShadowDrawImage->LoadResImage(_T("Shadow.PNG"), s_hInstance, _T("PIC"));

	// Already initialized
	_ASSERT(s_hInstance != INVALID_HANDLE_VALUE);

	// Add parent window - shadow pair to the map
	_ASSERT(s_Shadowmap.find(hParentWnd) == s_Shadowmap.end());	// Only one shadow for each window
	s_Shadowmap[hParentWnd] = this;

	// Create the shadow window
	m_hWnd = CreateWindowEx(WS_EX_LAYERED | WS_EX_TRANSPARENT, strWndClassName, NULL,
		/*WS_VISIBLE | */WS_CAPTION | WS_POPUPWINDOW,
		CW_USEDEFAULT, 0, 0, 0, hParentWnd, NULL, s_hInstance, NULL);

	// Determine the initial show state of shadow according to parent window's state
	LONG lParentStyle = GetWindowLong(hParentWnd, GWL_STYLE);
	if(!(WS_VISIBLE & lParentStyle))	// Parent invisible
		m_Status = SS_ENABLED;
	else if((WS_MAXIMIZE | WS_MINIMIZE) & lParentStyle)	// Parent visible but does not need shadow
		m_Status = SS_ENABLED | SS_PARENTVISIBLE;
	else	// Show the shadow
	{
		m_Status = SS_ENABLED | SS_VISABLE | SS_PARENTVISIBLE;
		::ShowWindow(m_hWnd, SW_SHOWNA);
		Update(hParentWnd);
	}

	// Replace the original WndProc of parent window to steal messages
	m_OriParentProc = GetWindowLong(hParentWnd, GWL_WNDPROC);

#pragma warning(disable: 4311)	// temporrarily disable the type_cast warning in Win32
	SetWindowLong(hParentWnd, GWL_WNDPROC, (LONG)ParentProc);
#pragma warning(default: 4311)

}

LRESULT CALLBACK CWndShadow::ParentProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	CWndShadow *pThis = s_Shadowmap[hwnd];

	switch(uMsg)
	{
	case WM_MOVE:
		if (pThis != NULL)
		{
			if(pThis->m_Status & SS_VISABLE)
			{
				RECT WndRect;
				GetWindowRect(hwnd, &WndRect);
				SetWindowPos(pThis->m_hWnd, 0, WndRect.left + - pThis->m_nSize, WndRect.top - pThis->m_nSize, 0, 0, SWP_NOSIZE | SWP_NOACTIVATE);
			}
		}
		break;

	case WM_SIZE:
		if (pThis != NULL)
		{
			if(pThis->m_Status & SS_ENABLED)
			{
				if(SIZE_MAXIMIZED == wParam || SIZE_MINIMIZED == wParam)
				{
					::ShowWindow(pThis->m_hWnd, SW_HIDE);
					pThis->m_Status &= ~SS_VISABLE;
				}
				else if(pThis->m_Status & SS_PARENTVISIBLE)	// Parent maybe resized even if invisible
				{
					// Awful! It seems that if the window size was not decreased
					// the window region would never be updated until WM_PAINT was sent.
					// So do not Update() until next WM_PAINT is received in this case
					if(LOWORD(lParam) > LOWORD(pThis->m_WndSize) || HIWORD(lParam) > HIWORD(pThis->m_WndSize))
						pThis->m_bUpdate = true;
					else
						pThis->Update(hwnd);
					if(!(pThis->m_Status & SS_VISABLE))
					{
						::ShowWindow(pThis->m_hWnd, SW_SHOWNA);
						pThis->m_Status |= SS_VISABLE;
					}
				}
				pThis->m_WndSize = lParam;
			}
		}
		break;

	case WM_PAINT:
		{
			if (pThis != NULL)
			{
				if(pThis->m_bUpdate)
				{
					pThis->Update(hwnd);
					pThis->m_bUpdate = false;
				}
			}
			break;
		}

		// In some cases of sizing, the up-right corner of the parent window region would not be properly updated
		// Update() again when sizing is finished
	case WM_EXITSIZEMOVE:
		if (pThis != NULL)
		{
			if(pThis->m_Status & SS_VISABLE)
			{
				pThis->Update(hwnd);
			}
		}
		break;

	case WM_SHOWWINDOW:
		if (pThis != NULL)
		{
			if(pThis->m_Status & SS_ENABLED)
			{
				if(!wParam)	// the window is being hidden
				{
					::ShowWindow(pThis->m_hWnd, SW_HIDE);
					pThis->m_Status &= ~(SS_VISABLE | SS_PARENTVISIBLE);
				}
				else if(!(pThis->m_Status & SS_PARENTVISIBLE))
				{
					//pThis->Update(hwnd);
					pThis->m_bUpdate = true;
					::ShowWindow(pThis->m_hWnd, SW_SHOWNA);
					pThis->m_Status |= SS_VISABLE | SS_PARENTVISIBLE;
				}
			}
		}
		break;

	case WM_DESTROY:
		if (pThis != NULL)
		{
			DestroyWindow(pThis->m_hWnd);	// Destroy the shadow
		}
		break;
		
	case WM_NCDESTROY:
		if (pThis != NULL)
		{
			s_Shadowmap.erase(hwnd);	// Remove this window and shadow from the map
		}
		break;
	}


#pragma warning(disable: 4312)	// temporrarily disable the type_cast warning in Win32
	// Call the default(original) window procedure for other messages or messages processed but not returned
	return ((WNDPROC)pThis->m_OriParentProc)(hwnd, uMsg, wParam, lParam);
#pragma warning(default: 4312)

}

void CWndShadow::Update(HWND hParent)
{
	RECT WndRect;
	GetWindowRect(hParent, &WndRect);
	//
	int nParentWndWidth = WndRect.right - WndRect.left;
	int nParentWndHeight = WndRect.bottom - WndRect.top;
	int nShadWndWid = nParentWndWidth + m_nSize * 2;
	int nShadWndHei = nParentWndHeight + m_nSize * 2;

	BLENDFUNCTION myBlendFunction = {0};
	myBlendFunction.AlphaFormat = AC_SRC_ALPHA;
	myBlendFunction.SourceConstantAlpha = 255;


	// Create the alpha blending bitmap
	BITMAPINFO bmi;        // bitmap header

	ZeroMemory(&bmi, sizeof(BITMAPINFO));
	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth = nShadWndWid;
	bmi.bmiHeader.biHeight = nShadWndHei;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = 32;         // four 8-bit components
	bmi.bmiHeader.biCompression = BI_RGB;
	bmi.bmiHeader.biSizeImage = nShadWndWid * nShadWndHei * 4;

	BYTE *pvBits;          // pointer to DIB section
	HBITMAP hbitmap = CreateDIBSection(NULL, &bmi, DIB_RGB_COLORS, (void **)&pvBits, NULL, 0);

	if (pvBits != NULL)
	{
		ZeroMemory(pvBits, bmi.bmiHeader.biSizeImage);
	}

	HDC hMemDC = CreateCompatibleDC(NULL);
	HBITMAP hOriBmp = (HBITMAP)SelectObject(hMemDC, hbitmap);

	if (m_pShadowDrawImage != NULL)
	{
		DrawBackground(hMemDC, nShadWndWid, nShadWndHei, m_pShadowDrawImage);
	}
	
	POINT ptDst = {WndRect.left  - m_nSize, WndRect.top - m_nSize};
	POINT ptSrc = {0, 0};
	SIZE WndSize = {nShadWndWid, nShadWndHei};
	BLENDFUNCTION blendPixelFunction= { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };

	MoveWindow(m_hWnd, ptDst.x, ptDst.y, nShadWndWid, nShadWndHei, FALSE);

	BOOL bRet= s_UpdateLayeredWindow(m_hWnd, NULL, &ptDst, &WndSize, hMemDC,
		&ptSrc, 0, &blendPixelFunction, ULW_ALPHA);

	DeleteObject(hbitmap);
	DeleteDC(hMemDC);

}

// »æÖÆ±³¾°
void CWndShadow::DrawBackground(HDC hMemDC, int nWidth, int nHeight, CDrawImage *pDrawImage)
{
	HDC hTempDC = ::CreateCompatibleDC(hMemDC);
	//
	BLENDFUNCTION myBlendFunction = {0};
	myBlendFunction.AlphaFormat = AC_SRC_ALPHA;
	myBlendFunction.SourceConstantAlpha = 255;
	//
	int nAroundLeft = 0;
	int nAroundTop = 0;
	int nAroundWidth = nWidth;
	int nAroundHeight = nHeight;
	int nXOriginDest = 0;
	int nYOriginDest = 0;
	int nWidthDest = 0;
	int nHeightDest = 0;
	INT nHorPageNum = 0;
	int nUpLeft_WidthSrc = 0;
	int nUpLeft_HeightSrc = 0;
	int nDownRight_WidthSrc = 0;
	int nDownRight_HeightSrc = 0;
	//
	INT nImgWidth = pDrawImage->GetWidth();
	INT nImgHeight = pDrawImage->GetHeight();
	//
	nUpLeft_WidthSrc = 25;
	nUpLeft_HeightSrc = 25;
	nDownRight_WidthSrc = 25;
	nDownRight_HeightSrc = 25;
	//
	INT nMiddleWidth = nImgWidth - (nUpLeft_WidthSrc + nDownRight_WidthSrc);
	INT nMiddleHeight = nImgHeight - (nUpLeft_HeightSrc + nDownRight_HeightSrc);
	//
	INT nHorizontalAlignmentMode = 0;
	//
	INT nVerticalAlignmentMode = 0;
	nHorizontalAlignmentMode = 1;
	nVerticalAlignmentMode = 1;
	//
	AlphaBlend(hMemDC, 0, 0, nUpLeft_WidthSrc, nUpLeft_HeightSrc, pDrawImage->GetDC(), 0, 0, nUpLeft_WidthSrc, nUpLeft_HeightSrc, myBlendFunction);
	//
	nXOriginDest = (nAroundLeft + (nAroundWidth - nDownRight_WidthSrc));
	nYOriginDest = (nAroundTop);
	AlphaBlend(hMemDC, nXOriginDest, nYOriginDest, nDownRight_WidthSrc, nUpLeft_HeightSrc, pDrawImage->GetDC(), nImgWidth - nDownRight_WidthSrc, 0, nDownRight_WidthSrc, nUpLeft_HeightSrc, myBlendFunction);
	//
	nXOriginDest = (nAroundLeft);
	nYOriginDest = (nAroundTop + (nAroundHeight - nDownRight_HeightSrc));
	AlphaBlend(hMemDC, nXOriginDest, nYOriginDest, nUpLeft_WidthSrc, nDownRight_HeightSrc, pDrawImage->GetDC(), 0, nImgHeight - nDownRight_HeightSrc, nUpLeft_WidthSrc, nDownRight_HeightSrc, myBlendFunction);
	//
	nXOriginDest = (nAroundLeft + (nAroundWidth - nDownRight_WidthSrc));
	nYOriginDest = (nAroundTop + (nAroundHeight - nDownRight_HeightSrc));
	AlphaBlend(hMemDC, nXOriginDest, nYOriginDest, nDownRight_WidthSrc, nDownRight_HeightSrc, pDrawImage->GetDC(), nImgWidth - nDownRight_WidthSrc, nImgHeight - nDownRight_HeightSrc, nDownRight_WidthSrc, nDownRight_HeightSrc, myBlendFunction);
	//
	nXOriginDest = (nAroundLeft + nUpLeft_WidthSrc);
	nYOriginDest = (nAroundTop);
	nWidthDest = (nAroundWidth - (nUpLeft_WidthSrc + nDownRight_WidthSrc));
	nHeightDest = (nUpLeft_HeightSrc);
	RECT myUpMiddleRect = {0, 0, 0, 0};
	myUpMiddleRect.left = nUpLeft_WidthSrc;
	myUpMiddleRect.top = 0;
	myUpMiddleRect.right = nImgWidth - nDownRight_WidthSrc;
	myUpMiddleRect.bottom = nUpLeft_HeightSrc;
	//
	this->DrawPngHorizontalAlignment(hMemDC, pDrawImage->GetDC(), nHorizontalAlignmentMode, nXOriginDest, nYOriginDest, nWidthDest, nHeightDest, &myUpMiddleRect);
	//
	nXOriginDest = (nAroundLeft);
	nYOriginDest = (nAroundTop + nUpLeft_HeightSrc);
	nWidthDest = (nUpLeft_WidthSrc);
	nHeightDest = (nAroundHeight - (nUpLeft_HeightSrc + nDownRight_HeightSrc));
	RECT myMiddleLeftRect = {0, 0, 0, 0};
	myMiddleLeftRect.left = 0;
	myMiddleLeftRect.top = nUpLeft_HeightSrc;
	myMiddleLeftRect.right = nUpLeft_WidthSrc;
	myMiddleLeftRect.bottom = nImgHeight - (nDownRight_HeightSrc);
	//
	this->DrawPngVerticalAlignment(hMemDC, pDrawImage->GetDC(), nVerticalAlignmentMode, nXOriginDest, nYOriginDest, nWidthDest, nHeightDest, &myMiddleLeftRect);
	//
	nXOriginDest = (nAroundLeft + nUpLeft_WidthSrc);
	nYOriginDest = (nAroundTop + (nAroundHeight - nDownRight_HeightSrc));
	nWidthDest = (nAroundWidth - (nUpLeft_WidthSrc + nDownRight_WidthSrc));
	nHeightDest = (nDownRight_HeightSrc);
	RECT myDownMiddleRect = {0, 0, 0, 0};
	myDownMiddleRect.left = nUpLeft_WidthSrc;
	myDownMiddleRect.top = nImgHeight - nDownRight_HeightSrc;
	myDownMiddleRect.right = nImgWidth - nDownRight_WidthSrc;
	myDownMiddleRect.bottom = nImgHeight;
	//
	this->DrawPngHorizontalAlignment(hMemDC, pDrawImage->GetDC(), nHorizontalAlignmentMode, nXOriginDest, nYOriginDest, nWidthDest, nHeightDest, &myDownMiddleRect);
	//
	nXOriginDest = (nAroundLeft + (nAroundWidth - nDownRight_WidthSrc));
	nYOriginDest = (nAroundTop + nUpLeft_HeightSrc);
	nWidthDest = (nDownRight_WidthSrc);
	nHeightDest = (nAroundHeight - (nUpLeft_HeightSrc + nDownRight_HeightSrc));
	RECT myMiddleRightRect = {0, 0, 0, 0};
	myMiddleRightRect.left = nImgWidth - nDownRight_WidthSrc;
	myMiddleRightRect.top = nUpLeft_HeightSrc;
	myMiddleRightRect.right = nImgWidth;
	myMiddleRightRect.bottom = nImgHeight - nDownRight_HeightSrc;
	//
	this->DrawPngVerticalAlignment(hMemDC, pDrawImage->GetDC(), nVerticalAlignmentMode, nXOriginDest, nYOriginDest, nWidthDest, nHeightDest, &myMiddleRightRect);
	//
	nXOriginDest = (nAroundLeft + nUpLeft_WidthSrc);
	nYOriginDest = (nAroundTop + nUpLeft_HeightSrc);
	nWidthDest = (nAroundWidth - (nUpLeft_WidthSrc + nDownRight_WidthSrc));
	nHeightDest = (nAroundHeight - (nUpLeft_HeightSrc + nDownRight_HeightSrc));
	//
	RECT myMiddleMiddleRect = {0, 0, 0, 0};
	myMiddleMiddleRect.left = nUpLeft_WidthSrc;
	myMiddleMiddleRect.top = nUpLeft_HeightSrc;
	myMiddleMiddleRect.right = nImgWidth - nDownRight_WidthSrc;
	myMiddleMiddleRect.bottom = nImgHeight - nDownRight_HeightSrc;
	this->DrawPngHorizontalVerticalAlignment(hMemDC, pDrawImage->GetDC(), nHorizontalAlignmentMode, nVerticalAlignmentMode, nXOriginDest, nYOriginDest, nWidthDest, nHeightDest, &myMiddleMiddleRect);
	////
	::DeleteDC(hTempDC);
}


// »æÖÆ±³¾°
void CWndShadow::DrawPngHorizontalAlignment(HDC hMemDC, HDC hTempDC, INT nHorizontalAlignmentMode, INT nXOriginDest, INT nYOriginDest, INT nWidthDest, INT nHeightDest, RECT *pDrawRect)
{
	//
	BLENDFUNCTION myBlendFunction = {0};
	myBlendFunction.AlphaFormat = AC_SRC_ALPHA;
	myBlendFunction.SourceConstantAlpha = 255;
	int nWidthSrc = pDrawRect->right - pDrawRect->left;
	int nHeightSrc = pDrawRect->bottom - pDrawRect->top;
	//
	if (nHorizontalAlignmentMode == 1)
	{
		//
		INT nTempLeftDest = 0;
		INT nTempTopDest = 0;
		INT nTempWidthDest = 0;
		INT nTempHeightDest = 0;
		INT nTempWidthSrc = 0;
		INT nTempHeightSrc = 0;
		INT nHorPageNum = 0;
		if ((nWidthDest % nWidthSrc) == 0)
		{
			nHorPageNum = nWidthDest / nWidthSrc;
		}
		else
		{
			nHorPageNum = nWidthDest / nWidthSrc + 1;
		}
		nTempHeightDest = nHeightSrc;
		nTempHeightSrc = nHeightSrc;
		for (int i = 0 ; i < nHorPageNum; i++)
		{
			nTempLeftDest = nXOriginDest + (nWidthSrc * i);
			nTempTopDest = nYOriginDest;
			if (i == (nHorPageNum - 1))
			{
				nTempWidthDest = nWidthDest - (nWidthSrc * i);
				nTempWidthSrc = nTempWidthDest;
			}
			else
			{
				nTempWidthDest = nWidthSrc;
				nTempWidthSrc = nWidthSrc;
			}
			AlphaBlend(hMemDC, nTempLeftDest, nTempTopDest, nTempWidthDest, nTempHeightDest, hTempDC, pDrawRect->left, pDrawRect->top, nTempWidthSrc, nTempHeightSrc, myBlendFunction);
		}
	}
	else
	{
		AlphaBlend(hMemDC, nXOriginDest, nYOriginDest, nWidthDest, nHeightDest, hTempDC, pDrawRect->left, pDrawRect->top, nWidthSrc, nHeightSrc, myBlendFunction);
	}
}

// »æÖÆ±³¾°
void CWndShadow::DrawPngVerticalAlignment(HDC hMemDC, HDC hTempDC, INT nVerticalAlignment, INT nXOriginDest, INT nYOriginDest, INT nWidthDest, INT nHeightDest, RECT *pDrawRect)
{
	//
	BLENDFUNCTION myBlendFunction = {0};
	myBlendFunction.AlphaFormat = AC_SRC_ALPHA;
	myBlendFunction.SourceConstantAlpha = 255;
	int nWidthSrc = pDrawRect->right - pDrawRect->left;
	int nHeightSrc = pDrawRect->bottom - pDrawRect->top;
	//
	if (nVerticalAlignment == 1)
	{
		//
		INT nTempLeftDest = 0;
		INT nTempTopDest = 0;
		INT nTempWidthDest = 0;
		INT nTempHeightDest = 0;
		INT nTempWidthSrc = 0;
		INT nTempHeightSrc = 0;
		INT nVerPageNum = 0;
		if ((nHeightDest % nHeightSrc) == 0)
		{
			nVerPageNum = nHeightDest / nHeightSrc;
		}
		else
		{
			nVerPageNum = nHeightDest / nHeightSrc + 1;
		}
		nTempWidthSrc = nWidthSrc;
		nTempWidthDest = nWidthSrc;
		for (int i = 0 ; i < nVerPageNum; i++)
		{
			nTempLeftDest = nXOriginDest;
			nTempTopDest = nYOriginDest + (nHeightSrc * i);
			if (i == (nVerPageNum - 1))
			{
				nTempHeightDest = nHeightDest - (nHeightSrc * i);
				nTempHeightSrc = nTempHeightDest;
			}
			else
			{
				nTempHeightDest = nHeightSrc;
				nTempHeightSrc = nHeightSrc;
			}
			AlphaBlend(hMemDC, nTempLeftDest, nTempTopDest, nTempWidthDest, nTempHeightDest, hTempDC, pDrawRect->left, pDrawRect->top, nTempWidthSrc, nTempHeightSrc, myBlendFunction);
		}
	}
	else
	{
		AlphaBlend(hMemDC, nXOriginDest, nYOriginDest, nWidthDest, nHeightDest, hTempDC, pDrawRect->left, pDrawRect->top, nWidthSrc, nHeightSrc, myBlendFunction);
	}
}

// »æÖÆ±³¾°
void CWndShadow::DrawPngHorizontalVerticalAlignment(HDC hMemDC, HDC hTempDC, INT nHorizontalAlignmentMode, INT nVerticalAlignmentMode, INT nXOriginDest, INT nYOriginDest, INT nWidthDest, INT nHeightDest, RECT *pDrawRect)
{
	//
	BLENDFUNCTION myBlendFunction = {0};
	myBlendFunction.AlphaFormat = AC_SRC_ALPHA;
	myBlendFunction.SourceConstantAlpha = 255;
	int nWidthSrc = pDrawRect->right - pDrawRect->left;
	int nHeightSrc = pDrawRect->bottom - pDrawRect->top;
	//
	if (nHorizontalAlignmentMode == 1 && nVerticalAlignmentMode == 1)
	{
		//
		INT nTempLeftDest = 0;
		INT nTempTopDest = 0;
		INT nTempWidthDest = 0;
		INT nTempHeightDest = 0;
		INT nTempWidthSrc = 0;
		INT nTempHeightSrc = 0;
		INT nHorPageNum = 0;
		INT nVerPageNum = 0;
		if ((nWidthDest % nWidthSrc) == 0)
		{
			nHorPageNum = nWidthDest / nWidthSrc;
		}
		else
		{
			nHorPageNum = nWidthDest / nWidthSrc + 1;
		}
		if ((nHeightDest % nHeightSrc) == 0)
		{
			nVerPageNum = nHeightDest / nHeightSrc;
		}
		else
		{
			nVerPageNum = nHeightDest / nHeightSrc + 1;
		}
		nTempHeightDest = nHeightSrc;
		nTempHeightSrc = nHeightSrc;
		for (int i = 0 ; i < nHorPageNum; i++)
		{
			for (int j = 0 ; j < nVerPageNum; j++)
			{
				nTempLeftDest = nXOriginDest + (nWidthSrc * i);
				nTempTopDest = nYOriginDest + (nHeightSrc * j);
				if (i == (nHorPageNum - 1))
				{
					nTempWidthDest = nWidthDest - (nWidthSrc * i);
					nTempWidthSrc = nTempWidthDest;
				}
				else
				{
					nTempWidthDest = nWidthSrc;
					nTempWidthSrc = nWidthSrc;
				}
				if (j == (nVerPageNum - 1))
				{
					nTempHeightDest = nHeightDest - (nHeightSrc * j);
					nTempHeightSrc = nTempHeightDest;
				}
				else
				{
					nTempHeightDest = nHeightSrc;
					nTempHeightSrc = nTempHeightDest;
				}
				AlphaBlend(hMemDC, nTempLeftDest, nTempTopDest, nTempWidthDest, nTempHeightDest, hTempDC, pDrawRect->left, pDrawRect->top, nTempWidthSrc, nTempHeightSrc, myBlendFunction);
			}
		}
	}
	else
	{
		AlphaBlend(hMemDC, nXOriginDest, nYOriginDest, nWidthDest, nHeightDest, hTempDC, pDrawRect->left, pDrawRect->top, nWidthSrc, nHeightSrc, myBlendFunction);
	}
}
