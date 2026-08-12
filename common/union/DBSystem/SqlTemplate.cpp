#include "stdafx.h"
#include "SqlTemplate.h"

// 检查指定表是否存在
CHAR *lpszCheckTableIsExistV1 = 
"SELECT count(*) FROM sqlite_master WHERE type='table' AND name='%s';";

// 根据编码创建索引
CHAR *lpszCreateIndexByCodeV1 = 
"create index %s_Index_Code on %s(Code)";

// 查询所有表数据
CHAR *lpszQueryAllDataByTableNameV1 = 
"select * from %s order by Code";

// 查询所有表数据
CHAR *lpszQueryAllDataByTableNameOfCompV1 = 
"select * from %s where Code like '%%%s%%'";

// 查询特定列的数据
CHAR *lpszQueryDataByTableNameAndCodeV1 = 
"select * from %s where Code='%s';";

// 模糊查找数据
CHAR *lpszFuzzyQueryDataByTableNameAndCodeV1 = 
"select * from %s where Code like '%s';";

// 查询最大列的数据
CHAR* lpszQueryMaxIDByTableNameV1 =
"select max(id) from %s;";

// 删除指定表中得全部数据
CHAR* lpszDeleteAllDataByTableNameV1 =
"delete from %s;";

// 删除指定表中指定ID得数据
CHAR* lpszDeleteDataByTableNameAndIDV1 =
"delete from %s where ID=%d;";

// 获取指定表中全部ID
CHAR* lpszGetAllIDByTableNameV1 = 
"select ID from %s";

// 设置声母编码索引
CHAR *lpszCreateIndexBySMCodeV1 = 
"create index %s_Index_SMCode on %s(SMCode)";

// 设置H声母编码索引
CHAR *lpszCreateIndexByHSMCodeV1 = 
"create index %s_Index_HSMCode on %s(HSMCode)";

// 统计多少条数据
CHAR *lpszCountNumByTableNumV1 = 
"select count(1) from %s";

// 统计多少条数据
CHAR *lpszCountNumOfCompByTableNumV1 = 
"Select count(1) From %s Where Code like '%%%s%%'";

// 按页返回数据
CHAR *lpszQueryDataByPageV1 =
"select * from %s order by Code limit %d OFFSET %d";
// 按页返回数据
CHAR *lpszQueryDataByPageForUrlV1 =
"select * from %s order by Word limit %d OFFSET %d";
// 按页返回数据
CHAR *lpszQueryDataOfCodeByPageV1 =
"Select * From %s Where Code like '%%%s%%' limit %d Offset %d";
// 删除指定表
CHAR* lpszDropTableByTableNameV1 = 
"drop table '%s';";

/************************************************************************/
/*<--    拼音自定义短语表相关Sql语句                                              */
/************************************************************************/

// 创建PinYinCustomPhrase表
CHAR *lpszCreatePinYinCustomPhraseTableV1 =
"create table PinYinCustomPhraseV1( ID Integer PRIMARY KEY,Code TEXT,Word TEXT,Pos Integer);";

// 插入数据
CHAR* lpszInsertPinYinCustomPhraseTableV1 = 
"insert into PinYinCustomPhraseV1 values(NULL, '%s', '%s', %d);";

// 更新数据
CHAR* lpszUpdatePinYinCustomPhraseTableV1 = 
"update PinYinCustomPhraseV1 set Code='%s', Word='%s', Pos=%d where ID=%d";

/************************************************************************/
/*<-- 五笔自定义短语表先关Sql语句                                                 */
/************************************************************************/

// 创建WuBiCustomPhrase表
CHAR *lpszCreateWuBiCustomPhraseTableV1 =
"create table WuBiCustomPhraseV1( ID Integer PRIMARY KEY,Code TEXT,Word TEXT,Pos Integer);";

// 插入数据
CHAR* lpszInsertWuBiCustomPhraseTableV1 = 
"insert into WuBiCustomPhraseV1 values(NULL, '%s', '%s', %d);";

// 更新数据
CHAR* lpszUpdateWuBiCustomPhraseTableV1 = 
"update WuBiCustomPhraseV1 set Code='%s', Word='%s', Pos=%d where ID=%d";

// 查询字条zz
CHAR* lpszQueryZZWuBiCustomPhraseTableV1 = 
"select Code from WuBiCustomPhraseV1 where Code like 'zz%';";
// 查询字条
CHAR* lpszQueryWuBiCustomPhraseTableV1 = 
"select Word from WuBiCustomPhraseV1 where Code='%s';";

/************************************************************************/
/*<-- 拼音用户短语表相关Sql语句                                                 */
/************************************************************************/

// 创建PinYinUserPhrase表
CHAR *lpszCreatePinYinUserPhraseTableV1 =
"create table PinYinUserPhraseV1( ID Integer PRIMARY KEY, Code TEXT,Word TEXT,Freq Integer, SMCode TEXT, HSMCode TEXT);";

// 插入数据
CHAR* lpszInsertPinYinUserPhraseTableV1 = 
"insert into PinYinUserPhraseV1 values(NULL, '%s', '%s', %d, '%s', '%s');";

// 更新数据
CHAR* lpszUpdatePinYinUserPhraseTableV1 = 
"update PinYinUserPhraseV1 set Code='%s', Word='%s', Freq=%d , SMCode = '%s', HSMCode = '%s' where ID=%d";

// 根据声母和全拼查询
CHAR *lpszQueryDataBySMCodeAndCodeV1 = 
"select * from PinYinUserPhraseV1 where ID in (select ID from PinYinUserPhraseV1 where SMCode = '%s'  ORDER  by Freq desc) and Code like '%s' ORDER  by Freq desc limit 10";

// 根据声母和全拼查询(zh, ch, sh)
CHAR *lpszQueryDataByHSMCodeAndCodeV1 =
"select * from PinYinUserPhraseV1 where ID in (select ID from PinYinUserPhraseV1 where SMCode = '%s' or HSMCode = '%s' ORDER  by Freq desc ) and Code like '%s' ORDER  by Freq desc limit 10";

// 查询词条是否存在
CHAR *lpszQueryIsExistByPYV1 =
"select count(ID) from PinYinUserPhraseV1 where Code='%s' and Word='%s';";

/************************************************************************/
/*<-- 五笔用户短语表相关Sql语句                                                 */
/************************************************************************/

// 创建WuBiUserPhrase表
CHAR *lpszCreateWuBiUserPhraseTableV1 =
"create table WuBiUserPhraseV1( ID Integer PRIMARY KEY,Code TEXT,Word TEXT,Freq Integer);";

// 插入数据
CHAR* lpszInsertWuBiUserPhraseTableV1 = 
"insert into WuBiUserPhraseV1 values(NULL, '%s', '%s', %d);";

// 更新数据
CHAR* lpszUpdateWuBiUserPhraseTableV1 = 
"update WuBiUserPhraseV1 set Code='%s', Word='%s', Freq=%d where ID=%d";

/************************************************************************/
/*<-- 用户最近输入短语表相关Sql语句                                                 */
/************************************************************************/

// 创建WuBiUserPhrase表
CHAR *lpszCreateLatelyUserPhraseTableV1 =
"create table LatelyUserPhraseV1( ID Integer PRIMARY KEY,Code TEXT,Word TEXT,Pos Integer, Freq Integer, ChildType Integer);";

// 插入数据
CHAR* lpszInsertLatelyUserPhraseTableForImeV1 = 
"replace into LatelyUserPhraseV1 (Code, Word, Pos, Freq, ChildType) values ('%s', '%s', %d, %d, %d);";
//"replace into LatelyUserPhraseV1 (Code, Word, Pos, Freq, ChildType) values ('%s', '%s', ( ifnull((select max(Pos) from LatelyUserPhraseV1 where Code = '%s'), 0)) + 1, ( ifnull( (select Freq from LatelyUserPhraseV1 where Code = '%s' and Word = '%s'), 0) + 1), %d);";

// 获取最大位置
CHAR* lpszGetMaxPosV1 = "select max(Pos) from LatelyUserPhraseV1 where Code = '%s'";
// 获取使用频率
CHAR* lpszGetFreqV1 = "select Freq, Pos from LatelyUserPhraseV1 where Code = '%s' and Word = '%s'";

// 更新数据
CHAR* lpszUpdateLatelyUserPhraseTableV1 = 
"update LatelyUserPhraseV1 set Freq=%d where ID=%d";

// 创建唯一索引
CHAR* lpszCreateUniqueIndexLatelyUserPhraseTableV1 = 
"create unique index LatelyUserPhraseV1_Index_Code on LatelyUserPhraseV1(Code desc, Word);";

// 插入数据
CHAR* lpszInsertLatelyUserPhraseTableV1 = 
"insert into LatelyUserPhraseV1 values(NULL, '%s', '%s', %d, %d, %d)";

/************************************************************************/
/*<-- 固定位置短语表相关Sql语句                                                 */
/************************************************************************/
// 创建PositionUserPhrase表
CHAR	*lpszCreatePositionUserPhraseTableV1 = 
"create table PositionUserPhraseV1( ID Integer PRIMARY KEY,Code TEXT,Word TEXT,Pos Integer, Freq Integer, ChildType Integer);";
// 插入数据
CHAR* lpszInsertPositionUserPhraseTableV1 = 
"replace into PositionUserPhraseV1(Code,Word,Pos,Freq,ChildType) values('%s', '%s', %d, %d, %d)";
// 更新数据
CHAR* lpszUpdatePositionUserPhraseTableV1 = 
"update PositionUserPhraseV1 set Code='%s', Word='%s', Pos = %d, Freq=%d where ID=%d;";

// 插入数据输入法
CHAR* lpszInsertPositionUserPhraseTableForImeV1 = 
"delete from PositionUserPhraseV1 where Code='%s' and Pos =%d; \
 delete from PositionUserPhraseV1 where Word='%s';	\
replace into PositionUserPhraseV1(Code, Word, Pos, Freq, ChildType) values ('%s', '%s', %d, %d, %d);";

// 排序查找
CHAR* lpszQueryPositionUserPhraseForAESV1 =
"select * from PositionUserPhraseV1 where Code='%s' ORDER BY Pos ASC;";

/************************************************************************/
/*<--    短语用户短语表相关Sql语句                                              */
/************************************************************************/

// 创建DuanYuUserPhrase表
CHAR *lpszCreateDuanYuUserPhraseTableV1 =
"create table DuanYuUserPhraseV1( ID Integer PRIMARY KEY,Code TEXT,Word TEXT,Freq Integer);";

// 插入数据
CHAR* lpszInsertDuanYuUserPhraseTableV1 = 
"insert into DuanYuUserPhraseV1 values(NULL, '%s', '%s', %d);";

// 更新数据
CHAR* lpszUpdateDuanYuUserPhraseTableV1 = 
"update DuanYuUserPhraseV1 set Code='%s', Word='%s', Freq=%d where ID=%d";

/************************************************************************/
/*<--    网址用户短语表相关Sql语句                                              */
/************************************************************************/
// 创建DuanYuUserPhrase表
CHAR *lpszCreateUrlUserPhraseTableV1  = 
"create table UrlUserPhraseV1( ID Integer PRIMARY KEY, Word TEXT,Freq Integer);";

// 插入数据
CHAR* lpszInsertUrlUserPhraseTableV1  =
"insert into UrlUserPhraseV1 values(NULL,  '%s', %d);";

// 更新数据
CHAR* lpszUpdateUrlUserPhraseTableV1 =
"update UrlUserPhraseV1 set Word='%s', Freq=%d where ID=%d";

// 创建自己的索引
CHAR* lpszCreateIndexUrlUserPhraseTableV1 = 
"create index UrlUserPhraseV1_Index_Word on UrlUserPhraseV1(Word)";

// 查询
CHAR* lpszQueryDataByWordForUrlV1 = 
"select * from UrlUserPhraseV1 where Word='%s' ORDER BY Freq DESC;";
// 查询
CHAR* lpszQueryDataForUrlV1OrderByWord= 
"select * from UrlUserPhraseV1 order by Word";
// 模糊查询
CHAR* lpszFuzzyQueryDataByWordForUrlV1 = 
"select * from UrlUserPhraseV1 where Word like '%s' ORDER BY Freq DESC;";
// 查询网址总数按照编码
CHAR *lpszQueryCountForUrlOfCodeV1 = 
"Select count(1) From UrlUserPhraseV1 Where Word like '%s'";
// 查询网址数据进行分页查找
CHAR *lpszQueryDataForUrlByPageV1 =
"Select * From UrlUserPhraseV1 limit %d Offset %d";
// 查询网址数据按照编码进行分页查找
CHAR *lpszQueryDataForUrlOfCodeByPageV1 =
"Select * From UrlUserPhraseV1 Where Word like '%%%s%%' limit %d Offset %d";


/************************************************************************/
/*<--    用户删除短语表相关Sql语句                                              */
/************************************************************************/

// 创建DeleteUserPhrase表
CHAR *lpszCreateDeleteUserPhraseTableV1  = 
"create table DeleteUserPhraseV1(ID integer PRIMARY KEY, Code Text, Word Text, Type integer, SMCode Text, HSMCode Text)";

// 插入数据
CHAR* lpszInsertDeleteUserPhraseTableV1  = 
"insert into DeleteUserPhraseV1 values (NULL, '%s', '%s', %d, '%s', '%s')";

// 根据声母和全拼查询
CHAR *lpszQueryDeleteDataBySMCodeAndCodeV1 = 
"select * from DeleteUserPhraseV1 where ID in (select ID from DeleteUserPhraseV1 where SMCode = '%s') ;";

// 根据声母和全拼查询(zh, ch, sh)
CHAR *lpszQueryDeleteDataByHSMCodeAndCodeV1 =
"select * from DeleteUserPhraseV1 where ID in (select ID from DeleteUserPhraseV1 where SMCode = '%s' or HSMCode = '%s' ) and Code like '%s' ;";
// 查询五笔删除词库
CHAR *lpszQueryDeleteDataForWBV1 = 
"select Code,Word from DeleteUserPhraseV1 where Code like '%s' and Type = 6;";

/************************************************************************/
/*<--    系统更新拼音表相关Sql语句                                              */
/************************************************************************/
// 创建UpdatePYPhrase表
CHAR *lpszCreateUpdatePYPhraseTableV2  = 
"create table LatelyUpdatePYPhraseV2 (ID integer PRIMARY KEY, Code Text, Word Text, Freq integer, SMCode Text, HSMCode Text, APos integer, SPos integer)";
// 插入数据
CHAR* lpszInsertUpdatePYPhraseTableV2  =
"insert into LatelyUpdatePYPhraseV2 values (NULL, '%s', '%s', %d, '%s', '%s', %d, %d)";
// 更新数据
CHAR* lpszUpdateUpdatePYPhraseTableV2  = 
"update LatelyUpdatePYPhraseV2 set Freq=%d where ID=%d";
// 根据声母和全拼查询
CHAR *lpszQueryUpdateDataBySMCodeAndCodeV2 =
"select * from LatelyUpdatePYPhraseV2 where ID in (select ID from LatelyUpdatePYPhraseV2 where SMCode = '%s') and Code like '%s' ;";
// 根据声母和全拼查询(zh, ch, sh)
CHAR *lpszQueryUpdateDataByHSMCodeAndCodeV2 =
"select * from LatelyUpdatePYPhraseV2 where ID in (select ID from LatelyUpdatePYPhraseV2 where SMCode = '%s' or HSMCode = '%s' ) and Code like '%s' ;";
// 完整查询
CHAR *lpszNormalQueryUpdateDataV2 = 
"select * from LatelyUpdatePYPhraseV2 where Code = '%s';";
/************************************************************************/
/*<-- 更新五笔表相关Sql语句                                                 */
/************************************************************************/
// 创建LatelyUpdateWBPhrase表
CHAR	*lpszCreateLatelyUpdateWBPhraseTableV2 =
"create table LatelyUpdateWBPhraseV2(ID integer PRIMARY KEY, Code Text, Word Text, Freq integer, APos integer, SPos integer)";
// 插入数据
CHAR* lpszInsertLatelyUpdateWBPhraseTableV2 =
"insert into LatelyUpdateWBPhraseV2 values (NULL, '%s', '%s', %d, %d, %d)";
// 更新数据
CHAR* lpszUpdateLatelyUpdateWBPhraseTableV2 =
"update LatelyUpdateWBPhraseV2 set Freq=%d where ID=%d";

/************************************************************************/
/*<--    网址用户短语表相关Sql语句                                              */
/************************************************************************/
// 创建UrlSystemPhrase表
CHAR *lpszCreateUrlSystemPhraseTableV1  = 
"create table UrlSystemPhraseV1( ID Integer PRIMARY KEY, Word TEXT,Freq Integer);";

// 插入数据
CHAR* lpszInsertUrlSystemPhraseTableV1  =
"insert into UrlSystemPhraseV1 values(NULL,  '%s', %d);";

// 更新数据
CHAR* lpszUpdateUrlSystemPhraseTableV1 =
"update UrlSystemPhraseV1 set Word='%s', Freq=%d where ID=%d";

// 创建自己的索引
CHAR* lpszCreateIndexUrlSystemPhraseTableV1 = 
"create index UrlSystemPhraseV1_Index_Word on UrlSystemPhraseV1(Word)";

// 查询
CHAR* lpszQueryDataByPageForUrlSysV1 =
"select * from UrlSystemPhraseV1 limit %d OFFSET %d";

// 查询
CHAR* lpszQueryDataByWordForUrlSysV1 = 
"select * from UrlSystemPhraseV1 where Word='%s' ORDER BY Freq DESC;";
// 模糊查询
CHAR* lpszFuzzyQueryDataByWordForUrlSysV1 = 
"select * from UrlSystemPhraseV1 where Word like '%s' ORDER BY Freq DESC;";

/************************************************************************/
/*<--    叠字表相关Sql语句                                              */
/************************************************************************/
// 创建叠字表
CHAR *lpszCreateDieZiPhraseTableV1 = 
"create table DieZiPhraseV1( ID Integer PRIMARY KEY, Word TEXT,Code TEXT,SplitCode TEXT,IsNormal Integer);";

// 创建唯一索引
CHAR* lpszCreateUniqueIndexDieZiPhraseTableV1 = 
"create index DieZiPhraseV1_Index_SplitCode on DieZiPhraseV1(SplitCode);";
// 查询五笔删除词库
CHAR *lpszQueryDieZiDataV1 = 
"select Code,Word from DieZiPhraseV1 where SplitCode = '%s' and IsNormal = 1;";
// 插入数据
CHAR* lpszInsertDieZiPhraseTableV1  =
"insert into DieZiPhraseV1 values(NULL,  '%s', '%s', '%s', 1);";
// ----------------网址直达表相关Sql语句---
// 创建网址直达表
CHAR* lpszCreateUrlDirectAccessTableV1 = 
"create table UrlDirectAccessV1(ID integer PRIMARY KEY, Code TEXT, Word TEXT,UrlAddess TEXT, SMCode Text, HSMCode Text)";
// 根据声母和全拼查询
CHAR *lpszQueryUrlDirectAccessBySMCodeAndCodeV1 =
"select * from UrlDirectAccessV1 where ID in (select ID from UrlDirectAccessV1 where SMCode = '%s') and Code like '%s' ;";
// 根据声母和全拼查询(zh, ch, sh)
CHAR *lpszQueryUrlDirectAccessByHSMCodeAndCodeV1 =
"select * from UrlDirectAccessV1 where ID in (select ID from UrlDirectAccessV1 where SMCode = '%s' or HSMCode = '%s' ) and Code like '%s' ;";
// 插入数据库
CHAR *lpszInsertUrlDirectAccessTableV1 = 
"insert into UrlDirectAccessV1 values (NULL, '%s', '%s','%s', '%s', '%s')";