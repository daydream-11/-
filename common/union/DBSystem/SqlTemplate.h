#ifndef __SQL_TEMPLATE_H__
#define __SQL_TEMPLATE_H__

#include "Type.h"
//------------------------------Common---------------------------
// 检查指定表是否存在
extern CHAR *lpszCheckTableIsExistV1;
// 创建索引
extern CHAR *lpszCreateIndexByCodeV1;
// 查询所有表数据
extern CHAR *lpszQueryAllDataByTableNameV1;
// 查询所有表数据
extern CHAR *lpszQueryAllDataByTableNameOfCompV1;
// 查询特定列的数据
extern CHAR *lpszQueryDataByTableNameAndCodeV1;
// 模糊查找数据
extern CHAR *lpszFuzzyQueryDataByTableNameAndCodeV1;
// 查询最大列的数据
extern CHAR* lpszQueryMaxIDByTableNameV1;
// 删除指定表中得全部数据
extern CHAR* lpszDeleteAllDataByTableNameV1;
// 删除指定表中指定ID得数据
extern CHAR* lpszDeleteDataByTableNameAndIDV1;
// 获取指定表中全部ID
extern CHAR* lpszGetAllIDByTableNameV1;
// 设置声母编码索引
extern CHAR *lpszCreateIndexBySMCodeV1;
// 设置H声母编码索引
extern CHAR *lpszCreateIndexByHSMCodeV1;
// 统计多少条数据
extern CHAR *lpszCountNumByTableNumV1;
// 统计多少条数据
extern CHAR *lpszCountNumOfCompByTableNumV1;
// 按页返回数据
extern CHAR *lpszQueryDataByPageV1;
// 按页返回数据ForUrl
extern CHAR *lpszQueryDataByPageForUrlV1;
// 按页返回数据
extern CHAR *lpszQueryDataOfCodeByPageV1;
// 删除指定表
extern CHAR* lpszDropTableByTableNameV1;

/************************************************************************/
/*<-- 拼音自定义短语表相关Sql语句                                       */
/************************************************************************/
// 创建PinYinCustomPhrase表
extern CHAR	*lpszCreatePinYinCustomPhraseTableV1;
// 插入数据
extern CHAR* lpszInsertPinYinCustomPhraseTableV1;
// 更新数据
extern CHAR* lpszUpdatePinYinCustomPhraseTableV1;

/************************************************************************/
/*<-- 五笔自定义短语表相关Sql语句                                                 */
/************************************************************************/
// 创建WuBiCustomPhrase表
extern CHAR	*lpszCreateWuBiCustomPhraseTableV1;
// 插入数据
extern CHAR* lpszInsertWuBiCustomPhraseTableV1;
// 更新数据
extern CHAR* lpszUpdateWuBiCustomPhraseTableV1;
// 查询字条zz
extern CHAR* lpszQueryZZWuBiCustomPhraseTableV1;
// 查询字条
extern CHAR* lpszQueryWuBiCustomPhraseTableV1;
/************************************************************************/
/*<-- 拼音用户短语表相关Sql语句                                                 */
/************************************************************************/
// 创建PinYinUserPhrase表
extern CHAR	*lpszCreatePinYinUserPhraseTableV1;
// 插入数据
extern CHAR* lpszInsertPinYinUserPhraseTableV1;
// 更新数据
extern CHAR* lpszUpdatePinYinUserPhraseTableV1;
// 根据声母和全拼查询
extern CHAR *lpszQueryDataBySMCodeAndCodeV1;
// 根据声母和全拼查询(zh, ch, sh)
extern CHAR *lpszQueryDataByHSMCodeAndCodeV1;
// 查询词条是否存在
extern CHAR *lpszQueryIsExistByPYV1;
/************************************************************************/
/*<-- 五笔用户短语表相关Sql语句                                                 */
/************************************************************************/
// 创建WuBiUserPhrase表
extern CHAR	*lpszCreateWuBiUserPhraseTableV1;
// 插入数据
extern CHAR* lpszInsertWuBiUserPhraseTableV1;
// 更新数据
extern CHAR* lpszUpdateWuBiUserPhraseTableV1;

/************************************************************************/
/*<-- 用户最近输入短语表相关Sql语句                                                 */
/************************************************************************/
// 创建LatelyUserPhrase表
extern CHAR	*lpszCreateLatelyUserPhraseTableV1;
// 插入数据
extern CHAR* lpszInsertLatelyUserPhraseTableV1;
// 更新数据
extern CHAR* lpszUpdateLatelyUserPhraseTableV1;
// 创建唯一索引
extern CHAR* lpszCreateUniqueIndexLatelyUserPhraseTableV1;
// 插入数据输入法
extern CHAR* lpszInsertLatelyUserPhraseTableForImeV1;
// 获取最大位置
extern CHAR* lpszGetMaxPosV1;
// 获取使用频率
extern CHAR* lpszGetFreqV1;

/************************************************************************/
/*<-- 固定位置短语表相关Sql语句                                                 */
/************************************************************************/
// 创建PositionUserPhrase表
extern CHAR	*lpszCreatePositionUserPhraseTableV1;
// 插入数据
extern CHAR* lpszInsertPositionUserPhraseTableV1;
// 更新数据
extern CHAR* lpszUpdatePositionUserPhraseTableV1;
// 插入数据输入法
extern CHAR* lpszInsertPositionUserPhraseTableForImeV1;
// 排序查找
extern CHAR* lpszQueryPositionUserPhraseForAESV1;

/************************************************************************/
/*<--    短语用户短语表相关Sql语句                                              */
/************************************************************************/
// 创建DuanYuUserPhrase表
extern CHAR *lpszCreateDuanYuUserPhraseTableV1 ;
// 插入数据
extern CHAR* lpszInsertDuanYuUserPhraseTableV1 ;
// 更新数据
extern CHAR* lpszUpdateDuanYuUserPhraseTableV1 ;

/************************************************************************/
/*<--    网址用户短语表相关Sql语句                                              */
/************************************************************************/
// 创建UrlUserPhrase表
extern CHAR *lpszCreateUrlUserPhraseTableV1 ;
// 插入数据
extern CHAR* lpszInsertUrlUserPhraseTableV1 ;
// 更新数据
extern CHAR* lpszUpdateUrlUserPhraseTableV1 ;
// 创建索引
extern CHAR* lpszCreateIndexUrlUserPhraseTableV1;
// 查询
extern CHAR* lpszQueryDataByWordForUrlV1;
// 查询
extern CHAR* lpszQueryDataForUrlV1OrderByWord;
// 模糊查询
extern CHAR* lpszFuzzyQueryDataByWordForUrlV1;
// 查询网址数据进行分页查找
extern CHAR *lpszQueryDataForUrlByPageV1;
// 查询网址总数按照编码
extern CHAR *lpszQueryCountForUrlOfCodeV1;
// 查询网址数据按照编码进行分页查找
extern CHAR *lpszQueryDataForUrlOfCodeByPageV1;



/************************************************************************/
/*<--    用户删除短语表相关Sql语句                                              */
/************************************************************************/
// 创建DeleteUserPhrase表
extern CHAR *lpszCreateDeleteUserPhraseTableV1 ;
// 插入数据
extern CHAR* lpszInsertDeleteUserPhraseTableV1 ;
// 根据声母和全拼查询
extern CHAR *lpszQueryDeleteDataBySMCodeAndCodeV1;
// 根据声母和全拼查询(zh, ch, sh)
extern CHAR *lpszQueryDeleteDataByHSMCodeAndCodeV1;
// 查询五笔删除词库
extern CHAR *lpszQueryDeleteDataForWBV1;

/************************************************************************/
/*<--    系统更新拼音表相关Sql语句                                              */
/************************************************************************/
// 创建UpdatePYPhrase表
extern CHAR *lpszCreateUpdatePYPhraseTableV2 ;
// 插入数据
extern CHAR* lpszInsertUpdatePYPhraseTableV2;
// 更新数据
extern CHAR* lpszUpdateUpdatePYPhraseTableV2;
// 根据声母和全拼查询
extern CHAR *lpszQueryUpdateDataBySMCodeAndCodeV2;
// 根据声母和全拼查询(zh, ch, sh)
extern CHAR *lpszQueryUpdateDataByHSMCodeAndCodeV2;
// 完整查询
extern CHAR *lpszNormalQueryUpdateDataV2;

/************************************************************************/
/*<-- 更新五笔表相关Sql语句                                                 */
/************************************************************************/
// 创建LatelyUpdateWBPhrase表
extern CHAR	*lpszCreateLatelyUpdateWBPhraseTableV2;
// 插入数据
extern CHAR* lpszInsertLatelyUpdateWBPhraseTableV2;
// 更新数据
extern CHAR* lpszUpdateLatelyUpdateWBPhraseTableV2;

/************************************************************************/
/*<--    网址系统表相关Sql语句                                              */
/************************************************************************/
// 创建UrlSystemPhrase表
extern CHAR *lpszCreateUrlSystemPhraseTableV1 ;
// 插入数据
extern CHAR* lpszInsertUrlSystemPhraseTableV1 ;
// 更新数据
extern CHAR* lpszUpdateUrlSystemPhraseTableV1 ;
// 创建索引
extern CHAR* lpszCreateIndexUrlSystemPhraseTableV1;
// 查询
extern CHAR* lpszQueryDataByPageForUrlSysV1;
// 查询
extern CHAR* lpszQueryDataByWordForUrlSysV1;
// 模糊查询
extern CHAR* lpszFuzzyQueryDataByWordForUrlSysV1;

/************************************************************************/
/*<--    叠字表相关Sql语句                                              */
/************************************************************************/
// 创建叠字表
extern CHAR *lpszCreateDieZiPhraseTableV1;
// 创建唯一索引
extern CHAR* lpszCreateUniqueIndexDieZiPhraseTableV1;
// 查询五笔删除词库
extern CHAR *lpszQueryDieZiDataV1;
// 插入数据
extern CHAR* lpszInsertDieZiPhraseTableV1;
// ----------------网址直达表相关Sql语句---
// 创建网址直达表
extern CHAR* lpszCreateUrlDirectAccessTableV1;
// 根据声母和全拼查询
extern CHAR *lpszQueryUrlDirectAccessBySMCodeAndCodeV1;
// 根据声母和全拼查询(zh, ch, sh)
extern CHAR *lpszQueryUrlDirectAccessByHSMCodeAndCodeV1;
// 插入数据库
extern CHAR *lpszInsertUrlDirectAccessTableV1;

#endif	// __SQL_TEMPLATE_H__