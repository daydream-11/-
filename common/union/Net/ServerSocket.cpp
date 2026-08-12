#include "stdafx.h"


//////////////////////////////////////////////////
// include files
//////////////////////////////////////////////////
#include "ServerSocket.h"


/** @name 构造与析构 */////////////////////////////////////////////////////
/// @{

/**********************************************************************
* 函数名称： ServerSocket
* 功能描述： 构造函数
* 输入参数： 
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2011/07/23		V1.0	    huanggenping	创建版本
***********************************************************************/
ServerSocket::ServerSocket () 
{
	__ENTER_FUNCTION_FOXNET

#if defined(__WINDOWS__)
	m_lpGetAcceptExSockAddrs = NULL;
	m_lpAcceptEx = NULL;
#endif

	m_Socket = new Socket();
	if (m_Socket == NULL)
	{
		throw 1;
	}

	__LEAVE_FUNCTION_FOXNET
}

/**********************************************************************
* 函数名称： ServerSocket
* 功能描述： 构造函数
* 输入参数： 
* <param name="uPort"></param>
* <param name="uBacklog"></param>
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2011/07/23		V1.0	    huanggenping	创建版本
***********************************************************************/
ServerSocket::ServerSocket (UINT uPort , UINT uBacklog) 
{
	__ENTER_FUNCTION_FOXNET

	BOOL bReturn = FALSE ;
	
	m_Socket = new Socket();
	if (m_Socket == NULL)
	{
		throw 1;
	}
	// create socket
	bReturn = m_Socket->Create( ) ;
	if (!bReturn)
	{
		throw 1;
	}
	bReturn = m_Socket->SetReuseAddr(TRUE);
	if (!bReturn)
	{
		throw 1;
	}
	bReturn = m_Socket->Bind(uPort);
	if (!bReturn)
	{
		throw 1;
	}
	// set listening queue size
	bReturn = m_Socket->Listen(uBacklog);
	if (!bReturn)
	{
		throw 1;
	}

	__LEAVE_FUNCTION_FOXNET
}

/**********************************************************************
* 函数名称： ~ServerSocket
* 功能描述： 析构函数
* 输入参数： 
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2011/07/23		V1.0	    huanggenping	创建版本
***********************************************************************/
ServerSocket::~ServerSocket () 
{
	__ENTER_FUNCTION_FOXNET
		
	if ( m_Socket != NULL ) 
	{
		m_Socket->Close();
		delete m_Socket;
		m_Socket = NULL;
	}
	__LEAVE_FUNCTION_FOXNET
}
	
/// @}

/** @name 公共成员函数 *///////////////////////////////////////////////////
/// @{

/**********************************************************************
* 函数名称： Init
* 功能描述： 
* 输入参数： 
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2011/07/23		V1.0	    huanggenping	创建版本
***********************************************************************/
BOOL ServerSocket::Init()
{
	__ENTER_FUNCTION_FOXNET
		
#if defined(__WINDOWS__)
	BOOL bReturn = m_Socket->CreateWSASocket();
	if (!bReturn)
	{
		return FALSE;
	}
	bReturn = m_Socket->SetReuseAddr(TRUE);
	if (!bReturn)
	{
		return FALSE;
	}

	bReturn = GetAcceptExFunctionAddress();
	if (!bReturn)
	{
		return FALSE;
	}
#endif
	return TRUE;
	
	__LEAVE_FUNCTION_FOXNET
}

/**********************************************************************
* 函数名称： Init
* 功能描述： 
* 输入参数： 
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2011/07/23		V1.0	    huanggenping	创建版本
***********************************************************************/
BOOL ServerSocket::Init(UINT uPort, UINT uBacklog)
{
	__ENTER_FUNCTION_FOXNET
		
#if defined(__WINDOWS__)
	BOOL bReturn = m_Socket->CreateWSASocket();
	if (!bReturn)
	{
		return FALSE;
	}
	bReturn = GetAcceptExFunctionAddress();
	if (!bReturn)
	{
		return FALSE;
	}
#elif defined(__LINUX__)
	BOOL bReturn = m_Socket->Create();
	if (!bReturn)
	{
		return FALSE;
	}
#endif
	bReturn = m_Socket->SetReuseAddr(TRUE);
	if (!bReturn)
	{
		return FALSE;
	}
	bReturn = m_Socket->Bind(uPort);
	if (!bReturn)
	{
		return FALSE;
	}

	bReturn = m_Socket->Listen(uBacklog);
	if (!bReturn)
	{
		return FALSE;
	}

	return TRUE;
	
	__LEAVE_FUNCTION_FOXNET
}

#if defined(__WINDOWS__)
/**********************************************************************
* 函数名称： GetAcceptExFunctionAddress
* 功能描述： 
* 输入参数： 
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2011/07/23		V1.0	    huanggenping	创建版本
***********************************************************************/
BOOL ServerSocket::GetAcceptExFunctionAddress()
{
	__ENTER_FUNCTION_FOXNET
		
	GUID GUIDAcceptEx = WSAID_ACCEPTEX;
	DWORD dwResult = 0;
	DWORD dwError = ::WSAIoctl(m_Socket->GetSOCKET(), SIO_GET_EXTENSION_FUNCTION_POINTER, &GUIDAcceptEx, sizeof(GUIDAcceptEx), &m_lpAcceptEx, sizeof(m_lpAcceptEx), &dwResult, NULL, NULL);
	if (dwError == SOCKET_ERROR)
	{
		return FALSE;
	}

	GUID GUIDAcceptExSockAddrs = WSAID_GETACCEPTEXSOCKADDRS;
	dwError = ::WSAIoctl(m_Socket->GetSOCKET(), SIO_GET_EXTENSION_FUNCTION_POINTER, &GUIDAcceptExSockAddrs, sizeof(GUIDAcceptExSockAddrs), &m_lpGetAcceptExSockAddrs, sizeof(m_lpGetAcceptExSockAddrs), &dwResult, NULL, NULL);
	if (dwError == SOCKET_ERROR)
	{
		return FALSE;
	}
	return TRUE;

	__LEAVE_FUNCTION_FOXNET
}
#endif

/**********************************************************************
* 函数名称： Bind
* 功能描述： 
* 输入参数：
* <param name="uPort"></param>
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2011/07/23		V1.0	    huanggenping	创建版本
***********************************************************************/
BOOL ServerSocket::Bind(UINT uPort)
{
	return m_Socket->Bind(uPort);
}

/**********************************************************************
* 函数名称： Listen
* 功能描述： 
* 输入参数：
* <param name="uBacklog"></param>
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2011/07/23		V1.0	    huanggenping	创建版本
***********************************************************************/
BOOL ServerSocket::Listen(UINT uBacklog)
{
	return m_Socket->Listen(uBacklog);
}

#if defined(__WINDOWS__)
/**********************************************************************
* 函数名称： AcceptEx
* 功能描述： 
* 输入参数：
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2011/07/23		V1.0	    huanggenping	创建版本
***********************************************************************/
BOOL ServerSocket::AcceptEx(SOCKET hAccessSocket, PVOID lpOutputBuffer, DWORD dwReceiveDataLength, DWORD dwLocalAddressLength, DWORD dwRemoteAddressLength, LPOVERLAPPED lpOverlapped)
{
	__ENTER_FUNCTION_FOXNET
		
	DWORD dwBytes = 0;
	BOOL bSuccess = m_lpAcceptEx(m_Socket->GetSOCKET(), hAccessSocket, lpOutputBuffer, dwReceiveDataLength, dwLocalAddressLength, dwRemoteAddressLength, &dwBytes, lpOverlapped);
	if (!bSuccess)
	{
		DWORD dwWSAErr = ::WSAGetLastError();
		if (dwWSAErr != ERROR_IO_PENDING)
		{
			return FALSE;
		}
	}	
	return TRUE;

	__LEAVE_FUNCTION_FOXNET
}
#endif
/**********************************************************************
* 函数名称： ConnectEx
* 功能描述： 重新尝试连接remote host
* 输入参数： 
* <param name="lpszhost"></param>
* <param name="nPort"></param>
* 输出参数：
* 返 回 值： 连接成功，返回TRUE；连接失败，返回FALSE
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2011/07/23		V1.0	    huanggenping	创建版本
***********************************************************************/
BOOL ServerSocket::ConnectEx(const CHAR * lpszhost, UINT nPort)
{
	return m_Socket->Connect(lpszhost, nPort);
}

/**********************************************************************
* 函数名称： Close
* 功能描述： 关闭服务端连接
* 输入参数： 
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2011/07/23		V1.0	    huanggenping	创建版本
***********************************************************************/
VOID ServerSocket::Close()
{
	__ENTER_FUNCTION_FOXNET
		
	if( m_Socket != NULL)
	{
		m_Socket->Close();
	}

	__LEAVE_FUNCTION_FOXNET
}

/**********************************************************************
* 函数名称： Accept
* 功能描述： 接受新的连接
* 输入参数： 
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2011/07/23		V1.0	    huanggenping	创建版本
***********************************************************************/
BOOL ServerSocket::Accept(Socket *pSocket) 
{
	__ENTER_FUNCTION_FOXNET
	
	UINT nSocketAddrInSize = sizeof(sockaddr_in);

	pSocket->Close();

	pSocket->m_SocketID = m_Socket->Accept((struct sockaddr *)(pSocket->GetSockAddrIn()), &nSocketAddrInSize);

	if (pSocket->m_SocketID == INVALID_SOCKET)
	{
		return FALSE ;
	}
	pSocket->SetPort(ntohs(pSocket->GetSockAddrIn()->sin_port));
	//
	pSocket->SetHost(inet_ntoa(pSocket->GetSockAddrIn()->sin_addr));


	return TRUE;

	__LEAVE_FUNCTION_FOXNET

	return FALSE ;
}

/// @}

/** @name 公共成员函数 *///////////////////////////////////////////////////
/// @{

/**********************************************************************
* 函数名称： GetLinger
* 功能描述： 获取socket's linger status
* 输入参数： 
* 输出参数：
* 返 回 值： 返回socket's linger status
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2011/07/23		V1.0	    huanggenping	创建版本
***********************************************************************/
const UINT ServerSocket::GetLinger()
{
	return m_Socket->GetLinger();
}

/**********************************************************************
* 函数名称： SetLinger
* 功能描述： 设置socket's linger status
* 输入参数： 
* 输出参数：
* <param name="nLingerTime"></param>
* 返 回 值： 执行成功，返回TRUE；执行失败，返回FALSE
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2011/07/23		V1.0	    huanggenping	创建版本
***********************************************************************/
VOID ServerSocket::SetLinger (UINT nLingerTime)
{
	m_Socket->SetLinger(nLingerTime); 
}

/**********************************************************************
* 函数名称： IsNonBlocking
* 功能描述： 获取socket's nonblocking status
* 输入参数： 
* 输出参数：
* 返 回 值： 返回socket's nonblocking status
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2011/07/23		V1.0	    huanggenping	创建版本
***********************************************************************/
const BOOL ServerSocket::IsNonBlocking()
{
	return m_Socket->IsNonBlocking(); 
}

/**********************************************************************
* 函数名称： SetNonBlocking
* 功能描述： 设置socket's nonblocking status
* 输入参数： 
* <param name="bOn"></param>
* 输出参数：
* 返 回 值： 执行成功，返回TRUE；执行失败，返回FALSE
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2011/07/23		V1.0	    huanggenping	创建版本
***********************************************************************/
VOID ServerSocket::SetNonBlocking(BOOL bOn)
{
	m_Socket->SetNonBlocking(bOn);
}

/**********************************************************************
* 函数名称： GetReceiveBufferSize
* 功能描述： 获取receive buffer size
* 输入参数： 
* 输出参数：
* 返 回 值： 返回receive buffer size
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2011/07/23		V1.0	    huanggenping	创建版本
***********************************************************************/
const UINT ServerSocket::GetReceiveBufferSize()
{
	return m_Socket->GetReceiveBufferSize();
}

/**********************************************************************
* 函数名称： GetReceiveBufferSize
* 功能描述： 设置receive buffer size
* 输入参数： 
* <param name="uReceiveBufferSize"></param>
* 输出参数：
* 返 回 值： 执行成功，返回TRUE；执行失败，返回FALSE
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2011/07/23		V1.0	    huanggenping	创建版本
***********************************************************************/
VOID ServerSocket::SetReceiveBufferSize(UINT uReceiveBufferSize) 
{ 
	m_Socket->SetReceiveBufferSize(uReceiveBufferSize); 
}

/**********************************************************************
* 函数名称： GetSendBufferSize
* 功能描述： 获取send buffer size
* 输入参数： 
* 输出参数：
* 返 回 值： 返回send buffer size
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2011/07/23		V1.0	    huanggenping	创建版本
***********************************************************************/
const UINT ServerSocket::GetSendBufferSize()
{
	return m_Socket->GetSendBufferSize(); 
}

/**********************************************************************
* 函数名称： SetSendBufferSize
* 功能描述： 设置send buffer size
* 输入参数： 
* <param name="uSendBufferSize"></param>
* 输出参数：
* 返 回 值： 执行成功，返回TRUE；执行失败，返回FALSE
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2011/07/23		V1.0	    huanggenping	创建版本
***********************************************************************/
VOID ServerSocket::SetSendBufferSize(UINT uSendBufferSize)
{
	m_Socket->SetSendBufferSize(uSendBufferSize);
}

/**********************************************************************
* 函数名称： GetSOCKET
* 功能描述： 获取Socket套连接字
* 输入参数： 
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2011/07/23		V1.0	    huanggenping	创建版本
***********************************************************************/
const SOCKET ServerSocket::GetSOCKET() 
{ 
	return m_Socket->GetSOCKET(); 
}

/// @}





