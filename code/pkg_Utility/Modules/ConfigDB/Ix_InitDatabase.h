#pragma once

interface Ix_SQLParser;

//! ��ʼ�����ݿ���ʶ���Ľӿ�
interface Ix_InitDatabase
{
	//! ָ��SQL���Ӵ������ݿ�
	virtual bool OpenConnection(const std::wstring& wstrConnection, 
		Ix_SQLParser* pSQLParser) = 0;
};
