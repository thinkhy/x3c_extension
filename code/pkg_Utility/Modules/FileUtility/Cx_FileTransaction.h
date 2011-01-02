#pragma once

#include "Ix_FileTransaction.h"

class Cx_FileTransaction : public Ix_FileTransaction
{
public:
	Cx_FileTransaction();
	virtual ~Cx_FileTransaction();

public:
	// From Ix_FileTransaction
	virtual void Rollback();
	virtual long GetLevel() const;
	virtual bool IsRollbacking() const;
	virtual bool DeletePathFile(LPCWSTR pszFileName, bool bRecycle = false);

private:
	long		m_lLevel;
};
