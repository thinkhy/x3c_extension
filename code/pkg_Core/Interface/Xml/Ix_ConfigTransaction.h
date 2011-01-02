/*! \file Ix_ConfigTransaction.h
 *  \brief ����д��������ĸ����� CConfigTransaction
 *  \author Zhang Yun Gui, C++ Plugin Framework
 *  \date   2010.10.22
 */
#ifndef X3_XML_CONFIGTRANSACTION_H_
#define X3_XML_CONFIGTRANSACTION_H_
#pragma once

#include <XComPtr.h>

//! �������ݱ�������Ľӿ�
/*! Ix_ConfigSection �� Ix_ConfigData һ�㶼��ת�����ýӿ�
	\see CConfigTransaction
*/
interface Ix_ConfigTransaction
{
	//! ׼��д����
	virtual void BeginTransaction() = 0;

	//! ����д����
	virtual bool EndTransaction() = 0;

	//! �������ݸı���ܴ����������ڱȽ�ĳ���Ƿ�ı�
	virtual ULONG GetModifiedCount() = 0;
};

//! д��������ĸ�����
/*! ��Ҫ�������õĺ����У��ñ����ں����ڶ���ֲ�������
	�����������øı����ݵĺ������˳���������ʱ�Ϳ����ñ�������
	\ingroup _GROUP_PLUGIN_XML_
	\see Ix_ConfigSection, Ix_ConfigData
*/
class CConfigTransaction
{
public:
	//! ���캯����׼��д����
	CConfigTransaction(const Cx_Ptr& obj) : m_trans(obj)
	{
		if (m_trans)
		{
			m_trans->BeginTransaction();
		}
	}

#ifdef X3_XML_ICONFIGDATA_H_
	//! ���캯����׼��д����
	CConfigTransaction(const Cx_Interface<Ix_ConfigData>& p) : m_trans(p)
	{
		if (m_trans)
		{
			m_trans->BeginTransaction();
		}
	}
#endif

	//! ��������������д����
	~CConfigTransaction()
	{
		Submit();
	}

	//! ����д����
	bool Submit()
	{
		bool ret = false;

		if (m_trans)
		{
			ret = m_trans->EndTransaction();
			m_trans.Release();
		}

		return ret;
	}

private:
	Cx_Interface<Ix_ConfigTransaction>	m_trans;
};

#endif // X3_XML_CONFIGTRANSACTION_H_
