#pragma once

#include "Ix_TempFolder.h"

class Cx_TempFolder : public Ix_TempFolder
{
public:
	Cx_TempFolder();
	virtual ~Cx_TempFolder();

	static void DeleteFolders();

public:
	// From Ix_TempFolder
	virtual void SetRootPath(const std::wstring& wstrPath);
	virtual bool DeleteFolder();
	virtual std::wstring CreateFolder(const std::wstring& wstrPrefix);
	virtual std::wstring GetPath() const;
	virtual std::wstring CreateFileName(const std::wstring& wstrPrefix, 
		const std::wstring& wstrExtName);

private:
	std::wstring	m_wstrPath;
	std::wstring	m_wstrRootPath;
	static std::vector<std::wstring> c_arrToDel;
};
