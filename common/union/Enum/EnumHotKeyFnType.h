///////////////////////////////////////////////////////////
//  EnumHotKeyFnType.h
//  Implementation of the Class EnumHotKeyFnType
//  Created on:      15-六月-2009 16:33:26
//  Original author: Administrator
///////////////////////////////////////////////////////////

#if !defined(EA_3B506EB6_D4EC_408a_BD94_81CC6166B529__INCLUDED_)
#define EA_3B506EB6_D4EC_408a_BD94_81CC6166B529__INCLUDED_

enum EnumHotKeyFnType
{
	/**
	 * 没有快捷键
	 */
	NO_HOT_KEY,
	/**
	 * 使用五笔词库快捷键
	 */
	USE_KJ_WB_WORD,
	/**
	 * 使用拼音词库快捷键
	 */
	USE_KJ_PY_WORD,
	/**
	 * 使用快笔词库快捷键
	 */
	USE_KJ_KB_WORD,
	/**
	 * 使用笔画词库快捷键
	 */
	USE_KJ_BH_WORD,
	/**
	 * 使用英语词库快捷键
	 */
	USE_KJ_EN_WORD,
	/**
	 * 使用快捷键中英文标点切换
	 */
	USE_KJ_BD_TOCUTOVER,
	/**
	 * 是否使用快捷键半角全角切换
	 */
	USE_KJ_BQ_TOCUTOVER,
	/**
	 * 使用随机皮肤快捷键
	 */
	USE_KJ_RANDOM_SKIN,
	/**
	 * 使用系统菜单快捷键
	 */
	USE_KJ_SYS_MENU,
	/**
	 * 使用软键盘快捷键
	 */
	USE_KJ_SOFT_KEYBOARD,
	/**
	 * 使用繁简体快捷键
	 */
	USE_KJ_FJT_TOCUTOVER,
	/**
	 * 使用设置属性快捷键
	 */
	USE_KJ_SETTING_CONFIG,
	/**
	 * 临时变量使用五笔词库快捷键
	 */
	TEMP_USE_KJ_WB_WORD,
	/**
	 * 临时变量使用拼音词库快捷键
	 */
	TEMP_USE_KJ_PY_WORD,
	/**
	 * 临时变量使用快笔词库快捷键
	 */
	TEMP_USE_KJ_KB_WORD,
	/**
	 * 临时变量使用笔画词库快捷键
	 */
	TEMP_USE_KJ_BH_WORD,
	/**
	 * 临时变量使用英语词库快捷键
	 */
	TEMP_USE_KJ_EN_WORD,
	/**
	 * 临时变量使用快捷键中英文标点切换
	 */
	TEMP_USE_KJ_BD_TOCUTOVER,
	/**
	 * 是否使用快捷键半角全角切换
	 */
	TEMP_USE_KJ_BQ_TOCUTOVER,
	/**
	 * 临时变量使用随机皮肤快捷键
	 */
	TEMP_USE_KJ_RANDOM_SKIN,
	/**
	 * 临时变量使用系统菜单快捷键
	 */
	TEMP_USE_KJ_SYS_MENU,
	/**
	 * 临时变量使用软键盘快捷键
	 */
	TEMP_USE_KJ_SOFT_KEYBOARD,
	/**
	 * 临时变量使用繁简体快捷键
	 */
	TEMP_USE_KJ_FJT_TOCUTOVER,
	/**
	 * 临时变量使用设置属性快捷键
	 */
	TEMP_USE_KJ_SETTING_CONFIG,
	/**
	 * 反查五笔快捷键
	 */
	USE_KJ_WB_PEGGING,
	/**
	 * 反查拼音快捷键
	 */
	USE_KJ_PY_PEGGING,
	/**
	 * 反查快笔快捷键
	 */
	USE_KJ_KB_PEGGING,
	/**
	 * 反查笔画快捷键
	 */
	USE_KJ_BH_PEGGING,
	/**
	 * 反查英语快捷键
	 */
	USE_KJ_EN_PEGGING,
	/**
	 * 临时变量反查五笔快捷键
	 */
	TEMP_USE_KJ_WB_PEGGING,
	/**
	 * 临时变量反查拼音快捷键
	 */
	TEMP_USE_KJ_PY_PEGGING,
	/**
	 * 临时变量反查快笔快捷键
	 */
	TEMP_USE_KJ_KB_PEGGING,
	/**
	 * 临时变量反查笔画快捷键
	 */
	TEMP_USE_KJ_BH_PEGGING,
	/**
	 * 临时变量反查英语快捷键
	 */
	TEMP_USE_KJ_EN_PEGGING,
	/**
	 * 反查快捷键
	 */
	USE_KJ_PEGGING,
	/**
	 * 临时变量反查快捷键
	 */
	TEMP_USE_KJ_PEGGING,
	/**
	 * 联想快捷键
	 */
	USE_KJ_ASSOCIATE,
	/**
	 * 临时变量联想快捷键
	 */
	TEMP_USE_KJ_ASSOCIATE,
	/**
	 * 使用自造词快捷键
	 */
	USE_KJ_MAKE_WORD,
	/**
	 * 临时变量使用自造词快捷键
	 */
	TEMP_USE_KJ_MAKE_WORD,
	/**
	 * 使用账号登陆快捷键
	 */
	USE_KJ_USER_PAGE,
	/**
	 * 临时变量：使用账号登陆快捷键
	 */
	TEMP_USE_KJ_USER_PAGE,
	/**
	 * 使用设置向导快捷键
	 */
	USE_KJ_SETTING_WIZARD,
	/**
	 * 临时变量：使用设置向导快捷键
	 */
	TEMP_USE_KJ_SETTING_WIZARD,
	/**
	 * 临时变量：快捷键五笔拼音混输
	 */
	TEMP_USE_KJ_WBPY_WORD,
	/**
	 * 快捷键五笔拼音混输
	 */
	USE_KJ_WBPY_WORD,
};
#endif // !defined(EA_3B506EB6_D4EC_408a_BD94_81CC6166B529__INCLUDED_)
