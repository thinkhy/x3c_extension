#pragma once

//! 不同数据库提供源的SQL指令的接口
interface Ix_SQLParser
{
	//! 销毁本对象
	virtual void Release() = 0;

	//! 返回当前的系统日期
	virtual std::wstring GetFunc_CURDATE() = 0;

	//! 返回当前的系统时间
	virtual std::wstring GetFunc_CURTIME() = 0;

	//! 返回当前的系统日期和时间
	virtual std::wstring GetFunc_NOW() = 0;
};
