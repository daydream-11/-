#ifndef __IME_STRUCT_H__
#define __IME_STRUCT_H__

#define LockCandList(dwlist) \
						LPINPUTCONTEXT lpIMC = NULL;\
						LPCANDIDATEINFO lpCandInfo = NULL;\
						LPCANDIDATELIST lpCandList = NULL;\
						\
						lpIMC = ImmLockIMC(CImeProc::m_hIMC); \
						if(!lpIMC) goto candExit;	if(!lpIMC->hCandInfo) goto candExit;\
						lpCandInfo = (LPCANDIDATEINFO)ImmLockIMCC(lpIMC->hCandInfo);\
						if(!lpCandInfo) goto candExit;\
						lpCandList  = (LPCANDIDATELIST)((LPBYTE)lpCandInfo +  lpCandInfo->dwOffset[dwlist])


#define UnLockCandList() \
					candExit:\
						if(NULL != lpCandInfo)	ImmUnlockIMCC(lpIMC->hCandInfo);\
						if(NULL != lpIMC)		ImmUnlockIMC(CImeProc::m_hIMC)

#define LockCompList() \
					LPINPUTCONTEXT lpIMC = NULL;\
					LPCOMPOSITIONSTRING lpCompStr = NULL;\
					\
					if(NULL == CImeProc::m_hIMC) goto exitUnLock;\
					lpIMC = ImmLockIMC(CImeProc::m_hIMC);\
					if(NULL == lpIMC) goto exitUnLock;\
					lpCompStr = (LPCOMPOSITIONSTRING)ImmLockIMCC(lpIMC->hCompStr);\
					if(NULL == lpCompStr) goto exitUnLock

#define UnLockCompList() \
				exitUnLock:\
					if(NULL != lpCompStr)	ImmUnlockIMCC(lpIMC->hCompStr);\
					if(NULL != lpIMC)	ImmUnlockIMC(CImeProc::m_hIMC)



#define LockPrivList() \
					LPINPUTCONTEXT	lpIMC = NULL;	\
					LPIMEPRIVATE	lpPriv = NULL;	\
					\
					if(NULL == CImeProc::m_hIMC) goto exitUnLock;\
					lpIMC = ImmLockIMC(CImeProc::m_hIMC);\
					if(lpIMC == NULL) goto exitUnLock;\
					lpPriv = (LPIMEPRIVATE)ImmLockIMCC(lpIMC->hPrivate);\
					if(lpPriv == NULL) goto exitUnLock


#define UnLockPrivList() \
				exitUnLock:\
					if(NULL != lpIMC->hPrivate)		ImmUnlockIMCC(lpIMC->hPrivate);\
					if(NULL != lpIMC)	ImmUnlockIMC(CImeProc::m_hIMC)

#define GETLPCOMPREADTSTR(lpcs)	(LPTSTR)((LPBYTE)(lpcs) + (lpcs)->dwCompReadStrOffset)
#define GETLPCOMPTSTR(lpcs)		(LPTSTR)((LPBYTE)(lpcs) + (lpcs)->dwCompStrOffset)
#define GETLPCANDTSTR(lpcs,i)	(LPTSTR)((LPBYTE)(lpcs) + (lpcs)->dwOffset[i])
#define GETLPRESULTSTR(lpcs)	(LPTSTR)((LPBYTE)(lpcs) + (lpcs)->dwResultStrOffset)

#define GETLPCLSISPY(lpcs, i)	(LPTSTR)((LPBYTE)(lpcs) + (lpcs)->dwClsOffset[i].bPYOffset)
#define GETLPCLSCANDTSTR(lpcs, i)	(LPTSTR)((LPBYTE)(lpcs) + (lpcs)->dwClsOffset[i].dwCandClsOffset)
#define GETLPCLSCOMPTSTR(lpcs, i)	(LPTSTR)((LPBYTE)(lpcs) + (lpcs)->dwClsOffset[i].dwCompClsOffset)
#define GETLPCLSREALCOMPTSTR(lpcs, i)	(LPTSTR)((LPBYTE)(lpcs) + (lpcs)->dwClsOffset[i].dwRealCompClsOffset)
#define GETLPCLSREALYD(lpcs, i)		(LPTSTR)((LPBYTE)(lpcs) + (lpcs)->dwClsOffset[i].dwCompYD)

typedef struct _tagIMEMSG			//IME消息结构
{
    UINT uMsg;
    WPARAM wParam;
    LPARAM lParam;
} IMEMSG, NEAR *PIMEMSG, FAR *LPIMEMSG;

const DWORD WN_MAX_INPUTNUM		= 64;	// 输入编码字节数
const DWORD WN_INPUT_BUFFER		= 512;	// 编码字节数缓冲区大小
const DWORD WN_MAX_CANDSTR		= 512;	// 候选子句最大字节数
const DWORD WN_MAX_CANDNUM		= 32;	// 显示的最多候选个数
const DWORD WN_MAX_CANDCLS		= 1024;					// 组合汉字子句的缓冲区大小
const DWORD LISTCAND_BUFFER		= 2048;					// 记录candlist汉字结果的长度
const DWORD MAX_PROMPT_NUM		= 10;	//步步提示的数量

const DWORD WN_MAX_NUMCANDCLS	= WN_MAX_INPUTNUM;		// 组合汉字子句最大个数

#endif	// __IME_STRUCT_H__