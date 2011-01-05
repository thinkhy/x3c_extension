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

/*! \file ChangeNotifyData.h
 *  \brief ����ı�֪ͨ��Ϣ���ݻ��� ChangeNotifyData �� ChangeObserver
 *  \author Zhang Yun Gui, C++ Plugin Framework
 *  \date   2010.10.22
 */
#ifndef X3_OBSERVER_CHANGENOTIFYDATA_H_
#define X3_OBSERVER_CHANGENOTIFYDATA_H_

#include "XComPtr.h"
#include "Ix_ChangeManager.h"

//! �ı�֪ͨ��Ϣ���ݵĻ���
/*!
	\ingroup _GROUP_CHANGE_OBSERVER_
	\see ChangeObserver
*/
class ChangeNotifyData
{
protected:
	//! ���캯���������������ഫ��type(Ψһ��ʶ)
	ChangeNotifyData(const char* type) : m_type(type)
	{
	}

public:
	//! �㲥�ı�֪ͨ
	void Notify()
	{
		Cx_Interface<Ix_ChangeManager> pIFManager(CLSID_ChangeManager);
		if (pIFManager.IsNotNull())
		{
			pIFManager->ChangeNotify(m_type, this);
		}
	}

	//! ���ظı�֪ͨ����
	const char* GetChangeType() const
	{
		return m_type;
	}

	//! ��������(�Ա�ɶ�̬ת��Ϊ��������)
	virtual ~ChangeNotifyData()
	{
	}

private:
	ChangeNotifyData();
	const char*		m_type;
};

//! �ı�֪ͨ�۲��߻���
/*! ����һ�ָı�֪ͨ�۲�������Ҫʵ�� DoUpdate() ˽�к���
	\ingroup _GROUP_CHANGE_OBSERVER_
	\see ChangeNotifyData
*/
class ChangeObserver : public Ix_ChangeObserver
{
private:
	//! �ַ��ı�֪ͨ���ɾ���ı�֪ͨ�۲�����ʵ��
	/*!
		\param data ֪ͨ������Ϊһ���ֲ������ĵ�ַ���ɶ�̬ת��Ϊ��������
	*/
	virtual void DoUpdate(ChangeNotifyData* data) = 0;

protected:
	//! ���캯�����������۲����ഫ��type(Ψһ��ʶ)
	ChangeObserver(const char* type, bool register_now = true)
		: m_type(type), m_times(0)
	{
		if (register_now)
		{
			RegisterObserver();
		}
	}

	//! ���ظı�֪ͨ����
	const char* GetChangeType() const
	{
		return m_type;
	}

	//! �����Ƿ�����ִ�иı�֪ͨ�ķַ�����
	bool IsUpdating() const
	{
		return m_times != 0;
	}

	//! ע��۲���
	void RegisterObserver()
	{
		Cx_Interface<Ix_ChangeManager> pIFManager(CLSID_ChangeManager);
		if (pIFManager.IsNotNull())
		{
			pIFManager->RegisterObserver(GetChangeType(), this);
		}
	}

public:
	//! ��������
	virtual ~ChangeObserver()
	{
		Cx_Interface<Ix_ChangeManager> pIFManager(CLSID_ChangeManager);
		if (pIFManager.IsNotNull())
		{
			pIFManager->UnRegisterObserver(GetChangeType(), this);
		}
	}

private:
	void Update(ChangeNotifyData* data)
	{
		//ASSERT(data && 0 == strcmp(data->GetChangeType(), GetChangeType()));
		++m_times;
		DoUpdate(data);
		--m_times;
	}

private:
	ChangeObserver();
	const char*	m_type;
	long		m_times;
};

#endif // X3_OBSERVER_CHANGENOTIFYDATA_H_
