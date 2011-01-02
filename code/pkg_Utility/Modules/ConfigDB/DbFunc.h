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

#ifndef _X3_CONFIGDB_DBFUNC_H
#define _X3_CONFIGDB_DBFUNC_H

#include <ctrim.h>

//! ���ݿⳣ�ú���
class DbFunc
{
public:
	//! ��ʾCOM������Ϣ
	static void PrintComError(_com_error &e, LPCSTR file, long lLine, LPCWSTR pszSQL = NULL);

	//! ��ʾ������Ϣ
	static void PrintError(CException* e, LPCSTR file, long lLine);

	//! ��ʾ��Ϣ����
	static void PrintInfo(LPCWSTR pszMsg, LPCSTR file, long lLine, bool bError = false);

	//! ����б�ŷָ��ĵ�һ�����Ӵ�
	static std::wstring GetLevel1Name(LPCWSTR name);

	static bool IsDBName(LPCWSTR name);

	static bool IsSelectSQL(LPCWSTR name);

	//! BOOLֵת��Ϊ�ַ�'y'��'n'
	static CHAR BoolToChar(BOOL bValue);

	//! ������ת��ΪCString����ȥ�������ݿ�����Ķ���ո�
	static CString GetBSTR(const _variant_t &v, LPCTSTR pszDefault = NULL);

	//! ������ת��Ϊ����
	static bool GetDate(COleDateTime& dt, const _variant_t &v);

	//! ������ת��Ϊ����ʱ��
	static bool GetDateTime(COleDateTime& dt, const _variant_t &v);

	//! ת���ɺ�ʱ�����ʱ��
	static COleDateTime GetTimeNew(const _variant_t &v);

	//! ������ת��Ϊ����
	static long GetLong(const _variant_t &v, long lDefault = 0);

	//! ������ת��Ϊ����
	static short GetShort(const _variant_t &v, short nDefault = 0);

	//! ������ת��Ϊ������
	static double GetDouble(const _variant_t &v, double dDefault = 0.0);

	//! ���ַ�������ת��Ϊ����ֵ���ַ���Ϊ'y'��'n'
	static BOOL GetBool(const _variant_t &v, BOOL bDefault = FALSE);
};

//! ���ַ�������ת��Ϊ�ַ�ֵ
inline CHAR GetChar(const _variant_t &v, CHAR cDefault)
{
	CHAR cRet = cDefault;
    if (v.vt != VT_NULL)
    {
		if (NULL != v.bstrVal)
			cRet = (CHAR)v.bstrVal[0];
    }
    return cRet;
}

#define CATCH_DB_STR_ERROR									\
	catch (_com_error &e)									\
	{														\
		DbFunc::PrintComError(e, __FILE__, __LINE__);		\
	}														\
	catch (CString str)										\
	{														\
		if (str.GetLength() > 0)							\
			DbFunc::PrintInfo(str, __FILE__, __LINE__);		\
	}														\
	catch (CException* e)									\
	{														\
		DbFunc::PrintError(e, __FILE__, __LINE__);			\
		e->Delete();										\
	}														\
	catch (...)												\
	{															\
		DbFunc::PrintInfo(L"Unknown exception", __FILE__, __LINE__, true);	\
	}

#endif // _X3_CONFIGDB_DBFUNC_H
