/*! \file Ix_ChangeObserver.h
 *  \brief ����ı�֪ͨ�۲��ߵĽӿ� Ix_ChangeObserver
 *  \author Zhang Yun Gui, C++ Plugin Framework
 *  \date   2010.10.22
 */
#ifndef X3_OBSERVER_ICHANGEOBSERVER_H_
#define X3_OBSERVER_ICHANGEOBSERVER_H_
#pragma once

class ChangeNotifyData;

//! �ı�֪ͨ�۲��ߵĽӿ�
/*!
	\interface Ix_ChangeObserver
	\ingroup _GROUP_CHANGE_OBSERVER_
*/
interface Ix_ChangeObserver
{
	//! �ı��֪ͨ
	/*!
		\param data ֪ͨ������һ��Ϊһ���ֲ������ĵ�ַ
	*/
	virtual void Update(ChangeNotifyData* data) = 0;
};

#endif // X3_OBSERVER_ICHANGEOBSERVER_H_
