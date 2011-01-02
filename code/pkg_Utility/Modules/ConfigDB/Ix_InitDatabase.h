#pragma once

interface Ix_SQLParser;

//! 初始化数据库访问对象的接口
interface Ix_InitDatabase
{
	//! 指定SQL连接串打开数据库
	virtual bool OpenConnection(const std::wstring& wstrConnection, 
		Ix_SQLParser* pSQLParser) = 0;
};
