#if !defined(AFX_SOCKETCLIENT_H__F25829F8_EFFB_4D11_9D58_889B45139518__INCLUDED_)
#define AFX_SOCKETCLIENT_H__F25829F8_EFFB_4D11_9D58_889B45139518__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WnSocketClient.h : header file
//

//
// 注意：
// 在 InitInstance() 函数中调用 AfxSocketInit();函数来初始化网络接口，在
// ExitInstance() 函数中调用 WSACleanup (); 关闭网络接口
//
/////////////////////////////////////////////////////////////////////////////
// CSocketClient command target

#include <afxsock.h>

#define MAX_BUFFER_SIZE			4096		// 默认缓冲大小
#define TEMP_SAVE_BUFFER_SIZE		(10*MAX_BUFFER_SIZE)
// 当下载的数据达到这个数的时候才保存到文件中
#define WRITE_TEMP_SAVE_MIN_BYTES	(TEMP_SAVE_BUFFER_SIZE - 2*MAX_BUFFER_SIZE)

class CSocketClient : public CSocket
{
// Attributes
public:
	BOOL IsConnected();
// Operations
public:
	CSocketClient ();
	virtual ~CSocketClient();
	CString GetDigitStrAtHead ( LPCTSTR lpszStr );
	int GetResponse ( CString *pcsResponseStr=NULL, BOOL bBlock=TRUE );
	BOOL GetResponse ( int nVerifyCode, CString *pcsResponseStr=NULL );
	CString GetResponseHistoryString () { return m_csResponseHistoryString; }
	void ClearResponseHistoryString () { m_csResponseHistoryString.Empty(); }

// Overrides
public:
	int m_nIndex;
	void Disconnect();
	int Receive ( char *szBuf, int size, BOOL bBlock=TRUE );
	BOOL GetIPAndPortByPasvString ( LPCTSTR lpszPasvString, OUT CString &csIP, OUT USHORT &nPort );
	void SetEventOfEndModule ( HANDLE hEvtEndModule );
	BOOL Send ( char *data, int size );
	BOOL SendString(LPCTSTR lpszData);
	BOOL Connect ( LPCTSTR lpszHost, USHORT nPort );
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSocketClient)
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CSocketClient)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
	virtual BOOL ConnectHelper(const SOCKADDR* lpSockAddr, int nSockAddrLen);
private:
	BOOL PumpMessagesMy(UINT uStopFlag);
	CString m_csResponseHistoryString;
	HANDLE m_hEvtEndModule;
	BOOL m_bConnected;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SOCKETCLIENT_H__F25829F8_EFFB_4D11_9D58_889B45139518__INCLUDED_)
