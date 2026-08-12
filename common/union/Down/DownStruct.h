#ifndef __UPDATE_STRUCT_H__
#define __UPDATE_STRUCT_H__

#include <vector>
using namespace std;


#define DEFAULT_HTTP_PORT			80
#define DEFAULT_HTTPS_PORT			443
#define DEFAULT_FTP_PORT			21
#define DEFAULT_SOCKS_PORT			6815

#define SLEEP_RETURN(x)\
{\
	if ( ::WaitForSingleObject ( m_hEvtEndModule, x ) == WAIT_OBJECT_0 )\
		return FALSE;\
}
#define SLEEP_BREAK(x)\
{\
	if ( ::WaitForSingleObject ( m_hEvtEndModule, x ) == WAIT_OBJECT_0 )\
		break;\
}
// 进入临间区
#define EnterCRIT(pCRIT,CRITName,FileName,Line) \
{\
	(pCRIT)->Lock ();\
	TRACE ( "--------> %s , EnterCriticalSection ,%s ( %d )\n", CRITName, FileName, Line );\
}
// 离开临间区
#define LeaveCRIT(pCRIT,CRITName,FileName,Line) \
{\
	TRACE ( "<-------- %s , LeaveCriticalSection ,%s ( %d )\n", CRITName, FileName, Line );\
	(pCRIT)->Unlock();\
}


#define SLEEP_RETURN_Down(x)\
{\
	if ( ::WaitForSingleObject ( m_hEvtEndModule, x ) == WAIT_OBJECT_0 )\
		return DownloadEnd(FALSE);\
}
// 有效的句柄
#define HANDLE_IS_VALID(h) ((HANDLE)(h) && ((HANDLE)(h)!=INVALID_HANDLE_VALUE))
#define MIN(x,y) (((DWORD)(x)<(DWORD)(y))?(x):(y))
#define MAX(x,y) (((DWORD)(x)>(DWORD)(y))?(x):(y))
#define GET_SAFE_STRING(str) ( (str)?(str):_T(""))
#define MAX_DOWNLOAD_THREAD_COUNT	16			// 下载一个文件最大使用的线程数
// 关闭句柄
#define CLOSE_HANDLE(h)\
{\
	if ( HANDLE_IS_VALID(h) )\
	{\
		::CloseHandle ( h );\
		(h) = NULL;\
	}\
}
//
// 单个对象的下载信息
//
struct TSingleDownloadInfo
{
	// 要下载文件的开始位置
	DWORD nWillDownloadStartPos;
	// 本次需要下载的大小，-1表示一直下载到文件尾
	DWORD nWillDownloadSize;
	// 该线程已下载的大小
	DWORD nDownloadedSize;
};

//
// 下载信息
//
struct TBaseDownloadInfo
{
	// 该文件由多少个线程在下载
	DWORD dwThreadCount;
};

// 下载返回的状态
typedef enum TEnumDownloadResult
{
	ENUM_DOWNLOAD_RESULT_SUCCESS,
	ENUM_DOWNLOAD_RESULT_FAILED,
	ENUM_DOWNLOAD_RESULT_CANCEL,
} ENUM_DOWNLOAD_RESULT;

typedef void (*FunCallbackSaveDownloadInfo)(int nIndex, int nDownloadedSize, int nSimpleSaveSize, WPARAM wParam);
typedef void (*FunCallbackDownloadProgressInfo)(WPARAM wParam);

#endif	// __UPDATE_STRUCT_H__