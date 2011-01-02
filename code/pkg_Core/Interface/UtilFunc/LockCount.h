//! \file LockCount.h
//! \brief �����Զ����������ĸ����� CLockCount

#ifndef UTILFUNC_LOCKCOUNT_H_
#define UTILFUNC_LOCKCOUNT_H_
#pragma once

//! �Զ����������ĸ�����
/*! ʹ�ñ����ں����ڶ���ֲ����������˳���������ʱ�Զ����ټ�����
	�����������оͿ���ͨ���жϸü��������Ƿ�Ϊ��ʼֵ��֪���Ƿ�����ص�״̬��
	\ingroup _GROUP_UTILFUNC
*/
class CLockCount
{
public:
	//! ���캯�����Զ����Ӽ���
	/*!
		\param p ���м��������ĵ�ַ���ü��������ĳ�ʼֵһ��Ϊ0
	*/
	CLockCount(long* p) : m_count(p)
	{
		InterlockedIncrement(m_count);
	}

	//! �����������Զ����ټ���
	~CLockCount()
	{
		Unlock();
	}

	//! ����������Զ����ټ���
	void Unlock()
	{
		if (m_count)
		{
			InterlockedDecrement(m_count);
			m_count = NULL;
		}
	}

private:
	long*	m_count;
};

#endif // UTILFUNC_LOCKCOUNT_H_
