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

#ifndef _X3_FILEUTILITY_TRANSSTEP_H
#define _X3_FILEUTILITY_TRANSSTEP_H

#include "Ix_FileUtility.h"

class CTransStep
{
public:
	CTransStep() {}
	virtual ~CTransStep() {}

	virtual bool DoStep() = 0;
};

class CTransDeleteFile : public CTransStep
{
public:
	CTransDeleteFile(LPCWSTR pszFileName, bool bRecycle)
		: m_wstrFileName(pszFileName), m_bRecycle(bRecycle)
	{
	}

	virtual bool DoStep()
	{
		return FileUtility()->DeletePathFile(m_wstrFileName.c_str(), m_bRecycle);
	}

private:
	std::wstring	m_wstrFileName;
	bool			m_bRecycle;
};

class CTransRenameFile : public CTransStep
{
public:
	CTransRenameFile(LPCWSTR pszOldFile, LPCWSTR pszNewFile)
		: m_wstrOldFile(pszOldFile), m_wstrNewFile(pszNewFile)
	{
	}

	virtual bool DoStep()
	{
		return FileUtility()->RenamePathFile(m_wstrOldFile.c_str(), m_wstrNewFile.c_str());
	}

private:
	std::wstring	m_wstrOldFile;
	std::wstring	m_wstrNewFile;
};

class CFileTransactions
{
public:
	static CFileTransactions& Instance()
	{
		static CFileTransactions obj;
		return obj;
	}

	~CFileTransactions()
	{
		Clear();
	}

	bool IsRollbacking() const
	{
		return m_bRollbacking;
	}

	void AddStep(CTransStep* pCommitStep, CTransStep* pRollbackStep)
	{
		ASSERT(!m_bRollbacking);
		m_steps.push_back(StepPair(pCommitStep, pRollbackStep));
	}

	void EndTransaction(bool bCommit)
	{
		m_bRollbacking = (m_bRollbacking || !bCommit);

		if (!m_bRollbacking)
		{
			while (!m_steps.empty())
			{
				if (m_steps.back().first->DoStep())
					m_steps.pop_back();
				else
				{
					m_bRollbacking = true;
					break;
				}
			}
		}

		if (m_bRollbacking)
		{
			std::vector<StepPair>::reverse_iterator it;
			for (it = m_steps.rbegin(); it != m_steps.rend(); it++)
			{
				if (!it->second->DoStep())
				{
				}
			}
		}

		Clear();
	}

	void Reset()
	{
		ASSERT(m_steps.empty());
		m_bRollbacking = false;
	}

protected:
	CFileTransactions() : m_bRollbacking(false)
	{
	}

	void Clear()
	{
		while (!m_steps.empty())
		{
			StepPair item = m_steps.back();
			m_steps.pop_back();
			delete item.first;
			delete item.second;
		}
	}

private:
	typedef std::pair<CTransStep*, CTransStep*> StepPair;
	std::vector<StepPair>	m_steps;
	bool					m_bRollbacking;
};

#endif // _X3_FILEUTILITY_TRANSSTEP_H
