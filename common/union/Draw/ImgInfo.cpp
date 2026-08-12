#include "StdAfx.h"
#include "ImgInfo.h"

CImgInfo::CImgInfo(void)
{
	m_nLeftSrc = 0;
	m_nTopSrc = 0;
	m_nWidthSrc = 0;
	m_nHeightSrc = 0;
	m_nLeftSrcHover = 0;
	m_nTopSrcHover = 0;
	m_nWidthSrcHover = 0;
	m_nHeightSrcHover = 0;
	m_nLeftSrcDown = 0;
	m_nTopSrcDown = 0;
	m_nWidthSrcDown = 0;
	m_nHeightSrcDown = 0;
	m_nImgWidth = 0;
	m_nImgHeight = 0;
	m_hBitmap = NULL;
	m_pImage = NULL;
	m_hGlobal = NULL;
	m_bHaveDeleteImage = TRUE;
}

CImgInfo::~CImgInfo(void)
{
	ClearImgInfo();	
}

/**********************************************************************
* 函数名称： ClearImgInfo
* 功能描述： 
* 输入参数： 
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2008/11/24		V1.0	    huanggenping	创建版本
***********************************************************************/
void CImgInfo::ClearImgInfo(void)
{
	if (m_hBitmap != NULL)
	{
		::DeleteObject(m_hBitmap);
		m_hBitmap = NULL;
	}
	if (m_bHaveDeleteImage)
	{
		if (m_pImage != NULL)
		{
			Image *pImage = (Image*)m_pImage;
			delete pImage;
			pImage = NULL;
			m_pImage = NULL;
		}
	}
	if (m_hGlobal != NULL)
	{
		::GlobalFree(m_hGlobal);
		m_hGlobal = NULL;
	}
}

/**********************************************************************
* 函数名称： LoadResBmp
* 功能描述： 获取加载图片句柄
* 输入参数： 
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2008/11/24		V1.0	    huanggenping	创建版本
***********************************************************************/
BOOL CImgInfo::LoadResBmp(const TCHAR * pszImageFile)
{
	HBITMAP hBitmap = NULL;//LoadBitmap(g_pGlobals->GetInstance(), pszImageFile);
	if (hBitmap == NULL)
	{
		return FALSE;
	}
	m_hBitmap = hBitmap;
	BITMAP bitMap;
	::GetObject(m_hBitmap, sizeof(bitMap), &bitMap);
	m_nImgWidth = bitMap.bmWidth;
	m_nImgHeight = bitMap.bmHeight;
	return TRUE;
}


/**********************************************************************
* 函数名称： LoadBmpImage
* 功能描述： 获取加载图片句柄
* 输入参数： 
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2008/11/24		V1.0	    huanggenping	创建版本
***********************************************************************/
BOOL CImgInfo::LoadBmpImage(const TCHAR * pszImageFile)
{
	HBITMAP hBitmap = (HBITMAP)LoadImage(NULL, pszImageFile, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	if (hBitmap == NULL)
	{
		return FALSE;
	}
	m_hBitmap = hBitmap;
	BITMAP bitMap;
	::GetObject(m_hBitmap, sizeof(bitMap), &bitMap);
	m_nImgWidth = bitMap.bmWidth;
	m_nImgHeight = bitMap.bmHeight;
	return TRUE;
}

/**********************************************************************
* 函数名称： LoadResImage
* 功能描述： 获取加载图片句柄
* 输入参数： 
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2008/11/24		V1.0	    huanggenping	创建版本
***********************************************************************/
BOOL CImgInfo::LoadResImage(HINSTANCE hInstance, const TCHAR * pszImageFile)
{
	HRSRC  hRes = FindResource(hInstance, pszImageFile, _T("Pic"));
	if (hRes == NULL)
	{
		return FALSE;
	}
	HGLOBAL  hData = LoadResource(hInstance, hRes);
	LPVOID  lpData = LockResource(hData);
	DWORD dwSize = SizeofResource(hInstance, hRes);
	m_hGlobal = ::GlobalAlloc(GHND, dwSize); 
	void * pBuffer = ::GlobalLock(m_hGlobal);
	memcpy(pBuffer, lpData, dwSize);
	::GlobalUnlock(m_hGlobal);
	IStream* pStream; 
	CreateStreamOnHGlobal(m_hGlobal, TRUE, &pStream);
	Image *pImage = Image::FromStream(pStream, FALSE);
	if (pImage == NULL)
	{
		return FALSE;
	}
	m_nImgWidth = pImage->GetWidth();
	m_nImgHeight = pImage->GetHeight();
	m_pImage = pImage;
	return TRUE;
}

/**********************************************************************
* 函数名称： LoadPngImage
* 功能描述： 获取加载图片句柄
* 输入参数： 
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2008/11/24		V1.0	    huanggenping	创建版本
***********************************************************************/
BOOL CImgInfo::LoadPngImage(const TCHAR * pszImageFile)
{
	HANDLE hFile = ::CreateFile(pszImageFile, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if(hFile == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}
	int nFileSize = ::GetFileSize(hFile, NULL);
	m_hGlobal = ::GlobalAlloc(GHND, nFileSize); 
	void * pBuffer = ::GlobalLock(m_hGlobal);
	DWORD dwReadSize = 0;
	ReadFile(hFile, pBuffer, nFileSize, &dwReadSize, NULL);
	::GlobalUnlock(m_hGlobal);
	IStream* pStream; 
	CreateStreamOnHGlobal(m_hGlobal, TRUE, &pStream);
	Image *pImage = Image::FromStream(pStream, FALSE);
	CloseHandle(hFile);
	if (pImage == NULL)
	{
		return FALSE;
	}
	m_nImgWidth = pImage->GetWidth();
	m_nImgHeight = pImage->GetHeight();
	m_pImage = pImage;
	return TRUE;
}

/**********************************************************************
* 函数名称： LoadImgInfo
* 功能描述： 获取加载图片句柄
* 输入参数： 
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2008/11/24		V1.0	    huanggenping	创建版本
***********************************************************************/
BOOL CImgInfo::LoadImgInfo(const TCHAR * pszImageFile)
{
	BOOL bFlag = FALSE;
	bFlag = LoadPngImage(pszImageFile);
	if (!bFlag)
	{
		return LoadBmpImage(pszImageFile);
	}
	return TRUE;
}

/**********************************************************************
* 函数名称： SetImage
* 功能描述： 设置图片GDI+指针
* 输入参数： 
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2008/11/24		V1.0	    huanggenping	创建版本
***********************************************************************/
void CImgInfo::SetImage(void *pImage)
{
	m_pImage = pImage;
}

/**********************************************************************
* 函数名称： GetImage
* 功能描述： 图片GDI+指针
* 输入参数： 
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2008/11/24		V1.0	    huanggenping	创建版本
***********************************************************************/
void* CImgInfo::GetImage(void)
{
	if (m_pImage == NULL)
	{
		return NULL;
	}
	return m_pImage;
}

/**********************************************************************
* 函数名称： SetHaveDeleteImage
* 功能描述： 
* 输入参数： 
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2008/11/24		V1.0	    huanggenping	创建版本
***********************************************************************/
void CImgInfo::SetHaveDeleteImage(BOOL bHaveDeleteImage)
{
	m_bHaveDeleteImage = bHaveDeleteImage;
}