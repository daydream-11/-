#include "stdafx.h"
#if defined(__LINUX__)
#include "Epoll.h"

Epoll::Epoll() 
{
	m_epfd = 0;
}

Epoll::~Epoll()
{
	Exit();
}

BOOL Epoll::Create(UINT uSize)
{
	m_epfd = epoll_create(uSize);

	if ( m_epfd < 0 )
	{
		perror("m_epfd<0");

		return FALSE;
	}

	return TRUE;
}

int Epoll::SetNonblocking(int nSocketFD)
{
	int flag = 1;
	if (ioctl(nSocketFD, FIONBIO, &flag) && ((flag = fcntl(nSocketFD, F_GETFL, 0)) < 0 || fcntl(nSocketFD, F_SETFL, flag|O_NONBLOCK) < 0))
	{
		return errno;
	}
	return 0;
}

int Epoll::Add(INT nSocketFD, SEpollObjectInfo* pEpollObjInfo, unsigned int iEvent)
{
	if (nSocketFD < 0 || NULL == pEpollObjInfo)
	{
		return -1;
	}
	epoll_event myEpollEvent;
	myEpollEvent.events = iEvent | EPOLLET | EPOLLERR | EPOLLHUP;
	myEpollEvent.data.u64 = (uint64)pEpollObjInfo;
	
	INT nReturn  = SetNonblocking(nSocketFD);
	if (nReturn)
	{
		return nReturn;
	}
	
	nReturn = epoll_ctl(m_epfd, EPOLL_CTL_ADD, nSocketFD, &myEpollEvent);

	if (nReturn)
	{
		perror("epoll_ctl Add field!");
	}

	return nReturn;

}

int Epoll::Mod(int nSocketFD, SEpollObjectInfo* pEpollObjInfo, unsigned int iEvent)
{
	if (nSocketFD < 0 || NULL == pEpollObjInfo)
	{
		return -1;
	}
	epoll_event myEpollEvent;
	myEpollEvent.events = iEvent | EPOLLET | EPOLLERR | EPOLLHUP;
	myEpollEvent.data.u64 = (uint64)pEpollObjInfo;
	//
	int nReturn = epoll_ctl(m_epfd, EPOLL_CTL_MOD, nSocketFD, &myEpollEvent);
	//
	if (nReturn)
	{
		perror("epoll_ctl Mod field!");
	}

	return nReturn;

}

int Epoll::Del(int nSocketFD, SEpollObjectInfo* pEpollObjInfo, unsigned int iEvent)
{
	if (nSocketFD < 0 || NULL == pEpollObjInfo)
	{
		return -1;
	}
	epoll_event myEpollEvent;
	myEpollEvent.events = 0;
	myEpollEvent.data.u64 = (uint64)pEpollObjInfo;
	//
	int nReturn = epoll_ctl(m_epfd, EPOLL_CTL_DEL, nSocketFD, &myEpollEvent);
	//
	if (nReturn)
	{
		perror("epoll_ctl Del field!");
	}

	return nReturn;

}

void Epoll::Exit()
{
	if ( m_epfd > 0 )
	{
		close(m_epfd);
		m_epfd = 0;
	}
}

#endif	// __LINUX__

