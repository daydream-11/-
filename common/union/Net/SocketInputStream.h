//
//文件名称：	SocketInputStream.h
//功能描述：	消息数据的接收缓存，提供数据的接收和格式化读取功能
//				
//
//
#ifndef __SOCKET_INPUT_STREAM_H__
#define __SOCKET_INPUT_STREAM_H__

#include "BaseType.h"
#include "Socket.h"

//初始化的接收缓存长度
#define DEFAULTSOCKETINPUTBUFFERSIZE 20*1024
//最大可以允许的缓存长度，如果超过此数值，则断开连接
#define DISCONNECTSOCKETINPUTSIZE 96*1024

class PlayerConnect;

class SocketInputStream
{
private:

	/** @name 私有成员变量 *///////////////////////////////////////////////////
    /// @{

	// 在Init中申请内存
	CHAR* m_pBuffer;
	// BUFFER的长度,在init中分配
	UINT m_uBufferLen;
	// 已经使用了多少BUFFER，其实是STREAM的长度
	UINT m_uBufferUse;
	// 跟客户端连接的对象
	PlayerConnect* m_pPlayerConnect;

	/// @}

public :
	SocketInputStream();
	~SocketInputStream();


public :

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
	VOID Init(PlayerConnect* pPlayerConnect);

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
	VOID InitBuffer(INT uBufferLen);

	/**********************************************************************
	* 函数名称： ProcessBuffer
	* 功能描述： 处理粘包的函数
	* 输入参数： 
	* <param name="lpszBuffer"></param>
	* <param name="dwBufferLen"></param>
	* 输出参数：
	* 返 回 值： 
	* 其它说明： 
	* 修改日期			版本号		修改人			修改内容
	* ---------------------------------------------------------------------
	* 2011/07/23		V1.0	    huanggenping	创建版本
	***********************************************************************/
	VOID ProcessBuffer(const char *lpszBuffer, INT nBufferLen);
	
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
	VOID LoopProcessBuf(UINT & uMsgCount);

	/// @}

};




#endif	// __SOCKET_INPUT_STREAM_H__
