#pragma once

#include "Ix_SQLParser.h"

class SQLParser_Access : public Ix_SQLParser
{
public:
	SQLParser_Access()
	{
	}

	void Release()
	{
		delete this;
	}

	std::wstring GetFunc_CURDATE()
	{
		return L"Date()";
	}

	std::wstring GetFunc_CURTIME()
	{
		return L"Time()";
	}

	std::wstring GetFunc_NOW()
	{
		return L"Now()";
	}
};

class SQLParser_SQLServer : public Ix_SQLParser
{
public:
	SQLParser_SQLServer()
	{
	}

	void Release()
	{
		delete this;
	}

	std::wstring GetFunc_CURDATE()
	{
		return L"GetDate()";
	}

	std::wstring GetFunc_CURTIME()
	{
		return L"GetTime()";
	}

	std::wstring GetFunc_NOW()
	{
		return L"GetNow()";
	}
};
