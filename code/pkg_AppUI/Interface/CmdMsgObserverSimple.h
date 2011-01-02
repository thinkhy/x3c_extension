/*! \file CmdMsgObserverSimple.h
 *  \brief ����������Ϣ�۲����� RawCmdMsgObserver
 *  \author Zhang Yun Gui, C++ Plugin Framework
 *  \date   2010.10.29
 */
#ifndef X3_OBSERVER_CMDMSGOBSERVERSIMPLE_H_
#define X3_OBSERVER_CMDMSGOBSERVERSIMPLE_H_
#pragma once

#include <RawCmdMsgObserver.h>

struct MENU_MSG_MAP;

//! ������Ϣ�۲��߻���
/*! �������ඨ���м��� DECLARE_MENU_MSG_MAP() \n
	��ʵ���ļ���ָ����Ӧ������˵���� MenuMsgMapFunctions 
	\ingroup _GROUP_CHANGE_OBSERVER_
	\see MenuMsgMapFunctions
*/
class CmdMsgObserverSimple : public RawCmdMsgObserver
{
protected:
	CmdMsgObserverSimple() : m_sender(0)
	{
	}

protected:
	int GetCurrentCommandSender() const;

private:
	bool OnRawCommand(UINT id, int sender);
	bool OnRawUpdateCmdUI(UINT id, bool& enabled, bool& checked, 
		std::wstring& text, int sender);
	virtual const MENU_MSG_MAP* GetMsgMapEntry() const = 0;

private:
	int	m_sender;
};

typedef void (CmdMsgObserverSimple::*PFN_MSG)(void);

//! �˵�������Ӧ����������
/*! ��CmdMsgObserverSimple�������ඨ���м��� DECLARE_MENU_MSG_MAP() \n
	��ʵ���ļ���ָ����Ӧ������������ʾ��
	\code
	BEGIN_MENU_MSG_MAP(class)
		ON_MENU_COMMAND(id, memberFxn)
		ON_MENU_COMMAND_RANGE(idMin, idMax, memberFxn)
		ON_MENU_UPDATE_CMDUI(id, memberFxn)
		ON_MENU_UPDATE_CMDUI_RANGE(idMin, idMax, memberFxn)
	END_MENU_MSG_MAP()
	\endcode
	\see CmdMsgObserverSimple
*/
union MenuMsgMapFunctions
{
	PFN_MSG	pfn;

	//! ��ͨ������Ӧ��������Ӧ�� ON_MENU_COMMAND
	void (CmdMsgObserverSimple::*pfn_COMMAND)();

	//! ����ID��Χ��������Ӧ��������Ӧ�� ON_MENU_COMMAND_RANGE
	void (CmdMsgObserverSimple::*pfn_COMMAND_RANGE)(UINT id);

	//! ��ͨ����Ĳ˵����º�������Ӧ�� ON_MENU_UPDATE_CMDUI
	void (CmdMsgObserverSimple::*pfn_UPDATE_CMDUI)(
		bool& enabled, bool& checked, std::wstring& text);

	//! ����ID��Χ�Ĳ˵����º�������Ӧ�� ON_MENU_UPDATE_CMDUI_RANGE
	void (CmdMsgObserverSimple::*pfn_UPDATE_CMDUI_RANGE)(
		UINT id, bool& enabled, bool& checked, std::wstring& text);
};

//! ������Ӧ����������
enum MenuMsgType
{
	kMenuMsgNull,
	kMenuMsgCommand,
	kMenuMsgCommandRange,
	kMenuMsgUpdateUI,
	kMenuMsgUpdateUIRange,
};

//! ������Ӧ���������
struct MENU_MSG_MAP
{
	UINT		id;
	UINT		lastid;
	MenuMsgType	type;
	PFN_MSG		pfn;
};

//! ��H�ļ��ж���������Ӧ��������������
/*!
	\see MenuMsgMapFunctions, BEGIN_MENU_MSG_MAP
*/
#define DECLARE_MENU_MSG_MAP()	\
private:	\
	const MENU_MSG_MAP* GetMsgMapEntry() const;	\
	static const MENU_MSG_MAP messageMap[];

//! ��CPP��ʵ��������Ӧ��������������
/*!
	\see MenuMsgMapFunctions, END_MENU_MSG_MAP, DECLARE_MENU_MSG_MAP
*/
#define BEGIN_MENU_MSG_MAP(theClass)	\
	const MENU_MSG_MAP* theClass::GetMsgMapEntry() const	\
		{ return messageMap; }	\
	const MENU_MSG_MAP theClass::messageMap[] = {

//! �Ǽ�һ����һ�������Ӧ����
/*!
	\see BEGIN_MENU_MSG_MAP, MenuMsgMapFunctions
*/
#define ON_MENU_COMMAND(id, memberFxn)	\
		{ id, id, kMenuMsgCommand, (PFN_MSG)&memberFxn },

//! �Ǽ�һ����Χ�������Ӧ����
/*!
	\see BEGIN_MENU_MSG_MAP, MenuMsgMapFunctions
*/
#define ON_MENU_COMMAND_RANGE(idMin, idMax, memberFxn)	\
		{ idMin, idMax, kMenuMsgCommandRange, \
		(PFN_MSG)(void (CmdMsgObserverSimple::*)(UINT))&memberFxn },

//! �Ǽ�һ����һ����ĸ��º���
/*!
	\see BEGIN_MENU_MSG_MAP, MenuMsgMapFunctions
*/
#define ON_MENU_UPDATE_CMDUI(id, memberFxn)	\
		{ id, id, kMenuMsgUpdateUI, \
		(PFN_MSG)(void (CmdMsgObserverSimple::*)(bool&,bool&,std::wstring&))&memberFxn },

//! �Ǽ�һ����Χ����ĸ��º���
/*!
	\see BEGIN_MENU_MSG_MAP, MenuMsgMapFunctions
*/
#define ON_MENU_UPDATE_CMDUI_RANGE(idMin, idMax, memberFxn)	\
		{ idMin, idMax, kMenuMsgUpdateUIRange, \
		(PFN_MSG)(void (CmdMsgObserverSimple::*)(UINT,bool&,bool&,std::wstring&))&memberFxn },

//! BEGIN_MENU_MSG_MAP��Ӧ�Ľ�����
/*!
	\see BEGIN_MENU_MSG_MAP, MenuMsgMapFunctions
*/
#define END_MENU_MSG_MAP()	\
		{ 0, 0, kMenuMsgNull, (PFN_MSG)0 }	\
	};

inline int CmdMsgObserverSimple::GetCurrentCommandSender() const
{
	return m_sender;
}

inline bool CmdMsgObserverSimple::OnRawCommand(UINT id, int sender)
{
	const MENU_MSG_MAP* pMsgMap = GetMsgMapEntry();

	m_sender = sender;
	for (int i = 0; pMsgMap[i].id != 0; i++)
	{
		union MenuMsgMapFunctions mmf;
		mmf.pfn = pMsgMap[i].pfn;

		if (pMsgMap[i].type == kMenuMsgCommand
			&& id == pMsgMap[i].id)
		{
			(this->*mmf.pfn_COMMAND)();
			return true;
		}
		else if (pMsgMap[i].type == kMenuMsgCommandRange
			&& id >= pMsgMap[i].id && id <= pMsgMap[i].lastid)
		{
			(this->*mmf.pfn_COMMAND_RANGE)(id);
			return true;
		}
	}

	return false;
}

inline bool CmdMsgObserverSimple::OnRawUpdateCmdUI(
	UINT id, bool& enabled, bool& checked, std::wstring& text, int sender)
{
	int i = 0;
	const MENU_MSG_MAP* pMsgMap = GetMsgMapEntry();

	m_sender = sender;
	for (; pMsgMap[i].id != 0; i++)
	{
		union MenuMsgMapFunctions mmf;
		mmf.pfn = pMsgMap[i].pfn;

		if (pMsgMap[i].type == kMenuMsgUpdateUI
			&& id == pMsgMap[i].id)
		{
			(this->*mmf.pfn_UPDATE_CMDUI)(enabled, checked, text);
			break;
		}
		else if (pMsgMap[i].type == kMenuMsgUpdateUIRange
			&& id >= pMsgMap[i].id && id <= pMsgMap[i].lastid)
		{
			(this->*mmf.pfn_UPDATE_CMDUI_RANGE)(id, enabled, checked, text);
			break;
		}
	}

	if (pMsgMap[i].id == 0)
	{
		for (i = 0; pMsgMap[i].id != 0; i++)
		{
			if (id >= pMsgMap[i].id && id <= pMsgMap[i].lastid)
				break;
		}
	}

	return pMsgMap[i].id != 0;
}

#endif // X3_OBSERVER_CMDMSGOBSERVERSIMPLE_H_
