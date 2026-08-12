#ifndef __DRAW_PAINT_H__
#define __DRAW_PAINT_H__

class CDrawPaint
{
private:

	void *m_pDIBManager;
	RECT m_rtPaint;
	BOOL m_bValid;
	int	m_nWidth;
	int m_nHeight;
	COLORREF m_textColor;
public:
	CDrawPaint(void);
	~CDrawPaint(void);

public:
	BOOL InitDrawPaint(void);
	BOOL Create(int nCx, int nCy);
	BOOL Resize(int nCx, int nCy);
	void Clear();
	BOOL IsValid();
	HDC GetDC();
public:

	BOOL OnDrawText(HDC & hDC, HFONT & hFont, COLORREF textColor, int nX, int nY, LPCTSTR strDrawText, int nTextLen, int nAlpha);
	void OnRenderText(HDC hDC, HFONT & hFont, COLORREF textColor, LPCTSTR strDrawText, int nTextLen);
	void OnDrawLine(HDC & hDC, HPEN & hPen, int nX1, int nY1, int nX2, int nY2, int nAlpha);
	void OnRenderLine(HDC hDC, HPEN & hPen, int nX1, int nY1, int nX2, int nY2);
	//
	void OnDrawPrev(HDC & hDC, HBITMAP hBitmap, COLORREF colorRef, int nLeft, int nTop, int nAlpha);
	void OnRenderPrev(HDC hDC, HBITMAP hBitmap, COLORREF colorRef);
	//
	void OnDrawNext(HDC & hDC, HBITMAP hBitmap, COLORREF colorRef, int nLeft, int nTop, int nAlpha);
	void OnRenderNext(HDC hDC, HBITMAP hBitmap, COLORREF colorRef);
};

#endif	// __DRAW_PAINT_H__

