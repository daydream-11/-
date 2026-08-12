#ifndef __STRUCT_H__
#define __STRUCT_H__


#include "Enum.h"
#include "MapParameter.h"
#include "VectorParameter.h"
#include "SkinStruct.h"
#include "BaseStruct.h"
#include "SkinStruct.h"
#include "imm.h"
#include <map>
using namespace std;

typedef void (*VOIDFunAddress)(int nOpenCommandMode);
typedef void (*BOOLFunAddress)(EnumBOOLFnType enumBOOLFnType);

typedef vector<xstring> CVectorSkinList;

// 执行无返回类型功能
typedef struct TVOIDFnVariable
{
	EnumVOIDFnType m_enumVOIDFnType;
	VOIDFunAddress m_pProcAddress;
	TVOIDFnVariable()
	{
		m_pProcAddress = NULL;
	}
}TVOIDFnVariable, *PTVOIDFNVARIABLE;

// 执行无返回类型功能对应的功能ID
typedef struct TFnMatchCmd
{
	int m_nCmdID;
	int m_nCmdType;
	EnumVOIDFnType m_enumVOIDFnType;
	EnumBOOLFnType m_enumBOOLFnType;
}TFnMatchCmd, *PTFNMATCHCMD;

// 执行无返回类型功能
typedef struct TVOIDFnStatus
{
	// 对应的控件ID
	int m_nItemID;
}TVOIDFnStatus, *PTVOIDFNSTATUS;

// 执行BOOL类型功能
typedef struct TBOOLFnVariable
{
	EnumBOOLFnType m_enumBOOLFnType;
	BOOL* m_pBOOLVariable;
	BOOLFunAddress m_pProcAddress;
	TCHAR m_strCfgName[100];
	TBOOLFnVariable()
	{
		m_enumBOOLFnType = NO_BOOL_TYPE;
		m_pBOOLVariable = NULL;
		m_pProcAddress = NULL;
		memset(m_strCfgName, 0, sizeof(m_strCfgName));
	}
}TBOOLFnVariable, *PTBOOLFNVARIABLE;

// 执行BOOL类型功能
typedef struct TBOOLFnStatus
{
	// 对应的控件ID
	int m_nItemID;
}TBOOLFnStatus, *PTBOOLFNSTATUS;

// 执行INT类型功能
typedef struct TINTFnVariable
{
	EnumINTFnType m_enumINTFnType;
	int* m_pINTVariable;
	TCHAR m_strCfgName[100];
	TINTFnVariable()
	{
	}
} TINTFnVariable, *PTINTFNVARIABLE;

// 执行CHAR类型功能
typedef struct TCHARFnVariable
{
	EnumCHARFnType m_shareEnumCHARFnType;
	void* m_pCHARVariable;
	TCHAR m_strCfgName[100];
	void* m_pProcAddress;
	TCHARFnVariable()
	{
		m_pProcAddress = NULL;
	}
}TCHARFnVariable, pTCHARFNVARIABLE;

// 执行快捷键类型功能
typedef struct THotKeyFnVariable
{
	EnumHotKeyFnType m_enumHotKeyFnType;
	EnumHotKeyFnType m_shareEnumHotKeyFnType;
	int m_nCmdID;
	BOOL* m_pBOOLVariable;
	void* m_pCHARVariable;
	TCHAR m_strCfgName[100];
	THotKeyFnVariable()
	{
		m_enumHotKeyFnType = NO_HOT_KEY;
		m_shareEnumHotKeyFnType = NO_HOT_KEY;
		m_nCmdID = 0;
		m_pBOOLVariable = NULL;
		m_pCHARVariable = NULL;
		memset(m_strCfgName, 0, sizeof(m_strCfgName));
	}
}THotKeyFnVariable, *PTHOTKEYFNVARIABLE;

typedef struct TShortCutMatch
{
	xstring m_strDescribe;
	xstring m_strHotKeyLetter;
	EnumHotKeyFnType m_tempEnumHotKeyFnType;
	EnumHotKeyFnType m_shareEnumHotKeyFnType;
}TShortCutMatch, *PTSHORTCUTMATCH;

enum EIEProtectedMode
{
	// 无状态设置
	NoSetIEProtectedMode = -1,
	// 不是IE保护模式
	NotIEProtectedMode = 0,
	// 是IE保护模式
	YesIEProtectedMode = 1,
};

typedef map<EnumVOIDFnType, TVOIDFnVariable*> CMapVOIDFnVariable;
typedef map<EnumBOOLFnType, TBOOLFnVariable*> CMapBOOLFnVariable;
typedef map<EnumINTFnType, TINTFnVariable*> CMapINTFnVariable;
typedef map<EnumCHARFnType, TCHARFnVariable*> CMapCHARFnVariable;
typedef map<EnumHotKeyFnType, THotKeyFnVariable*> CMapHotKeyFnVariable;

typedef map<int, TFnMatchCmd*> CMapFnMatchCmd;

typedef vector<TShortCutMatch*> CVectorTShortCutMatch;

typedef vector<xstring> CVectorMakeWord;

// 执行Check复选框类型功能
typedef struct TCheckFnStatus
{
	// 对应的控件ID
	int m_nCheckID;
	// 对应控件名称
	xstring strCheckName;
	TCheckFnStatus()
	{
		m_nCheckID = 0;
	}
	//
}TCheckFnStatus, *PTCHECKFNSTATUS;

typedef struct TRadioMatch 
{
	int m_nRadioID;			// 对应的RADIO控件ID
	xstring strCheckName;	// 对应控件名称
	int m_nRadioValue;		// 对应RADIO控件的值
}TRadioMatch, *PTRADIOMATCH;

typedef vector< TRadioMatch* > CVectorRadioMatch;
// 执行Radio复选框类型功能
typedef struct TRadioFnStatus
{
	// 对应的控件ID
	CVectorRadioMatch *m_pVectorRadioMatch;
	TRadioFnStatus()
	{
		m_pVectorRadioMatch = new CVectorRadioMatch();
	}
	void DelRadioFnStatus()
	{
		if (m_pVectorRadioMatch != NULL)
		{
			delete m_pVectorRadioMatch;
			m_pVectorRadioMatch = NULL;
		}
	}
}TRadioFnStatus, *PTRADIOFNSTATUS;

typedef map<EnumBOOLFnType, TCheckFnStatus* > CMapCheckFnStatus;
typedef map<EnumINTFnType, TRadioFnStatus* > CMapRadioFnStatus;

// 单个参数MAP
typedef MapParameter<xstring, xstring> CMapSingleParameter;
// 多个向量参数列表
typedef VectorParameter<CMapSingleParameter*> CVectorMultiParameter;
// MAP装置向量列表参数
typedef MapParameter<xstring, CVectorMultiParameter*> CMapMultiVectorParameter;

// 单个风格配置参数
typedef MapParameter<xstring, xstring> CMapSingleSkinParameter;
// 多个风格配置参数
typedef VectorParameter<CMapSingleSkinParameter*> CVectorMultiSkinParameter;
// 一个窗口风格参数
typedef VectorParameter<CVectorMultiSkinParameter*> CVectorSingleWndParameter;
// 皮肤按钮配置参数
typedef MapParameter<xstring, CVectorSingleWndParameter*> CMapMultiWndParameter;

// 全角 + 英文标点符号
static TCHAR pszLowSoftKeyboardLayout[13][49 * 2] = 
{
	//0 1 2 3 4 5 6 7 8 9 a b c d e f g h i j k l m n o p q r s t u v w x y z ; = , - . / ` [ \ ] '
	{_T("　ˉ，、；：？！…—·〔（【〈“〉《》∶「」『［）＂＇‘”〕々‖】’〗～〖』¨］ˇ｛｝。｀〃｜．")}, // 8.标点符号
	{_T("　ⅪⅡⅢⅣⅤⅥⅦⅧⅨⅩ㈠⑸⑶㈢⒊㈣㈤㈥⒏㈦㈧㈨⑺⑹⒐⒑⒈⒋㈡⒌⒎⑷⒉⑵⒍⑴㈩　⑻Ⅻ⑼⑽Ⅰ　　　　")}, // 9.数字序号
	{_T("　　≡≠＝≤≥＜＞≮≯∧⊙∠∑－∏∪∩∫∈　∵∽≌∮∝±×∨÷　⌒＋∥／⊥∴　　∷√　≈∞　　　")}, //10.数学符号
	{_T("　¤°′″＄￡￥‰％℃百　毫万二亿兆吉七太拍艾　　八九○三千四六微一厘五分　　　￠　　　十　　　")}, //12.单位符号
	{_T("　┄┍┎┏┐┑┒┓　─┬╀┾┮┞┯┰┱┣┲┳　╂╁　│├┟┭┠┢┿┝┽┡┼　　╃┈　　┌┆　┊　")}, //11.制表符
	{_T("　　　　　　　　　　　■＾＠▲☆※→←◇↑↓〓￣＿◆□§★△○◎＼№＆●＃¤　―　♂♀　℃�‰°")}, //13.特殊符号
	{_T("　　　　　　　　　　　κχυμγνξοθπρ　ωψι　αδλεηφβτζσ　　　　　　　　　　　")}, // 2.希腊字母
	{_T("　　　　　　　　　　　лъшнвопржстуьызиагмдёщбчецф　э　юя　й　кх")}, // 3.俄文字母
	{_T("　ㄦㄉ　　ㄓ　　ㄚㄞㄢㄇㄖㄏㄎㄍㄑㄕㄘㄛㄨㄜㄠㄩㄙㄟㄣㄆㄐㄋㄔㄧㄒㄊ　ㄗㄈㄤ　ㄝ　ㄡㄥㄅ　　　　")}, // 4.注音符号
	{_T("　　　　　　　　　　　ē　ǔěǎè　īǒíǐìǘǖò　āàé　óùáúōū　　ǚ　ǜü　ê　　")}, // 5.拼音
	{_T("　　ぃぅぇぉかきくけこなもむぬすねのはつひふへゅゃってさせにそちめしみたまほ　ょんゎをぁと　ゐゑ")}, // 6.日文平假名
	{_T("　ケィゥヴェォカヵキクナモムヌスネノハツヒフヘュャッテサセニソチメシミタマホコョヶヮヲァトンヰヱ")}, // 7.日文片假名
	{_T("　０１２３４５６７８９ａｂｃｄｅｆｇｈｉｊｋｌｍｎｏｐｑｒｓｔｕｖｗｘｙｚ；＝，－．／｀［＼］＇")} // 1.ＰＣ键盘
};
//全角 + 英文标点符号 + Shift
static TCHAR pszCapSoftKeyboardLayout[13][49 * 2] = {
	// 0 1 2 3 4 5 6 7 8 9 a b c d e f g h i j k l m n o p q r s t u v w x y z ; = , - . / ` [ \ ] '
	{_T("　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　")},// 8.标点符号
	{_T("　　　　　　　　　　　①⒂⒀③⒔④⑤⑥⒙⑦⑧⑨⒄⒃⒚⒛⒒⒕②⒖⒘⒁⒓⑿⒗⑾⑩　⒅　⒆⒇　　　　　")},// 9.数字序号
	{_T("　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　")},//10.数学符号
	{_T("　　　　　　　　　　　佰　　　贰　　　柒　　　　　捌玖零叁仟肆陆　壹　伍　　　　　　　　拾　　　")},//12.单位符号
	{_T("　┅┕┖┗┘┙┚┛　━┴╈╆┶┦┷┸┹┫┺┻　╊╉　┃┤┧┵┨┪╇┥╅┩╄　　╋┉　　└┇　┋　")},//11.制表符
	{_T("　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　")},//13.特殊符号
	{_T("　　　　　　　　　　　ΚΧΥΜΓΝΞΟΘΠΡ　ΩΨΙ　ΑΔΛΕΗΦΒΤΖΣ　　　　　　　　　　　")},// 2.希腊字母
	{_T("　　　　　　　　　　　ЛЪШНВОПРЖСТУЬЫЗИАГМДЁЩБЧЕЦФ　Э　ЮЯ　Й　КХ")},// 3.俄文字母
	{_T("　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　")},// 4.注音符号
	{_T("　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　")},// 5.拼音
	{_T("　　いうえおがぎぐげごぱろるぷずぺぽばづびぶべゆや　でざぜぴぞぢれじりだらぼ　よ　わ　あど　　　")},// 6.日文平假名
	{_T("　ゲイウ　エオガ　ギグパロルプズペポバヅビブベユヤ　デザゼピゾヂレジリダラボゴヨ　ワ　アド　　　")},// 7.日文片假名
	{_T("　）！＠＃＄％＾＆＊（ＡＢＣＤＥＦＧＨＩＪＫＬＭＮＯＰＱＲＳＴＵＶＷＸＹＺ：＋＜＿＞？～｛｜｝＂")}// 1.ＰＣ键盘
};

static const TCHAR pszArabNumber[10][3] = 
{
	{_T("0")},
	{_T("1")},
	{_T("2")},
	{_T("3")},
	{_T("4")},
	{_T("5")},
	{_T("6")},
	{_T("7")},
	{_T("8")},
	{_T("9")}
};


static const TCHAR pszCapitalNumber[10][3] = 
{
	{_T("零")},
	{_T("壹")},
	{_T("贰")},
	{_T("叁")},
	{_T("肆")},
	{_T("伍")},
	{_T("陆")},
	{_T("柒")},
	{_T("捌")},
	{_T("玖")}
};

static const TCHAR pszChineseNumber[11][3] = 
{
	{_T("○")},
	{_T("一")},
	{_T("二")},
	{_T("三")},
	{_T("四")},
	{_T("五")},
	{_T("六")},
	{_T("七")},
	{_T("八")},
	{_T("九")},
	{_T("十")}
};

static const TCHAR pszRuleOutExe[1][50] = 
{
	_T("wnuserpage.exe")
};

#define IME_UI_NAME _T("WNINPUTUI")

#ifndef __IME_WB__
#define __IME_WB__
#endif

typedef struct _tagUIEXTEND			// UI窗口扩展的内容
{
    HWND m_hUIWnd;		// UI窗口句柄
	HWND m_hStatusWnd;	// 状态栏窗口句柄
	HWND m_hCompWnd;	// 编码框窗口句柄
    HWND m_hCandWnd;	// 候选窗口句柄
	HWND m_hMergeWnd;	// 组合窗口句柄
	HWND m_hMenuWnd;	// 固定窗口句柄
	HWND m_hTipWnd;		// 提示窗口句柄
	HWND m_hIMCWnd;		// 
} UIEXTEND, NEAR *PUIEXTEND, FAR *LPUIEXTEND;
const DWORD FIGWL_UIHWND   = 0;		//窗口存储的UI窗口句柄偏移位
const UINT UIEXTENDSOFTKEYBOARD =  sizeof(HWND);	//窗口扩展的大小
#define WM_EXE_MSG						WM_USER + 301
#define WM_APPBAR_DATA_MSG				WM_USER + 302
#define WM_SHOW_USERPAGE_LOGIN				WM_USER + 11
#define WM_SHOW_USERPAGE_INFO				WM_USER + 12

#endif	// __STRUCT_H__
