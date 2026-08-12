///////////////////////////////////////////////////////////
//  EnumBOOLFnType.h
//  Implementation of the Class EnumBOOLFnType
//  Created on:      21-五月-2009 9:24:41
//  Original author: Administrator
///////////////////////////////////////////////////////////

#if !defined(EA_6E11FA3D_A259_4478_A196_DB429F690766__INCLUDED_)
#define EA_6E11FA3D_A259_4478_A196_DB429F690766__INCLUDED_

enum EnumBOOLFnType
{

	/**
	 * 没有数据
	 */
	NO_BOOL_TYPE = 1,
	/**
	 * 纯拼音模式：拼音提示五笔编码
	 */
	IS_PURE_PY_REMIND_WB_CODE = 3,
	/**
	 * 纯五笔输入：编码步步提示
	 */
	IS_PURE_WB_CODE_GRADUALLY_REMIND = 6,
	/**
	 * 纯五笔输入：单字输入模式
	 */
	IS_PURE_WB_SINGLE_INPUT_MODE = 7,
	/**
	 * 纯五笔输入：空码时取消输入
	 */
	IS_PURE_WB_EMPTY_CODE_CANCEL_INPUT = 8,
	/**
	 * 纯五笔输入：4码截至上屏
	 */
	IS_PURE_WB_FOUR_CODE_STOP_OUTPUT = 9,
	/**
	 * 纯五笔输入：误码时发出报警音
	 */
	IS_PURE_WB_ERROR_CODE_ALARM = 10,
	/**
	 * 纯五笔输入：4码唯一的字词，则自动上屏
	 */
	IS_PURE_WB_FOUR_CODE_ONLY_OUTPUT = 11,
	/**
	 * Shift + 字母输入英文时首字母大写
	 */
	IS_SHIFT_INPUT_EN_FIRST_LETTER_CAPITAL = 12,
	/**
	 * 切换到英文状态时保留输入窗口中已经存在的字符并上屏
	 */
	IS_TRANSFER_EN_OUTPUT_EXIST_COMP = 13,
	/**
	 * 在不同的窗口中显示拼音和候选词
	 */
	IS_DIFFERENT_WND_SHOW_COMP_CAND = 14,
	/**
	 * 隐藏状态栏
	 */
	IS_HIDDEN_STATUS = 15,
	/**
	 * 全屏程序时隐藏状态栏
	 */
	IS_FULL_SCREEN_HIDDEN_STATUS = 16,
	/**
	 * 使用皮肤
	 */
	IS_USE_SKIN = 17,
	/**
	 * 重设字体
	 */
	IS_RE_SET_FONT_STYLE = 18,
	/**
	 * 重设颜色
	 */
	IS_RE_SET_COLOR = 19,
	/**
	 * 智能删除误造词：错词上屏5秒内按下退格键自动删除新造错词
	 */
	IS_INTELLIGEN_DELETE_MAKE_WORD = 20,
	/**
	 * 网址模式：不切换中英文状态即可输入网址和电子邮箱
	 */
	IS_WEB_INPUT_MODE = 21,
	/**
	 * 数字后面的“。”输出为“.”
	 */
	IS_NUM_AFTER_OUTPUT_EN_PERIOD = 22,
	/**
	 * 自定义短语：通过haha输入^_^这样的符号
	 */
	IS_USER_DEFINE_PHRASE = 23,
	/**
	 * 分号模式：以分号“;”开头，快速输入英文，大写数字及时间日期
	 */
	IS_SEMICOLON_INPUT_MODE = 24,
	/**
	 * 用小键盘进行英文输入（即不用小键盘选词）
	 */
	IS_KEYPAD_INPUT_EN = 25,
	/**
	 * 网址、邮箱自动补全
	 */
	IS_WEB_MAIL_AUTO_REPLENISH = 26,
	/**
	 * 五笔和其他混合输入：编码步步提示
	 */
	IS_MIX_WB_CODE_GRADUALLY_REMIND = 27,
	/**
	 * 五笔混合输入：四码截止上屏
	 */
	IS_MIX_WB_FOUR_CODE_STOP_OUTPUT = 28,
	/**
	 * 五笔和其他混合输入：4码有唯一的字词，则自动上屏
	 */
	IS_MIX_WB_FOUR_CODE_ONLY_OUTPUT = 29,
	/**
	 * 五笔和其他混合输入：四码自动上屏、非五笔用户勿选
	 */
	IS_MIX_WB_FOUR_CODE_AUTO_OUTPUT = 30,
	/**
	 * 中文状态下使用英文标点
	 */
	IS_CN_STATUS_USE_EN_PUNCTUATION = 31,
	/**
	 * 临时变量在不同的窗口中显示拼音和候选词
	 */
	TEMP_IS_DIFFERENT_WND_SHOW_COMP_CAND = 32,
	/**
	 * 使用分割线
	 */
	USE_CUT_LINE = 33,
	/**
	 * 临时变量使用皮肤
	 */
	TEMP_USE_SKIN = 34,
	/**
	 * 临时变量使用分割线
	 */
	TEMP_USE_CUT_LINE = 35,
	/**
	 * 临时变量重设字体
	 */
	TEMP_RE_SET_FONT_STYLE = 36,
	/**
	 * 临时变量重设颜色
	 */
	TEMP_RE_SET_COLOR = 37,
	/**
	 * 五笔混输：四码空码取消
	 */
	IS_MIX_WB_FOUR_CODE_EMPTY_CANCEL = 38,
	/**
	 * 临时变量隐藏状态栏
	 */
	TEMP_HIDDEN_STATUS = 39,
	/**
	 * 临时变量是否打开软键盘
	 */
	TEMP_OPEN_SOFT_KEYBOARD = 40,
	/**
	 * 打开软键盘第几个
	 */
	TEMP_NUM_SOFT_KEYBOARD = 41,
	/**
	 * 五笔输入模式
	 */
	IS_USE_WB_MODE = 42,
	/**
	 * 拼音输入模式
	 */
	IS_USE_PY_MODE = 43,
	/**
	 * 英语输入模式
	 */
	EN_INPUT_MODE = 44,
	/**
	 * 快笔输入模式
	 */
	KB_INPUT_MODE = 45,
	/**
	 * 笔画输入模式
	 */
	BH_INPUT_MODE = 46,
	/**
	 * 是否使用快捷键减号(-)等号(=)翻页
	 */
	IS_USE_KJ_OEM_MINUS_PLUS = 47,
	/**
	 * 是否使用快捷键左右方括号([ ])翻页
	 */
	IS_USE_KJ_SQUARE_BRACKETS = 48,
	/**
	 * 是否使用快捷键逗号(,)句号(.)翻页
	 */
	IS_USE_KJ_OEM_COMMA_PERIOD = 49,
	/**
	 * 是否使用快捷键上页(Page Up)下页(Page On)翻页
	 */
	IS_USE_KJ_PAGE_UP_PAGE_ON = 50,
	/**
	 * 是否使用快捷键下页(Tab)上页(Shift Tab)翻页
	 */
	IS_USE_KJ_TAB_SHIFT_TAB = 51,
	/**
	 * 五笔反查模式
	 */
	IS_USE_WB_PEGGING = 52,
	/**
	 * 拼音反查模式
	 */
	IS_USE_PY_PEGGING = 53,
	/**
	 * 快笔反查模式
	 */
	KB_PEGGING_MODE = 54,
	/**
	 * 笔画反查模式
	 */
	BH_PEGGING_MODE = 55,
	/**
	 * 英语反查模式
	 */
	IS_USE_EN_PEGGING = 56,
	/**
	 * 纯五笔输入：四码有重码时发出报警音
	 */
	IS_PURE_WB_FOUR_CODE_REPEAT_ALARM = 57,
	/**
	 * 联想反查自动隐藏窗口
	 */
	IS_PEGGING_ASSOCIATE_AUTO_HIDE_WND = 58,
	/**
	 * 是否显示用户信息窗口
	 */
	IS_SHOW_USER_SYN_WND = 59,
	/**
	 * 纯五笔模式：分号(')第三重码
	 */
	IS_PURE_WB_SINGLE_QUOTES_CHOOSE_THREE = 60,
	/**
	 * 纯五笔模式：分号(;)第二重码
	 */
	IS_PURE_WB_SEMICOLON_CHOOSE_SECOND = 61,
	/**
	 * 是否开启打字速度
	 */
	IS_USE_OUTPUT_WORD_SPEED = 62,
	/**
	 * 五笔混输：分号(;)第二重码
	 */
	IS_MIX_WB_SEMICOLON_CHOOSE_SECOND = 63,
	/**
	 * 隐藏网址导航窗口
	 */
	IS_HIDDEN_ADWEB_WND = 65,
	/**
	 * 斜杠 \ 转顿号、
	 */
	IS_SLASH_TO_CONVERT_PAUSE_MARK = 66,
	/**
	 * 反斜杠 / 转顿号、
	 */
	IS_OPPOSITE_SLASH_TO_CONVERT_PAUSE_MARK = 67,
	/**
	 * 隐藏固定位置和删除候选字菜单
	 */
	IS_HIDE_FIXED_POS_DELETE_CAND_MENU = 68,
	/**
	 * 是否使用五笔自定义词组
	 */
	IS_USE_WB_CUSTOM_PHRASE = 69,
	/**
	 * 是否使用五笔用户词组
	 */
	IS_USE_WB_USER_PHRASE = 70,
	/**
	 * 是否使用拼音自定义词组
	 */
	IS_USE_PY_CUSTOM_PHRASE = 71,
	/**
	 * 是否使用拼音用户词组
	 */
	IS_USE_PY_USER_PHRASE = 72,
	/**
	 * 是否使用短语用户词组
	 */
	IS_USE_DY_USER_PHRASE = 73,
	/**
	 * 是否使用网址用户词组
	 */
	IS_USE_URL_USER_PHRASE = 74,
	/**
	 * 是否使用首字母简拼
	 */
	IS_USE_FIRST_LETTER_JIAN_PIN = 75,
	/**
	 * 动态组词：没有全匹配的候选词时，自动构造新词
	 */
	IS_USE_DYNAMIC_MAKE_PIN_YIN_WORD = 76,
	/**
	 * 动态造词：没有全匹配的候选词时，自动记录到拼音用户词库
	 */
	IS_USE_DYNAMIC_ADD_USER_PIN_YIN_WORD = 77,
	/**
	 * 空码时检索GBK汉字
	 */
	IS_EMPTY_CODE_QUERY_GBK_WORD = 78,
	/**
	 * 使用编码样式
	 */
	USE_COMP_STYLE = 79,
	/**
	 * 临时变量使用编码样式
	 */
	TEMP_USE_COMP_STYLE = 80,
	/**
	 * 使用候选样式
	 */
	USE_CAND_STYLE = 81,
	/**
	 * 临时变量使用候选样式
	 */
	TEMP_USE_CAND_STYLE = 82,
	/**
	 * 是否使用快捷键减号(-)等号(=)翻页
	 */
	IS_USE_KJ_OEM_MINUS_PLUS_PHRASE_CHOOSE_WORD = 83,
	/**
	 * 是否使用快捷键左右方括号([ ])翻页
	 */
	IS_USE_KJ_SQUARE_BRACKETS_PHRASE_CHOOSE_WORD = 84,
	/**
	 * 是否使用快捷键逗号(,)句号(.)翻页
	 */
	IS_USE_KJ_OEM_COMMA_PERIOD_PHRASE_CHOOSE_WORD = 85,
	/**
	 * 拼音纠错：自动识别某些错误输入
	 */
	IS_USE_PIN_YIN_ERROR_RECOVERY = 86,
	/**
	 * 拼音纠错：gn->ng(如：dign->ding)
	 */
	IS_USE_ERROR_RECOVERY_GN_TO_NG = 87,
	/**
	 * 拼音纠错：mg->ng(如：komg->kong)
	 */
	IS_USE_ERROR_RECOVERY_MG_TO_NG = 88,
	/**
	 * 拼音纠错：iou->iu(如：jiou->jiu)
	 */
	IS_USE_ERROR_RECOVERY_IOU_TO_IU = 89,
	/**
	 * 拼音纠错：uei->ui(如：tuei->tui)
	 */
	IS_USE_ERROR_RECOVERY_UEI_TO_UI = 90,
	/**
	 * 拼音纠错：uen->un(如：kuen->kun)
	 */
	IS_USE_ERROR_RECOVERY_UEN_TO_UN = 91,
	/**
	 * 使用英语系统词库
	 */
	IS_USE_YY_SYS_WORD = 92,
	/**
	 * 在候选窗口显示英语的中文翻译
	 */
	IS_CAND_SHOW_YY_TRANSLATE = 93,
	/**
	* 取消迷你咨询
	*/
	IS_CANCEL_MINI_NEWS = 94,
	/**
	* 取消手机助手
	*/
	IS_CANCEL_WDJ_HELP_HAND = 95,
	/*
	* 是否使用删除词库窗口
	*/
	IS_USE_DEL_USER_PHRASE = 96,
		/*
	* 是否使用系统最新更新词库窗口
	*/
	IS_USE_LU_SYSTEM_PHRASE = 97,
	/**
	* 使用细胞词库
	*/
	IS_USE_CELL_DICT = 98,
	/**
	* 使用细胞词库自动更新
	*/
	IS_USE_AUTO_UPDATE_CELL_DICT = 99,
	 /**
	 * 是否自动同步词库
	 */
	 IS_SYNC_MB = 100,
	 /**
	 * 是否自动同步配置
	 */
	 IS_SYNC_CFG = 101,
	  /**
	 * 是否取消每日新词
	 */
	 IS_CANCLE_DAILY_NEW_WORD = 102,
	  /**
	 * 是否不使用shift和ctrl中文切换键
	 */
	 IS_NOUSE_SHIFT_CTRL_SWITCH_CE = 103,
	 /**
	 * 是否使用固定位置词库
	 */
	 IS_USE_POSITION_PHRASE = 104,
	 /**
	 * 是否使用五笔Z按键重复输入
	 */
	 IS_USE_WB_Z_REPEAT_INPUT = 105,
	/**
	 * 是否光标跟随
	 */
	IS_NOCURSOR_FOLLOW = 106,
	  /**
	 * 是否取消皮肤推荐
	 */
	 IS_CANCLE_RECOMMEND_SKIN = 107,
	  /**
	 * 是否取消迷你购物
	 */
	 IS_CANCEL_MINI_SHOP = 108,
};
#endif // !defined(EA_6E11FA3D_A259_4478_A196_DB429F690766__INCLUDED_)
