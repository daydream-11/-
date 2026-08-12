#ifndef __DRAW_IMAGE_H__
#define __DRAW_IMAGE_H__

class CDrawImage
{
private:

	BOOL m_bAlphaChannel;
	int m_nWidth;
	int m_nHeight;
	void *m_pDIBManager;

public:
	CDrawImage(void);
	~CDrawImage(void);

public:
	BOOL InitDrawImage();
	BOOL LoadResImage(const TCHAR * pszImageFile, HMODULE hResModule, const TCHAR * strResourceType);
	BOOL LoadImage(LPCTSTR lpszFileName);
	BOOL LoadImage(HGLOBAL hGlobal, DWORD dwSize);
	void ClearImage();
	BOOL PrepareMemDC(int cx, int cy);
	BOOL EnableAlphaChannel(BOOL bModifyRgb = TRUE);
	int GetWidth();
	int GetHeight();
	BOOL IsAlphaChannelValid();
	HDC GetDC();
};

#endif	// __DRAW_IMAGE_H__
