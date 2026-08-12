#ifndef __ENUM_H__
#define __ENUM_H__

#include <vector>
#include <map>
using namespace std;

#include "EnumBOOLFnType.h"
#include "EnumMenuFnType.h"
#include "EnumINTFnType.h"
#include "EnumVOIDFnType.h"
#include "EnumCHARFnType.h"
#include "EnumHotKeyFnType.h"

enum EnumFnType
{
	/**
	 * 使用拼音输入
	 */
	USE_PY = 1,
	/**
	 * 使用五笔输入
	 */
	USE_WB = 2,
	/**
	 * 使用英语输入
	 */
	USE_EN = 3,
	/**
	 * 使用快笔输入
	 */
	USE_KB = 4,
	/**
	 * 使用笔画输入
	 */
	USE_BH = 5,
};

enum EnumMBType
{
	/**
	 * 不属于任何词库
	 */
	UN_SYS_MB = 0,
	/**
	 * 拼音系统词库(单字库)
	 */
	PY_SYS_SINGLE = 1,
	/**
	 * 拼音系统词库
	 */
	PY_SYS = 2,
	/**
	 * 拼音用户词库
	 */
	PY_USR = 3,
	/**
	 * 拼音专业词库
	 */
	PY_CELL = 4,
	/**
	 * 拼音自造词库
	 */
	PY_MAKE = 5,
	/**
	 * 五笔系统词库
	 */
	WB_SYS = 6,
	/**
	 * 五笔用户词库
	 */
	WB_USR = 7,
	/**
	 * 五笔专业词库
	 */
	WB_CELL = 8,
	/**
	 * 英语系统词库
	 */
	EN_SYS = 9,
	/**
	 * 英语用户词库
	 */
	EN_USR = 10,
	/**
	 * 快笔系统词库
	 */
	KB_SYS = 11,
	/**
	 * 快笔用户词库
	 */
	KB_USR = 12,
	/**
	 * 笔画系统词库
	 */
	BH_SYS = 13,
	/**
	 * 笔画用户词库
	 */
	BH_USR = 14,
	/**
	 * GBK词库
	 */
	GBK_SYS = 15,
	/**
	 * 网址系统词库
	 */
	URL_SYS = 16,
	/**
	 * 最近上屏的词
	 */
	 LATE_SYS = 19,
	/**
	 * 固定位置的词
	 */
	POS_SYS = 20,
	/**
	 * 其他系统词库（比如用户把双拼作为一种词库）
	 */
	OTHER_SYS = 21,
	/**
	 * 其他用户词库（比如用户把双拼作为一种词库）
	 */
	OTHER_USR = 22,
	/**
	 * 拼音自定义词组
	 */
	PY_CUSTOM_PHRASE = 23,
	/**
	 * 五笔自定义词组
	 */
	WB_CUSTOM_PHRASE = 24,
	/**
	 * 自定义短语用户词库
	 */
	DY_USER_PHRASE = 25,
	/**
	 * 网址用户词库
	 */
	URL_USER_PHRASE = 26,
	/**
	 * 五笔自定义说明
	 */
	 WB_CUSTOM_EXPLAIN = 27,
	 /**
	 * 网址用户自动造词
	 */
	 URL_USER_MAKE = 28,
	 /**
	 * 拼音自定义表达式
	 */
	 PY_CUSTOM_EXPRESSION = 29,
	 /**
	 * 拼音自造词属于词组连在一起
	 */
	 PY_MAKE_LIKE_PHRASE = 30,
	 /**
	 * 拼音自造词属于单字连在一起
	 */
	 PY_MAKE_LIKE_SINGLE = 31,
	  /**
	 * 用户删除词条
	 */
	 DELETE_USER = 32,
	 /**
	 * 系统更新词条
	 */
	 UPDATE_SYS = 33,
	 /**
	 * 叠字字库
	 */
	 DIE_ZI_SYS = 34,
	 /**
	 * 拼音每日新詞
	 */
	 PY_DAILY = 35,
	 /**
	 * 五筆每日新詞
	 */
	 WB_DAILY = 36,
	 /**
	 * 五笔自定义单个词（如：zzdl）
	 */
	 WB_CUSTOM_CALCULATE_PHRASE = 37,
	 /**
	 * 拼音自定义单个词（如：zzdl）
	 */
	 PY_CUSTOM_CALCULATE_PHRASE = 38,
	 /**
	 * 删除词条
	 */
	 DEL_SYS = 39,
	 /**
	 * 字符画词条
	 */
	 ZFH_SYS = 40,
};

// 打开命令方式
enum EOpenCommandMode
{
	// 使用快捷键打开
	EOpenComandByOther = 0,
	// 使用快捷键打开
	EOpenComandByHotKey = 1,
};

typedef pair<EnumBOOLFnType, BOOL> CPairBOOLFnType;
typedef pair<EnumINTFnType, int> CPairINTFnType;
typedef pair<EnumCHARFnType, const TCHAR *> CPairCHARFnType;

typedef vector<EnumMBType> TVectorEnumMBType;

typedef map<EnumBOOLFnType, BOOL> CMapBOOLFnType;
typedef map<EnumINTFnType, int> CMapINTFnType;
typedef map<EnumCHARFnType, TCHAR *> CMapCHARFnType;


#endif	// __ENUM_H__
