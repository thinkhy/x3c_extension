#pragma once

interface IFileCryptHandler;
interface Ix_ConfigData;

struct ConfigXmlImpl
{
	long				m_nTransaction;
	ULONG				m_nModifiedCount;
	std::wstring		m_strFileName;
	std::wstring		m_strRootName;
	std::wstring		m_strEncoding;
	std::wstring		m_strNameSpace;
	std::wstring		m_strSchemaLocation;
	bool				m_bModified;
	bool				m_bNeedLoad;
	CXTPDOMDocumentPtr	m_xmlDoc;
	CXTPDOMElementPtr	m_xmlRoot;
	IFileCryptHandler*	m_pCryptHandler;
	Ix_ConfigData*		m_pThis;

	ConfigXmlImpl(Ix_ConfigData* pThis) : m_pThis(pThis)
	{
		m_nTransaction = 0;
		m_nModifiedCount = 0;
		m_bModified = false;
		m_bNeedLoad = true;
		m_strEncoding = L"UTF-8";
		m_pCryptHandler = NULL;
	}

	CXTPDOMElementPtr GetRoot()
	{
		if (NULL == m_xmlRoot)
			Reload();
		return m_xmlRoot;
	}

	void SetModified(bool bModified = true)
	{
		m_bModified = bModified;
		if (bModified)
			m_nModifiedCount++;
	}

	bool Reload();
	void NewDoc();
	CXTPDOMElementPtr GetParentNode(Ix_ConfigSection* pParent, std::wstring& strSection);
	CXTPDOMElementPtr GetParentNode(CXTPDOMElementPtr xmlParent, std::wstring& strSection);
};
