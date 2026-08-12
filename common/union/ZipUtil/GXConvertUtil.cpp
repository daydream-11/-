#include "StdAfx.h"
#include "GXConvertUtil.h"

void GXConvertUtil::ConvertUInt64ToString(UInt64 value, char *s, UInt32 base)
{
    if (base < 2 || base > 36)
    {
        *s = '\0';
        return;
    }
    char temp[72];
    int pos = 0;
    do 
    {
        int delta = (int)(value % base);
        temp[pos++] = (char)(delta < 10) ? ('0' + delta) : ('a' + (delta - 10));
        value /= base;
    } 
    while (value != 0);
    do
    {
        *s++ = temp[--pos];
    }
    while (pos > 0);
    *s = '\0';
}

void GXConvertUtil::ConvertUInt64ToString(UInt64 value, wchar_t *s)
{
    wchar_t temp[32];
    int pos = 0;
    do 
    {
        temp[pos++] = (wchar_t)(L'0' + (int)(value % 10));
        value /= 10;
    }
    while (value != 0);
    do 
    {
        *s++ = temp[--pos];
    } 
    while (pos > 0);
    *s = '\0';
}

void GXConvertUtil::ConvertUInt32ToString(UInt32 value, char *s) 
{
    ConvertUInt64ToString(value, s);
}

void GXConvertUtil::ConvertUInt32ToString(UInt32 value, wchar_t *s)
{ 
    ConvertUInt64ToString(value, s);
}

void GXConvertUtil::ConvertInt64ToString(Int64 value, char *s)
{
    if (value < 0)
    {
        *s++ = '-';
        value = -value;
    }
    ConvertUInt64ToString(value, s);
}

void GXConvertUtil::ConvertInt64ToString(Int64 value, wchar_t *s)
{
    if (value < 0)
    {
        *s++ = L'-';
        value = -value;
    }
    ConvertUInt64ToString(value, s);
}
void GXConvertUtil::ConvertUInt32ToHexWithZeros(UInt32 value, char *s)
{
    for (int i = 0; i < 8; i++)
    {
        int t = value & 0xF;
        value >>= 4;
        s[7-i] = (char)((t < 10) ? ('0' + t) : ('A' + (t - 10)));
    }
    s[8] = '\0';
}

UInt64 GXConvertUtil::ConvertStringToUInt64(const wchar_t *s, const wchar_t **end)
{
    UInt64 result = 0;
    for(;;)
    {
        wchar_t c = *s;
        if (c < '0' || c > '9')
        {
            if (end != NULL)
            {
                *end = s;
            }
            return result;
        }
        result *= 10;
        result += (c - '0');
        s++;
    }
}

UInt64 GXConvertUtil::ConvertStringAToUInt64(const char *s, const char **end)
{
    UInt64 result = 0;
    for(;;)
    {
        char c = *s;
        if (c < '0' || c > '9')
        {
            if (end != NULL)
            {
                *end = s;
            }
            return result;
        }
        result *= 10;
        result += (c - '0');
        s++;
    }
}

UInt32 GXConvertUtil::ConvertStringAToUInt32(const char* s, const char** end)
{
    return (UInt32)ConvertStringAToUInt64(s, end) ;
}

UInt32 GXConvertUtil::ConvertStringToUInt32(const wchar_t* s, const wchar_t** end)
{
    return (UInt32)ConvertStringToUInt64(s, end) ;
}

bool GXConvertUtil::IsEqualNoCase(const UString& lhs, const UString& rhs)
{
    if (lhs.size() != rhs.size())
    {
        return false ;
    }
    return IsEqualNoCasePrivate(lhs.c_str(), rhs.c_str()) ;
}

bool GXConvertUtil::IsEqualNoCasePrivate(const wchar_t* lhs, const wchar_t* rhs)
{
    for(;;)
    {
        if (*lhs == *rhs)
        {
            if (*lhs++ == 0)
            {
                return true;
            }
            rhs++;
            continue;
        }
        if (::towupper(*lhs++) == towupper(*rhs++))
        {
            continue;
        }
        return false;
    }
}

Int32 GXConvertUtil::Compare(const UString& lhs, const UString& rhs)
{
    return lhs.compare(rhs) ;
}


UString GXConvertUtil::MultiByteToUnicodeString(const AString& src, int codePage) 
{
    return MultiByteToUnicodeString(src.c_str(),(Int32)src.size(),codePage) ;
}

UString GXConvertUtil::MultiByteToUnicodeString(const char* src, Int32 len,int codePage)
{
    bool result = true;
    UString str = DoMultiByteToUnicodeString(src, len, codePage, result);
    if (result)
    {
        return str;
    }
    return UString();
}

UString GXConvertUtil::DoMultiByteToUnicodeString(const char* src, Int32 len,UInt32 codePage, bool& result)
{
    result = true;
    if (src == NULL)
    {
        return UString();
    }
    if (len < 0)
    {
        len = static_cast<Int32>(strlen((src)));
    }
    int minSize = ::MultiByteToWideChar(codePage, 0, src, len, NULL, 0);
    if (minSize > 0)
    {
        minSize += 1;
        wchar_t* buf = new wchar_t[minSize];
        if (!buf)
        {
            result = false ;
            return UString() ;
        }
        int ret = ::MultiByteToWideChar(codePage, 0, src, len, buf, minSize);
        if (ret > 0 && ret < minSize)
        {
            buf[ret] = 0;
        }
        else
        {
            result = false;
            buf[0] = 0;
        }
        UString resutStr(buf);
        delete [] buf;
        return resutStr;
    }
    else
    {
        result = false ;
        return UString() ;
    }
}

AString GXConvertUtil::UnicodeStringToMultiByte(const UString& src, UInt32 codePage)
{
    //CP_UTF8  = 65001
    if(codePage == 65001)
    {
        return GXConvertUtil::UnicodeStringToMultiByte(src, codePage, 0);
    }
    else
    {
        return GXConvertUtil::UnicodeStringToMultiByte(src, codePage, '_');
    }
}

AString GXConvertUtil::UnicodeStringToMultiByte(const UString& src,char defaultChar, UInt32 codePage)
{
    bool result = true ;
    AString str = DoUnicodeStringToMultiByte(src, codePage, defaultChar, result) ;
    if(result)
    {
        return str ;
    }
    return AString();
}

AString GXConvertUtil::DoUnicodeStringToMultiByte(const UString& src,UInt32 codePage, char defaultChar, bool& result)
{
    result = true;
    int minSize = ::WideCharToMultiByte(codePage,0,src.c_str(),(int)src.size(),NULL,0,NULL,NULL);
    if (minSize > 0)
    {
        minSize += 8;
        char* buf = new char[minSize];
        if (!buf)
        {
            result = false ;
            return AString() ;
        }

        int len = 0 ;
        if(defaultChar != 0)
        {
            BOOL defUsed = FALSE ;
            char defaultChars[2] ;
            defaultChars[0] = defaultChar ;
            defaultChars[1] = 0 ;
            len = ::WideCharToMultiByte(codePage,0,src.c_str(), (int)src.size(),buf,minSize,defaultChars, &defUsed);
        }
        else
        {
            len = ::WideCharToMultiByte(codePage, 0, src.c_str(), (int)src.size(), buf, minSize, NULL, NULL);
        }
        
        if (len > 0 && len < minSize)
        {
            buf[len] = 0;
        }
        else
        {
            result = false ;
            buf[0] = 0 ;
        }
        AString resultStr(buf);
        delete [] buf;
        return resultStr ;
    }
    else
    {
        result = false ;
        return AString() ;
    }
}

void GXConvertUtil::Format(UString& str, const UString::value_type* fmt , ...)
{
    UString& result = str;
    Int32 retValue = 0;
    const Int32 BUF_SIZE = 1024;
    UString::value_type buf[BUF_SIZE] ;
    Int32 size = BUF_SIZE ;
    if (fmt != NULL, *fmt != 0)
    {
        va_list args;
        va_start(args, fmt);
        Int32 nRet = FormatToBuffer(buf, size,fmt, args);
        if (nRet == 0)
        {
            result = buf ;
        }
        else if (nRet == -1)
        {
            result = _T("") ;
            retValue = -1 ;
        }
        else if(nRet == 1)
        {
            //retry util the buffer is enough          
            const Int32 MAX_TIME = 1024 ;
            Int32 nTimes = 0 ;
            for(nTimes = 0 ; nTimes < MAX_TIME ; nTimes++)
            {
                size *= 2 ;
                UString::value_type* pNewBuf = new UString::value_type[size] ;
                bool isOK = true ;
                nRet  = FormatToBuffer(pNewBuf,size,fmt,args) ;
                if(0 == nRet)
                {
                    result = pNewBuf ;                    
                }
                else if(-1 == nRet)
                {
                    result = _T("") ;
                    retValue = -1 ;
                }
                else if(1 == nRet)
                {
                    isOK = false ;
                }
                delete [] pNewBuf ;
                pNewBuf = NULL ;
                if(isOK)
                {
                    break ;
                }
            }
            if(nTimes == MAX_TIME)
            {
                retValue = 1 ;
            }
        }
        va_end(args);
    }
    if(retValue != 0)
    {
        result.clear() ;
    }
}

Int32 GXConvertUtil::FormatToBuffer(UString::value_type* buf, Int32 size ,const UString::value_type* format, va_list args)
{
    errno = 0 ;
    Int32 n = _vsnwprintf_s(buf,size, size - 1, format,args);
    if(( n >= 0) && (n < size))
    {
        return 0 ;
    }
    else
    {
        if(n == -1)
        {
            if(errno == EINVAL)
            {
                return -1 ;
            }
        }
        return 1 ;
    }
}