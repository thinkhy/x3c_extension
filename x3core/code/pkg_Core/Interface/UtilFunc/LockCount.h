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

//! \file LockCount.h
//! \brief �����Զ����������ĸ����� CLockCount

#ifndef UTILFUNC_LOCKCOUNT_H_
#define UTILFUNC_LOCKCOUNT_H_

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
