/*********************************************************************
* 版权所有 (C)2008, 深圳市新飞杨数码科技有限公司。
* 
* 文件名称： FileAPI.cpp
* 文件标识： 
* 内容摘要： 对文件进行一个简单的封装操作，针对Windows的操作系统
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
#include "FileAPI.h"

#if defined(__WINDOWS__)
#include <io.h>			// for _open()
#include <fcntl.h>		// for _open()/_close()/_read()/_write()...
#include <string.h>		// for memcpy()
#elif defined(__LINUX__)
#include <sys/types.h>	// for open()
#include <sys/stat.h>	// for open()
#include <unistd.h>		// for fcntl()
#include <fcntl.h>		// for fcntl()
#include <sys/ioctl.h>	// for ioctl()
#include <errno.h>		// for errno
#endif



/**********************************************************************
* 函数名称： OpenEx
* 功能描述： exception version of open()
* 输入参数： 
* <param name="lpszFileName"></param>
* <param name="nFlag"></param>
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2011/07/23		V1.0	    huanggenping	创建版本
***********************************************************************/
INT FileAPI::OpenEx(const CHAR * lpszFileName, INT nFlag) 
{
	__ENTER_FUNCTION_FOXNET

#if defined(__WINDOWS__)
	INT fd = _open(lpszFileName, nFlag);
#elif defined(__LINUX__)
	INT fd = open(lpszFileName, nFlag);
#endif
	
	return fd;

	__LEAVE_FUNCTION_FOXNET
}

/**********************************************************************
* 函数名称： OpenEx
* 功能描述： exception version of open()
* 输入参数： 
* <param name="lpszFileName"></param>
* <param name="nFlag"></param>
* <param name="nMode"></param>
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2011/07/23		V1.0	    huanggenping	创建版本
***********************************************************************/
INT FileAPI::OpenEx(const CHAR * lpszFileName, INT nFlag, INT nMode) 
{
	__ENTER_FUNCTION_FOXNET

#if defined(__WINDOWS__)
	INT fd = _open(lpszFileName, nFlag, nMode);
#elif defined(__LINUX__)
	INT fd = open(lpszFileName, nFlag, nMode);
#endif
	

	return fd;

	__LEAVE_FUNCTION_FOXNET
}

/**********************************************************************
* 函数名称： ReadEx
* 功能描述： 读取文件
* 输入参数： 
* <param name="fd"></param>
* <param name="pBuffer"></param>
* <param name="uBufferLen"></param>
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2011/07/23		V1.0	    huanggenping	创建版本
***********************************************************************/
UINT FileAPI::ReadEx(INT fd, VOID * pBuffer, UINT uBufferLen) 
{
	__ENTER_FUNCTION_FOXNET

#if defined(__WINDOWS__)
	INT nResult = _read(fd, pBuffer, uBufferLen);
#elif defined(__LINUX__)
	INT nResult = read (fd, pBuffer, uBufferLen);
#endif
	

	return nResult;

	__LEAVE_FUNCTION_FOXNET
}

/**********************************************************************
* 函数名称： WriteEx
* 功能描述： 写入文件
* 输入参数： 
* <param name="fd"></param>
* <param name="pBuffer"></param>
* <param name="uBufferLen"></param>
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2011/07/23		V1.0	    huanggenping	创建版本
***********************************************************************/
UINT FileAPI::WriteEx(INT fd, const VOID * pBuffer, UINT uBufferLen) 
{
	__ENTER_FUNCTION_FOXNET

#if defined(__WINDOWS__)
	INT nResult = _write(fd, pBuffer, uBufferLen);
#elif defined(__LINUX__)
	INT nResult = write(fd, pBuffer, uBufferLen);
#endif
	

	return nResult;

	__LEAVE_FUNCTION_FOXNET
}


/**********************************************************************
* 函数名称： CloseEx
* 功能描述： exception version of close()
* 输入参数： 
* <param name="fd"></param>
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2011/07/23		V1.0	    huanggenping	创建版本
***********************************************************************/
BOOL FileAPI::CloseEx (INT fd) 
{
	__ENTER_FUNCTION_FOXNET

	if (close(fd) < 0) 
	{
		return FALSE;
	}

	return TRUE;

	__LEAVE_FUNCTION_FOXNET

	return FALSE;
}

/**********************************************************************
* 函数名称： FcntlEx
* 功能描述： exception version of fcntl ()
* 输入参数： 
* <param name="fd"></param>
* <param name="nCommand"></param>
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2011/07/23		V1.0	    huanggenping	创建版本
***********************************************************************/
INT FileAPI::FcntlEx(INT fd, INT nCommand) 
{
	__ENTER_FUNCTION_FOXNET

#if defined(__WINDOWS__)
	return 0;
#elif defined(__LINUX__)
	INT nResult = fcntl(fd, nCommand);
	if (nResult < 0) 
	{
		
	}
	return nResult;
#endif

	__LEAVE_FUNCTION_FOXNET
}

/**********************************************************************
* 函数名称： FcntlEx
* 功能描述： exception version of fcntl ()
* 输入参数： 
* <param name="fd"></param>
* <param name="nCommand"></param>
* <param name="lArg"></param>
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2011/07/23		V1.0	    huanggenping	创建版本
***********************************************************************/
INT FileAPI::FcntlEx(INT fd, INT nCommand, LONG lArg) 
{
	__ENTER_FUNCTION_FOXNET

#if defined(__LINUX__)
	INT nResult = fcntl(fd, nCommand, lArg);
	if (nResult < 0)
	{

	}
	return nResult;
#elif defined(__WINDOWS__)
	return 0 ;
#else
	return 0;
#endif

	__LEAVE_FUNCTION_FOXNET
}


/**********************************************************************
* 函数名称： GetFileNonblockingEx
* 功能描述： is this stream is nonblocking?
* 输入参数： 
* <param name="fd"></param>
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2011/07/23		V1.0	    huanggenping	创建版本
***********************************************************************/
BOOL FileAPI::GetFileNonblockingEx(INT fd) 
{
	__ENTER_FUNCTION_FOXNET

#if defined(__LINUX__)
	INT nFlag = FcntlEx(fd, F_GETFL, 0);
	return nFlag | O_NONBLOCK;
#elif defined(__WINDOWS__)
	return FALSE;
#else
	return FALSE;
#endif

	__LEAVE_FUNCTION_FOXNET
}

/**********************************************************************
* 函数名称： SetFileNonblockingEx
* 功能描述： make this strema blocking/nonblocking
* 输入参数： 
* <param name="fd"></param>
* <param name="bOn"></param>
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2011/07/23		V1.0	    huanggenping	创建版本
***********************************************************************/
VOID FileAPI::SetFileNonblockingEx(INT fd, BOOL bOn) 
{
	__ENTER_FUNCTION_FOXNET

#if defined(__LINUX__)
	INT nFlag = FcntlEx(fd, F_GETFL, 0);

	if (bOn)
	{
		nFlag |= O_NONBLOCK;
	}
	else
	{
		nFlag &= ~O_NONBLOCK;
	}
	FcntlEx( fd , F_SETFL , nFlag );
#elif defined(__WINDOWS__)

#endif

	__LEAVE_FUNCTION_FOXNET
}


/**********************************************************************
* 函数名称： IoctlEx
* 功能描述： exception version of ioctl()
* 输入参数： 
* <param name="fd"></param>
* <param name="nRequest"></param>
* <param name="pArgp"></param>
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2011/07/23		V1.0	    huanggenping	创建版本
***********************************************************************/
VOID FileAPI::IoctlEx(INT fd, INT nRequest, VOID * pArgp)
{
	__ENTER_FUNCTION_FOXNET

#if defined(__LINUX__)
	if (ioctl(fd, nRequest, pArgp) < 0 ) 
	{
		
	}
#elif defined(__WINDOWS__)
#endif

	__LEAVE_FUNCTION_FOXNET
}


/**********************************************************************
* 函数名称： SetFileNonblockingEx2
* 功能描述： make this stream blocking/nonblocking
* 输入参数： 
* <param name="fd"></param>
* <param name="bOn"></param>
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2011/07/23		V1.0	    huanggenping	创建版本
***********************************************************************/
VOID FileAPI::SetFileNonblockingEx2(INT fd, BOOL bOn)
{
	__ENTER_FUNCTION_FOXNET

#if defined(__LINUX__)
	ULONG uArg = 0;
	if (bOn)
	{
		uArg = 1;
	}
	else
	{
		uArg = 0;
	}
	IoctlEx(fd, FIONBIO, &uArg);
#elif defined(__WINDOWS__)
#endif

	__LEAVE_FUNCTION_FOXNET
}

/**********************************************************************
* 函数名称： AvailableFileEx
* 功能描述： how much bytes available in this stream?
* 输入参数： 
* <param name="fd"></param>
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2011/07/23		V1.0	    huanggenping	创建版本
***********************************************************************/
UINT FileAPI::AvailableFileEx(INT fd)
{
	__ENTER_FUNCTION_FOXNET

#if defined(__LINUX__)
	UINT uArg = 0;
	IoctlEx(fd, FIONREAD, &uArg);
	return uArg;
#elif defined(__WINDOWS__)
	return 0;
#else
	return 0;
#endif

	__LEAVE_FUNCTION_FOXNET
}

/**********************************************************************
* 函数名称： DupEx
* 功能描述： exception version of dup()
* 输入参数： 
* <param name="fd"></param>
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2011/07/23		V1.0	    huanggenping	创建版本
***********************************************************************/
INT FileAPI::DupEx(INT fd)
{
	__ENTER_FUNCTION_FOXNET

	INT nNewfd = 0;
#if defined(__LINUX__)
	nNewfd = dup(fd);
#elif defined(__WINDOWS__)
	nNewfd = _dup(fd);
#endif

	if (nNewfd < 0) 
	{
#if defined(__LINUX__)
		
#elif defined(__WINDOWS__)

#endif
	}

	return nNewfd;

	__LEAVE_FUNCTION_FOXNET
}


/**********************************************************************
* 函数名称： LseekEx
* 功能描述： exception version of lseek()
* 输入参数： 
* <param name="fd"></param>
* <param name="lOffset"></param>
* <param name="nWhence"></param>
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2011/07/23		V1.0	    huanggenping	创建版本
***********************************************************************/
LONG FileAPI::LseekEx(INT fd, LONG lOffset, INT nWhence)
{
	__ENTER_FUNCTION_FOXNET

	LONG lResult = 0;
#if defined(__LINUX__)
	lResult = lseek(fd, lOffset, nWhence);
	if (lResult < 0) 
	{
		
	}
#elif defined(__WINDOWS__)
	lResult = _lseek(fd, lOffset, nWhence);
	if ( lResult < 0 )
	{

	}
#endif

	return lResult;

	__LEAVE_FUNCTION_FOXNET

}

/**********************************************************************
* 函数名称： TellEx
* 功能描述： exception version of tell()
* 输入参数： 
* <param name="fd"></param>
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2011/07/23		V1.0	    huanggenping	创建版本
***********************************************************************/
LONG FileAPI::TellEx(INT fd)
{
	__ENTER_FUNCTION_FOXNET

	LONG lResult = 0;
#if defined(__LINUX__)
	lResult = 0;
#elif defined(__WINDOWS__)
	lResult = _tell(fd);
	if (lResult < 0)
	{

	}
#endif

	return lResult;

	__LEAVE_FUNCTION_FOXNET
}

