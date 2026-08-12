#ifndef __IOCP_INTERFACE_H__
#define __IOCP_INTERFACE_H__

#include "GameType.h"
#include "SocketAPI.h"
#include "IPlayerConnect.h"
#include <vector>
using namespace std;

#define IODATABUFLEN	8192		//取 SERVERSENDBUFLEN 以及 SERVERRECVBUFLEN的最大值

// 异步IO类型
enum AsynIOType
{
	ASYN_IO_UNKOWN	= 0,
	ASYN_IO_READ	= 1,
	ASYN_IO_WRITE   = 2,
	ASYN_IO_ACCEPT  = 3,
	ASYN_IO_WRITE_CLIENT   = 4,
};

enum AllotType
{
	// 预分配
	ALLOT_POOL = 0,
	// New分配
	ALLOT_NEW = 1,
};


//一些基本的数值定义
#define SERVERSENDBUFLEN 8192		//服务端连接SOCKET的发送缓冲区大小,setsockopt
#define SERVERRECVBUFLEN 8192		//服务端连接SOCKET的接收缓冲区大小,setsockopt

#define CLIENTSENDBUFLEN 8192		//客户端的连接SOCKET发送缓冲区大小,setsockopt
#define CLIENTRECVBUFLEN 8192		//客户端的连接SOCKET接收缓冲区大小,setsockopt

#define NETSTREAMLEN	8192		//消息流的大小(用于处理粘包)

#define KEEPLIVETIME	120 * 1000	//客户端应该每10秒发一个心跳包，心跳可以检测两次机会

#define LINK_SOCONNECTTIME_SEC	20	//客户端恶意连接上20秒内不发消息
// 最大Buff数目
#define	MAX_ASYN_IO_BUFF_COUNT 16

// 处理网络消息
typedef VOID(WINAPI* ProcessNetworkMsgProc)(CHAR *pPacketMsg, INT nPacketSize, VOID *pPlayerConnect);
// 处理日志
typedef VOID(WINAPI* ProcessSetLogProc)(CHAR* szLog);


// 配置文件结构
struct SClientConfig
{
	// 最大分配连接数
	UINT uMaxConnect;
	// 开始索引ID
	UINT uStartConnectIndex;
	// 最大分配发送IO数
	UINT uMaxSendIOResult;
	// IO内存配置格式
	TVectorIOMemoryConfig *pVectorIOMemoryConfig;
};

// 配置文件结构
struct SConnectConfig
{
	// 端口号
	UINT uPort;
	// 最大监听数
	UINT uBackLog;
	// 最大分配连接数
	UINT uMaxConnect;
	// 最多同时连接数
	UINT uMaxAccpet;
	// 最大分配发送IO数
	UINT uMaxSendIOResult;
	// 连接的索引起始值
	UINT uStartConnectIndex;
	// IO内存配置格式
	TVectorIOMemoryConfig *pVectorIOMemoryConfig;
};

// IO缓冲区
struct AsynIoData
{
	VOID *pBaseIOData;
};

// IO缓冲区
struct AsynIoBuffer
{
	INT		len;
	CHAR*	buf;
};

#ifdef __WINDOWS__

struct AsynIOResult : public OVERLAPPED
{
	// 操作类型（自定义）
	AsynIOType nAsynIOType;
	// 分配类型
	AllotType nAllotType;
	// 绑定的连接
	VOID* pConnect;
};

#elif defined (__LINUX__)

struct AsynIOResult
{
	// 操作类型（自定义）
	AsynIOType nAsynIOType;
	// 分配类型
	AllotType nAllotType;
	// 绑定的连接
	VOID* pConnect;
};

#endif

struct BaseIOData : public AsynIOResult
{
	// 分配类型
	AllotType nAllotType;
	// 用于socket的缓冲结构
	AsynIoBuffer wsaBuf;
	// 有效数据长度
	INT nDataLen;
	// 指向IODataMemory
	VOID *pDataMemory;
};


struct AsynRecvIOResult : public AsynIOResult
{
	// 用于socket的缓冲结构
	AsynIoBuffer wsaBuf;
	// 有效数据长度
	INT nDataLen;
	// 真实的数据缓冲区
	CHAR szDataBuf[IODATABUFLEN];
	// 获取缓冲区信息
	AsynIoBuffer* GetBufferList()
	{
		return &wsaBuf;
	}
	// 获取缓冲区数量
	UINT GetBufferCount()
	{
		return 1;
	}
	// 获取连接对象
	VOID* GetConnect()
	{
		return pConnect;
	}
	// 设置连接对象
	VOID SetConnect(VOID *pConnect)
	{
		this->pConnect = pConnect;
	}
};

struct AsynSendIOResult : public AsynIOResult
{
	AsynIoBuffer asynIoBufferArray[MAX_ASYN_IO_BUFF_COUNT];
	AsynIoData asynIoDataArray[MAX_ASYN_IO_BUFF_COUNT];
	INT nBufferCount;
	VOID *pConnect;
	//
	VOID Init(UINT uIndex)
	{

	}
	// 获取缓冲区信息
	AsynIoBuffer* GetBufferList()
	{
		return asynIoBufferArray;
	}
	// 获取缓冲区数量
	UINT GetBufferCount()
	{
		return nBufferCount;
	}
	// 获取连接对象
	VOID* GetConnect()
	{
		return pConnect;
	}
	// 设置连接对象
	VOID SetConnect(VOID *pConnect)
	{
		this->pConnect = pConnect;
	}
	AsynIoData* GetAsynIoDataArray()
	{
		return asynIoDataArray;
	}
	VOID Clear()
	{
		memset(asynIoBufferArray, 0, sizeof(asynIoBufferArray));
		memset(asynIoDataArray, 0, sizeof(asynIoDataArray));
		nBufferCount = 0;
		pConnect = NULL;
	}
};

// 发送最大延迟包数
enum
{
	EMaxSendDelay = 512
};
// 连接的状态
enum EConnectStatus
{
	// 初始化的值
	ENotConnected,
	// 在ListenThreadProc中对象池中取出后，但还没被aCCEPT时的值
	EWaitConnected,
	// 连接上
	EAlreadyConnected,
	// 在连接过程中有错误发生 在设置超检查和接收消息时设置
	EErrorConnected
};

class PlayerConnect;

#include <map>
#include <vector>
using namespace std;

typedef map<UINT, PlayerConnect*> TMapPlayerConnect;
typedef vector<PlayerConnect*> TVectorPlayerConnect;	

#endif	// __IOCP_INTERFACE_H__
