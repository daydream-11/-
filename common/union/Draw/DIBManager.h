#ifndef __DIB_MANAGER_H__
#define __DIB_MANAGER_H__

class CDIBManager
{
public:
	CDIBManager(void);
	CDIBManager(HDC hdc, int cx, int cy);
	~CDIBManager(void);
	BOOL IsValid();
	void Clear();
	BOOL Create(HDC hdc, int cx, int cy);
	void Flush(DWORD dwVal);
	BOOL Resize(int cx, int cy, HBITMAP * pOld = NULL);
	HDC GetSafeHdc();
	BYTE * GetBits();
	const BITMAPINFO* GetBitmapInfo();
	int GetSize();
	int GetWidth();
	int GetHeight();
	HBITMAP GetHBitmap();
	BOOL Backup();
	BOOL Restore();
	BOOL ClearBackup();
	BOOL IsBackup();
protected:
	HDC m_hMemDC;
	HBITMAP m_hMemBmp;
	HBITMAP m_hOldBmp;
	BITMAPINFOHEADER m_bmpHeader;
	BYTE * m_pBits;
	BYTE * m_pBackup;
};

#endif	// __DIB_MANAGER_H__
