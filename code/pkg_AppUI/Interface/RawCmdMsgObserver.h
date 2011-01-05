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

/*! \file RawCmdMsgObserver.h
 *  \brief ����������Ϣ�۲����� RawCmdMsgObserver
 *  \author Zhang Yun Gui, C++ Plugin Framework
 *  \date   2010.10.29
 */
#ifndef X3_OBSERVER_RAWCMDMSGOBSERVER_H_
#define X3_OBSERVER_RAWCMDMSGOBSERVER_H_
#pragma once

#include <ChangeNotifyData.h>

//! ������Ϣ����
/*!
	\ingroup _GROUP_CHANGE_OBSERVER_
	\see RawCmdMsgObserver
*/
struct RawCmdMsgEventData : public ChangeNotifyData
{
	//! �㲥ִ��������Ϣ�Ĺ��캯��
	/*!
		\param _id �˵�����ԴID
		\param _sender ��Ϣ�����ߵ�������Ϣ���ɾ���Ӧ�þ����京��
	*/
	RawCmdMsgEventData(UINT _id, int _sender = 0)
		: ChangeNotifyData("RawCmdMsgEvent")
		, ret(false), id(_id), sender(_sender)
		, enabled(NULL), checked(NULL), text(NULL)
	{
	}

	//! �㲥���������Ϣ�Ĺ��캯��
	/*!
		\param[in] _id �˵�����ԴID
		\param[in,out] _enabled ����Ӧ�����������Ƿ����
		\param[in,out] _checked ����Ӧ�����������Ƿ��
		\param[in,out] _text ����Ӧ�������������ʾ�ı�
		\param[in] _sender ��Ϣ�����ߵ�������Ϣ���ɾ���Ӧ�þ����京��
	*/
	RawCmdMsgEventData(UINT _id, bool& _enabled, bool& _checked, 
		std::wstring& _text, int _sender = 0)
		: ChangeNotifyData("RawCmdMsgEvent")
		, ret(false), id(_id), sender(_sender)
		, enabled(&_enabled), checked(&_checked), text(&_text)
	{
	}

	bool	ret;
	UINT	id;
	int		sender;
	bool*	enabled;
	bool*	checked;
	std::wstring*	text;
};

//! ������Ϣ�۲��߻���
/*!
	\ingroup _GROUP_CHANGE_OBSERVER_
	\see RawCmdMsgEventData
*/
class RawCmdMsgObserver : public ChangeObserver
{
protected:
	//! ���캯��
	RawCmdMsgObserver() : ChangeObserver("RawCmdMsgEvent")
	{
	}

protected:
	//! ��Ӧ����ִ����Ϣ
	/*!
		\param id �˵�����ԴID
		\param sender ��Ϣ�����ߵ�������Ϣ���ɾ���Ӧ�þ����京��
		\return �Ƿ���Ӧ�˱�֪ͨ
	*/
	virtual bool OnRawCommand(UINT id, int sender)
	{
		id; sender;
		return false;
	}

	//! ��Ӧ���������Ϣ
	/*!
		\param[in] id �˵�����ԴID
		\param[in,out] enabled ����Ӧ�����������Ƿ����
		\param[in,out] checked ����Ӧ�����������Ƿ��
		\param[in,out] text ����Ӧ�������������ʾ�ı�
		\param[in] sender ��Ϣ�����ߵ�������Ϣ���ɾ���Ӧ�þ����京��
		\return �Ƿ���Ӧ�˱�֪ͨ
	*/
	virtual bool OnRawUpdateCmdUI(UINT id, bool& enabled, bool& checked, 
		std::wstring& text, int sender)
	{
		id; enabled; checked; text; sender;
		return false;
	}

private:
	void DoUpdate(ChangeNotifyData* data)
	{
#ifdef _USRDLL
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
#endif
		RawCmdMsgEventData* mydata = dynamic_cast<RawCmdMsgEventData*>(data);
		ASSERT(mydata);

		if (mydata->enabled)
		{
			mydata->ret = mydata->ret || OnRawUpdateCmdUI(mydata->id, 
				*mydata->enabled, *mydata->checked, *mydata->text, mydata->sender);
		}
		else
		{
			mydata->ret = mydata->ret
				|| OnRawCommand(mydata->id, mydata->sender);
		}
	}
};

#endif // X3_OBSERVER_RAWCMDMSGOBSERVER_H_
