#pragma once

/**
  *@class AutoHKey
  *@author 沈结
  *@data 20150414
  *@brief 自动关闭HKEY对象
  */
class AutoHKey
{
public:
	AutoHKey(void);

	~AutoHKey(void);

public:
	HKEY * operator &();

	operator HKEY();

public:
	void close();

private:
	HKEY _hKey;
};
