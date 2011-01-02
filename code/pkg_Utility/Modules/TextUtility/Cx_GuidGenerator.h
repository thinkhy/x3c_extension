#pragma once

#include "Ix_GuidGenerator.h"

class Cx_GuidGenerator : public Ix_GuidGenerator
{
public:
	Cx_GuidGenerator() {}
	virtual ~Cx_GuidGenerator() {}

public:
	// From Ix_GuidGenerator
	virtual std::wstring CreateGuid(bool withBrackets = false);
	virtual std::wstring RemoveGuidBrackets(const std::wstring& uid);
	virtual std::wstring GetCurrentTimeString(bool hasYear = true);
	virtual ULONG CreateID(long type = 0);
};
