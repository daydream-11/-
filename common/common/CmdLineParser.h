#pragma once

#include <string>
#include <vector>

/**
  *@class CmdLineParser
  *@brief 命令行
  *       /name value
  */
class CmdLineParser
{
public:
	CmdLineParser();

	~CmdLineParser();

public:
	//分析命令行 s:/name value /name2=value -name3
	void parser(const char *s);

	std::string getString() const;	//返回 parser 分析的 s 字符串

	bool exist(const char *name);

	std::string getValue(const char *name);

	const std::vector<std::string> *names();

	const std::vector<std::string> *values();

private:
	void parser(const char *b, const char *e);

private:
	std::string				m_string;
	std::vector<std::string> m_names;
	std::vector<std::string> m_values;
};