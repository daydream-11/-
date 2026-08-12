/*********************************************************************
* 版权所有 (C)2008, 深圳市新飞杨数码科技有限公司。
* 
* 文件名称： SocketAPI.h
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

#ifndef __SOCKET_API_H__
#define __SOCKET_API_H__

#include "BaseType.h"
#if defined (__WINDOWS__)
#include <WinSock2.h>
#include <mswsock.h>
#elif defined (__LINUX__)
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <fcntl.h>
#endif

#if defined (__LINUX__)
typedef		INT		SOCKET;
#define     INVALID_SOCKET   -1
#define		SOCKET_ERROR	 -1
#endif

#define ERROR_SIZE 256

static const INT SOCKET_ERROR_WOULDBLOCK = -100;


//////////////////////////////////////////////////////////////////////
//
// Platform Independent Socket API Collection (exception based)
//
//////////////////////////////////////////////////////////////////////
namespace SocketAPI 
{

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
	BOOL GetLastErrorEx();

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
	BOOL StartupSocket();

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
	VOID CleanupSocket();

	/**********************************************************************
	* 函数名称： SocketEx
	* 功能描述： exception version of socket()
	* 输入参数： 
	* <param name="nSocketType">SOCKET类型（SOCK_STREAM为TCP/IP，SOCK_DGRAM为UDP）</param>
	* <param name="nProtocolType"></param>
	* <param name="nProtocol"></param>
	* 输出参数：
	* 返 回 值： 
	* 其它说明： 
	* 修改日期			版本号		修改人			修改内容
	* ---------------------------------------------------------------------
	* 2011/07/23		V1.0	    huanggenping	创建版本
	***********************************************************************/
	SOCKET SocketEx(INT nSocketType, INT nProtocolType, INT nProtocol);

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
	SOCKET WSASocketEx(INT nSocketType , INT nProtocolType , INT nProtocol, INT nFlags);

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
	BOOL BindEx(SOCKET hSocket, const struct sockaddr* lpSocketAddress, UINT nSocketAddressLen);

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
	BOOL ConnectEx(SOCKET hSocket, const struct sockaddr * lpSocketAddress, UINT nSocketAddressLen);

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
	BOOL ListenEx(SOCKET hSocket, UINT nBacklog);

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
	SOCKET AcceptEx(SOCKET hSocket, struct sockaddr * lpSocketAddress, UINT * pSocketAddressLen);

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
	BOOL GetSockoptEx(SOCKET hSocket, INT nLevel, INT nOptionName, VOID * pOptonValue, INT * pOptionLen);

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
	UINT GetSockoptEx2(SOCKET hSocket, INT nLevel, INT nOptionName, VOID * pOptonValue, UINT * pOptionLen);

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
	BOOL SetSockoptEx(SOCKET hSocket, INT nLevel, INT nOptionName, const VOID* pOptonValue, UINT pOptionLen);

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
	INT SendEx(SOCKET hSocket, const VOID * pBuffer, UINT nBufferLen, UINT nFlag);
	
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
	UINT SendToEx(SOCKET hSocket, const VOID * pBuffer, INT nBufferLen, UINT nFlag, const struct sockaddr * lpSocketAddress, INT nSocketAddressLen);

	/**********************************************************************
	* 函数名称： SendToEx
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
	UINT RecvEx(SOCKET hSocket, VOID * pBuffer, UINT nBufferLen, UINT nFlag);

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
	INT WSARecvEx(SOCKET hSocket, LPWSABUF pBuffer, UINT uBufferCount, LPDWORD pNumberOfBytesRecvd, LPDWORD pFlags, LPWSAOVERLAPPED lpOverlapped, LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine);
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
	INT WSASendEx(SOCKET hSocket, LPWSABUF pBuffer, UINT uBufferCount, LPDWORD pNumberOfBytesSend, DWORD dwFlags, LPWSAOVERLAPPED lpOverlapped, LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine);
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
	UINT RecvFromEx(SOCKET hSocket, VOID * pBuffer, INT nBufferLen, UINT nFlag, struct sockaddr * lpSocketAddress, UINT* pSocketAddressLen);

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
	BOOL CloseSocketEx (SOCKET hSocket);

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
	BOOL IoctlSocketEx (SOCKET hSocket, LONG lCommand, ULONG* puArgp);

	/**********************************************************************
	* 函数名称： GetSocketNonblockingEx
	* 功能描述： check if socket is nonblocking mode
	* 输入参数： 
	* <param name="hSocket"></param>
	* 输出参数：
	* 返 回 值： 
	* 其它说明： 
	* 修改日期			版本号		修改人			修改内容
	* ---------------------------------------------------------------------
	* 2011/07/23		V1.0	    huanggenping	创建版本
	***********************************************************************/
	BOOL GetSocketNonblockingEx(SOCKET hSocket);

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
	BOOL SetSocketNonblockingEx(SOCKET hSocket, BOOL bOn);

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
	UINT AvailableSocketEx (SOCKET hSocket);

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
	BOOL ShutDownEx(SOCKET hSocket, UINT nHow);

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
	INT SelectEx(INT maxfdp1, fd_set * pReadSet, fd_set * pWriteSet, fd_set * pExceptSet, struct timeval * pTimeOut);


};//end of namespace 



#endif // __SOCKET_API_H__
