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

/*! \file Ix_UIConfig.h
 *  \brief ��������������ݶ�д�ӿ� Ix_UIConfig
 *  \author Zhang Yun Gui, C++ Plugin Framework
 *  \date   2010.11.2
 */
#ifndef X3_VIEW_IUICONFIG_H_
#define X3_VIEW_IUICONFIG_H_

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
