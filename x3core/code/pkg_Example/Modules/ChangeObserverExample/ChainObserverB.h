//! \file ChainObserverB.h
//! \brief ����ְ�����۲����� ChainObserverB

#ifndef EXAMPLE_CHAINB_OBSERVER_H_
#define EXAMPLE_CHAINB_OBSERVER_H_
#pragma once

#include <ChangeNotifyData.h>

//! ��Ϊ���ӵ�ְ�����۲�����
/*! �����������ö�������඼�ܴ���ͬһ�����ã��ж���֪ͨ����
	\note ����������ӱ���˽�м̳�
	\ingroup _GROUP_CHANGE_OBSERVER_
*/
class ChainObserverB : public ChangeObserver
{
public:
	//! ChainObserverB �۲��ߵ�֪ͨ������
	class Data : public ChangeNotifyData
	{
	public:
		//! ��һ��ְ����֪ͨ
		static bool DoWork1(int value)
		{
			Data data(1, &value, NULL);
			data.Notify();
			return data.ret;
		}

		//! �ڶ���ְ����֪ͨ
		static bool DoWork2(char c)
		{
			Data data(2, NULL, &c);
			data.Notify();
			return data.ret;
		}

		int		type;
		bool	ret;
		int*	value;
		char*	c;

	private:
		Data(int _type, int* _value, char* _c)
			: ChangeNotifyData(typeid(ChainObserverB).name())
			, type(_type), ret(false), value(_value), c(_c)
		{
		}
	};

protected:
	ChainObserverB() : ChangeObserver(typeid(ChainObserverB).name())
	{
	}

	//! ����������Ӧ��һ��ְ����֪ͨ
	virtual bool OnChainWork1(int value)
	{
		value; return false;
	}

	//! ����������Ӧ�ڶ���ְ����֪ͨ
	virtual bool OnChainWork2(char c)
	{
		c; return false;
	}

private:
	void DoUpdate(ChangeNotifyData* data)
	{
		Data* mydata = dynamic_cast<Data*>(data);
		ASSERT(mydata);
		
		switch (mydata->type)
		{
		case 1:
			mydata->ret = OnChainWork1(*(mydata->value)) || mydata->ret;
			break;

		case 2:
			mydata->ret = OnChainWork2(*(mydata->c)) || mydata->ret;
			break;

		default:
			ASSERT(FALSE);
		}
	}
};

#endif // EXAMPLE_CHAINB_OBSERVER_H_
