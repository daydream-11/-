///////////////////////////////////////////////////////////
//  EnumVOIDFnType.h
//  Implementation of the Class EnumVOIDFnType
//  Created on:      09-六月-2009 11:20:51
//  Original author: Administrator
///////////////////////////////////////////////////////////

#if !defined(EA_C6BC85E7_FB7C_4c25_9C55_472D8951FD70__INCLUDED_)
#define EA_C6BC85E7_FB7C_4c25_9C55_472D8951FD70__INCLUDED_

enum EnumVOIDFnType
{
	/**
	 * 设置属性功能
	 */
	SETTING_ATTRIBUTE,
	/**
	 * 设置向导功能
	 */
	SETTING_WIZARD,
	/**
	 * 登陆通行证
	 */
	LOGIN_PASSPORT,
	/**
	 * 中文状态转换为英文状态
	 */
	CN_STATUS_TO_EN_STATUS,
	/**
	 * 英文状态转换为中文状态
	 */
	EN_STATUS_TO_CN_STATUS,
	/**
	 * 中文状态英文状态切换
	 */
	CE_TO_CUT_OVER,
	/**
	 * 半角全角状态切换
	 */
	BQ_TO_CUT_OVER,
	/**
	 * 简体繁体状态切换
	 */
	FJ_TO_CUT_OVER,
	/**
	 * 中文标点，英文标点切换
	 */
	BD_TO_CUT_OVER,
	/**
	 * 繁体状态切换
	 */
	FT_TO_CUT_OVER,
	/**
	 * 简体状态切换
	 */
	JT_TO_CUT_OVER,
	/**
	 * 半角状态切换
	 */
	BJ_TO_CUT_OVER,
	/**
	 * 全角状态切换
	 */
	QJ_TO_CUT_OVER,
	/**
	 * 皮肤设置
	 */
	SETTING_STYLE,
	/**
	 * 编码反查
	 */
	CODE_PEGGING,
	/**
	 * 词组联想
	 */
	PHRASE_ASSOCIATE,
	/**
	 * 随机选择皮肤
	 */
	RANDOM_MODIFY_SKIN,
	/**
	 * 打开关于对话框
	 */
	DO_ABOUT_DLG,
	/**
	 * 打开用户登录进程
	 */
	DO_USER_PAGE,
	/**
	 * 打开功能菜单
	 */
	DO_POPUP_FN_MENU,
	/**
	 * 用户自造词
	 */
	DO_MAKE_WORD_DLG,
	/**
	 * 设置我的主页
	 */
	DO_SET_START_PAGE_DLG,
	/**
	 * 更多皮肤下载
	 */
	DO_MORE_SKIN_DOWN ,
	/**
	 * 浏览本地皮肤
	 */
	DO_BROWSE_LOCAL_SKIN ,
	/**
	 * 打开软键盘
	 */
	DO_POPUP_FN_SOFTKEYBOARD
};
#endif // !defined(EA_C6BC85E7_FB7C_4c25_9C55_472D8951FD70__INCLUDED_)
