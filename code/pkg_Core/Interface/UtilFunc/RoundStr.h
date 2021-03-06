//! \file RoundStr.h
//! \brief 定义四舍五入字符串的函数 RoundStr

#ifndef UTILFUNC_ROUNDSTR_H_
#define UTILFUNC_ROUNDSTR_H_

//! 得到四舍五入的字符串（去掉小数点后末尾的'0'）
/*! 
	\ingroup _GROUP_UTILFUNC
	\param value 要转换的浮点数
	\param decimal 保留小数点后第几位数，超出部分四舍五入
	\return 转换后的字符串
*/
inline std::wstring RoundStr(double value, int decimal = 4)
{
    WCHAR buf[65] = { 0 };
    
    WCHAR fmt[] = L"%.2lf";
    if (decimal < 1) decimal = 1;
    if (decimal > 5) decimal = 5;
    fmt[2] = (WCHAR)('0' + decimal);
#if _MSC_VER <= 1200 // VC6
	swprintf(buf, fmt, value);
#else
    swprintf_s(buf, 65, fmt, value);	
#endif
    
    LPWSTR p = wcschr(buf, '.');
    if (p != NULL)
    {
		int i = decimal;
        for (; i > 0 && p[i] == '0'; i--)
            p[i] = 0;
        if (p[i] == '.')
            p[i] = 0;
    }
    
    return buf;
}

#endif // UTILFUNC_ROUNDSTR_H_
