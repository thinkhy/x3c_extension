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

#ifndef _X3_UTILITY_TEXTUTIL_H
#define _X3_UTILITY_TEXTUTIL_H

#include <Ix_StringConvert.h>
#include <Ix_TextFileUtil.h>

class Cx_TextUtil
	: public Ix_StringConvert
	, public Ix_TextFileUtil
{
protected:
	Cx_TextUtil() {}
	virtual ~Cx_TextUtil() {}

private:
	// From Ix_TextFileUtil
	//
	virtual bool ReadTextFile(std::wstring& content, 
		const std::wstring& filename, 
		ULONG limitMB = 16, UINT codepage = CP_ACP);
	virtual bool SaveTextFile(const std::wstring& content, 
		const std::wstring& filename, 
		bool utf16 = true, UINT codepage = CP_ACP);
	virtual bool SaveTextFile(const std::string& content, 
		const std::wstring& filename, 
		bool utf16 = true, UINT codepage = CP_ACP);
	virtual bool IsUTF16File(const std::wstring& filename, bool& utf16);
	virtual bool IsUTF8File(const std::wstring& filename, bool& utf8);
	virtual bool UnicodeToAnsi(const std::wstring& filename, UINT codepage = CP_ACP);
	virtual bool AnsiToUnicode(const std::wstring& filename, UINT codepage = CP_ACP);
	virtual long GetLineCount(const std::wstring& text);
	virtual std::wstring GetLine(const std::wstring& text, 
		long line, LPCWSTR* nextLine = NULL);
	virtual bool IsSpaceLine(const std::wstring& text);

	// From Ix_StringConvert
	//
	virtual bool TrimSpace(std::wstring& text, LPCWSTR targets);
	virtual bool TrimLeft(std::wstring& text, LPCWSTR targets);
	virtual bool TrimRight(std::wstring& text, LPCWSTR targets);
	virtual bool RemoveInvalidChars(std::wstring& text, LPCWSTR targets);
	virtual bool ReplaceAll(std::wstring& text, 
		const std::wstring& match, 
		const std::wstring& newtext);
	virtual bool ReplaceChar(std::wstring& text, 
		const std::wstring& match, 
		const std::wstring& chars);
	virtual bool ToDBC(std::wstring& text, bool punct = false);
	virtual std::string ToAnsi(const std::wstring& text, UINT codepage = CP_ACP);
	virtual std::wstring ToUnicode(const std::string& text, UINT codepage = CP_ACP);

private:
	DWORD GetHeadBytes(const std::wstring& wstrFileName, BYTE buf[5]);
	bool GetFileContent(std::wstring& content, BYTE* buf, long size, UINT codepage);
	bool ReadTextFile(BYTE head[5], std::wstring& content, 
		const std::wstring& wstrFileName, 
		ULONG nLenLimitMB, UINT codepage);
};

#endif // _X3_UTILITY_TEXTUTIL_H
