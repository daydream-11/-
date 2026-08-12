#ifndef __MENU_DEFINE_H__
#define __MENU_DEFINE_H__


#define ID_CMD_BEGINNING							0xF000
/****************************************************************************/
#define ID_CMD_SIMPLE_WB_INPUT_MODE					0x0001 // 纯五笔(W)
#define ID_CMD_BLEND_WB_PY_INPUT_MODE				0x0002 // 五笔拼音混合(X)
#define ID_CMD_SIMPLE_PY_INPUT_MODE					0x0003 // 纯拼音(P)
#define ID_CMD_CONVERT_TO_JIAN_TI					0x0004 // 简体(J)
#define ID_CMD_CONVERT_TO_FAN_TI					0x0005 // 繁体(F)
#define ID_CMD_CONVERT_TO_BAN_JIAO					0x0006 // 半角(B)
#define ID_CMD_CONVERT_TO_QUAN_JIAO					0x0007 // 全角(Q)
#define ID_CMD_LEFT_RIGHT_SHIFT						0x0008 // 左右Shift(A)
#define ID_CMD_LEFT_SHIFT							0x0009 // 左Shift(S)
#define ID_CMD_RIGHT_SHIFT							0x000A // 右Shift(D)
#define ID_CMD_LEFT_RIGHT_CTRL						0x000B // 左右Ctrl(J)
#define ID_CMD_LEFT_CTRL							0x000C // 左Ctrl(K)
#define ID_CMD_RIGHT_CTRL							0x000D // 右Ctrl(L)"
#define ID_CMD_NO_USE_SHIFT_CTRL					0x000E // 不使用快捷键(C)
#define ID_CMD_USE_PEGGING							0x000F // 编码反查(C)
#define ID_CMD_USE_ASSOCIATE						0x0010 // 词组联想(X)
#define ID_CMD_PEGGING_WB_CODE						0x0011 // 五笔编码(W)
#define ID_CMD_PEGGING_PY_CODE						0x0012 // 拼音编码(P)
#define ID_CMD_PEGGING_EN_CODE						0x0013 // 英语编码(E)
#define ID_CMD_CONVERT_TO_BIG5						0x0014 // 繁体(大五码)
#define ID_CMD_CONVERT_TO_HXW						0x0015 // 火星文
#define ID_CMD_SHUANG_PIN_INPUT_MODE			0x0016 // 双拼输入模式


#define ID_CMD_OPEN_SETTING_CONFIG					0x0100 // 设置属性(C)
#define ID_CMD_OPEN_SETTING_WIZARD					0x0101 // 设置向导(D)
#define ID_CMD_OPEN_IME_UTIL						0x0102 // 输入法管理器(J)
#define ID_CMD_OPEN_MB_MANAGER						0x0103 // 词库管理工具(M)
#define ID_CMD_FEEDBACK_URL							0x0104 // 用户建议(R)
#define ID_CMD_WEB_SITE_NONSTOP						0x0106 // 网址直达
#define ID_CMD_OPEN_TOOL_KIT						0x0107 // 工具箱
#define ID_CMD_MAKE_WORD							0x0150 // 手工造词
#define ID_CMD_USERPAGE								0x0151 // 用户登陆
#define ID_CMD_ACTIVEIME							0x0152 // 重新激活

#define ID_CMD_STATUS_SET_TRANSPARENT_80			0x0200 // 状态栏百分之80透明(E)
#define ID_CMD_STATUS_SET_TRANSPARENT_60			0x0201 // 状态栏百分之60透明(S)
#define ID_CMD_STATUS_SET_TRANSPARENT_40			0x0202 // 状态栏百分之40透明(F)
#define ID_CMD_STATUS_SET_TRANSPARENT_20			0x0203 // 状态栏百分之20透明(T)
#define ID_CMD_STATUS_SET_TRANSPARENT_0				0x0204 // 状态栏关闭透明(C)
#define ID_CMD_COMP_CAND_SET_TRANSPARENT_80			0x0205 // 编码候选百分之80透明(E)
#define ID_CMD_COMP_CAND_SET_TRANSPARENT_60			0x0206 // 编码候选百分之60透明(S)
#define ID_CMD_COMP_CAND_SET_TRANSPARENT_40			0x0207 // 编码候选百分之40透明(F)
#define ID_CMD_COMP_CAND_SET_TRANSPARENT_20			0x0208 // 编码候选百分之20透明(T)
#define ID_CMD_COMP_CAND_SET_TRANSPARENT_0			0x0209 // 编码候选关闭透明(C)
#define ID_CMD_ALL_WND_SET_TRANSPARENT_80			0x020A // 所有窗口百分之80透明(E)
#define ID_CMD_ALL_WND_SET_TRANSPARENT_60			0x020B // 所有窗口百分之60透明(S)
#define ID_CMD_ALL_WND_SET_TRANSPARENT_40			0x020C // 所有窗口百分之40透明(F)
#define ID_CMD_ALL_WND_SET_TRANSPARENT_20			0x020D // 所有窗口百分之20透明(T)
#define ID_CMD_ALL_WND_SET_TRANSPARENT_0			0x020E // 所有窗口关闭透明(C)
#define ID_CMD_SET_TRANSPARENT_DLG					0x020F // 自定义窗口透明度(V)

#define ID_CMD_SKIN_SETTING							0x0300 // 皮肤设置(S)
#define ID_CMD_SKIN_OFFICIAL						0x0301 // 皮肤官网(G)
#define ID_CMD_EDIT_SKIN_EDITOR						0x0302 // 皮肤编辑器(E)
#define ID_CMD_BRWOSE_LOCAL_SKIN					0x0303 // 浏览本地皮肤(V)
#define ID_CMD_RAND_CHANGE_SKIN						0x0304 // 随机换肤(H)
#define ID_CMD_USE_DEFAULT_SKIN						0x0305 // 默认皮肤(D)

#define ID_CMD_POPUP_NORMAL_MENU					0x0400 // 弹出正常菜单
#define ID_CMD_POPUP_SOFT_KEYBOARD					0x0401 // 弹出软键盘
#define ID_CMD_JIAN_TI_FAN_TI_SWITCH_OVER			0x0402 // 简体繁体切换
#define ID_CMD_BAN_JIAO_QUAN_JIAO_SWITCH_OVER		0x0403 // 半角全角切换
#define ID_CMD_CN_EN_INPUT_SWITCH_OVER				0x0404 // 中英文输入切换
#define ID_CMD_CN_EN_BIAO_DIAN_SWITCH_OVER			0x0405 // 中英文标点切换
#define ID_CMD_SOFTKEYBOARD_SWITCH_OVER				0x0420 // 软键盘切换

#define ID_CMD_OPEN_ABOUT_DLG						0x0500 // 关于(A)
#define ID_CMD_OPEN_HELP_URL						0x0501 // 帮助(H)
#define ID_CMD_OPEN_CELL_DICT_URL					0x0502 // 细胞词库(C)
#define ID_CMD_OPEN_DOWN_SKIN_URL					0x0503 // 皮肤下载(N)
#define ID_CMD_OPEN_OFFICIAL_WEI_BO_URL				0x0504 // 官方微博(B)
#define ID_CMD_OPEN_OFFICIAL_FOURM_URL				0x0505 // 官方论坛(F)
#define ID_CMD_OPEN_OFFICIAL_WEB_URL				0x0506 // 官方网站(S)
#define ID_CMD_OPEN_FEED_BACK_URL					0x0507 // 反馈建议(K)
#define ID_CMD_OPEN_REPORT_ERROR_URL				0x0508 // 报告错误(R)
#define ID_CMD_OPEN_NEWS							0x0509 // 今日资讯(R)
#define ID_CMD_OPEN_DAILY_WORDS						0x050A // 今日新词(X)
#define ID_CMD_OPEN_DAILY_SKIN						0x050B // 今日皮肤(P)
#define ID_CMD_OPEN_DAILY_SHOP						0x050C // 今日购物(G)
#define ID_CMD_SET_DEFAULT_SETTING					0x0600 // 恢复默认设置(R)
#define ID_CMD_SOFT_KEY_BOARD_BEGIN					0x0700 // 开始
#define ID_CMD_SOFT_KEY_BOARD_FUN1					0x0701 // 1 PC 键盘     asdfghjkl;
#define ID_CMD_SOFT_KEY_BOARD_FUN2					0x0702 // 2 希腊字母    αβγδε
#define ID_CMD_SOFT_KEY_BOARD_FUN3					0x0703 // 3 俄文字母    абвгд
#define ID_CMD_SOFT_KEY_BOARD_FUN4					0x0704 // 4 注音符号    ㄆㄊㄍㄐㄔ
#define ID_CMD_SOFT_KEY_BOARD_FUN5					0x0705 // 5 拼音字母    ā á ě è ó
#define ID_CMD_SOFT_KEY_BOARD_FUN6					0x0706 // 6 日文平假名  ぁぃぅぇぉ
#define ID_CMD_SOFT_KEY_BOARD_FUN7					0x0707 // 7 日文片假名  ァィゥヴェ
#define ID_CMD_SOFT_KEY_BOARD_FUN8					0x0708 // 8 标点符号    『‖々·〗
#define ID_CMD_SOFT_KEY_BOARD_FUN9					0x0709 // 9 数字序号    ⅠⅡⅢ㈠①
#define ID_CMD_SOFT_KEY_BOARD_FUN0					0x070A // 0 数学符号    ±×÷∑√
#define ID_CMD_SOFT_KEY_BOARD_FUNA					0x070B // A 制表符      ┓┼┞┳┼
#define ID_CMD_SOFT_KEY_BOARD_FUNB					0x070C // B 中文数字    壹贰千万兆
#define ID_CMD_SOFT_KEY_BOARD_FUNC					0x070D // C 特殊符号    ▲☆◆□→
#define ID_CMD_SOFT_KEY_BOARD_CLOSE					0x070E // 关闭软键盘(L)
#define ID_CMD_SOFT_KEY_BOARD_END					0x0710

#define ID_CMD_BEGIN_SKIN_POSITION					0x1000 // 皮肤开始



#endif	// __MENU_DEFINE_H__