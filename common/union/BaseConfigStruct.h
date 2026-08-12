#ifndef __BASE_CONFIG_STRUCT_H__
#define __BASE_CONFIG_STRUCT_H__

#define SOFT_FILE_PATH						_T("7654Soft")
#define DRIVERS_32_FILE_NAME				_T("JiHe32.sys")
#define DRIVERS_64_FILE_NAME				_T("JiHe64.sys")
#define DRIVERS_SYS_FILE_NAME				_T("7654JiHe.sys")



// 定义推广商标示符长度
#define MAX_ADVERT_IDENTIFIER_LENGTH 30
// 定义玩家标示符长度
#define MAX_PLAYER_IDENTIFIER_LENGTH 33
// 定义验证码长度
#define MAX_SIGN_CODE_LENGTH 33
// 定义软件标示符长度
#define MAX_SOFT_IDENTIFIER_LENGTH 30
// 定义软件版本长度
#define MAX_SOFT_VER_LENGTH 20

// 定义统计计算安装数据间隔时间
#define MAX_PROCESS_INSTALL_STATISTICS_TIME 60 * 1000
// 定义统计计算安装数据间隔时间
#define MAX_COMMIT_TRANSACTION_TIME 60 * 1000

#define IS_VAILABILITY_EQUIP_POSITION(a) ( ((a) > NO_POSITION) && ((a) <= SHOES_POSITION) )

#define IS_VAILABILITY_GAME_EQUIP_PROPERTY(a) ( ((a) > NO_PROPERTY) && ((a) <= SHOES_PROPERTY) )

#define IS_VAILABILITY_THEURGY_ID(a) ( ((a) > GAME_THEURGY_ID_NONE) && ((a) <= GAME_SQUAMA_ART_ID) )
//
#define OFFICIALWEB_URL					_T("http://www.7654.com/promote")
#define OFFICIALFORUM_URL				_T("http://www.7654.com/promote")
#define OFFICIALWEIBO_URL				_T("http://www.7654.com/promote")
#define UPDMAKE_ADDRESS_URL				("http://updmake.7654.com/update.xml")
/////

#define SOFT_FILE_PATH						_T("7654Soft")
#define STATISTICS_DLL_NAME					_T("Statistics.dll")
#define UTILITY_EXE_NAME					_T("Utility.exe")
#define UNINST_EXE_NAME						_T("7654Uninst.exe")
#define	SOFT_APP_INI_FILE					_T("7654BaoHe.ini")
#define CONFIG_PATH							_T("Config")

//
#define SOFT_FILE_NAME						_T("7654Setup_1.0.0_00252")
#define SOFT_MAX_VERSION					_T("1.0")
#define SOFT_MIN_VERSION					_T("1.0")
#define SOFT_VERSION_INFO					_T("1.0.1.1027")
#define SOFT_VERSION_ITER					_T("008.002")
#define SOFT_NAME							_T("7654合集包制作工具")
#define SOFT_MAKE_APP_NAME					_T("7654合集包制作工具")
#define UPDATE_EXE_NAME						_T("7654MakeUpd.exe")
#define OFFICIAL_WEB						_T("http://www.7654.com/promote")
#define USEVESTIGE_FILE						_T("UseVestige.ini")

#define SOFT_CFG_PATH						_T("7654")
#define SOFT_USER_PATH						_T("7654.users")
#define CONFIG_FILE							_T("Config.ini")
#define MAIN_EXE_NAME						_T("7654Setup.exe")
#define SOFT_SERVICE_NAME					_T("service.exe")
#define SOFT_BAOKU_PATH						_T("51Jishu\\1.0.1.1027\\")
#define SOFT_BAOKU_NAME						_T("BaoKuUninst.exe")
#define SOFTWAREKIT_FILE_PATH				_T("7654BaoKu")
#define SOFTWAREKIT_FULL_NAME				_T("7654BaoKu.exe")
//
//_T("7654Setup.exe")
//
#define SERVICE_DLL_NAME					_T("Service.dll")
#define SERVICE_NAME_KEY					("7654_service_name")
#define SERVICE_DISPLAY_KEY					("7654_display_name")
#define SERVICE_DESCRIPTION_KEY				("7654_description_name")
#define SERVICE_EXE_NAME					_T("7654Setup_1.0.0_00252.exe")

#define SOFT7654_MAKE_ID					_T("7654soft")
#define SOFT7654_MAKE_VER					_T("7654ver")
#define SOFT7654_MAKE_IDENTIFIER			_T("7654Identifier")
#define SOFT7654_MAKE_UNINSTALL_IDENTIFIER	_T("7654IdentifierUninstall")
#define SOFT7654_MAKE_ONLINE_IDENTIFIER		_T("7654IdentifierOnline")
#define SOFTWAREKIT_NAME					_T("7654软件库")
#define SOFTWAREKIT_UNINST                  _T("BaoKuUninst.exe")



#endif	// __BASE_CONFIG_STRUCT_H__
