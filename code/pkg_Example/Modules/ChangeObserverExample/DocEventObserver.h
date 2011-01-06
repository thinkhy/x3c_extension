//! \file DocEventObserver.h
//! \brief �����ĵ��¼��۲����� DocEventObserver

#ifndef EXAMPLE_DOCEVENT_OBSERVER_H_
#define EXAMPLE_DOCEVENT_OBSERVER_H_
#pragma once

#include <ChangeNotifyData.h>

//! �ĵ��¼�����
enum kDocEventType
{
	kDocEvent_BeforeOpen,		//!< �ĵ���֮ǰ
	kDocEvent_AfterOpen,		//!< �ĵ���֮��
	kDocEvent_OpenFail,			//!< �ĵ���ʧ��
};

//! ��Ϊ���ӵ��ĵ��¼��۲�����
/*! �����������������඼����Ӧ����¼�֪ͨ
	\note ����������ӱ���˽�м̳�
	\ingroup _GROUP_CHANGE_OBSERVER_
*/
class DocEventObserver : public ChangeObserver
{
public:
	//! DocEventObserver �۲��ߵ�֪ͨ������
	class Data : public ChangeNotifyData
	{
	public:
		Data(kDocEventType _event)
			: ChangeNotifyData(typeid(DocEventObserver).name()), event(_event)
		{
		}

		kDocEventType event;
	};

protected:
	DocEventObserver() : ChangeObserver(typeid(DocEventObserver).name())
	{
	}

	//! ��Ӧ�ĵ���֮ǰ��֪ͨ
	virtual void OnDocEventBeforeOpen() {}

	//! ��Ӧ�ĵ���֮���֪ͨ
	virtual void OnDocEventAfterOpen() {}

	//! ��Ӧ�ĵ���ʧ�ܵ�֪ͨ
	virtual void OnDocEventOpenFail() {}

private:
	void DoUpdate(ChangeNotifyData* data)
	{
		Data* mydata = dynamic_cast<Data*>(data);
		ASSERT(mydata);
		
		switch (mydata->event)
		{
		case kDocEvent_BeforeOpen:
			OnDocEventBeforeOpen();
			break;

		case kDocEvent_AfterOpen:
			OnDocEventAfterOpen();
			break;

		case kDocEvent_OpenFail:
			OnDocEventOpenFail();
			break;

		default:
			ASSERT(FALSE);
		}
	}
};

#endif // EXAMPLE_DOCEVENT_OBSERVER_H_
