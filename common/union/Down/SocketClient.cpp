// WnSocketClient.cpp : implementation file
//

#include "stdafx.h"
#include "SocketClient.h"
#include "DownStruct.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#pragma comment(lib, "wsock32.lib")
#define _afxSockThreadState AfxGetModuleThreadState()
#define _AFX_SOCK_THREAD_STATE AFX_MODULE_THREAD_STATE
#define   WM_SOCKET_NOTIFY		0x0373   
#define   WM_SOCKET_DEAD		0x0374 

CString GetOneLine(CString &str)
{
	int nPos = str.Find(_T("\r\n"), 0);
	if ( nPos < 0 ) 
	{
		return _T("");
	}
	CString csOneLine = str.Left (nPos);
	str = str.Mid (nPos + 2);
	return csOneLine;
}


/////////////////////////////////////////////////////////////////////////////
// CSocketClient

CSocketClient::CSocketClient ()
	: m_hEvtEndModule ( NULL )
	, m_bConnected ( FALSE )
	, m_nIndex ( -1 )
{
}

CSocketClient::~CSocketClient()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CSocketClient, CSocket)
	//{{AFX_MSG_MAP(CSocketClient)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CSocketClient member functions

BOOL CSocketClient::IsConnected() 
{
	return m_bConnected; 
}

CString CSocketClient::GetDigitStrAtHead ( LPCTSTR lpszStr )
{
	if ( !lpszStr ) 
	{
		return _T("");
	}
	CString csStr = lpszStr;
	csStr.TrimLeft(); csStr.TrimRight();
	CString csDigitStr;
	for ( int i=0; isdigit ( (int)csStr[i] ); i++ )
	{
		csDigitStr += csStr[i];
	}

	return csDigitStr;
}

//
// return : ------------------------------------------
//		> 0		-	回应代码
//		= 0		-	未读到数据
//		= -1	-	网络出错
//
int CSocketClient::GetResponse ( CString *pcsResponseStr/*=NULL*/, BOOL bBlock/*=TRUE*/ )
{
	if ( pcsResponseStr ) 
	{
		*pcsResponseStr = _T("");
	}
	CString csOneLine = GetOneLine ( m_csResponseHistoryString );
	if ( csOneLine.IsEmpty () )
	{
		char szRecvBuf[MAX_BUFFER_SIZE] = {0};
		int nRet = Receive ( szRecvBuf, sizeof(szRecvBuf), bBlock );
		if ( nRet <= 0 )
		{
			if ( nRet < 0 ) 
			{
				//Log ( L_WARNING, "(%d) Receive response data failed", m_nIndex );
			}
			return nRet;
		}
		m_csResponseHistoryString += szRecvBuf;
		csOneLine = GetOneLine ( m_csResponseHistoryString );
		if ( csOneLine.IsEmpty () ) return -1;
	}

	if ( pcsResponseStr ) *pcsResponseStr = csOneLine;
	CString csRetCode = GetDigitStrAtHead ( csOneLine );

	//Log ( L_NORMAL, "(%d) FTP server response: %s", m_nIndex, csOneLine );
	return _ttoi( csRetCode );
}

BOOL CSocketClient::GetResponse ( int nVerifyCode, CString *pcsResponseStr/*=NULL*/ )
{
	CString csResponseStr;
	int nResponseCode = GetResponse ( &csResponseStr );
	if ( pcsResponseStr ) *pcsResponseStr = csResponseStr;
	if ( nResponseCode != nVerifyCode )
	{
		CString csMsg;
		csMsg.Format (_T("Receive error response code : %s"), csResponseStr );
		return FALSE;
	}
	return TRUE;
}

BOOL CSocketClient::SendString(LPCTSTR lpszData)
{
	// 格式化
	char szDataBuf[MAX_BUFFER_SIZE] = {'0'};
	#if _UNICODE
		int nNum = WideCharToMultiByte(CP_OEMCP, 0, lpszData, -1, 0, 0, 0, 0);
		WideCharToMultiByte(CP_OEMCP, NULL, lpszData, -1, szDataBuf, nNum, NULL, FALSE);
	#else
		sprintf(szDataBuf, "%s", lpszData);
	#endif
	return Send(szDataBuf, strlen(szDataBuf) );
}

BOOL CSocketClient::Send(char *data, int size)
{
	ASSERT ( m_hEvtEndModule && m_hEvtEndModule != INVALID_HANDLE_VALUE );
	ASSERT ( m_hSocket != INVALID_SOCKET );
	if ( !data || size < 1 ) return TRUE;

	int nRemainBytes = size;
	int nSentTotalBytes = 0;
	int nSendFailedCount = 0;
	while ( nRemainBytes > 0 )
	{
		int nSentBytes = CSocket::Send ( data+nSentTotalBytes, nRemainBytes );
		if ( nSentBytes < 0 )
		{
			nSendFailedCount ++;
			if ( nSendFailedCount > 10 )
			{
				//Log ( L_WARNING, "(%d) Send net data block failed", m_nIndex );
				m_bConnected = FALSE;
				return FALSE;
			}
			else
			{
				SLEEP_RETURN ( 100 );
			}
		}
		else
		{
			nRemainBytes -= nSentBytes;
			nSentTotalBytes += nSentBytes;
			nSendFailedCount = 0;
		}
	}

	return TRUE;

}

void CSocketClient::SetEventOfEndModule(HANDLE hEvtEndModule)
{
	m_hEvtEndModule = hEvtEndModule;
	ASSERT ( m_hEvtEndModule && m_hEvtEndModule != INVALID_HANDLE_VALUE );
}

// 从类似 "(192,168,0,2,4,31)" 字符串中得到IP地址和端口号
//
BOOL CSocketClient::GetIPAndPortByPasvString(LPCTSTR lpszPasvString, OUT CString &csIP, OUT USHORT &nPort)
{
	if ( !lpszPasvString ) return FALSE;
	TCHAR *p = _tcschr ((TCHAR*)lpszPasvString, _T('('));
	if ( !p )
	{
		return FALSE;
	}
	CString csPasvStr = p+1, csTemp;
	int nPosStart = 0, nPosEnd = 0;
	int nMultiple = 0, nMantissa = 0;
	for ( int i=0; ; i++ )
	{
		nPosEnd = csPasvStr.Find (_T(","), nPosStart );
		if ( nPosEnd < 0 )
		{
			if ( i == 5 )
			{
				nPosEnd = csPasvStr.Find (_T(")"), nPosStart );
				csTemp = csPasvStr.Mid ( nPosStart, nPosEnd-nPosStart );
				nMantissa = _ttoi ( csTemp );
				break;
			}
			else return FALSE;
		}
		csTemp = csPasvStr.Mid ( nPosStart, nPosEnd-nPosStart );
		csTemp.TrimLeft(); csTemp.TrimRight();
		if ( i < 4 )
		{
			if ( !csIP.IsEmpty () ) csIP += _T(".");
			csIP += csTemp;
		}
		else if ( i == 4 )
		{
			nMultiple = _ttoi ( csTemp );
		}
		else return FALSE;
		nPosStart = nPosEnd + 1;
	}
	nPort = nMultiple*256 + nMantissa;

	return TRUE;
}

//
// return : -----------------------------------------------------------
//		>= 0	-	收到的字节数
//		-1		-	失败
//
int CSocketClient::Receive(char *szBuf, int size, BOOL bBlock/*=TRUE*/)
{
	if ( !szBuf || size < 0 ) return -1;
	int nReadSize = 0;
	if ( bBlock )
	{
		nReadSize = CSocket::Receive ( szBuf, size );
		if ( nReadSize <= 0 ) nReadSize = -1;
	}
	else
	{
		nReadSize = CAsyncSocket::Receive ( szBuf, size );
		if ( nReadSize < 0 )
		{
			if ( WSAEWOULDBLOCK  == GetLastError () )
				nReadSize = 0;
			else
				nReadSize = -1;
		}
	}

	if ( nReadSize == -1 )
	{
		m_bConnected = FALSE;
	}
	return nReadSize;
}

void CSocketClient::Disconnect()
{
	CancelBlockingCall();
	Close();
	m_bConnected = FALSE;
}

BOOL CSocketClient::Connect(LPCTSTR lpszHost, USHORT nPort)
{
	if (lpszHost == NULL)
	{
		return FALSE;
	}
	int nTextLen = (int)_tcslen(lpszHost);
	if (nTextLen <= 0)
	{
		return FALSE;
	}
	if (nPort < 1)
	{
		return FALSE;
	}
	Close();
	if (!Create())
	{
		return FALSE;
	}
	m_bConnected = CSocket::Connect(lpszHost, nPort);
	if (!m_bConnected)
	{
		return FALSE;
	}
	return TRUE;
}

//
// 改写这个虚函数，可以在调用 CancelBlockingCall() 函数时立即终止连接
//
BOOL CSocketClient::ConnectHelper(const SOCKADDR *lpSockAddr, int nSockAddrLen)
{
	if (!CAsyncSocket::ConnectHelper(lpSockAddr, nSockAddrLen))
	{
		if (GetLastError() == WSAEWOULDBLOCK)
		{
			while (PumpMessagesMy(FD_CONNECT))
			{
				if (m_nConnectError != -1)
				{
					WSASetLastError(m_nConnectError);
					return (m_nConnectError == 0);
				}
			}
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSocketClient::PumpMessagesMy(UINT uStopFlag)
{
	// The same socket better not be blocking in more than one place.
	ASSERT(m_pbBlocking == NULL);

	_AFX_SOCK_THREAD_STATE* pState = _afxSockThreadState;

	ASSERT(pState->m_hSocketWindow != NULL);

	BOOL bBlocking = TRUE;
	m_pbBlocking = &bBlocking;
	CWinThread* pThread = AfxGetThread();

	// This is not a timeout in the WinSock sense, but more
	// like a WM_KICKIDLE to keep message pumping alive
	UINT nTimerID = ::SetTimer(pState->m_hSocketWindow, 1, m_nTimeOut, NULL);

	if (nTimerID == 0)
		AfxThrowResourceException();

	BOOL bPeek = TRUE;

	while (bBlocking)
	{
		TRY
		{
			MSG msg;
			if ( ::PeekMessage(&msg, pState->m_hSocketWindow,
				WM_SOCKET_NOTIFY, WM_SOCKET_DEAD, PM_REMOVE) )
			{
				if (msg.message == WM_SOCKET_NOTIFY && (SOCKET)msg.wParam == m_hSocket)
				{
					if (WSAGETSELECTEVENT(msg.lParam) == FD_CLOSE)
					{
						break;
					}
					if (WSAGETSELECTEVENT(msg.lParam) == uStopFlag)
					{
						if (uStopFlag == FD_CONNECT)
							m_nConnectError = WSAGETSELECTERROR(msg.lParam);
						break;
					}
				}
				if (msg.wParam != 0 || msg.lParam != 0)
					CSocket::AuxQueueAdd(msg.message, msg.wParam, msg.lParam);

				bPeek = TRUE;
			}
			else if ( ::PeekMessage(&msg, pState->m_hSocketWindow,
						WM_TIMER, WM_TIMER, PM_REMOVE) )
			{
				break;
			}

			if (bPeek && ::PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
			{
				if (OnMessagePending())
				{
					// allow user-interface updates
					pThread->OnIdle(-1);
				}
				else
				{
					bPeek = FALSE;
				}
			}
			else
			{
				// no work to do -- allow CPU to sleep
				SLEEP_RETURN ( 100 );
				bPeek = TRUE;
			}
		}
		CATCH_ALL(e)
		{
			TRACE0("Error: caught exception in PumpMessage - continuing.\n");
			e->Delete ();
			bPeek = TRUE;
		}
		END_CATCH_ALL
	}

	::KillTimer(pState->m_hSocketWindow, nTimerID);

	if (!bBlocking)
	{
		WSASetLastError(WSAEINTR);
		return FALSE;
	}
	m_pbBlocking = NULL;

	::PostMessage(pState->m_hSocketWindow, WM_SOCKET_NOTIFY, 0, 0);

	return TRUE;

}
