#ifndef __GAME_DEFINE_H__
#define __GAME_DEFINE_H__

/////////////////////////////////////////////////////////////////////////////////
// 数据库操作状态
/////////////////////////////////////////////////////////////////////////////////
enum EDBOprateStatus
{
	// 数据不变
	DB_FIXEDLY,
	// 插入数据
	DB_INSERT,
	// 更新数据
	DB_UPDATE,
	// 删除数据
	DB_DELETE,
};

// 数据库事务状态
enum ETransactionStatus
{
	// 没有状态
	NO_STATUS,
	// 打开状态
	OPEN_STATUS,
};

// 安装数据标识符
enum EInstallFlag
{
	// 没有错误
	NO_INSTALL_ERROR = 0,
	// sign错误
	SIGN_CODE_ERROR = 1,
	// 间隔时间错误
	INTERVAL_TIME_ERROR = 2,
};


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

// 定义游戏服务器跟php服务器约定的Key(gswb的32位MD5加密)
#define KEY_IDENTIFIER "0410cf07d350e99b05a2b5ce80f26dda"
// 定义统计计算安装数据间隔时间
#define MAX_ERROR_INTERVAL_TIME 2 * 1000



// 定义宏显示消息日志
#define SHOW_MSG_LOG

// 自定义用户消息
#define WM_USERMESSSAGE		WM_USER + 1256
// 用户自定义消息参数
enum 
{
	// 
	eSYNC_USERCFG	= 0X01,
	eEXIT_LOGIN		= 0X02,	
	//
	eNO_USER		= 0X03,
	ePWD_ERROR		= 0X04,
	//
	eSET_TOPMOST	= 0X05,
	//
	eSHOW_LOGIN_PAGE,
};

#endif	// __GAME_DEFINE_H__
