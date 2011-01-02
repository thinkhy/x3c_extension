/*! \file Ix_ChangeManager.h
 *  \brief ����ı�֪ͨ�������Ľӿ� Ix_ChangeManager
 *  \author Zhang Yun Gui, C++ Plugin Framework
 *  \date   2010.10.22
 */
#ifndef X3_OBSERVER_ICHANGEMANAGER_H_
#define X3_OBSERVER_ICHANGEMANAGER_H_
#pragma once

#include "Ix_ChangeObserver.h"

const XCLSID CLSID_ChangeManager("34c6e7c0-fe4a-45a1-b227-3da06e08499f");

//! �ı�֪ͨ�������Ľӿ�
/*!
	\interface Ix_ChangeManager
	\ingroup _GROUP_CHANGE_OBSERVER_
	\see CLSID_ChangeManager
*/
interface Ix_ChangeManager
{
	//! ע��۲���
	/*!
		\param type ֪ͨ������, �ɾ���ϵͳ����
		\param observer Ҫ��ӵĹ۲���
	*/
	virtual void RegisterObserver(const char* type, Ix_ChangeObserver* observer) = 0;

	//! ע���۲���
	/*!
		\param type ֪ͨ������, �ɾ���ϵͳ����
		\param observer Ҫȥ���Ĺ۲���
	*/
	virtual void UnRegisterObserver(const char* type, Ix_ChangeObserver* observer) = 0;

	//! ��һ��۲��߹㲥�ı�֪ͨ
	/*!
		\param type ֪ͨ������, �ɾ���ϵͳ����
		\param data ֪ͨ������һ��Ϊһ���ֲ������ĵ�ַ
	*/
	virtual void ChangeNotify(const char* type, ChangeNotifyData* data) = 0;
};

#endif // X3_OBSERVER_ICHANGEMANAGER_H_
