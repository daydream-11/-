#ifndef __DB_STRUCT_H__
#define __DB_STRUCT_H__


enum ManagerType
{
	DeleteUserPhrase = 1,
	DuanYuUserPhrase,
	LatelyUpdatePYPhrase,
	LatelyUpdateWBPhrase,
	LatelyUserPhrase,
	PinYinCustomPhrase,
	PinYinUserPhrase,
	PositionUserPhrase,
	UrlUserPhrase,
	WBCustomPhrase,
	WuBiUserPhrase,
	UrlSysPhrase,
	DieZiPhrase,
	UrlDirectAccess,
};

// 细胞词库状态
enum ECellDictState
{
	// 没有状态
	ECellDictNotState = 0,
	// 正在下载状态
	ECellDictDown = 1,
	// 正在更新状态
	ECellDictUpdate = 2,
	// 已经删除状态
	ECellDictDelete = 3,
	// 正在完成状态
	ECellDictFinish = 100,
};


// 细胞词库状态
enum ECellDictUseState
{
	// 没有选中状态
	ECellDictNotChoose = 0,
	// 已经选中状态
	ECellDictInChoose = 1,
};

enum QUERY_GBK_MODE
{
	// 总是查询GBK
	YES_QUERY_GBK = 0,
	// 空码查询GBK
	EMPTY_QUERY_GBK = 1,
	// 不查询GBK
	NO_QUERY_GBK = 2,
};

struct StringValueLength
{
	// 字符串长度
	INT nValueLength;
};

// 通用专业词库版本头
struct SCommonCellMBHeader
{
	// 公司版权标示符
	CHAR szCompanyIdentifier[10];
	// 细胞词库标识符
	CHAR szCellIdentifier[10];
	// 词库结构文件版本
	UINT uStructVersion;
	// 细胞词库ID
	UINT uCellDictID;
	// 细胞词库状态(0:准备状态；1:正在下载状态；2:正在更新状态；3:删除状态；100:完成状态；)
	BYTE byCellDictState;
	// 细胞词库状态(0:未使用状态；1:使用状态；)
	BYTE byCellDictUseState;
	// 细胞词条文件版本
	UINT uCellDictVersion;
	// 词条个数
	UINT uCellDictNum;
	// 文件创建时间
	UINT uCellDictCreateTime;
	// 词条最后更新日期
	UINT uCellDictLastUpdateTime;
	// 细胞词库长度
	UINT uCellDictLength;
	//
	SCommonCellMBHeader()
	{
		// 公司版权标示符
		memset(szCompanyIdentifier, 0, sizeof(szCompanyIdentifier));
		// 细胞词库标识符
		memset(szCellIdentifier, 0, sizeof(szCellIdentifier));
		// 词库结构文件版本
		uStructVersion = 0;
		// 细胞词库ID
		uCellDictID = 0;
		// 细胞词库状态(0:准备状态；1:正在下载状态；2:正在更新状态；3:删除状态；100:完成状态)
		byCellDictState = 0;
		// 细胞词库状态(0:未使用状态；1:使用状态；)
		byCellDictUseState = 0;
		// 细胞词条文件版本
		uCellDictVersion = 0;
		// 词条个数
		uCellDictNum = 0;
		// 文件创建时间
		uCellDictCreateTime = 0;
		// 词条最后更新日期
		uCellDictLastUpdateTime = 0;
		// 细胞词库长度
		uCellDictLength = sizeof(SCommonCellMBHeader);
	}
	//
	VOID serialize
		(
		const CHAR *szCompanyIdentifier
		, const CHAR *szCellIdentifier
		, UINT uStructVersion
		, UINT uCellDictID
		, BYTE byCellDictState
		, BYTE byCellDictUseState
		, UINT uCellDictVersion
		, UINT uCellDictNum
		, UINT uCellDictCreateTime
		, UINT uCellDictLastUpdateTime
		)
	{
		strcpy(this->szCompanyIdentifier, szCompanyIdentifier);
		strcpy(this->szCellIdentifier, szCellIdentifier);
		this->uCellDictID = uCellDictID;
		this->byCellDictState = byCellDictState;
		this->byCellDictUseState = byCellDictUseState;
		this->uStructVersion = uStructVersion;
		this->uCellDictVersion = uCellDictVersion;
		this->uCellDictNum = uCellDictNum;
		this->uCellDictCreateTime = uCellDictCreateTime;
		this->uCellDictLastUpdateTime = uCellDictLastUpdateTime;
		this->uCellDictLength = sizeof(SCommonCellMBHeader);
	}
	// 设置字符串的长度
	VOID SetValueLength(INT nValueLength)
	{
		StringValueLength *pStringValueLength = (StringValueLength*)((char*)this + uCellDictLength);
		pStringValueLength->nValueLength = nValueLength;
		uCellDictLength += sizeof(nValueLength);
	}
	// 获取字符串的长度
	INT GetValueLength(INT nPostion)
	{
		StringValueLength *pStringValueLength = (StringValueLength*)((char*)this + (sizeof(SCommonCellMBHeader) + nPostion));
		return pStringValueLength->nValueLength;
	}
	// 设置字符串信息
	void SetValue(const TCHAR *lpszValue)
	{
		INT nTextLen = (INT)_tcslen(lpszValue);
		//
		this->SetValueLength(nTextLen * 2);
		//
		CHAR *lpszChar = ((CHAR*)this) + uCellDictLength;
		TCHAR *szValue = (TCHAR*)(lpszChar);
		_tcscpy(szValue, lpszValue);
		uCellDictLength += (nTextLen * 2 + sizeof(TCHAR));
	}
	// 获取字符串信息
	const TCHAR* GetValue(INT nValueLength)
	{
		CHAR *lpszChar = ((CHAR*)this) + sizeof(SCommonCellMBHeader) + nValueLength;
		TCHAR *lpszValue = (TCHAR*)(lpszChar);
		return lpszValue;
	}
};


// 通用版本的文件头
struct SCommonMBHeader
{
	// 标示符
	CHAR szIdentifier[10];
	// 索引文件版本
	UINT uVersion;
	//
	VOID serialize
		(
		const CHAR *szIdentifier,
		UINT uVersion
		)
	{
		strcpy(this->szIdentifier, szIdentifier);
		this->uVersion = uVersion;
	}
};


// 系统细胞词库信息
struct SSystemCellDictInfo
{
	// 细胞词库ID
	UINT uCellDictID;
	// 细胞词库版本
	UINT uCellDictVer;
	// 细胞词库状态
	ECellDictState eCellDictState;
	// 细胞词库名称
	xstring strCellDictName;
};

typedef vector<SSystemCellDictInfo*> TVectorSystemCellDict;

// 系统码表的标示符
#define __MB_IDENTIFIER__					"__GS__"

// 细胞码表的标示符
#define __CELL_DICT_IDENTIFIER__			"__Dict__"

// 拼音词库文件版本
#define PY_CELL_DICT_IDX_VERSION	20000

#define CODE_MAX_LENGTH					400
#define WORD_MAX_LENGTH					1000
struct CSplitPinYin
{
	// 声母索引
	UINT uSMIndex;
	// 韵母索引
	UINT uYMIndex;
	// 拼音编码
	TCHAR strPYCode[7];
	//
	CSplitPinYin()
	{
		uSMIndex = 0;
		uYMIndex = 0;
		memset(strPYCode, 0, sizeof(strPYCode));
	}
	//
	VOID Copy(CSplitPinYin *pFromSplitPinYin)
	{
		this->uSMIndex = pFromSplitPinYin->uSMIndex;
		this->uYMIndex = pFromSplitPinYin->uYMIndex;
		_tcscpy(this->strPYCode, pFromSplitPinYin->strPYCode);
	}
};
typedef vector<CSplitPinYin> TVectorSplitPYParse;
typedef vector<TVectorSplitPYParse> TVectorGroupSplitPYParse;
typedef map<xstring, vector<xstring>>	TMapFuzzyManger;

// 处理回调函数
typedef VOID(__cdecl* ProcessSetSplitPinYinProc)(TVectorSplitPYParse *pVectorSplitPYParse);

// 每日更新
typedef struct _DailyNewWord 
{
	unsigned char nAPos;// 全拼固定位置
	unsigned char nSPos;// 简拼固定位置
	string strWord;
	string strCode;
	_DailyNewWord()
		:nAPos(10),
		nSPos(10),
		strWord(""),
		strCode("")
	{
	}
} DailyNewWord, *DailyNewWordPtr;
typedef vector<DailyNewWordPtr> TVectorDailyNewWord;

struct SHXWDataInfo
{
	// 汉字
	xstring strHanZi;
	// 火星文
	xstring strHxw;
};
typedef map<xstring, SHXWDataInfo*> TMapHXWDataInfo;
// 字符画
struct SZFHDataInfo
{
	// 汉字
	xstring strHanZi;
	// 字符画
	xstring strZfh;
};
typedef map<xstring, SZFHDataInfo*> TMapZFHDataInfo;
// 网址直达
typedef struct SUrlDirectAccess
{
	// 查询名称
	xstring strQueryName;
	// 网站名称
	xstring strUrlName;
	// 网址
	xstring strUrlAddress;
} *UrlDirectAccessPtr;
typedef vector<UrlDirectAccessPtr> TVectorUrlDirectAccess;
#endif	// __DB_STRUCT_H__
