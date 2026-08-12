#include "stdafx.h"

#include "File.h"
#include "Assertx.h"


/** @name 构造与析构 */////////////////////////////////////////////////////
/// @{

/**********************************************************************
* 函数名称： File
* 功能描述： 构造函数
* 输入参数： 
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2011/07/23		V1.0	    huanggenping	创建版本
***********************************************************************/
File::File()
{
	__ENTER_FUNCTION

	m_fd = INVALID_HANDLE ;
	memset( m_lpszFileName, 0, _MAX_PATH ) ;

	__LEAVE_FUNCTION
}

/**********************************************************************
* 函数名称： File
* 功能描述： 构造函数
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
File::File(const CHAR * lpszFileName, INT nFlag)
{
	__ENTER_FUNCTION

	m_fd = INVALID_HANDLE;
	memset(m_lpszFileName, 0, _MAX_PATH);

	Open(lpszFileName, nFlag);

	__LEAVE_FUNCTION
}

/**********************************************************************
* 函数名称： File
* 功能描述： 构造函数
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
File::File(const CHAR * lpszFileName, INT nFlag, INT nMode)
{
	__ENTER_FUNCTION

	m_fd = INVALID_HANDLE ;
	memset(m_lpszFileName, 0, _MAX_PATH);

	Open(lpszFileName, nFlag, nMode);

	__LEAVE_FUNCTION
}

/**********************************************************************
* 函数名称： ~File
* 功能描述： 析构函数
* 输入参数： 
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2011/07/23		V1.0	    huanggenping	创建版本
***********************************************************************/
File::~File()
{
	__ENTER_FUNCTION

	if( m_fd != INVALID_HANDLE )
	{
		Close();
	}

	__LEAVE_FUNCTION
}

/**********************************************************************
* 函数名称： Open
* 功能描述： 打开文件
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
BOOL File::Open(const CHAR * lpszFileName, INT nFlag)
{
	__ENTER_FUNCTION

	strncpy( m_lpszFileName, lpszFileName, _MAX_PATH - 1);
	m_fd = FileAPI::OpenEx( lpszFileName, nFlag);
	if (m_fd < 0)
	{
		m_fd = INVALID_HANDLE;
		return FALSE ;
	}
	return TRUE;

	__LEAVE_FUNCTION

	return FALSE;
}

/**********************************************************************
* 函数名称： Open
* 功能描述： 打开文件
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
BOOL File::Open(const CHAR * lpszFileName, INT nFlag, INT nMode)
{
	__ENTER_FUNCTION

	strncpy( m_lpszFileName, lpszFileName, _MAX_PATH - 1);
	m_fd = FileAPI::OpenEx(lpszFileName, nFlag, nMode);
	if (m_fd < 0)
	{
		m_fd = INVALID_HANDLE;
		return FALSE;
	}
	return TRUE;

	__LEAVE_FUNCTION

	return FALSE;
}

/**********************************************************************
* 函数名称： Read
* 功能描述： 读取文件
* 输入参数： 
* <param name="pBuffer"></param>
* <param name="uBufferLen"></param>
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2011/07/23		V1.0	    huanggenping	创建版本
***********************************************************************/
UINT File::Read(VOID * pBuffer, UINT uBufferLen)
{
	__ENTER_FUNCTION

	return FileAPI::ReadEx(m_fd, pBuffer, uBufferLen);

	__LEAVE_FUNCTION

	return 0;
}

/**********************************************************************
* 函数名称： Write
* 功能描述： 写入文件
* 输入参数： 
* <param name="pBuffer"></param>
* <param name="uBufferLen"></param>
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2011/07/23		V1.0	    huanggenping	创建版本
***********************************************************************/
UINT File::Write(const VOID * pBuffer, UINT uBufferLen)
{
	__ENTER_FUNCTION

	return FileAPI::WriteEx(m_fd, pBuffer, uBufferLen);

	__LEAVE_FUNCTION

	return 0;
}

/**********************************************************************
* 函数名称： Seek
* 功能描述： 
* 输入参数： 
* <param name="lOffset"></param>
* <param name="nWhence"></param>
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2011/07/23		V1.0	    huanggenping	创建版本
***********************************************************************/
long File::Seek(long lOffset, INT nWhence)
{
	__ENTER_FUNCTION

	return FileAPI::LseekEx(m_fd, lOffset, nWhence);

	__LEAVE_FUNCTION

	return 0;
}

/**********************************************************************
* 函数名称： Tell
* 功能描述： 
* 输入参数： 
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2011/07/23		V1.0	    huanggenping	创建版本
***********************************************************************/
long File::Tell()
{
	__ENTER_FUNCTION

	return FileAPI::TellEx(m_fd);

	__LEAVE_FUNCTION

	return 0 ;
}

/**********************************************************************
* 函数名称： Close
* 功能描述： 
* 输入参数： 
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2011/07/23		V1.0	    huanggenping	创建版本
***********************************************************************/
VOID File::Close()
{
	__ENTER_FUNCTION

	FileAPI::CloseEx(m_fd) ;
	m_fd = INVALID_HANDLE;

	__LEAVE_FUNCTION
}

