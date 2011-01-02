/*! \file Ix_UIConfig.h
 *  \brief ��������������ݶ�д�ӿ� Ix_UIConfig
 *  \author Zhang Yun Gui, C++ Plugin Framework
 *  \date   2010.11.2
 */
#ifndef X3_VIEW_IUICONFIG_H_
#define X3_VIEW_IUICONFIG_H_
#pragma once

#include <ConfigIOSection.h>

const XCLSID CLSID_UIConfig("4472ba6d-d833-40b9-899f-edc017ec9166");

//! �����������ݶ�д�ӿ�
/*!
	\interface Ix_UIConfig
	\ingroup _GROUP_APPUI_
	\see CLSID_UIConfig
*/
interface Ix_UIConfig
{
	//! ���ؽ����������ݶ��󣬷ǿ�
	virtual Ix_ConfigData* GetUIConfig() = 0;

	//! ����ָ�����ƵĽ������ýڵ�
	virtual CConfigIOSection GetUISection(LPCWSTR name) = 0;

	//! �������ָı��˵���������
	virtual bool Save() = 0;
};

#endif // X3_VIEW_IUICONFIG_H_
