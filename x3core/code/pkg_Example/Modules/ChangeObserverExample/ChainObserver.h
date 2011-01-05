//! \file ChainObserver.h
//! \brief ����ְ�����۲����� ChainObserver

#ifndef EXAMPLE_CHAIN_OBSERVER_H_
#define EXAMPLE_CHAIN_OBSERVER_H_
#pragma once

#include <ChangeNotifyData.h>

//! ��Ϊ���ӵ�ְ�����۲�����
/*! �����������ö�������඼�ܴ���ͬһ������
	\note ����������ӱ���˽�м̳�
	\ingroup _GROUP_CHANGE_OBSERVER_
*/
class ChainObserver : public ChangeObserver
{
public:
	//! ChainObserver �۲��ߵ�֪ͨ������
	class Data : public ChangeNotifyData
	{
	public:
		Data(int* _sum) : ChangeNotifyData(typeid(ChainObserver).name()), sum(_sum)
		{
		}

		int*	sum;
	};

protected:
	ChainObserver() : ChangeObserver(typeid(ChainObserver).name())
	{
	}

	//! ����������Ӧְ����֪ͨ
	virtual void OnChain(int& sum)
	{
		sum;
	}

private:
	void DoUpdate(ChangeNotifyData* data)
	{
		Data* mydata = dynamic_cast<Data*>(data);
		ASSERT(mydata && mydata->sum);
		OnChain(*(mydata->sum));
	}
};

#endif // EXAMPLE_CHAIN_OBSERVER_H_
