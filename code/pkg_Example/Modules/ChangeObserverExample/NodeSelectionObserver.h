//! \file NodeSelectionObserver.h
//! \brief ����ڵ�ѡ��ı�۲����� NodeSelectionObserver

#ifndef EXAMPLE_NODESELECTION_OBSERVER_H_
#define EXAMPLE_NODESELECTION_OBSERVER_H_
#pragma once

#include <ChangeNotifyData.h>

//! ��Ϊ���ӵĽڵ�ѡ��ı�۲�����
/*! �����������������඼��Ӧ�ڵ�仯�����ɱ�������ѭ���仯
	\note ����������ӱ���˽�м̳�
	\ingroup _GROUP_CHANGE_OBSERVER_
*/
class NodeSelectionObserver : public ChangeObserver
{
public:
	//! NodeSelectionObserver �۲��ߵ�֪ͨ������
	class Data : public ChangeNotifyData
	{
	public:
		Data(ULONG _objid, NodeSelectionObserver* _sender)
			: ChangeNotifyData(typeid(NodeSelectionObserver).name())
			, objid(_objid), sender(_sender)
		{
		}

		ULONG	objid;
		void*	sender;
	};

protected:
	NodeSelectionObserver() : ChangeObserver(typeid(NodeSelectionObserver).name())
	{
	}

	//! ����������Ӧ�ڵ�ѡ��ı�֪ͨ
	virtual void OnNodeSelection(ULONG objid, void* sender)
	{
		objid; sender;
	}

private:
	void DoUpdate(ChangeNotifyData* data)
	{
		Data* mydata = dynamic_cast<Data*>(data);
		ASSERT(mydata);
		OnNodeSelection(mydata->objid, mydata->sender);
	}
};

#endif // EXAMPLE_NODESELECTION_OBSERVER_H_
