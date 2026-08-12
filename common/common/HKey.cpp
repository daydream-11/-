#include "pch.h"
#include "HKey.h"

AutoHKey::AutoHKey(void)
: _hKey(NULL)
{
}

AutoHKey::~AutoHKey(void)
{
	close();
}

HKEY *AutoHKey::operator &()
{
	return &_hKey;
}

AutoHKey::operator HKEY()
{
	return _hKey;
}

void AutoHKey::close()
{
	if (_hKey)
	{
		RegCloseKey(_hKey);
		_hKey = NULL;
	}
}
