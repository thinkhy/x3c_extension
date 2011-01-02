#include "StdAfx.h"
#include "DbFunc.h"
#include <ReadInts.h>

void DbFunc::PrintComError(_com_error &e, LPCSTR file, long lLine, LPCWSTR pszSQL)
{
	HRESULT hr = e.Error();
	bool bSQLError = ((hr & 0xFFFFFF00) == 0x80040E00 || 0x80004005 == hr);

	CString strError, str;

	strError.Format(L"[0x%lx] %s", hr, (LPCTSTR) e.Description());

	if (!bSQLError)
	{
		str.Format(L"\nSource: %s", (LPCTSTR) e.Source());
		strError += str;
	}
	if (pszSQL != NULL)
	{
		str.Format(L"\nCommand: %s", pszSQL);
		strError += str;
	}

	if (bSQLError)
	{
		LOG_EVENT_2(LOGHEAD L"IDS_SQL_ERROR", towstr(strError), kLogType_Error, file, lLine);
	}
	else
	{
		LOG_EVENT_2(LOGHEAD L"IDS_DB_ERROR", towstr(strError), kLogType_Error, file, lLine);
	}
}

void DbFunc::PrintInfo(LPCWSTR pszMsg, LPCSTR file, long lLine, bool bError)
{
	if (bError)
	{
		LOG_EVENT_2(LOGHEAD L"IDS_DB_ERROR", pszMsg, kLogType_Error, file, lLine);
	}
	else
	{
		LOG_EVENT_2(LOGHEAD L"IDS_DB_INFO", pszMsg, kLogType_Info, file, lLine);
	}
}

void DbFunc::PrintError(CException* e, LPCSTR file, long lLine)
{
	TCHAR szErrorMessage[512];
	e->GetErrorMessage(szErrorMessage, _countof(szErrorMessage));
	LOG_EVENT_2(LOGHEAD L"IDS_DB_ERROR", szErrorMessage, kLogType_Error, file, lLine);
}

static inline void cutstr(LPWSTR pch)
{
	if (pch)
		*pch = 0;
}

std::wstring DbFunc::GetLevel1Name(LPCWSTR name)
{
	WCHAR buf[41];

	StrCpyNW(buf, name ? name : L"", _countof(buf));
	cutstr(StrChrW(buf, '\\'));
	cutstr(StrChrW(buf, '/'));
	cutstr(StrChrW(buf, ' '));

	std::wstring wstr(buf);
	trim::ctrim(wstr);

	return wstr;
}

bool DbFunc::IsDBName(LPCWSTR name)
{
	return name && *name && StrChrW(name, ' ') == NULL;
}

bool DbFunc::IsSelectSQL(LPCWSTR name)
{
	return StrStrIW(name, L"SELECT ") == name;
}

CHAR DbFunc::BoolToChar(BOOL bValue)
{
	return bValue ? 'y' : 'n';
}

CString DbFunc::GetBSTR(const _variant_t &v, LPCTSTR pszDefault)
{
	CString str (pszDefault);

    if (v.vt != VT_NULL)
    {
		if (VT_BSTR == v.vt)
		{
			str = v.bstrVal;
			str.TrimRight();
		}
		else
		{
			str.Format(L"%ld", v.lVal);
		}
    }

    return str;
}

bool DbFunc::GetDate(COleDateTime& dt, const _variant_t &v)
{
	bool bRet = false;

	if (VT_DATE == v.vt)
	{
		dt = v.date;
		dt.SetDate(dt.GetYear(), dt.GetMonth(), dt.GetDay());
		bRet = (dt.GetStatus() == dt.valid);
	}
	else if (VT_BSTR == v.vt)
	{
		int nums[3];
		if (ReadInts(v.bstrVal, nums, 3) == 3)
		{
			dt.SetDate(nums[0], nums[1], nums[2]);
			bRet = (dt.GetStatus() == dt.valid);
		}
	}

    return bRet;
}

bool DbFunc::GetDateTime(COleDateTime& dt, const _variant_t &v)
{
    bool bRet = false;

	if (VT_DATE == v.vt)
	{
		dt = v.date;
		bRet = (dt.GetStatus() == dt.valid);
	}
	else if (VT_BSTR == v.vt)
	{
		int nums[6] = { 0, 0, 0, 0, 0, 0 };
		if (ReadInts(v.bstrVal, nums, 6) >= 3)
		{
			dt.SetDateTime(nums[0], nums[1], nums[2], nums[3], nums[4], nums[5]);
			bRet = (dt.GetYear() >= 1980);
		}
	}

    return bRet;
}

COleDateTime DbFunc::GetTimeNew(const _variant_t &v)
{
	// Date -> CString
	COleDateTime OleTime = v; 
	CString strDate = OleTime.Format(L"%Y-%m-%d %H:%M:%S");

	// CString -> COleDateTime
	COleVariant vtime(strDate);
	vtime.ChangeType(VT_DATE);
	COleDateTime Oletime=vtime;

	SYSTEMTIME systime;
	VariantTimeToSystemTime(Oletime, &systime);
	COleDateTime time(systime);
	return time;
}

long DbFunc::GetLong(const _variant_t &v, long lDefault)
{
    long ret = lDefault;

    if (v.vt != VT_NULL)
	{
		if (VT_BSTR == v.vt)
		{
			if (NULL != v.bstrVal)
			{
				ret = _wtol(v.bstrVal);
			}
		}
		else
		{
			ret = v.lVal;
		}
	}
	
    return ret;
}

short DbFunc::GetShort(const _variant_t &v, short nDefault)
{
    short ret = nDefault;

	if (v.vt != VT_NULL)
	{
		if (VT_BSTR == v.vt)
		{
			if (NULL != v.bstrVal)
			{
				ret = (short)_wtol(v.bstrVal);
			}
		}
		else
		{
			ret = v.iVal;
		}
	}
	
    return ret;
}

double DbFunc::GetDouble(const _variant_t &v, double dDefault)
{
    double ret = dDefault;
    
	if (v.vt != VT_NULL)
	{
		ret = v.dblVal;
	}

    return ret;
}

BOOL DbFunc::GetBool(const _variant_t &v, BOOL bDefault)
{
	BOOL bRet = bDefault;

    if (v.vt != VT_NULL)
	{
		if (VT_BSTR == v.vt)
		{
			if (NULL != v.bstrVal)
			{
				bRet = ('y' == v.bstrVal[0]);
			}
		}
		else
		{
			bRet = (0 != v.lVal);
		}
	}
	
    return bRet;
}
