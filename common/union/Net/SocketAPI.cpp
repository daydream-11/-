/*********************************************************************
* 版权所有 (C)2008, 深圳市新飞杨数码科技有限公司。
* 
* 文件名称： SocketAPI.cpp
* 文件标识： 
* 内容摘要： 对网络socket进行一个简单的封装操作，针对Windows的操作系统
* 其它说明： 
* 当前版本： 1.0.20110723
* 作    者： huanggenping
* 完成日期： 2011-07-23
* 
* 修改记录1：
*    修改日期：
*    版 本 号：
*    修 改 人：
*    修改内容： 
* 修改记录2：…
**********************************************************************/

#include "stdafx.h"
#include "SocketAPI.h"

/** @name 公共成员变量 */////////////////////////////////////////////////////
/// @{


CHAR szError[ERROR_SIZE];

/// @}


/**********************************************************************
* 函数名称： GetLastErrorEx
* 功能描述： 
* 输入参数： 
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/03/23		V1.0	    huanggenping	创建版本
***********************************************************************/
BOOL SocketAPI::GetLastErrorEx() 
{
#if defined(__WINDOWS__)
	INT nError = WSAGetLastError();
	switch (nError) 
	{
	case WSANOTINITIALISED:
		{
			strncpy(szError, "WSANOTINITIALISED", ERROR_SIZE);
			break;
		}
	case WSAENETDOWN:
		{
			strncpy(szError, "WSAENETDOWN", ERROR_SIZE);
			break;
		}
	case WSAEAFNOSUPPORT:
		{
			strncpy(szError, "WSAEAFNOSUPPORT", ERROR_SIZE);
			break;
		}
	case WSAEINPROGRESS:
		{
			strncpy(szError, "WSAEINPROGRESS", ERROR_SIZE);
			break;
		}
	case WSAEMFILE:
		{
			strncpy(szError, "WSAEMFILE", ERROR_SIZE);
			break;
		}
	case WSAENOBUFS:
		{
			strncpy(szError, "WSAENOBUFS", ERROR_SIZE);
			break;
		}
	case WSAEPROTONOSUPPORT:
		{
			strncpy(szError, "WSAEPROTONOSUPPORT", ERROR_SIZE);
			break;
		}
	case WSAEPROTOTYPE:
		{
			strncpy(szError, "WSAEPROTOTYPE", ERROR_SIZE);
			break;
		}
	case WSAESOCKTNOSUPPORT:
		{
			strncpy(szError, "WSAESOCKTNOSUPPORT", ERROR_SIZE);
			break;
		}
	case WSAEADDRINUSE:
		{
			strncpy(szError, "WSAEADDRINUSE", ERROR_SIZE);
			break;
		}
	case WSAEINTR:
		{
			strncpy(szError, "WSAEINTR", ERROR_SIZE);
			break;
		}
	case WSAEALREADY:
		{
			strncpy(szError, "WSAEALREADY", ERROR_SIZE);
			break;
		}
	case WSAEADDRNOTAVAIL:
		{
			strncpy(szError, "WSAEADDRNOTAVAIL", ERROR_SIZE);
			break;
		}
	case WSAECONNREFUSED:
		{
			strncpy(szError, "WSAECONNREFUSED", ERROR_SIZE);
			break;
		}
	case WSAEFAULT:
		{
			strncpy(szError, "WSAEFAULT", ERROR_SIZE);
			break;
		}
	case WSAEINVAL:
		{
			strncpy(szError, "WSAEINVAL", ERROR_SIZE);
			break;
		}
	case WSAEISCONN:
		{
			strncpy(szError, "WSAEISCONN", ERROR_SIZE);
			break;
		}
	case WSAENETUNREACH:
		{
			strncpy(szError, "WSAENETUNREACH", ERROR_SIZE);
			break;
		}
	case WSAENOTSOCK:
		{
			strncpy(szError, "WSAENOTSOCK", ERROR_SIZE ) ;
			break;
		}
	case WSAETIMEDOUT:
		{
			strncpy(szError, "WSAETIMEDOUT", ERROR_SIZE);
			break;
		}
	case WSAEWOULDBLOCK:
		{
			strncpy(szError, "WSAEWOULDBLOCK", ERROR_SIZE);
			break;
		}
	case WSAEOPNOTSUPP:
		{
			strncpy(szError, "WSAEOPNOTSUPP", ERROR_SIZE);
			break ;
		}
	case WSAENOPROTOOPT:
		{
			strncpy(szError, "WSAENOPROTOOPT", ERROR_SIZE);
			break ;
		}
	case WSAENETRESET:
		{
			strncpy(szError, "WSAENETRESET", ERROR_SIZE);
			break ;
		}
	case WSAENOTCONN:
		{
			strncpy(szError, "WSAENOTCONN", ERROR_SIZE);
			break ;
		}
	case WSAEACCES : 
		{
			strncpy(szError, "WSAEACCES", ERROR_SIZE);
			break ;
		}
	case WSAESHUTDOWN:
		{
			strncpy(szError, "WSAESHUTDOWN", ERROR_SIZE);
			break ;
		}
	case WSAEMSGSIZE:
		{
			strncpy(szError, "WSAEMSGSIZE", ERROR_SIZE );
			break;
		}
	case WSAEHOSTUNREACH:
		{
			strncpy(szError, "WSAEHOSTUNREACH", ERROR_SIZE);
			break ;
		}
	case WSAECONNABORTED:
		{
			strncpy(szError, "WSAECONNABORTED", ERROR_SIZE);
			break ;
		}
	case WSAECONNRESET:		
		{
			strncpy(szError, "WSAECONNRESET", ERROR_SIZE);
			break;
		}
	default:
		{
			strncpy(szError, "UNKNOWN", ERROR_SIZE);
			break;
		};
	};
#endif
	return TRUE;
}

/**********************************************************************
* 函数名称： StartupSocket
* 功能描述： 
* 输入参数： 
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/03/23		V1.0	    huanggenping	创建版本
***********************************************************************/
BOOL SocketAPI::StartupSocket()
{
#if defined(__WINDOWS__)
	WORD wVersionRequested;
	WSADATA myWSaData;
	int nError = 0;
	wVersionRequested = MAKEWORD(2, 2);
	nError = WSAStartup(wVersionRequested, &myWSaData); 
	if (nError != 0)
	{
		return FALSE;
	}
	if (LOBYTE(myWSaData.wVersion ) != 2 || HIBYTE(myWSaData.wVersion) != 2)
	{
		WSACleanup();
		return FALSE;
	}
#endif
	return TRUE;
}

/**********************************************************************
* 函数名称： CleanSocket
* 功能描述： 
* 输入参数： 
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/03/23		V1.0	    huanggenping	创建版本
***********************************************************************/
VOID SocketAPI::CleanupSocket()
{
#if defined(__WINDOWS__)
	::WSACleanup();
#endif
}

/**********************************************************************
* 函数名称： SocketEx
* 功能描述： exception version of socket ()
* 输入参数： 
* <param name="nSocketType"> SOCKET类型（SOCK_STREAM为TCP/IP，SOCK_DGRAM为UDP）</param>
* <param name="nProtocolType"></param>
* <param name="nProtocol"></param>
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/03/23		V1.0	    huanggenping	创建版本
***********************************************************************/
SOCKET SocketAPI::SocketEx(INT nSocketType , INT nProtocolType , INT nProtocol) 
{
	__ENTER_FUNCTION_FOXNET

	SOCKET hSocket = ::socket(nSocketType, nProtocolType, nProtocol);

	if (hSocket == INVALID_SOCKET ) 
	{
		GetLastErrorEx();
	}

	return hSocket;
	
	__LEAVE_FUNCTION_FOXNET

	return INVALID_SOCKET;
}

#if defined(__WINDOWS__)

/**********************************************************************
* 函数名称： WSASocketEx
* 功能描述： 
* 输入参数： 
* <param name="nSocketType"> </param>
* <param name="nProtocolType"></param>
* <param name="nProtocol"></param>
* <param name="nFlags"></param>
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/03/23		V1.0	    huanggenping	创建版本
***********************************************************************/
SOCKET SocketAPI::WSASocketEx(INT nSocketType , INT nProtocolType , INT nProtocol, INT nFlags)
{
	__ENTER_FUNCTION_FOXNET

	SOCKET hSocket = ::WSASocket(nSocketType, nProtocolType, nProtocol, NULL, 0, nFlags);	
	if (hSocket == INVALID_SOCKET ) 
	{
		GetLastErrorEx();
	}

	return hSocket;
	
	__LEAVE_FUNCTION_FOXNET

	return INVALID_SOCKET;
}

#endif

/**********************************************************************
* 函数名称： BindEx
* 功能描述： exception version of bind()
* 输入参数： 
* <param name="hSocket"></param>
* <param name="lpSocketAddress"></param>
* <param name="nSocketAddressLen"></param>
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2011/07/23		V1.0	    huanggenping	创建版本
***********************************************************************/
BOOL SocketAPI::BindEx(SOCKET hSocket, const struct sockaddr * lpSocketAddress, UINT nSocketAddressLen) 
{
	__ENTER_FUNCTION_FOXNET

	INT nReturn = bind(hSocket, lpSocketAddress, nSocketAddressLen);
	if (nReturn == SOCKET_ERROR) 
	{
		GetLastErrorEx();
		return FALSE ;
	}
	
	return TRUE ;

	__LEAVE_FUNCTION_FOXNET

	return FALSE ;
}

/**********************************************************************
* 函数名称： ConnectEx
* 功能描述： exception version of connect()
* 输入参数： 
* <param name="hSocket"></param>
* <param name="lpSocketAddress"></param>
* <param name="nSocketAddressLen"></param>
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2011/07/23		V1.0	    huanggenping	创建版本
***********************************************************************/
BOOL SocketAPI::ConnectEx(SOCKET hSocket, const struct sockaddr * lpSocketAddress, UINT nSocketAddressLen)
{
	__ENTER_FUNCTION_FOXNET

	if (connect(hSocket, lpSocketAddress, nSocketAddressLen) == SOCKET_ERROR ) 
	{
		GetLastErrorEx();
		return FALSE ;
	}

	return TRUE ;
	
	__LEAVE_FUNCTION_FOXNET

	return FALSE ;
}

/**********************************************************************
* 函数名称： ListenEx
* 功能描述： exception version of listen()
* 输入参数： 
* <param name="hSocket"></param>
* <param name="nBacklog"></param>
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2011/07/23		V1.0	    huanggenping	创建版本
***********************************************************************/
BOOL SocketAPI::ListenEx(SOCKET hSocket, UINT nBacklog)
{
	__ENTER_FUNCTION_FOXNET

	if (listen(hSocket, nBacklog) == SOCKET_ERROR) 
	{
		GetLastErrorEx();
		return FALSE ;
	}

	return TRUE ;
	
	__LEAVE_FUNCTION_FOXNET

	return FALSE ;
}

/**********************************************************************
* 函数名称： AcceptEx
* 功能描述： exception version of accept()
* 输入参数： 
* <param name="hSocket"></param>
* <param name="lpSocketAddress"></param>
* <param name="pSocketAddressLen"></param>
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2011/07/23		V1.0	    huanggenping	创建版本
***********************************************************************/
SOCKET SocketAPI::AcceptEx(SOCKET hSocket, struct sockaddr * lpSocketAddress, UINT * pSocketAddressLen)
{
	__ENTER_FUNCTION_FOXNET

#if defined(__LINUX__)
	SOCKET hAccpetSocket = accept(hSocket, lpSocketAddress , pSocketAddressLen);
#elif defined(__WINDOWS__)
	SOCKET hAccpetSocket = accept(hSocket, lpSocketAddress, (int*)pSocketAddressLen);
#endif
	
	if (hAccpetSocket == INVALID_SOCKET) 
	{
		GetLastErrorEx();
		return -1;
	}

	return hAccpetSocket;

	__LEAVE_FUNCTION_FOXNET

	return INVALID_SOCKET ;
}

/**********************************************************************
* 函数名称： GetSockoptEx
* 功能描述： exception version of getsockopt()
* 输入参数： 
* <param name="hSocket"></param>
* <param name="nLevel"></param>
* <param name="nOptionName"></param>
* <param name="pOptonValue"></param>
* <param name="pOptionLen"></param>
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2011/07/23		V1.0	    huanggenping	创建版本
***********************************************************************/
BOOL SocketAPI::GetSockoptEx(SOCKET hSocket, INT nLevel, INT nOptionName, VOID * pOptonValue, INT * pOptionLen)
{
	__ENTER_FUNCTION_FOXNET

#if defined(__LINUX__)
	/*if (getsockopt(hSocket, nLevel, nOptionName, pOptonValue, (socklen_t*)pOptionLen) == SOCKET_ERROR)
	{
		GetLastErrorEx();
		return FALSE ;
	}*/
#elif defined(__WINDOWS__)
	if (getsockopt(hSocket, nLevel, nOptionName, (CHAR*)pOptonValue, (int*)pOptionLen) == SOCKET_ERROR)
	{
		GetLastErrorEx();
		return FALSE ;
	}
#endif

	

	return TRUE ;
	
	__LEAVE_FUNCTION_FOXNET

	return FALSE ;
}

/**********************************************************************
* 函数名称： GetSockoptEx2
* 功能描述： exception version of getsockopt()
* 输入参数： 
* <param name="hSocket"></param>
* <param name="nLevel"></param>
* <param name="nOptionName"></param>
* <param name="pOptonValue"></param>
* <param name="pOptionLen"></param>
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2011/07/23		V1.0	    huanggenping	创建版本
***********************************************************************/
UINT SocketAPI::GetSockoptEx2(SOCKET hSocket, INT nLevel, INT nOptionName, VOID * pOptonValue, UINT * pOptionLen)
{
	__ENTER_FUNCTION_FOXNET

#if defined(__LINUX__)
	/*if (getsockopt(hSocket, nLevel, nOptionName, pOptonValue, pOptionLen) == SOCKET_ERROR)
	{
		GetLastErrorEx();
		return 1;
	}*/
#elif defined(__WINDOWS__)
	if (getsockopt(hSocket, nLevel, nOptionName, (CHAR*)pOptonValue, (int*)pOptionLen) == SOCKET_ERROR)
	{
		GetLastErrorEx();
		return 1;
	}
#endif
	
	return 0;

	__LEAVE_FUNCTION_FOXNET

	return 1;
}

/**********************************************************************
* 函数名称： SetSockoptEx
* 功能描述： exception version of setsockopt()
* 输入参数： 
* <param name="hSocket"></param>
* <param name="nLevel"></param>
* <param name="nOptionName"></param>
* <param name="pOptonValue"></param>
* <param name="pOptionLen"></param>
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2011/07/23		V1.0	    huanggenping	创建版本
***********************************************************************/
BOOL SocketAPI::SetSockoptEx(SOCKET hSocket, INT nLevel, INT nOptionName, const VOID* pOptonValue, UINT pOptionLen)
{
	__ENTER_FUNCTION_FOXNET

	/*if (setsockopt(hSocket, nLevel, nOptionName, (CHAR*)pOptonValue, pOptionLen) == SOCKET_ERROR)
	{
		GetLastErrorEx();
		return FALSE ;
	}*/

	return TRUE ;
	
	__LEAVE_FUNCTION_FOXNET

	return FALSE ;
}


/**********************************************************************
* 函数名称： SendEx
* 功能描述： exception version of send()
* 输入参数： 
* <param name="hSocket"></param>
* <param name="pBuffer"></param>
* <param name="nBufferLen"></param>
* <param name="nFlag"></param>
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2011/07/23		V1.0	    huanggenping	创建版本
***********************************************************************/
INT SocketAPI::SendEx(SOCKET hSocket, const VOID * pBuffer, UINT nBufferLen, UINT nFlag)
{
	__ENTER_FUNCTION_FOXNET

	INT nSend = 0;

	_MY_TRY
	{
#if defined(__LINUX__)
		nSend = ::send(hSocket, pBuffer, nBufferLen, nFlag);
#elif defined(__WINDOWS__)
		nSend = ::send(hSocket, (const CHAR *)pBuffer, nBufferLen, nFlag);
		if (nSend == SOCKET_ERROR) 
		{
			INT nError = WSAGetLastError();
			if (nError == WSAEWOULDBLOCK)
			{
				return SOCKET_ERROR_WOULDBLOCK;
			}
			GetLastErrorEx();
		} 
		else if ( nSend == 0 )
		{

		}
#endif
	}
	_MY_CATCH
	{

	}

	return nSend;
	
	__LEAVE_FUNCTION_FOXNET

	return 0 ;
}

/**********************************************************************
* 函数名称： SendToEx
* 功能描述： exception version of sendto()
* 输入参数： 
* <param name="hSocket"></param>
* <param name="pBuffer"></param>
* <param name="nBufferLen"></param>
* <param name="nFlag"></param>
* <param name="lpSocketAddress"></param>
* <param name="nSocketAddressLen"></param>
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2011/07/23		V1.0	    huanggenping	创建版本
***********************************************************************/
UINT SocketAPI::SendToEx(SOCKET hSocket, const VOID * pBuffer, INT nBufferLen, UINT nFlag, const struct sockaddr * lpSocketAddress, INT nSocketAddressLen)
{
	__ENTER_FUNCTION_FOXNET

	INT nSend = sendto(hSocket, (const CHAR *)pBuffer, nBufferLen, nFlag, lpSocketAddress, nSocketAddressLen);

	if (nSend == SOCKET_ERROR) 
	{
		GetLastErrorEx();
	}

	return nSend;

	__LEAVE_FUNCTION_FOXNET

	return 0 ;
}

/**********************************************************************
* 函数名称： RecvEx
* 功能描述： exception version of recv()
* 输入参数： 
* <param name="hSocket"></param>
* <param name="pBuffer"></param>
* <param name="nBufferLen"></param>
* <param name="nFlag"></param>
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2011/07/23		V1.0	    huanggenping	创建版本
***********************************************************************/
UINT SocketAPI::RecvEx(SOCKET hSocket, VOID * pBuffer, UINT nBufferLen, UINT nFlag)
{
	__ENTER_FUNCTION_FOXNET

	INT nRecv = 0;
	

#if defined(__LINUX__)
	nRecv = recv(hSocket, pBuffer, nBufferLen, nFlag);
#elif defined(__WINDOWS__)
	//
	nRecv = recv(hSocket, (CHAR*)pBuffer, nBufferLen, nFlag);
	//
	if (nRecv == SOCKET_ERROR) 
	{
		INT nError = WSAGetLastError();
		if (nError == WSAEWOULDBLOCK)
		{
			return SOCKET_ERROR_WOULDBLOCK;
		}
		GetLastErrorEx();
	} 
	else if ( nRecv == 0 )
	{

	}
#endif

	return nRecv;
	
	__LEAVE_FUNCTION_FOXNET

	return 0 ;
}

#if defined(__WINDOWS__)

/**********************************************************************
* 函数名称： WSARecvEx
* 功能描述： exception version of WSARecv()
* 输入参数： 
* <param name="hSocket"></param>
* <param name="pBuffer"></param>
* <param name="uBufferCount"></param>
* <param name="pNumberOfBytesRecvd"></param>
* <param name="pFlags"></param>
* <param name="lpOverlapped"></param>
* <param name="lpCompletionRoutine"></param>
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2011/07/23		V1.0	    huanggenping	创建版本
***********************************************************************/
INT SocketAPI::WSARecvEx(SOCKET hSocket, LPWSABUF pBuffer, UINT uBufferCount, LPDWORD pNumberOfBytesRecvd, LPDWORD pFlags, LPWSAOVERLAPPED lpOverlapped, LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine)
{
	__ENTER_FUNCTION_FOXNET

	INT nRecv = ::WSARecv(hSocket, pBuffer, uBufferCount, (LPDWORD)pNumberOfBytesRecvd, (LPDWORD)pFlags, lpOverlapped, lpCompletionRoutine);

	return nRecv;
	
	__LEAVE_FUNCTION_FOXNET

	return 0 ;
}

#endif

#if defined(__WINDOWS__)

/**********************************************************************
* 函数名称： WSASendEx
* 功能描述： exception version of WSARecv()
* 输入参数： 
* <param name="hSocket"></param>
* <param name="pBuffer"></param>
* <param name="uBufferCount"></param>
* <param name="pNumberOfBytesSend"></param>
* <param name="dwFlags"></param>
* <param name="lpOverlapped"></param>
* <param name="lpCompletionRoutine"></param>
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2011/07/23		V1.0	    huanggenping	创建版本
***********************************************************************/
INT SocketAPI::WSASendEx(SOCKET hSocket, LPWSABUF pBuffer, UINT uBufferCount, LPDWORD pNumberOfBytesSend, DWORD dwFlags, LPWSAOVERLAPPED lpOverlapped, LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine)
{
	__ENTER_FUNCTION_FOXNET

	INT nSend = ::WSASend(hSocket, pBuffer, uBufferCount, pNumberOfBytesSend, dwFlags, lpOverlapped, lpCompletionRoutine); 

	return nSend;
	
	__LEAVE_FUNCTION_FOXNET

	return 0 ;
}

#endif

/**********************************************************************
* 函数名称： RecvFromEx
* 功能描述： exception version of recvfrom()
* 输入参数： 
* <param name="hSocket"></param>
* <param name="pBuffer"></param>
* <param name="nBufferLen"></param>
* <param name="nFlag"></param>
* <param name="lpSocketAddress"></param>
* <param name="pSocketAddressLen"></param>
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2011/07/23		V1.0	    huanggenping	创建版本
***********************************************************************/
UINT SocketAPI::RecvFromEx(SOCKET hSocket, VOID * pBuffer, INT nBufferLen, UINT nFlag, struct sockaddr * lpSocketAddress, UINT* pSocketAddressLen)
{
	__ENTER_FUNCTION_FOXNET

	INT nReceived = 0;

#if defined(__LINUX__)
	
#elif defined(__WINDOWS__)
	nReceived = recvfrom(hSocket, (CHAR*)pBuffer, nBufferLen, nFlag, lpSocketAddress, (int*)pSocketAddressLen);

	if ( nReceived == SOCKET_ERROR ) 
	{

	}
#endif
	

	return nReceived;

	__LEAVE_FUNCTION_FOXNET

	return 0 ;
}


/**********************************************************************
* 函数名称： GetSocketNonblockingEx
* 功能描述： exception version of closesocket() 
* 输入参数： 
* <param name="hSocket"></param>
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2011/07/23		V1.0	    huanggenping	创建版本
***********************************************************************/
BOOL SocketAPI::CloseSocketEx (SOCKET hSocket)
{
	__ENTER_FUNCTION_FOXNET

#if defined(__LINUX__)
	close(hSocket);
#elif defined(__WINDOWS__)
	if (closesocket(hSocket) == SOCKET_ERROR ) 
	{
		GetLastErrorEx();
		return FALSE ;
	}
#endif
	

	return TRUE ;
	
	__LEAVE_FUNCTION_FOXNET

	return FALSE ;
}

/**********************************************************************
* 函数名称： IoctlSocketEx
* 功能描述： exception version of ioctlsocket()
* 输入参数： 
* <param name="hSocket"></param>
* <param name="lCommand"></param>
* <param name="puArgp"></param>
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2011/07/23		V1.0	    huanggenping	创建版本
***********************************************************************/
BOOL SocketAPI::IoctlSocketEx (SOCKET hSocket, LONG lCommand, ULONG* puArgp)
{
	__ENTER_FUNCTION_FOXNET

#if defined(__LINUX__)
	
#elif defined(__WINDOWS__)
	if (ioctlsocket(hSocket, lCommand, puArgp) == SOCKET_ERROR)
	{
		GetLastErrorEx();

		return FALSE ;
	}
#endif
	

	return TRUE ;
	
	__LEAVE_FUNCTION_FOXNET

	return FALSE ;
}
 

/**********************************************************************
* 函数名称： GetSocketNonblockingEx
* 功能描述： make socket nonblocking mode
* 输入参数： 
* <param name="hSocket"></param>
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2011/07/23		V1.0	    huanggenping	创建版本
***********************************************************************/
BOOL SocketAPI::GetSocketNonblockingEx (SOCKET hSocket)
{
	__ENTER_FUNCTION_FOXNET

	return FALSE ;
	
	__LEAVE_FUNCTION_FOXNET

	return FALSE ;
}


/**********************************************************************
* 函数名称： SetSocketNonblockingEx
* 功能描述： make socket nonblocking mode
* 输入参数： 
* <param name="hSocket"></param>
* <param name="bOn"></param>
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2011/07/23		V1.0	    huanggenping	创建版本
***********************************************************************/
BOOL SocketAPI::SetSocketNonblockingEx(SOCKET hSocket, BOOL bOn)
{
	__ENTER_FUNCTION_FOXNET

#if defined(__LINUX__)
	return TRUE;
#elif defined(__WINDOWS__)
	
	ULONG uArgp = 0;
	if (bOn)
	{
		uArgp = 1;
	}
	else
	{
		uArgp = 0;
	}
	return IoctlSocketEx(hSocket, FIONBIO, &uArgp);
#endif
	
	__LEAVE_FUNCTION_FOXNET

	return FALSE ;
}

/**********************************************************************
* 函数名称： AvailableSocketEx
* 功能描述： get amount of data in socket input buffer
* 输入参数： 
* <param name="hSocket"></param>
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2011/07/23		V1.0	    huanggenping	创建版本
***********************************************************************/
UINT SocketAPI::AvailableSocketEx (SOCKET hSocket)
{
	__ENTER_FUNCTION_FOXNET

	ULONG uArgp = 0;
	
#if defined(__LINUX__)
	
#elif defined(__WINDOWS__)
	IoctlSocketEx(hSocket, FIONREAD, &uArgp);
#endif

	return uArgp;
	
	__LEAVE_FUNCTION_FOXNET

	return 0 ;
}


/**********************************************************************
* 函数名称： ShutDownEx
* 功能描述： exception version of shutdown()
* 输入参数： 
* <param name="hSocket"></param>
* <param name="nHow"></param>
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2011/07/23		V1.0	    huanggenping	创建版本
***********************************************************************/
BOOL SocketAPI::ShutDownEx(SOCKET hSocket, UINT nHow)
{
	__ENTER_FUNCTION_FOXNET

	if (shutdown(hSocket, nHow) < 0) 
	{
		GetLastErrorEx();

		return FALSE ;
	}

	return TRUE ;
	
	__LEAVE_FUNCTION_FOXNET

	return FALSE ;
}

/**********************************************************************
* 函数名称： SelectEx
* 功能描述： exception version of select()
* 输入参数： 
* <param name="nFds"></param>
* <param name="pReadSet"></param>
* <param name="pWriteSet"></param>
* <param name="pExceptSet"></param>
* <param name="pTimeOut"></param>
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2011/07/23		V1.0	    huanggenping	创建版本
***********************************************************************/
INT SocketAPI::SelectEx(INT nFds, fd_set * pReadSet, fd_set * pWriteSet, fd_set * pExceptSet, struct timeval * pTimeOut)
{
	__ENTER_FUNCTION_FOXNET

	INT nResult = 0;

	_MY_TRY 
	{
		nResult = select(nFds, pReadSet, pWriteSet, pExceptSet, pTimeOut);
		if (nResult == SOCKET_ERROR)
		{
			GetLastErrorEx();
		}
	} 
	_MY_CATCH
	{

	}

	return nResult;

	__LEAVE_FUNCTION_FOXNET

	return 0 ;
}




