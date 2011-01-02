#include "stdafx.h"
#include "Cx_GuidGenerator.h"
#include <time.h>
#include <SysErrStr.h>

#pragma comment(lib,"Rpcrt4.lib")

#if _MSC_VER < 1400 // not VC8
typedef LPWSTR RPC_WSTR;
#endif // _MSC_VER

std::wstring Cx_GuidGenerator::CreateGuid(bool withBrackets)
{
	std::wstring wstrGuid;
	GUID guid;
	HRESULT hr;

	if (SUCCEEDED(hr = CoCreateGuid(&guid)))
	{
		RPC_WSTR pszGuid = NULL;

		UuidToStringW(&guid, &pszGuid);

		if (withBrackets)
		{
			wstrGuid = L"{";
			wstrGuid += (LPCWSTR)pszGuid;
			wstrGuid += L"}";
		}
		else
		{
			wstrGuid += (LPCWSTR)pszGuid;
		}

		RpcStringFreeW(&pszGuid);
	}
	else
	{
		LOG_WARNING2(LOGHEAD L"IDS_COCREATEGUID_FAIL", GetSystemErrorString(hr));
	}

	return wstrGuid;
}

std::wstring Cx_GuidGenerator::RemoveGuidBrackets(const std::wstring& uid)
{
	size_t index = 0;
	size_t len = uid.size();

	if (len > 2 && '{' == uid[0])
	{
		index++;
		len--;
	}
	if (len > 2 && '}' == uid[uid.size() - 1])
	{
		len--;
	}

	return std::wstring(uid, index, len);
}

ULONG Cx_GuidGenerator::CreateID(long type)
{
	if (0 == type)
	{
		static long s_nID = 0;
		return InterlockedIncrement(&s_nID);
	}

	typedef std::pair<long, long> IDPAIR;
	static std::vector<IDPAIR>	s_arrID;

	for (size_t i = 0; i < s_arrID.size(); ++i)
	{
		if (s_arrID[i].first == type)
		{
			return InterlockedIncrement(&(s_arrID[i].second));
		}
	}

	s_arrID.push_back(IDPAIR(type, 1L));
	return 1L;
}

std::wstring Cx_GuidGenerator::GetCurrentTimeString(bool hasYear)
{
	WCHAR szTime[30] = { 0, 0, 0, 0, 0, 0 };
	
#if _MSC_VER < 1400 // not VC8
	time_t tim = ::time(NULL);
	struct tm* ptm = localtime(&tim);
	
	if (ptm != NULL)
	{
		swprintf(szTime, 
			L"%04d-%02d-%02d %02d:%02d:%02d", 
			ptm->tm_year + 1900, 
			ptm->tm_mon + 1, ptm->tm_mday, 
			ptm->tm_hour, ptm->tm_min, ptm->tm_sec);
	}
#else	// VC8
	struct tm ttm;
	__time64_t tim = ::_time64(NULL);
	errno_t err = _localtime64_s(&ttm, &tim);
	
	if (0 == err)
	{
		swprintf_s(szTime, _countof(szTime), 
			L"%04d-%02d-%02d %02d:%02d:%02d", 
			ttm.tm_year + 1900, 
			ttm.tm_mon + 1, ttm.tm_mday, 
			ttm.tm_hour, ttm.tm_min, ttm.tm_sec);
	}
#endif
	
	return hasYear ? szTime : szTime + 5;
}
