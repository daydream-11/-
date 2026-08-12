/*********************************************************************
* 版权所有 (C)2008, 深圳市新飞杨数码科技有限公司。
* 
* 文件名称： Socket.cpp
* 文件标识： 
* 内容摘要： 网络Socket的功能实现所有的网络操作，包括主要模块、函数及其功能的说明
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
#include "Socket.h"

/** @name 构造与析构 */////////////////////////////////////////////////////
/// @{

/**********************************************************************
* 函数名称： Socket
* 功能描述： 构造函数
* 输入参数： 
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2011/07/23		V1.0	    huanggenping	创建版本
***********************************************************************/
Socket::Socket () 
{ 
	__ENTER_FUNCTION_FOXNET

	m_SocketID = INVALID_SOCKET;
	memset(m_lpszHost, 0, IP_SIZE);
	m_nPort = 0;
	
	__LEAVE_FUNCTION_FOXNET
}

/**********************************************************************
* 函数名称： Socket
* 功能描述： 构造函数
* 输入参数： 
* <param name="lpszhost"></param>
* <param name="nPort"></param>
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2011/07/23		V1.0	    huanggenping	创建版本
***********************************************************************/
Socket::Socket(const CHAR * lpszHost, UINT nPort) 
{ 
	__ENTER_FUNCTION_FOXNET

	strncpy(m_lpszHost, lpszHost, IP_SIZE - 1);
	m_nPort = nPort;

	Create();

	__LEAVE_FUNCTION_FOXNET
}

/**********************************************************************
* 函数名称： ~Socket
* 功能描述： 析构函数
* 输入参数： 
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2011/07/23		V1.0	    huanggenping	创建版本
***********************************************************************/
Socket::~Socket () 
{ 
	__ENTER_FUNCTION_FOXNET

	Close();
	
	__LEAVE_FUNCTION_FOXNET
}

/// @}

/** @name 公共成员函数 *///////////////////////////////////////////////////
/// @{

/**********************************************************************
* 函数名称： Create
* 功能描述： 创建Socket套连接字
* 输入参数： 
* 输出参数：
* 返 回 值： 执行成功，返回TRUE；执行失败，返回FALSE
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2011/07/23		V1.0	    huanggenping	创建版本
***********************************************************************/
BOOL Socket::Create()
{
	__ENTER_FUNCTION_FOXNET
	
	m_SocketID = SocketAPI::SocketEx(AF_INET, SOCK_STREAM, 0);
    
	memset( &m_SockAddr , 0 , sizeof(m_SockAddr) );
	
	m_SockAddr.sin_family = AF_INET;

	if (IsValid())
	{
		return TRUE;
	}
	else 
	{
		return FALSE;
	}

	__LEAVE_FUNCTION_FOXNET

	return FALSE ;
}

#if defined(__WINDOWS__)
/**********************************************************************
* 函数名称： CreateWSASocket
* 功能描述： 
* 输入参数： 
* 输出参数：
* 返 回 值： 执行成功，返回TRUE；执行失败，返回FALSE
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2011/07/23		V1.0	    huanggenping	创建版本
***********************************************************************/
BOOL Socket::CreateWSASocket()
{
	__ENTER_FUNCTION_FOXNET
	
	m_SocketID = SocketAPI::WSASocketEx(AF_INET, SOCK_STREAM, IPPROTO_IP, WSA_FLAG_OVERLAPPED);

	m_SockAddr.sin_family = AF_INET;

	if (IsValid())
	{
		return TRUE;
	}
	else 
	{
		return FALSE;
	}

	__LEAVE_FUNCTION_FOXNET

	return FALSE ;
}
#endif

/**********************************************************************
* 函数名称： Close
* 功能描述： 关闭Socket套连接字连接
* 输入参数： 
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2011/07/23		V1.0	    huanggenping	创建版本
***********************************************************************/
VOID Socket::Close() 
{ 
	__ENTER_FUNCTION_FOXNET

	SocketAPI::CloseSocketEx(m_SocketID);
	//
	m_SocketID = INVALID_SOCKET;
	m_nPort = 0 ;
	memset(&m_SockAddr, 0, sizeof(sockaddr_in));
	memset(m_lpszHost, 0, IP_SIZE);
	
	__LEAVE_FUNCTION_FOXNET
}
	
/**********************************************************************
* 函数名称： Connect
* 功能描述： 尝试连接remote host
* 输入参数： 
* 输出参数：
* 返 回 值： 连接成功，返回TRUE；连接失败，返回FALSE
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2011/07/23		V1.0	    huanggenping	创建版本
***********************************************************************/
BOOL Socket::Connect() 
{ 
	__ENTER_FUNCTION_FOXNET

	m_SockAddr.sin_addr.s_addr = inet_addr(m_lpszHost);
	
	m_SockAddr.sin_port = htons(m_nPort);
	
	BOOL nResult = SocketAPI::ConnectEx(m_SocketID, (const struct sockaddr *)&m_SockAddr , sizeof(m_SockAddr));
	if (nResult)
	{
		return TRUE ;
	}
	else
	{
		return FALSE ;
	}

	__LEAVE_FUNCTION_FOXNET

	return 0 ;
}

/**********************************************************************
* 函数名称： Connect
* 功能描述： 尝试连接remote host
* 输入参数： 
* <param name="lpszHost"></param>
* <param name="nPort"></param>
* 输出参数：
* 返 回 值： 连接成功，返回TRUE；连接失败，返回FALSE
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2011/07/23		V1.0	    huanggenping	创建版本
***********************************************************************/
BOOL Socket::Connect(const CHAR * lpszHost, UINT nPort) 
{ 
	__ENTER_FUNCTION_FOXNET

	strncpy(m_lpszHost, lpszHost, IP_SIZE - 1);
	m_nPort = nPort;

	return Connect();

	__LEAVE_FUNCTION_FOXNET

	return FALSE;
}

/**********************************************************************
* 函数名称： ReConnect
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
BOOL Socket::ReConnect (const CHAR * lpszhost, UINT nPort)
{
	__ENTER_FUNCTION_FOXNET

	Close();

	m_nPort = nPort;
	strncpy(m_lpszHost, lpszhost, IP_SIZE - 1);

	Create();

	return Connect();	

	__LEAVE_FUNCTION_FOXNET

	return FALSE ;
}

/**********************************************************************
* 函数名称： Send
* 功能描述： 发送数据
* 输入参数： 
* <param name="pBuffer"></param>
* <param name="uBufferLen"></param>
* <param name="nFlag"></param>
* 输出参数：
* 返 回 值： 连接成功，返回TRUE；连接失败，返回FALSE
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2011/07/23		V1.0	    huanggenping	创建版本
***********************************************************************/
INT Socket::Send(const char * pBuffer, UINT uBufferLen, UINT nFlag)
{ 
	__ENTER_FUNCTION_FOXNET

	for (INT nSend = 0, nTemp = 0 ; ;)
	{
		nTemp = SocketAPI::SendEx(m_SocketID, pBuffer + nSend, uBufferLen - nSend, nFlag);
		if (nTemp < 1) 
		{
			return SOCKET_ERROR;
		}
		nSend += nTemp;
		if (nSend == uBufferLen) 
		{
			return nSend;
		}
	}

	return SOCKET_ERROR;

	__LEAVE_FUNCTION_FOXNET

	return 0 ;
}

/**********************************************************************
* 函数名称： Receive
* 功能描述： 接收数据
* 输入参数： 
* <param name="pBuffer"></param>
* <param name="uBufferLen"></param>
* <param name="nFlag"></param>
* 输出参数：
* 返 回 值： 连接成功，返回TRUE；连接失败，返回FALSE
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2011/07/23		V1.0	    huanggenping	创建版本
***********************************************************************/
UINT Socket::Receive(VOID * pBuffer, UINT uBufferLen, UINT nFlag)
{ 
	__ENTER_FUNCTION_FOXNET

	return SocketAPI::RecvEx(m_SocketID, pBuffer, uBufferLen, nFlag);

	__LEAVE_FUNCTION_FOXNET

	return 0 ;
}

#if defined(__WINDOWS__)
/**********************************************************************
* 函数名称： WSARecv
* 功能描述： 接收数据
* 输入参数： 
* <param name="pBuffer"></param>
* <param name="uBufferCount"></param>
* <param name="pNumberOfBytesRecvd"></param>
* <param name="pFlags"></param>
* <param name="lpOverlapped"></param>
* <param name="lpCompletionRoutine"></param>
* 输出参数：
* 返 回 值： 连接成功，返回TRUE；连接失败，返回FALSE
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2011/07/23		V1.0	    huanggenping	创建版本
***********************************************************************/
UINT Socket::WSARecv(LPWSABUF pBuffer, UINT uBufferCount, LPDWORD pNumberOfBytesRecvd, LPDWORD pFlags, LPWSAOVERLAPPED lpOverlapped, LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine)
{
	return SocketAPI::WSARecvEx(m_SocketID, pBuffer, uBufferCount, pNumberOfBytesRecvd, pFlags, lpOverlapped, lpCompletionRoutine);
}

/**********************************************************************
* 函数名称： WSASend
* 功能描述： 接收数据
* 输入参数： 
* <param name="pBuffer"></param>
* <param name="uBufferCount"></param>
* <param name="pNumberOfBytesSend"></param>
* <param name="dwFlags"></param>
* <param name="lpOverlapped"></param>
* <param name="lpCompletionRoutine"></param>
* 输出参数：
* 返 回 值： 连接成功，返回TRUE；连接失败，返回FALSE
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2011/07/23		V1.0	    huanggenping	创建版本
***********************************************************************/
UINT Socket::WSASend(LPWSABUF pBuffer, UINT uBufferCount, LPDWORD pNumberOfBytesSend, DWORD dwFlags, LPWSAOVERLAPPED lpOverlapped, LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine)
{
	return SocketAPI::WSASendEx(m_SocketID, pBuffer, uBufferCount, pNumberOfBytesSend, dwFlags, lpOverlapped, lpCompletionRoutine);
}

#endif

/**********************************************************************
* 函数名称： Available
* 功能描述： 接收数据
* 输入参数： 
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2011/07/23		V1.0	    huanggenping	创建版本
***********************************************************************/
const UINT Socket::Available()
{ 
	__ENTER_FUNCTION_FOXNET

	return SocketAPI::AvailableSocketEx(m_SocketID);

	__LEAVE_FUNCTION_FOXNET

	return 0 ;
}

/**********************************************************************
* 函数名称： Accept
* 功能描述： 接收Socket套连接字
* 输入参数： 
* <param name="lpSocketAddress"></param>
* <param name="pSocketAddressLen"></param>
* 输出参数：
* 返 回 值： 
* 其它说明： 返回Socket套连接字
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2011/07/23		V1.0	    huanggenping	创建版本
***********************************************************************/
SOCKET Socket::Accept(struct sockaddr * lpSocketAddress, UINT * pSocketAddressLen)
{
	__ENTER_FUNCTION_FOXNET

	return SocketAPI::AcceptEx(m_SocketID, lpSocketAddress, pSocketAddressLen);

	__LEAVE_FUNCTION_FOXNET

	return INVALID_SOCKET ;
}


/**********************************************************************
* 函数名称： Bind
* 功能描述： 绑定Socket套连接字
* 输入参数： 
* 输出参数：
* 返 回 值： 
* 其它说明： 返回Socket套连接字
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2011/07/23		V1.0	    huanggenping	创建版本
***********************************************************************/
BOOL Socket::Bind()
{
	__ENTER_FUNCTION_FOXNET

	m_SockAddr.sin_addr.s_addr = INADDR_ANY;
	m_SockAddr.sin_port        = htons(m_nPort);
	
	BOOL bResult = SocketAPI::BindEx(m_SocketID, (const struct sockaddr *)&m_SockAddr, sizeof(m_SockAddr));

	if (bResult)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
	__LEAVE_FUNCTION_FOXNET

	return FALSE;
}

/**********************************************************************
* 函数名称： Bind
* 功能描述： 绑定Socket套连接字
* 输入参数： 
* 输出参数：
* <param name="nPort"></param>
* 返 回 值： 
* 其它说明： 返回Socket套连接字
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2011/07/23		V1.0	    huanggenping	创建版本
***********************************************************************/
BOOL Socket::Bind(UINT nPort)
{
	__ENTER_FUNCTION_FOXNET

	m_nPort = nPort;

	return Bind();

	__LEAVE_FUNCTION_FOXNET

	return 0 ;
}

/**********************************************************************
* 函数名称： Listen
* 功能描述： 绑定Socket套连接字
* 输入参数： 
* 输出参数：
* <param name="nPort"></param>
* 返 回 值： 
* 其它说明： 返回Socket套连接字
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2011/07/23		V1.0	    huanggenping	创建版本
***********************************************************************/
BOOL Socket::Listen(INT nBacklog)
{
	__ENTER_FUNCTION_FOXNET
		
	return SocketAPI::ListenEx(m_SocketID, nBacklog);

	__LEAVE_FUNCTION_FOXNET

	return FALSE ;
}

/**********************************************************************
* 函数名称： GetLinger
* 功能描述： 
* 输入参数： 
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2011/07/23		V1.0	    huanggenping	创建版本
***********************************************************************/
const UINT Socket::GetLinger()
{ 
	__ENTER_FUNCTION_FOXNET

	struct linger myLinger;

	INT nLingerSize = sizeof(myLinger);
	
	SocketAPI::GetSockoptEx(m_SocketID , SOL_SOCKET , SO_LINGER , &myLinger, &nLingerSize);
	
	return myLinger.l_linger;

	__LEAVE_FUNCTION_FOXNET

	return 0 ;
}

/**********************************************************************
* 函数名称： SetLinger
* 功能描述： 
* 输入参数： 
* 输出参数：
* <param name="nLingerTime"></param>
* 返 回 值： 执行成功，返回TRUE；执行失败，返回FALSE
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2011/07/23		V1.0	    huanggenping	创建版本
***********************************************************************/
BOOL Socket::SetLinger(UINT nLingerTime) 
{
	__ENTER_FUNCTION_FOXNET

	struct linger myLinger;
	
	if (nLingerTime > 0)
	{
		myLinger.l_onoff = 1;
	}
	else
	{
		myLinger.l_onoff = 0;
	}
	myLinger.l_linger = nLingerTime;
	
	return SocketAPI::SetSockoptEx(m_SocketID, SOL_SOCKET, SO_LINGER, &myLinger , sizeof(myLinger));

	__LEAVE_FUNCTION_FOXNET

	return FALSE ;
}

/**********************************************************************
* 函数名称： GetSocketError
* 功能描述： 获取is Error
* 输入参数： 
* 输出参数：
* 返 回 值： 返回is Error
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2011/07/23		V1.0	    huanggenping	创建版本
***********************************************************************/
const UINT Socket::GetSocketError() 
{ 
	__ENTER_FUNCTION_FOXNET

	return IsSocketError(); 

	__LEAVE_FUNCTION_FOXNET

	return 0 ;
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
const BOOL Socket::IsNonBlocking () 
{ 
	__ENTER_FUNCTION_FOXNET

	return SocketAPI::GetSocketNonblockingEx(m_SocketID);

	__LEAVE_FUNCTION_FOXNET

	return FALSE ;
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
BOOL Socket::SetNonBlocking(BOOL bOn) 
{ 
	__ENTER_FUNCTION_FOXNET

	return SocketAPI::SetSocketNonblockingEx(m_SocketID, bOn);

	__LEAVE_FUNCTION_FOXNET

	return FALSE;
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
const UINT Socket::GetReceiveBufferSize()
{ 
	__ENTER_FUNCTION_FOXNET

	UINT uReceiveBufferSize = 0;
	INT nSizeOfValue = sizeof(uReceiveBufferSize);

	SocketAPI::GetSockoptEx(m_SocketID, SOL_SOCKET, SO_RCVBUF, &uReceiveBufferSize, &nSizeOfValue);
	
	return uReceiveBufferSize;

	__LEAVE_FUNCTION_FOXNET

	return 0 ;
}

/**********************************************************************
* 函数名称： SetReceiveBufferSize
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
BOOL Socket::SetReceiveBufferSize(UINT uReceiveBufferSize)
{ 
	__ENTER_FUNCTION_FOXNET

	return (BOOL)(SocketAPI::SetSockoptEx(m_SocketID, SOL_SOCKET, SO_RCVBUF, &uReceiveBufferSize, sizeof(UINT)));

	__LEAVE_FUNCTION_FOXNET

	return FALSE;
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
const UINT Socket::GetSendBufferSize()
{ 
	__ENTER_FUNCTION_FOXNET

	UINT uSendBufferSize = 0;
	INT nSizeOfValue = sizeof(uSendBufferSize);

	SocketAPI::GetSockoptEx(m_SocketID, SOL_SOCKET, SO_SNDBUF, &uSendBufferSize, &nSizeOfValue);
	
	return uSendBufferSize;

	__LEAVE_FUNCTION_FOXNET

	return 0 ;
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
BOOL Socket::SetSendBufferSize(UINT uSendBufferSize)
{ 
	__ENTER_FUNCTION_FOXNET

	return (BOOL)(SocketAPI::SetSockoptEx(m_SocketID, SOL_SOCKET, SO_SNDBUF, &uSendBufferSize, sizeof(UINT)));

	__LEAVE_FUNCTION_FOXNET

	return FALSE ;
}

/**********************************************************************
* 函数名称： SetSockopt
* 功能描述： 
* 输入参数： 
* <param name="nLevel"></param>
* <param name="nOptionName"></param>
* <param name="pOptonValue"></param>
* <param name="pOptionLen"></param>
* 输出参数：
* 返 回 值： 执行成功，返回TRUE；执行失败，返回FALSE
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2011/07/23		V1.0	    huanggenping	创建版本
***********************************************************************/
BOOL Socket::SetSockopt(INT nLevel, INT nOptionName, const VOID* pOptonValue, UINT pOptionLen)
{ 
	__ENTER_FUNCTION_FOXNET

	return (BOOL)SocketAPI::SetSockoptEx(m_SocketID, nLevel, nOptionName, pOptonValue, pOptionLen);

	__LEAVE_FUNCTION_FOXNET

	return FALSE;
}

/**********************************************************************
* 函数名称： ShutDown
* 功能描述： exception version of shutdown()
* 输入参数： 
* <param name="uHow"></param>
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2011/07/23		V1.0	    huanggenping	创建版本
***********************************************************************/
BOOL Socket::ShutDown(UINT uHow)
{
	__ENTER_FUNCTION_FOXNET

	return (BOOL)SocketAPI::ShutDownEx(m_SocketID, uHow);

	__LEAVE_FUNCTION_FOXNET

	return FALSE;
}

/**********************************************************************
* 函数名称： GetPort
* 功能描述： 获取端口
* 输入参数： 
* 输出参数：
* 返 回 值： 返回m_nPort
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2011/07/23		V1.0	    huanggenping	创建版本
***********************************************************************/
const UINT Socket::GetPort() 
{ 
	__ENTER_FUNCTION_FOXNET

	return m_nPort; 

	__LEAVE_FUNCTION_FOXNET
}

/**********************************************************************
* 函数名称： GetHostIP
* 功能描述： 获取连接的Host IP
* 输入参数： 
* 输出参数：
* 返 回 值： 返回连接的Host IP
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2011/07/23		V1.0	    huanggenping	创建版本
***********************************************************************/
const IP_t Socket::GetHostIP() 
{ 
	__ENTER_FUNCTION_FOXNET
	
	return (IP_t)(m_SockAddr.sin_addr.s_addr); 

	__LEAVE_FUNCTION_FOXNET
}


/**********************************************************************
* 函数名称： GetIP
* 功能描述： 获取连接的IP
* 输入参数： 
* 输出参数：
* 返 回 值： 返回连接的IP
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2011/07/23		V1.0	    huanggenping	创建版本
***********************************************************************/
const CHAR * Socket::GetIP()
{
	__ENTER_FUNCTION_FOXNET
	
	return inet_ntoa(m_SockAddr.sin_addr);

	__LEAVE_FUNCTION_FOXNET
}

/**********************************************************************
* 函数名称： IsValid
* 功能描述： 检测Socket套连接字是否有效
* 输入参数： 
* 输出参数：
* 返 回 值： 套连接字有效，返回TRUE；否则，返回FALSE
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2011/07/23		V1.0	    huanggenping	创建版本
***********************************************************************/
const BOOL Socket::IsValid()
{
	__ENTER_FUNCTION_FOXNET

	if (m_SocketID == INVALID_SOCKET)
	{
		return FALSE;
	}
	return TRUE;

	__LEAVE_FUNCTION_FOXNET
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
const SOCKET Socket::GetSOCKET()
{ 
	__ENTER_FUNCTION_FOXNET

	return m_SocketID; 

	__LEAVE_FUNCTION_FOXNET
}

/**********************************************************************
* 函数名称： SetSOCKET
* 功能描述： 设置Socket套连接字
* 输入参数： 
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2011/07/23		V1.0	    huanggenping	创建版本
***********************************************************************/
VOID Socket::SetSOCKET(SOCKET hSocket)
{
	__ENTER_FUNCTION_FOXNET

	m_SocketID = hSocket; 

	__LEAVE_FUNCTION_FOXNET
}

/**********************************************************************
* 函数名称： IsSocketError
* 功能描述： 检测Socket套连接字是否错误
* 输入参数： 
* 输出参数：
* 返 回 值： 套连接字有错，返回TRUE；否则，返回FALSE
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2011/07/23		V1.0	    huanggenping	创建版本
***********************************************************************/
const BOOL Socket::IsSocketError()
{
	__ENTER_FUNCTION_FOXNET

	INT nError = 0;
	UINT nLen = sizeof(nError);
	
	INT nResult = SocketAPI::GetSockoptEx2(m_SocketID, SOL_SOCKET ,SO_ERROR , &nError, &nLen);

	if (nResult == 0) 
	{
		return FALSE;
	}
	else 			  
	{
		return TRUE;
	}

	__LEAVE_FUNCTION_FOXNET

	return FALSE ;
}

/**********************************************************************
* 函数名称： IsReuseAddr
* 功能描述： 
* 输入参数： 
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2011/07/23		V1.0	    huanggenping	创建版本
***********************************************************************/
const BOOL Socket::IsReuseAddr()
{
	__ENTER_FUNCTION_FOXNET 
		
	INT nReuseAddrValue = 0;
	INT nReuseAddrSize = sizeof(nReuseAddrValue);
	
	SocketAPI::GetSockoptEx(m_SocketID, SOL_SOCKET, SO_REUSEADDR, &nReuseAddrValue, &nReuseAddrSize);
	
	if (nReuseAddrValue == 1)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
	__LEAVE_FUNCTION_FOXNET

	return FALSE;
}

/**********************************************************************
* 函数名称： SetReuseAddr
* 功能描述： 
* 输入参数： 
* <param name="bOn"></param>
* 输出参数：
* 返 回 值： 执行成功，返回TRUE；执行失败，返回FALSE
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2011/07/23		V1.0	    huanggenping	创建版本
***********************************************************************/
BOOL Socket::SetReuseAddr(BOOL bOn)
{
	__ENTER_FUNCTION_FOXNET 

	INT nOptionValue = 0;
	if (bOn)
	{
		nOptionValue = 1;
	}
	else
	{
		nOptionValue = 0;
	}
	
	return SocketAPI::SetSockoptEx(m_SocketID, SOL_SOCKET, SO_REUSEADDR, &nOptionValue, sizeof(nOptionValue));
	
	__LEAVE_FUNCTION_FOXNET

	return TRUE ;
}

/**********************************************************************
* 函数名称： GetSockopt
* 功能描述： exception version of getsockopt()
* 输入参数： 
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
UINT Socket::GetSockopt(INT nLevel, INT nOptionName, VOID * pOptonValue, INT * pOptionLen)
{
	__ENTER_FUNCTION_FOXNET

	return SocketAPI::GetSockoptEx(m_SocketID, nLevel, nOptionName, pOptonValue, pOptionLen);

	__LEAVE_FUNCTION_FOXNET

	return 0;
}

/**********************************************************************
* 函数名称： SetSockAddr
* 功能描述： 设置m_SockAddr的指针
* 输入参数： 
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2011/07/23		V1.0	    huanggenping	创建版本
***********************************************************************/
VOID Socket::SetSockAddr(sockaddr *pSockAddr)
{
	memcpy(&m_SockAddr, pSockAddr, sizeof(sockaddr_in));
}

/**********************************************************************
* 函数名称： GetSockAddrIn
* 功能描述： 获取m_SockAddr的指针
* 输入参数： 
* 输出参数：
* 返 回 值： 返回m_SockAddr的指针
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2011/07/23		V1.0	    huanggenping	创建版本
***********************************************************************/
const sockaddr_in* Socket::GetSockAddrIn()
{
	return &m_SockAddr;
}

/**********************************************************************
* 函数名称： SetHost
* 功能描述： 设置m_lpszHost的值
* 输入参数： 
* <param name="lpszHost"></param>
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2011/07/23		V1.0	    huanggenping	创建版本
***********************************************************************/
VOID Socket::SetHost(const CHAR * lpszHost)
{
	strncpy(m_lpszHost, lpszHost, IP_SIZE - 1);
}

/**********************************************************************
* 函数名称： SetPort
* 功能描述： 设置m_nPort的值
* 输入参数： 
* <param name="nPort"></param>
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2011/07/23		V1.0	    huanggenping	创建版本
***********************************************************************/
VOID Socket::SetPort(int nPort)
{
	m_nPort = nPort;
}