// Copyright 2008-2011 Zhang Yun Gui, rhcad@hotmail.com
// https://sourceforge.net/projects/x3c/
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

//! \file ConvStr.h
//! \brief ����UNICODE����ANSI�����໥ת������

#ifndef UTILFUNC_CONVSTR_H_
#define UTILFUNC_CONVSTR_H_

_STD_BEGIN

//! UNICODE��ת��ΪANSI��, std::w2a
/*!
	\ingroup _GROUP_UTILFUNC
	\param s UNICODE��
	\param codepage Ŀ��ANSI���ı��룬���� CP_UTF8 ��ʾUTF-8��ʽ����
	\return Ŀ��ANSI��
*/
inline std::string w2a(LPCWSTR s, UINT codepage = CP_ACP)
{
	std::string str;
	int wlen = (NULL == s) ? 0 : (int)wcslen(s);

	if (wlen > 0)
	{
		long len = WideCharToMultiByte(codepage, 0, s, wlen, NULL, 0, NULL, NULL);
		str.resize(len);
		WideCharToMultiByte(codepage, 0, s, wlen, 
			const_cast<char*>(str.data()), len, NULL, NULL);
	}

	return str;
}

//! UNICODE��ת��ΪANSI��, std::w2a
/*!
	\ingroup _GROUP_UTILFUNC
	\param s UNICODE��
	\param codepage Ŀ��ANSI���ı��룬���� CP_UTF8 ��ʾUTF-8��ʽ����
	\return Ŀ��ANSI��
*/
inline std::string w2a(const std::wstring& s, UINT codepage = CP_ACP)
{
	return w2a(s.c_str(), codepage);
}

//! ANSI��ת��ΪUNICODE��, std::a2w
/*!
	\ingroup _GROUP_UTILFUNC
	\param s ԴANSI��
	\param codepage ԴANSI���ı��룬���� CP_UTF8 ��ʾUTF-8��ʽ����
	\return UNICODE��
*/
inline std::wstring a2w(LPCSTR s, UINT codepage = CP_ACP)
{
	std::wstring wstr;
	int len = (NULL == s) ? 0 : (int)strlen(s);

	if (len > 0)
	{
		int wlen = MultiByteToWideChar(codepage, 0, s, len, NULL, 0);
		wstr.resize(wlen);
		MultiByteToWideChar(codepage, 0, s, len, 
			const_cast<LPWSTR>(wstr.data()), wlen);
	}

	return wstr;
}

//! ANSI��ת��ΪUNICODE��, std::a2w
/*!
	\ingroup _GROUP_UTILFUNC
	\param s ԴANSI��
	\param codepage ԴANSI���ı��룬���� CP_UTF8 ��ʾUTF-8��ʽ����
	\return UNICODE��
*/
inline std::wstring a2w(const std::string& s, UINT codepage = CP_ACP)
{
	return a2w(s.c_str(), codepage);
}

#ifdef _UNICODE
inline std::wstring w2t(LPCWSTR s) { return s; }
inline std::wstring w2t(const std::wstring& s) { return s; }
inline std::wstring t2w(LPCTSTR s) { return s; }
#else
inline std::string w2t(LPCWSTR s) { return w2a(s); }
inline std::string w2t(const std::wstring& s) { return w2a(s); }
inline std::wstring t2w(LPCTSTR s) { return a2w(s); }
#endif

_STD_END
#endif // UTILFUNC_CONVSTR_H_
