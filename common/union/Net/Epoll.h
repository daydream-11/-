#ifndef __EPOLL_H__
#define __EPOLL_H__

#if defined(__LINUX__)

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <assert.h>
#include <stdio.h>

#include "BaseType.h"

#define MAX_EPOLL_FD_SIZE	20000
#define MAX_EPOLL_TIME_OUT	500
#define MAX_WAIT_SIZE		20000

struct SEpollObjectInfo
{
	// 链接对象
	VOID *pPlayerConnect;
	// 网络类型
	UINT uAsynNetType;
	//
	SEpollObjectInfo()
	{
		pPlayerConnect = NULL;
		uAsynNetType = 0;
	}
};

/**
* Epoll封装类
**/
class Epoll
{
public:
	Epoll();
	~Epoll();

public:

	BOOL Create(UINT uSize);

	int Add(int nSocketFD, SEpollObjectInfo* pEpollObjInfo, unsigned int iEvent);

	int Mod(int nSocketFD, SEpollObjectInfo* pEpollObjInfo, unsigned int iEvent);

	int Del(int nSocketFD, SEpollObjectInfo* pEpollObjInfo, unsigned int iEvent = EPOLLIN);

	void Exit();

private:
	int SetNonblocking(int nSocketFD);

public:
	int				m_epfd;			//epoll 文件描述符
};


#endif	// __LINUX__

#endif //__EPOLL_H__

