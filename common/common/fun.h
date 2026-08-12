#pragma once

#include <string>
#include <vector>
#include <list>


/**
  *@fun.h
  * 简单的函数
  */


/******* 内存有关 ********/
/**
*@brief 将数据转换成字符串
*@例如: 1 char arr[2] = {'1', '2', '3'}, 调用mem_get_str(arr, 3),则返回"123"
*       2 char arr[3] = {'1', '\0', '3'}, 调用mem_get_str(arr,3),则返回"1"
*/
extern std::string mem_get_str(const char *addr, size_t size);

void mem_set_str(char *addr, size_t addrSize, const std::string &v);


/******* 路劲有关 ********/
/**
 *@brief 获取exe的路径
 * 例如: c:\aa\a.exe 则返回 a:\aa
 */
std::string fs_get_exe_path();

/*@brief 获取exe的名称
 * 例如: c:\aa\a.exe 则返回 a.exe
 */
std::string fs_get_exe_filename();

/*@brief 获取exe的名称
 * 例如: c:\aa\a.exe 则返回c:\aa\a.exe
 */
std::string fs_get_exe_fullname();

//删除文件名里面的路径
std::string fs_path_strip_path(const std::string &f);

/*强制删除文件 path 目录下的 filename 文件*/
void fs_delete_file(const std::string &filename);

std::string fs_get_special_folder_path(int csidl);

//返回临时文件名(包含路劲)
std::string fs_get_tmp_filename(const char *prefix=NULL);

std::string fs_get_tmp_path();

/******* 进程有关 ********/

/*@brief 通过程序名称获取进程id列表
 * 例如: 4.exe 返回 4043 4023
 */
std::string string_makeupper(const std::string &s);
bool process_id(const std::string &filename, std::list<int> &ids);

/******* 数字有关 ********/
/**
  *@brief 将int转换成string
  */
std::string num2str(int v);

std::string num2str(unsigned int v);

std::string num2str(long long v);

std::string num2str(float v);

/**
  *@brief 将data二进制数据，转换成可读的十六进制字符串
  */
std::string binary2Hex(const char *data, int len, const char *space=NULL);

/*utf8转换到gbk*/
std::string utf82gbk(const char *utf8);

/*将gbk转换成utf8*/
std::string gbk2utf8(const char *gbk);

/*将unicode转换成gbk*/
std::string unicode2gbk(const wchar_t *unicode);

std::wstring utf8_to_unicode(const char *utf8);

std::string unicode_to_utf8(const wchar_t *unicode);

std::string w2a(const wchar_t *s);

std::wstring a2w(const char *s);

/*是否为网吧环境*/ 
bool is_wang_ba();

/*返回CPU使用率*/
int cpu_use_percent();

/*返回内存使用率 0-100*/
int mem_use_percent();

/******* 时间有关 ********/
/*返回当前日期与时间*/
std::string time_cur_data_time();

/*返回当前日期*/
std::string time_cur_data();

/*返回当前时间*/
std::string time_cur_time();

/*将文件时间转换为时间戳*/
long long filetime2timestamp(const FILETIME &fm);

time_t systemtime2timet(const SYSTEMTIME& st);

int atoi(const std::string &s);

//在str中查找sub，忽略大小写
const char *strstri(const char *str, const char *sub);

//在str中查找sub，忽略大小写
const char *strstri(const std::string &str, const char *sub);


/******* 系统有关 ********/

//返回当前登陆的用户名
std::string get_user_name();

//返回当前是否为64位系统
bool is_64bit_system();

/**
  *@fun shell_execute 已path为当前目录 执行 path 下 filename
  *@prarm path 作为文件目录与当前目录使用 可以为空
  *       filename 文件名
  */
void shell_execute(const char *path, const char *filename, const char *cmdLine, int showCmd);


/******* 注册表 ********/
/**
  *reg_get_value_str 设置hKey下子项 值
  */
std::string reg_get_value_str(HKEY hKey, const char *subKey, const char *valueName, int valueMaxLen, int samDesired=KEY_QUERY_VALUE);
bool reg_get_value_str(std::string &res/*返回结果*/, HKEY hKey, const char *subKey, const char *valueName, int valueMaxLen, int samDesired=KEY_QUERY_VALUE);

void reg_set_value_str(HKEY hKey, const char *subKey, const char *valueName, const std::string &value, int samDesired=KEY_SET_VALUE);

/**
  *@reg_create_node 创建 subKey下面的keyName子节点
  *@brief        keyName 支持 a\b\c 一次性创建
  */
void reg_create_node(HKEY hKey, const char *subKey, const char *keyName, int samDesired=KEY_WRITE);

bool reg_node_is_exist(HKEY hKey, const char *subKey);									//节点是否存在
void reg_node_delete(HKEY hKey, const char *subKey);									//删除节点

bool reg_value_is_exist(HKEY hKey, const char *subKey, const char *valueName);			//属性是否存在
void reg_value_delete(HKEY hKey, const char *subKey, const char *valueName);				//删除属性

//is_foreground_fullscreen 该函数有概率误判
bool is_foreground_fullscreen();														//当前是否为全屏


bool is_fullscreen();																	//当前是否为全屏