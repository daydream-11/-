///////////////////////////////////////////////////////////
//  EnumINTFnType.h
//  Implementation of the Class EnumINTFnType
//  Created on:      21-五月-2009 16:49:07
//  Original author: Administrator
///////////////////////////////////////////////////////////

#if !defined(EA_380F3AFF_2D09_407b_B3C0_984E4336B64D__INCLUDED_)
#define EA_380F3AFF_2D09_407b_B3C0_984E4336B64D__INCLUDED_

enum EnumINTFnType
{
	/**
	 * 编码字体大小
	 */
	COMP_FONT_SIZE = 0,
	/**
	 * 候选词窗口对齐方式：（0：跟随编码、1：编码窗口下方、2：编码窗口右侧）
	 */
	CAND_WND_ALIGN_AT_COMP_WND = 1,
	/**
	 * 初始输入状态（0：中文，1：英文）
	 */
	INIT_CE_STATUS = 2,
	/**
	 * 初始繁简体状态（0：简体，1：繁体,2：Big5）
	 */
	INIT_FJ_STATUS = 3,
	/**
	 * 初始全半角状态（0：半角，1：全角）
	 */
	INIT_BQ_STATUS = 4,
	/**
	 * 横排显示或竖排显示（1：横排显示，0竖排显示）
	 */
	COMP_CAND_WND_SHOW_MODE = 5,
	/**
	 * 五笔和其他混合输入：混输词频调整
	 */
	MIX_WB_INPUT_POS_REVISION = 6,
	/**
	 * 纯五笔输入：五笔词频调整
	 */
	PURE_WB_INPUT_POS_REVISION = 7,
	/**
	 * 纯拼音输入：拼音词频调整
	 */
	PURE_PY_INPUT_POS_REVISION = 8,
	/**
	 * 回车键用于
	 */
	ENTER_KEY_USE_FOR = 9,
	/**
	 * 升级选项：程序升级
	 */
	APPLICATION_UPDATE = 10,
	/**
	 * 临时变量候选词窗口对齐方式：（0：跟随编码、1：编码窗口下方、2：编码窗口右侧）
	 */
	TEMP_CAND_WND_ALIGN_AT_COMP_WND = 11,
	/**
	 * 临时变量横排显示或竖排显示（1：横排显示，0竖排显示）
	 */
	TEMP_COMP_CAND_WND_SHOW_MODE = 12,
	/**
	 * 显示候选字个数
	 */
	SHOW_CAND_WORD_NUM = 13,
	/**
	 * 临时变量显示候选字个数
	 */
	TEMP_SHOW_CAND_NUM = 14,
	/**
	 * 临时变量编码字体大小
	 */
	TEMP_COMP_FONT_SIZE = 15,
	/**
	 * 分割线左边距离
	 */
	CUT_LINE_LEFT = 16,
	/**
	 * 临时变量分割线左边距离
	 */
	TEMP_CUT_LINE_LEFT = 17,
	/**
	 * 临时变量分割线右边距离
	 */
	TEMP_CUT_LINE_RIGHT = 18,
	/**
	 * 分割线右边距离
	 */
	CUT_LINE_RIGHT = 19,
	/**
	 * 编码左边距离
	 */
	COMP_LEFT_POS = 20,
	/**
	 * 临时变量编码左边距离
	 */
	TEMP_COMP_LEFT_POS = 21,
	/**
	 * 临时变量编码上面距离
	 */
	TEMP_COMP_TOP_POS = 22,
	/**
	 * 编码上面距离
	 */
	COMP_TOP_POS = 23,
	/**
	 * 编码右边距离
	 */
	COMP_RIGHT_POS = 24,
	/**
	 * 临时变量编码右边距离
	 */
	TEMP_COMP_RIGHT_POS = 25,
	/**
	 * 临时变量编码下边边距离
	 */
	TEMP_COMP_BOTTOM_POS = 26,
	/**
	 * 编码下边边距离
	 */
	COMP_BOTTOM_POS = 27,
	/**
	 * 候选左边距离
	 */
	CAND_LEFT_POS = 28,
	/**
	 * 临时变量候选左边距离
	 */
	TEMP_CAND_LEFT_POS = 29,
	/**
	 * 候选上面距离
	 */
	CAND_TOP_POS = 30,
	/**
	 * 候选右边距离
	 */
	CAND_RIGHT_POS = 31,
	/**
	 * 临时变量候选右边距离
	 */
	TEMP_CAND_RIGHT_POS = 32,
	/**
	 * 临时变量候选下边边距离
	 */
	TEMP_CAND_BOTTOM_POS = 33,
	/**
	 * 候选下边边距离
	 */
	CAND_BOTTOM_POS = 34,
	/**
	 * 临时变量候选上面距离
	 */
	TEMP_CAND_TOP_POS = 35,
	/**
	 * 临时变量候选字体大小
	 */
	TEMP_CAND_FONT_SIZE = 36,
	/**
	 * 候选字体大小
	 */
	CAND_FONT_SIZE = 37,
	/**
	 * 状态栏相对屏幕的左边位置
	 */
	STATUS_LEFT_POS_OF_SCREEN = 38,
	/**
	 * 状态栏相对屏幕的上边位置
	 */
	STATUS_TOP_POS_OF_SCREEN = 39,
	/**
	 * 临时变量当前繁简体状态（0：简体，1：繁体）
	 */
	TEMP_CUR_FJ_STATUS = 40,
	/**
	 * 临时变量当前全半角状态（0：半角，1：全角）
	 */
	TEMP_CUR_BQ_STATUS = 41,
	/**
	 * 临时变量当前输入状态（0：中文，1：英文）
	 */
	TEMP_CUR_CE_STATUS = 42,
	/**
	 * 临时变量当前标点状态（0：中文标点，1：英文标点）
	 */
	TEMP_CUR_BD_STATUS = 43,
	/**
	 * 编码窗口相对屏幕的左边位置
	 */
	TEMP_COMP_OF_SCREEN_LEFT_POS = 44,
	/**
	 * 编码窗口相对屏幕的上边位置
	 */
	TEMP_COMP_OF_SCREEN_TOP_POS = 45,
	/**
	 * 初始标点状态（0：中文标点，1：英文标点）
	 */
	INIT_BD_STATUS = 46,
	/**
	 * 临时变量当前单引号状态（0：左边单引号，1：右边单引号）
	 */
	TEMP_SINGLE_QUOTES_STATUS = 47,
	/**
	 * 临时变量当前双引号状态（0：左边双引号，1：右边双引号）
	 */
	TEMP_DOUBLE_QUOTES_STATUS = 48,
	/**
	 * 当前更改皮肤配置次数
	 */
	CUR_MODIFY_STYLE_TIMES = 49,
	/**
	 * 临时变量当前更改皮肤配置次数
	 */
	TEMP_CUR_MODIFY_STYLE_TIMES = 50,
	/**
	 * 当前更改弹出网站次数
	 */
	CUR_MODIFY_ADWEB_TIMES = 51,
	/**
	 * 临时变量当前更改弹出网站次数
	 */
	TEMP_CUR_MODIFY_ADWEB_TIMES = 52,
	/**
	 * 当前更改拼音纠错次数
	 */
	CUR_MODIFY_ERROR_RECOVERY_TIMES = 53,
	/**
	 * 编码反查或者词组联想（0：都不是，1：编码反查，2：词组联想）
	 */
	CODE_PEGGING_PHRASE_ASSOCIATE_MODE = 54,
	/**
	 * 候选窗口相对屏幕的左边位置
	 */
	TEMP_CAND_OF_SCREEN_LEFT_POS = 55,
	/**
	 * 候选窗口相对屏幕的上边位置
	 */
	TEMP_CAND_OF_SCREEN_TOP_POS = 56,
	/**
	 * 显示功能设置中的用户词库对话框
	 */
	SHOW_USER_WORD_DLG = 57,
	/**
	 * 临时变量显示功能设置中的用户词库对话框
	 */
	TEMP_SHOW_USER_WORD_DLG = 58,
	/**
	 * 联想反查自动隐藏时间
	 */
	PEGGING_ASSOCIATE_AUTO_HIDE_SECOND = 59,
	/**
	 * 编码窗口相对屏幕的左边位置
	 */
	COMP_LEFT_POS_OF_SCREEN = 60,
	/**
	 * 编码窗口相对屏幕的上边位置
	 */
	COMP_TOP_POS_OF_SCREEN = 61,
	/**
	 * 候选窗口相对屏幕的上边位置
	 */
	CAND_TOP_POS_OF_SCREEN = 62,
	/**
	 * 候选窗口相对屏幕的左边位置
	 */
	CAND_LEFT_POS_OF_SCREEN = 63,
	/**
	 * 用户等级
	 */
	USER_GRADE = 64,
	/**
	 * 用户编号
	 */
	USER_ID = 65,
	/**
	 * 中英文切换快捷键
	 */
	CE_TO_CUT_OVER_HOTKEY = 66,
	/**
	 * 当前更改热键配置次数
	 */
	CUR_MODIFY_HOTKEY_TIMES = 67,
	/**
	 * 临时变量当前更改热键配置次数
	 */
	TEMP_CUR_MODIFY_HOTKEY_TIMES = 68,
	/**
	 * 使用：Ctrl + 数字选择软键盘
	 */
	USE_CTRL_NUM_OPEN_SOFTKEYBOARD = 69,
	/**
	 * 自动造词设置
	 */
	AUTO_MAKE_WORD_SETTING = 70,
	/**
	 * 当前更改其他配置次数
	 */
	CUR_MODIFY_OTHER_TIMES = 71,
	/**
	 * 临时变量：当前更改其他配置次数
	 */
	TEMP_CUR_MODIFY_OTHER_TIMES = 72,
	///**
	// * 是否固定窗口模式
	// */
	//FIXED_WND_MODE,
	///**
	// * 临时变量：是否固定窗口模式
	// */
	//TEMP_FIXED_WND_MODE,
	///**
	// * 定横排窗口宽度
	// */
	//FIXED_HOR_WND_WIDTH,
	///**
	// * 临时变量：定横排窗口宽度
	// */
	//TEMP_FIXED_HOR_WND_WIDTH,
	///**
	// * 固定横排窗口高度
	// */
	//FIXED_HOR_WND_HEIGHT,
	///**
	// * 临时变量：固定横排窗口高度
	// */
	//TEMP_FIXED_HOR_WND_HEIGHT,
	///**
	// * 固定竖排窗口宽度
	// */
	//FIXED_VER_WND_WIDTH,
	///**
	// * 临时变量：固定竖排窗口宽度
	// */
	//TEMP_FIXED_VER_WND_WIDTH,
	///**
	// * 固定竖排窗口高度
	// */
	//FIXED_VER_WND_HEIGHT,
	///**
	// * 临时变量：固定竖排窗口高度
	// */
	//TEMP_FIXED_VER_WND_HEIGHT,
	//
	/**
	 * 状态栏窗口透明度
	 */
	STATUS_WND_TRANSPARENCY = 73,
	/**
	 * 候选框窗口透明度
	 */
	CAND_WND_TRANSPARENCY = 74,
	/**
	 * 所有窗口透明度
	 */
	ALL_WND_TRANSPARENCY = 75,
	/**
	 * 临时变量上一个输入状态（0：中文，1：英文）
	 */
	TEMP_FRONT_CE_STATUS = 76,
	/**
	 * 查询汉字类型：（0：GBK汉字，1：常用汉字）
	 */
	QUERY_CHINESE_WORD_MODE = 77,
	/**
	 * 临时变量当前更改拼音纠错次数
	 */
	 TEMP_CUR_MODIFY_ERROR_RECOVERY_TIMES = 78,
	 /**
	 * 是否自动同步词库
	 */
	 STATUS_SYNC_MB = 79,
	 /**
	 * 是否自动同步配置
	 */
	 STATUS_SYNC_CONFIG = 80,
	 /*
	 * 自动同步词库间隔时间
	 */
	 SYNC_USERMB_TIME = 81,
	 /**
	 * 状态栏窗口宽度
	 */
	 STATUS_WND_WIDTH = 82,
	 /**
	 * 状态栏窗口高度
	 */
	 STATUS_WND_HEIGHT = 83,
	 /**
	 * 二三候选字
	 */
	 CHOSE_23_CAND_KEY = 84,
	/**
	 * 临时变量当前火星文
	 */
	TEMP_CUR_HXW_STATUS = 85,

};
#endif // !defined(EA_380F3AFF_2D09_407b_B3C0_984E4336B64D__INCLUDED_)
