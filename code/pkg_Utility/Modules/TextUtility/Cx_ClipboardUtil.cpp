#include "StdAfx.h"
#include "Cx_ClipboardUtil.h"
#include <ConvStr.h>
#include <SysErrStr.h>

bool Cx_ClipboardUtil::CopyText(HWND wndOwner, const std::wstring& text)
{
	bool bRet = false;
	DWORD err = 0;

	if (!text.empty() && ::OpenClipboard(wndOwner))
	{
		HGLOBAL hMem = ::GlobalAlloc(GMEM_MOVEABLE, sizeof(WCHAR) * (text.size() + 1));
		if (hMem != NULL)
		{
			LPWSTR lpStr = (LPWSTR)::GlobalLock(hMem);
			if (NULL == lpStr)
			{
				::GlobalFree(hMem);
			}
			else
			{
				lstrcpyW(lpStr, text.c_str());
				::GlobalUnlock(hMem);

				::EmptyClipboard();
				if (::SetClipboardData(CF_UNICODETEXT, hMem))
				{
					bRet = true;
				}
				else
				{
					err = GetLastError();
					LOG_WARNING2(LOGHEAD L"IDS_SETCLIP_FAIL", GetSystemErrorString(err));
				}
			}
		}
		else
		{
			err = GetLastError();
			LOG_WARNING2(LOGHEAD L"IDS_ALLOCMEM_FAIL", GetSystemErrorString(err));
		}

		::CloseClipboard();
	}
	else
	{
		err = GetLastError();
		LOG_WARNING2(LOGHEAD L"IDS_OPENCLIP_FAIL", GetSystemErrorString(err));
	}

	return bRet;
}

bool Cx_ClipboardUtil::PasteText(HWND wndOwner, std::wstring& text, bool clear)
{
	text.resize(0);

	if (!::IsClipboardFormatAvailable(CF_UNICODETEXT)
		&& !::IsClipboardFormatAvailable(CF_TEXT))
	{
		LOG_INFO(LOGHEAD L"IDS_CLIP_NOTEXT");
		return false;
	}

	if (!::OpenClipboard(wndOwner))
	{
		DWORD err = GetLastError();
		LOG_WARNING2(LOGHEAD L"IDS_OPENCLIP_FAIL", GetSystemErrorString(err));
	}
	else
	{
		if (::IsClipboardFormatAvailable(CF_UNICODETEXT))
		{
			HGLOBAL hMem = ::GetClipboardData(CF_UNICODETEXT);
			if (hMem != NULL)
			{
				LPCWSTR lpStr = (LPCWSTR)::GlobalLock(hMem);
				if (lpStr != NULL)
				{
					text = lpStr;
					::GlobalUnlock(hMem);
				}
			}
		}
		else if (::IsClipboardFormatAvailable(CF_TEXT))
		{
			HGLOBAL hMem = ::GetClipboardData(CF_UNICODETEXT);
			if (hMem != NULL)
			{
				LPCSTR lpStr = (LPCSTR)::GlobalLock(hMem);
				if (lpStr != NULL)
				{
					text = std::a2w(lpStr);
					::GlobalUnlock(hMem);
				}
			}
		}

		if (clear)
		{
			::EmptyClipboard();
		}

		::CloseClipboard();
	}

	return !text.empty();
}

bool Cx_ClipboardUtil::CanPasteText()
{
	return ::IsClipboardFormatAvailable(CF_UNICODETEXT)
		|| ::IsClipboardFormatAvailable(CF_TEXT);
}
