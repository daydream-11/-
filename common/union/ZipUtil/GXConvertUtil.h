
#ifndef __GX_CONVERT_UTIL_H
#define __GX_CONVERT_UTIL_H

#include <stddef.h>
#include <string>

typedef std::wstring UString;
typedef std::string  AString ;

typedef __int64 Int64;
typedef unsigned __int64 UInt64;

typedef int Int32;
typedef unsigned int UInt32;

class GXConvertUtil
{
public:
    static void ConvertUInt64ToString(UInt64 value, char *s, UInt32 base = 10);

    static void ConvertUInt64ToString(UInt64 value, wchar_t *s);

    static void ConvertInt64ToString(Int64 value, char *s);

    static void ConvertInt64ToString(Int64 value, wchar_t *s);

    static void ConvertUInt32ToString(UInt32 value, char *s);

    static void ConvertUInt32ToString(UInt32 value, wchar_t *s);

    static UInt64 ConvertStringToUInt64(const wchar_t *s, const wchar_t **end);

    static UInt32 ConvertStringToUInt32(const wchar_t* s, const wchar_t** end);

    static UInt32 ConvertStringAToUInt32(const char* s, const char** end);

    static UInt64 ConvertStringAToUInt64(const char *s, const char **end);

    static void ConvertUInt32ToHexWithZeros(UInt32 value, char *s);

    static bool IsEqualNoCase(const UString& lhs, const UString& rhs);

    static Int32 Compare(const UString& lhs, const UString& rhs);

    static UString MultiByteToUnicodeString(const AString& src, int codePage = CP_ACP);

    static UString MultiByteToUnicodeString(const char* src, Int32 len, int codePage = CP_ACP);

    static AString UnicodeStringToMultiByte(const UString& src, UInt32 codePage = CP_ACP);

    static AString UnicodeStringToMultiByte(const UString& src, char defaultChar, UInt32 codePage = CP_ACP);

    static void Format(UString& str, const UString::value_type* fmt , ...);

private:

    static UString DoMultiByteToUnicodeString(const char* src, Int32 len,UInt32 codePage, bool& result);

    static AString DoUnicodeStringToMultiByte(const UString& src,UInt32 codePage, char defaultChar, bool& result);

    static bool IsEqualNoCasePrivate(const wchar_t* lhs, const wchar_t* rhs);

    static Int32 FormatToBuffer(UString::value_type* buf, Int32 size ,const UString::value_type* format, va_list args);
};

#endif
