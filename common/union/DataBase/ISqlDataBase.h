#ifndef __I_SQL_DATABASE_H__
#define __I_SQL_DATABASE_H__

class ISqlConnection
{
public:
	// 打开数据库
	virtual BOOL Open(const CHAR *szHost, INT nPort, const CHAR *szUser, const CHAR *szPassword, const CHAR *szDBName) = 0;
	// 关闭数据库
	virtual void Close(void) = 0;
	// 删除本身
	virtual void DeleteThis(void) = 0;
};

// 获取MSSQL连接对象
ISqlConnection* GetStaticMsSqlConnection();
// 实例化MSSQL连接对象
ISqlConnection* GetNewMsSqlConnection();

// 获取MYSQL连接对象
ISqlConnection* GetStaticMySqlConnection();
// 实例化MYSQL连接对象
ISqlConnection* GetNewMySqlConnection();

// 获取Sqlite连接对象
ISqlConnection* GetStaticSQLiteConnection();
// 实例化Sqlite连接对象
ISqlConnection* GetNewSQLiteConnection();

// 获取AccessSQL连接对象
ISqlConnection* GetStaticAccessSQLConnection();
// 实例化AccessSQL连接对象
ISqlConnection* GetNewAccessSQLConnection();

class ISqlDataReader
{
public:
	// 是否已经结束
	virtual BOOL Read() = 0;
	// 移动下一条记录
	virtual BOOL MoveNext() = 0;
	// 获取索引字符串
	virtual const CHAR* GetFieldValue(INT nField) = 0;
	// 获取索引字符串
	virtual const CHAR* GetFieldValue(const CHAR *strFieldName) = 0;
	// 获取索引整数
	virtual INT GetIntField(INT nField, INT nNullValue = 0) = 0;
	// 获取索引整数
	virtual INT GetIntField(const CHAR *strFieldName, INT nNullValue = 0) = 0;
	// 获取索引浮点数
	virtual FLOAT GetFloatField(INT nField, FLOAT fNullValue = 0.0) = 0;
	// 获取索引浮点数
	virtual FLOAT GetFloatField(const CHAR *strFieldName, FLOAT fNullValue = 0.0) = 0;
	// 获取索引浮点数
	virtual DOUBLE GetDoubleField(INT nField, DOUBLE dNullValue = 0.0) = 0;
	// 获取索引浮点数
	virtual DOUBLE GetDoubleField(const CHAR *strFieldName, DOUBLE dNullValue = 0.0) = 0;
	// 获取索引字符串
	virtual string GetStringField(INT nField, const CHAR *strNullValue = "") = 0;
	// 获取索引字符串
	virtual string GetStringField(const CHAR *strFieldName, const CHAR *strNullValue = "") = 0;
	// 获取索引二进制
	virtual INT GetBinaryField(INT nField, CHAR *lpszContent, UINT uMaxLen, INT nNullValue = 0) = 0;
	// 获取索引二进制
	virtual INT GetBinaryField(const CHAR *strFieldName, CHAR *lpszContent, UINT uMaxLen, INT nNullValue = 0) = 0;
	// 判断字段是否为空
	virtual BOOL IsFieldNull(INT nField) = 0;
	// 判断字段是否为空
	virtual BOOL IsFieldNull(const CHAR *strFieldName) = 0;
	// 获取索引字段名称
	virtual const CHAR* GetFieldName(INT nColumn) = 0;
	// 获取索引位置
	virtual INT GetFieldIndex(const CHAR *strFieldName) = 0;
	// 获取字段列总数
	virtual INT GetFieldCount() = 0;
	// 获取记录总数
	virtual INT GetRowCount() = 0;
	// 终结操作
	virtual void Close() = 0;
	// 删除本身
	virtual void DeleteThis(void) = 0;
};

// 获取MSSQL读取对象
ISqlDataReader* GetStaticMsSqlDataReader();
// 实例化MSSQL读取对象
ISqlDataReader* GetNewMsSqlDataReader();

// 获取MYSQL读取对象
ISqlDataReader* GetStaticMySqlDataReader();
// 实例化MYSQL读取对象
ISqlDataReader* GetNewMySqlDataReader();

// 获取Sqlite读取对象
ISqlDataReader* GetStaticSQLiteDataReader();
// 实例化Sqlite读取对象
ISqlDataReader* GetNewSQLiteDataReader();

// 获取AccessSQL读取对象
ISqlDataReader* GetStaticAccessSQLDataReader();
// 实例化AccessSQL读取对象
ISqlDataReader* GetNewAccessSQLDataReader();

class ISqlCommand
{
public:
	
	/** @name 添加输入参数函数 *///////////////////////////////////////////////////
    /// @{
	
	// 添加存储过程参数（整数类型）
	virtual void AddIntInputParameter(const CHAR *lpszName, INT nValue) = 0;
	// 添加存储过程参数（短整数类型）
	virtual void AddShortInputParameter(const CHAR *lpszName, SHORT nValue) = 0;
	// 添加存储过程参数（字节类型）
	virtual void AddByteInputParameter(const CHAR *lpszName, BYTE byValue) = 0;
	// 添加存储过程参数（字符类型）
	virtual void AddStringInputParameter(const CHAR *lpszName, const CHAR *lpszValue) = 0;
	// 添加存储过程参数（二进制类型）
	virtual void AddBinaryInputParameter(const CHAR *lpszName, CHAR *lpszValue, INT nLen) = 0;

	/// @}

public:

	/** @name 添加输出参数函数 *///////////////////////////////////////////////////
    /// @{

	// 添加输出存储过程参数（整数类型）
	virtual void AddIntOutputParameter(const CHAR *lpszName) = 0;

	/// @}

public:

	/** @name 获取返回参数函数 *///////////////////////////////////////////////////
    /// @{

	// 获取存储过程返回的参数（整数类型）
	virtual INT GetIntParameterValue(const CHAR *lpszName) = 0;

	/// @}

public:

	/** @name 清空对象参数函数 *///////////////////////////////////////////////////
    /// @{

	// 清空对象参数
	virtual VOID ClearParameter() = 0;

	/// @}

public:

	/** @name 执行SQL语句函数 *///////////////////////////////////////////////////
    /// @{


	// 执行无返回值
	virtual BOOL ExecuteNonQuery(LPCSTR strSQL, BOOL bUseStoredProc = FALSE) = 0;
	// 执行无返回值
	virtual INT ExecuteQuery(LPCSTR strSQL, BOOL bUseStoredProc = FALSE) = 0;
	// 执行查询结果
	virtual ISqlDataReader* ExecuteReader(LPCSTR strSQL, BOOL bUseStoredProc = FALSE) = 0;
	// 执行查询结果
	virtual BOOL ExecuteReader(ISqlDataReader *pSqlDataReader, LPCSTR strSQL, BOOL bUseStoredProc = FALSE) = 0;
	// 执行查询结果
	virtual INT ExecuteScalar(LPCSTR strSQL, INT nNullValue = 0, BOOL bUseStoredProc = FALSE) = 0;

	/// @}

public:

	/** @name 虚成员函数 *///////////////////////////////////////////////////
    /// @{

	// 设置SqlConnection指针
	virtual void SetSqlConnection(ISqlConnection *pSqlConnection) = 0;
	// 开始执行
	virtual VOID ExecuteBegin(void) = 0;
	// 结束执行
	virtual VOID ExecuteEnd(void) = 0;
	// 删除本身
	virtual void DeleteThis(void) = 0;

	/// @}
};

// 获取MSSQL命令对象
ISqlCommand* GetStaticMsSqlCommand();
// 实例化MSSQL命令对象
ISqlCommand* GetNewMsSqlCommand();

// 获取MYSQL命令对象
ISqlCommand* GetStaticMySqlCommand();
// 实例化MYSQL命令对象
ISqlCommand* GetNewMySqlCommand();

// 获取SQLite命令对象
ISqlCommand* GetStaticSQLiteCommand();
// 实例化SQLite命令对象
ISqlCommand* GetNewSQLiteCommand();

// 获取AccessSQL命令对象
ISqlCommand* GetStaticAccessSQLCommand();
// 实例化AccessSQL命令对象
ISqlCommand* GetNewAccessSQLCommand();

#endif	// __I_SQL_DATABASE_H__