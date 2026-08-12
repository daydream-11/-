#include "stdafx.h"
#include "SocketInputStream.h"
#include "PlayerConnect.h"

SocketInputStream::SocketInputStream() 
{
__ENTER_FUNCTION_FOXNET

	m_uBufferUse = 0;
	m_uBufferLen = 0;
	m_pPlayerConnect = NULL;
	m_pBuffer = NULL;

__LEAVE_FUNCTION_FOXNET
}

SocketInputStream::~SocketInputStream() 
{
__ENTER_FUNCTION_FOXNET
		
	SAFE_DELETE_ARRAY(m_pBuffer);
		
__LEAVE_FUNCTION_FOXNET
}


/** @name 公共成员函数 *///////////////////////////////////////////////////
/// @{

/**********************************************************************
* 函数名称： Init
* 功能描述： 初始化输入Socket消息流
* 输入参数： 
* <param name="pPlayerConnect">对应的连接对象</param>
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2011/07/23		V1.0	    huanggenping	创建版本
***********************************************************************/
VOID SocketInputStream::Init(PlayerConnect* pPlayerConnect)
{
	__ENTER_FUNCTION_FOXNET

	m_pPlayerConnect = pPlayerConnect;

	__LEAVE_FUNCTION_FOXNET
}

/**********************************************************************
* 函数名称： InitBuffer
* 功能描述： 初始化接受缓冲区
* 输入参数：
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2011/07/23		V1.0	    huanggenping	创建版本
***********************************************************************/
VOID SocketInputStream::InitBuffer(INT uBufferLen)
{
	__ENTER_FUNCTION_FOXNET

	m_uBufferLen = uBufferLen;
	if (m_pBuffer == NULL)
	{
		m_pBuffer = new CHAR[m_uBufferLen];
	}
	memset(m_pBuffer, 0, m_uBufferLen);

	__LEAVE_FUNCTION_FOXNET
}


/**********************************************************************
* 函数名称： ProcessBuffer
* 功能描述： 处理粘包的函数
* 输入参数： 
* <param name="lpszBuffer"></param>
* <param name="nBufferLen"></param>
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2011/07/23		V1.0	    huanggenping	创建版本
***********************************************************************/
VOID SocketInputStream::ProcessBuffer(const CHAR *lpszBuffer, INT nBufferLen)
{
	CHAR *lpszRecvBuffer = (CHAR*)lpszBuffer;
	static INT nLastStaticMsgID = 0;
	static INT nLastStaticMsgLen = 0;
	if (nBufferLen >= PACKET_HEADER_SIZE)
	{
		if (lpszRecvBuffer[0] == 't' && lpszRecvBuffer[1] == 'g' && lpszRecvBuffer[2] == 'w')
		{
			CHAR szTGWValue[500] = {'\0'};
			BOOL bFindNextPacket = FALSE;
			for (int i = 3; i < nBufferLen; i++)
			{
				if ((lpszRecvBuffer[i] == 0x7B) && (lpszRecvBuffer[i + 1] == 0x7D))	//
				{
					memcpy(szTGWValue, lpszBuffer, i);
					bFindNextPacket = TRUE;
					// 过虑腾讯的tgw消息包头
					lpszRecvBuffer += i;
					nBufferLen -= i;
					break;
				}
			}
			if (!bFindNextPacket)
			{
				memcpy(szTGWValue, lpszBuffer, nBufferLen);
				//Log::SaveLog("./Game/tgw.log", szTGWValue);
				return;
			}
			//Log::SaveLog("./Game/tgw.log", szTGWValue);
		}
		if ((lpszRecvBuffer[0] == 0x7B) && (lpszRecvBuffer[1] == 0x7D))	//
		{
			PacketHeader *pPacketHeader = (PacketHeader*)lpszRecvBuffer;
			nLastStaticMsgID = pPacketHeader->packetID;
			nLastStaticMsgLen = pPacketHeader->uPacketLen;
			//m_pPlayerConnect->WriteLog("收到消息命令【%d】长度【%d】", pPacketHeader->packetID, pPacketHeader->uPacketLen);
			INT nPacketSize =  pPacketHeader->uPacketLen;
			if (nPacketSize > MAX_MSG_LEN || nPacketSize < PACKET_HEADER_SIZE) // 大于允许最大消息包长度
			{
				// 服务器消息包太大
				//CHAR szLog[200] = {'\0'};
				//sprintf(szLog, "接收【%d】服务器消息【%d】包太大【0】", m_pPlayerConnect->GetPlayer()->GetPlayerID(), pPacketHeader->packetID);
				//OnProcessSetLogProc(szLog);
				m_pPlayerConnect->SetConnectStatus(EErrorConnected);
				m_pPlayerConnect->GetSocket()->Close();
				return;
			}
			if (nBufferLen == nPacketSize)
			{
				// 长度相符，正好一个完整包
				m_pPlayerConnect->OnPushMsg(pPacketHeader, nPacketSize); 
				return;
			}
		}
	}

	// 把收到的消息拷贝到缓冲区
	if ((m_uBufferUse + nBufferLen) >= m_uBufferLen)
	{
		m_pPlayerConnect->SetConnectStatus(EErrorConnected);
		return;
	}
	memcpy((m_pBuffer + m_uBufferUse), lpszRecvBuffer, nBufferLen);
	m_uBufferUse += nBufferLen;

	UINT uMsgCount = 0;
	// 轮询看是已经有完整消息包
	LoopProcessBuf(uMsgCount);
	if ((m_uBufferUse >= MAX_MSG_LEN) && (uMsgCount == 0))	//在缓冲区已经大于最大单个消息包，并且里面没有一个消息包的包头标识，错误
	{
		m_pPlayerConnect->SetConnectStatus(EErrorConnected);
		//
		if (m_pPlayerConnect->GetPlayer()->GetPlayerID() < 100000)
		{
			// 服务器消息包太大
			//CHAR szLog[200] = {'\0'};
			//sprintf(szLog, "接收【%d】服务器消息包错误，上一个消息【ID：%d】【大小：%d】【0】", m_pPlayerConnect->GetPlayer()->GetPlayerID(), nLastStaticMsgID, nLastStaticMsgLen);
			//OnProcessSetLogProc(szLog);
		}
		return;
	}
}

/**********************************************************************
* 函数名称： LoopProcessBuf
* 功能描述： 循环处理缓冲区
* 输入参数： 
* <param name="uMsgCount">返回消息个数</param>
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2011/07/23		V1.0	    huanggenping	创建版本
***********************************************************************/
VOID SocketInputStream::LoopProcessBuf(UINT & uMsgCount)
{
	static INT nLastStaticMsgID = 0;
	static INT nLastStaticMsgLen = 0;
	CHAR szLog[200] = {'\0'};
	if ((m_pBuffer[0] == 0x7B) && (m_pBuffer[1] == 0x7D))
	{
		if (m_uBufferUse >= PACKET_HEADER_SIZE)
		{
			PacketHeader *pPacketHeader = (PacketHeader*)m_pBuffer;
			//
			nLastStaticMsgID = pPacketHeader->packetID;
			nLastStaticMsgLen = pPacketHeader->uPacketLen;
			//
			INT nPacketSize =  pPacketHeader->uPacketLen;
			//m_pPlayerConnect->WriteLog("收到消息命令【%d】长度【%d】", pPacketHeader->packetID, pPacketHeader->uPacketLen);
			if (nPacketSize > MAX_MSG_LEN || nPacketSize < PACKET_HEADER_SIZE) // 大于允许最大消息包长度
			{
				m_pPlayerConnect->SetConnectStatus(EErrorConnected);
				m_pPlayerConnect->GetSocket()->Close();
				// 服务器消息包太大
				//CHAR szLog[200] = {'\0'};
				//sprintf(szLog, "接收【%d】服务器消息【%d】包太大【1】", m_pPlayerConnect->GetPlayer()->GetPlayerID(), pPacketHeader->packetID);
				//OnProcessSetLogProc(szLog);
				return;
			}
			if (m_uBufferUse == (UINT)nPacketSize) // 长度相符，正好一个完整包
			{
				m_pPlayerConnect->OnPushMsg(pPacketHeader, nPacketSize); 
				++uMsgCount;
				m_uBufferUse = 0;
				return;
			}
			else if (m_uBufferUse > (UINT)nPacketSize) // 缓冲区里有其它消息包
			{
				m_pPlayerConnect->OnPushMsg(pPacketHeader, nPacketSize);
				++uMsgCount;
				//内存移动
				memmove(m_pBuffer, (m_pBuffer + nPacketSize), (m_uBufferUse - nPacketSize));
				m_uBufferUse -= nPacketSize;
				LoopProcessBuf(uMsgCount);// 重新新的调用
			}
		}
	}
	else
	{
		m_pPlayerConnect->SetConnectStatus(EErrorConnected);
		m_pPlayerConnect->GetSocket()->Close();
		// 数据包错误
		//CHAR szLog[200] = {'\0'};
		//sprintf(szLog, "接收【%d】服务器消息包错误，上一个消息【ID：%d】【大小：%d】【BufferUser: %d】【1】", m_pPlayerConnect->GetPlayer()->GetPlayerID(), nLastStaticMsgID, nLastStaticMsgLen, m_uBufferUse);
		//OnProcessSetLogProc(szLog);
	}
}

/// @}