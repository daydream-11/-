#pragma once
#include "SingletonTemplate.h"
#include "CandNode.h"

enum DataManagerType
{
	GBKData = 1,
	WuBiData,
	YingYuData,
	UrlData,
	PinYinData,
	PinYinSingle,
};
enum MatchType
{
	MatchMB = 1,
	MatchDat,
	MatchIdx,
};

class CDBSystemManager
{
public:
	CDBSystemManager(void);
public:
	~CDBSystemManager(void);
private:
	// 
	HINSTANCE m_hMainInstance;
public:
	// 加载数据
	int LoadData(ManagerType _Type, int everyPageNum, int curPage);
	// 加载数据
	int LoadData(ManagerType _Type, const TCHAR *lpszQueryComp, int everyPageNum, int curPage);
	// 获取加载的数据
	void GetDataList(ManagerType _Type, TVectorCandNode* pTVectorCandNode);
	// 导出数据
	VOID DoExport(ManagerType _Type, const TCHAR *lpszExportFile);
	// 导入数据
	BOOL DoImport(ManagerType _Type, const TCHAR *lpszImport);
	// 同步数据
	VOID DoSyncMB(ManagerType _Type,  TCHAR *lpszSyncFile);
	// 清空数据 
	BOOL DeleteAll(ManagerType _Type);
	// 删除数据  
	BOOL DeleteData(CCandInfo* pCandInfo, const TCHAR *lpszQueryComp);
	// 删除数据  
	BOOL DeleteData(ManagerType _Type, CCandNode* pCCandNode);
	// 修改数据
	BOOL UpdateData(ManagerType _Type, CCandNode* pCCandNode);
	// 插入数据
	BOOL InsertData(ManagerType _Type, CCandNode* pCCandNode);
	// 恢复默认配置
	BOOL DoRecoverDefault(ManagerType _Type, TCHAR* pTemp, BOOL bNotIgnored = TRUE);
	// 升级
	BOOL DoLevelUpAndSync(ManagerType _Type, TCHAR* pTemp);
	// 更新每日新词
	VOID DoUpdateDailyNewWord(TVectorDailyNewWord* pVecotrPYDaily, TVectorDailyNewWord* pVecotrWBDaily);
	// 检测没有下载的细胞词库
	VOID DoCheckNeedDownloadCellDict();
public:
	// 获取拼音信息
	xstring GetSinglePYInfoOfPYIndex(const TCHAR * strPYIndex);
public:
	// 初始化
	BOOL Init();
	// 加载
	BOOL Load
		(
		HINSTANCE hInstance
		, const TCHAR *lpszSoftInstallPath
		, const TCHAR * lpszSystemDBPath
		, const TCHAR *lpszCfgRootPath
		, const TCHAR *lpszCfgUserPath
		);
	// 设置拆分函数过程
	VOID  OnSetProcessSetSplitPinYinProc(ProcessSetSplitPinYinProc pProcessSetSplitPinYinProc);
	// 拆分拼音个数
	VOID SetSplitPinYinSize(INT nSplitPinYinSize, BOOL bSplitFullMatch);
public:
	// 对候选词进行固定位置调整
	BOOL SetToPosition(CCandInfo *pCandInfo, const TCHAR *pInput, BYTE byPosition);
	// 取消候选词的固定位置
	BOOL ResetPosition(CCandInfo *pCandInfo, const TCHAR *pInput, BYTE byPosition);
public:
	// 设置是否首字母简拼
	VOID SetUseFirstLetterJianPin(BOOL bUseFirstLetterJianPin);
	// 设置动态组词：没有全匹配的候选词时，自动构造新词
	VOID SetUseDynamicMakePinYinWord(BOOL bUseDynamicMakePinYinWord);
	// 设置动态造词：没有全匹配的候选词时，自动记录到拼音用户词库
	VOID SetUseDynamicAddUserPinYinWord(BOOL bUseDynamicAddUserPinYinWord);
	// 设置五笔单字输入法模式
	VOID SetWbSingleWordInput(BOOL bWbSingleWordInput);
	// 仅在全码匹配时显示词组
	VOID SetWbOnlySameCodeShowPhrase(BOOL bWbOnlySameCodeShowPhrase);
	// 五笔重码字词排序（0：默认排序；1：单字优先；2：词组优先）
	VOID SetWbSameCodeCandidateWordSortMode(BYTE byWbSameCodeCandidateWordSortMode); 
	// 五笔候选词重码时（0：一二级简码置后；1：所有的简码置后；2：所有的简码隐藏）
	VOID SetWbSameCandidateOneTwoPostpone(BYTE byWbSameCandidateOneTwoPostpone);
	// 设置启用细胞词库
	VOID SetUseCellDict(BOOL bUseCellDict);
	// 设置造词类型
	void SetMakeWordType(int nMakeWordType);
	// 设置GBK模式
	VOID SetQueryGBKMode(int nQueryGBKMode);
	// 设置每页候选个数
	void SetEveryPage(int nEveryPage);
	// 设置拼音纠错配置功能
	VOID SetPYErrorRecoveryConfig
		(
		BOOL bErrorRecoveryGnToNg,
		BOOL bErrorRecoveryMgToNg,
		BOOL bErrorRecoveryIouToIu,
		BOOL bErrorRecoveryUeiToUi,
		BOOL bErrorRecoveryUenToUn
		);
	// 设置模糊音配置功能
	void SetFuzzyConfig(const vector<xstring>& myFuzzyVector);
public:
	// 通过编码查询候选词
	BOOL QueryNormal(TVectorEnumMBType *pVectorEnumMBType, const TCHAR * pszComp, CCandList *pCandList);
	//
	VOID QueryUserComp(const TCHAR *lpszComp, CCandList *pCandList);
	//
	VOID QueryUrlComp(const TCHAR *lpszComp, CCandList *pCandList);
	// 查询五笔重码个数
	int QueryWbReCompNum(CCandInfo* pCandInfo);
	// 查询五笔编码
	BOOL BuildWbComp(CCandInfo *pCandInfo, CCandList *pCandList);
	// 获取火星文
	SHXWDataInfo* GetHXWDataInfo(const TCHAR *lpszHanZi);
	// 按编码查询五笔用户
	void QueryWbReCompByCode(const TCHAR *lpszComp, CCandList *pCandList);
public:
	// 选择一个候选词上屏
	BOOL DoSelectCand(CCandInfo *pCandInfo, int ifmFlg, int nFcLxStatus, TVectorEnumMBType *pVectorEnumMBType, CCandList *pCandList);
	// 获取记录条数
	int GetRecordTotal(void);
	// 获取候选字的当前第几页
	int GetCurrentPage(void);
	// 是否为最后一页
	BOOL IsTheLastPage();
	// 显示第一页数据
	BOOL DoFirstData(CCandList *pCandList);
	// 调用候选词的上一页数据
	BOOL DoPrevData(CCandList *pCandList);
	// 调用候选词的下一页数据
	BOOL DoNextData(CCandList *pCandList);
	// 显示最后一页数据
	BOOL DoEndData(CCandList *pCandList);
	// 没有数据
	void NoData();
private:
	//
	VOID CheckMatchMB(DataManagerType _Type, const TCHAR * lpszSystemDBPath);
	//
	VOID CheckMatchIdxFile(DataManagerType _Type, const TCHAR * lpszFile);
	//
	VOID CheckMatchDatFile(DataManagerType _Type, const TCHAR * lpszFile);
public:
	VOID CheckMatchFile(MatchType _match, DataManagerType _Type, const TCHAR * lpszFile);
	// 删除细胞词库
	VOID DeleteCellDict(UINT uCellID);
	// 设置是否选中状态
	VOID SetChooseState(UINT uCellID, BOOL bChoose);
public:
	// 是否匹配拆分拼音
	BOOL IsMatchSplitPinYin(CSplitPinYin *pSplitPinYin, UINT uPinYinSMIndex, UINT uPinYinYMIndex);
	// 获取网址直达信息
	BOOL GetUrlDirectAccess(const TCHAR* strComp, UrlDirectAccessPtr pUrlDirectAccess);
};
typedef ChaSingleton<CDBSystemManager> CDBSystemManagerInstance;

