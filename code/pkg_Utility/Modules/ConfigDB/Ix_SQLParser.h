#pragma once

//! ��ͬ���ݿ��ṩԴ��SQLָ��Ľӿ�
interface Ix_SQLParser
{
	//! ���ٱ�����
	virtual void Release() = 0;

	//! ���ص�ǰ��ϵͳ����
	virtual std::wstring GetFunc_CURDATE() = 0;

	//! ���ص�ǰ��ϵͳʱ��
	virtual std::wstring GetFunc_CURTIME() = 0;

	//! ���ص�ǰ��ϵͳ���ں�ʱ��
	virtual std::wstring GetFunc_NOW() = 0;
};
