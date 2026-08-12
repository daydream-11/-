#include "pch.h"
#include "CmdLineParser.h"
#include <algorithm>

CmdLineParser::CmdLineParser()
{
}

CmdLineParser::~CmdLineParser()
{

}

void CmdLineParser::parser(const char *s)
{
	m_names.clear();
	m_values.clear();
	m_string = s == NULL ? "" : s;

	int len = int(strlen(s));
	const char *b = NULL;

	for (int i=0; i<len; )
	{
		if (s[i] == '/' || s[i] == '-')
		{//找到一个名字
			if (b == NULL)
			{
				b = s+i;
			}
			else 
			{
				parser(b, s+i);
				b = s+i;
			}
		}

		i++;
	}

	if (b)
	{
		parser(b, s+len);
	}
}

std::string	CmdLineParser::getString() const
{
	return m_string;
}

bool CmdLineParser::exist(const char *name)
{
	if (std::find(m_names.begin(), m_names.end(), name) == m_names.end())
	{
		return false;
	}

	return true;
}

std::string CmdLineParser::getValue(const char *name)
{
	std::vector<std::string>::iterator it = std::find(m_names.begin(), m_names.end(), name);

	if (it == m_names.end())
	{
		return "";
	}

	return m_values[it-m_names.begin()];
}

const std::vector<std::string> *CmdLineParser::names()
{
	return &m_names;
}

const std::vector<std::string> *CmdLineParser::values()
{
	return &m_values;
}

void CmdLineParser::parser(const char *b, const char *e)
{
	std::string name;

	while (b < e)
	{
		if (*b==' ' || *b=='\t' || *b=='=')
		{
			break;
		}

		name.push_back(*b++);
	}

	int nameLen = int(name.length());

	if (nameLen != 0)
	{
		m_names.push_back(name);

		std::string value;

		while (++b < e)
		{//提取名字后面的参数 去掉前面的空格
			if (*b == '/')
			{
				break;
			}

			value.push_back(*b);
		}

		value.erase(0, value.find_first_not_of(' '));
		value.erase(value.find_last_not_of(' ')+1);

		m_values.push_back(value);
	}
}