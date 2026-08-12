//
//文件名称：	Type.h
//功能描述：	类型定义，区分不同操作系统间系统调用的设置，所有当前工程
//				内的代码都必须第一个引用此文件
//版本说明：	Windows操作系统需要定义宏：__WINDOWS__
//				Linux操作系统需要定义宏：__LINUX__
//
//

#ifndef __GAME_TYPE_H__
#define __GAME_TYPE_H__

#include "Type.h"
#include "Assertx.h"
#include "GameUtil.h"
#include "GameDefine.h"
#include "PacketDefine.h"
#include "FileDefine.h"
#include "Log.h"

struct IOMemoryConfig
{
	// 内存大小
	UINT uMemorySize;
	// 内存个数
	UINT uBlockCount;
};

typedef vector<IOMemoryConfig> TVectorIOMemoryConfig;

// 方向
enum OBJECT_DIRECTION
{
	A_LEFT = 0,
	A_RIGHT = 1,
};

#endif	// __GAME_TYPE_H__
