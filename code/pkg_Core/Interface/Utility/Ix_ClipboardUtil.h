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

/*! \file Ix_ClipboardUtil.h
 *  \brief ������ʵ�ò����Ľӿ� Ix_ClipboardUtil
 *  \author Zhang Yun Gui, C++ Plugin Framework
 *  \date   2010.10.22
 */
#ifndef X3_UTIL_ICLIPBOARDUTIL_H_
#define X3_UTIL_ICLIPBOARDUTIL_H_

#include <Ix_Object.h>

const XCLSID CLSID_ClipboardUtil("fc957aed-3c48-461e-b9b8-6ff255f2e71d");

//! ������ʵ�ò����ĵ�ʵ���ӿ�
/*!
	\interface Ix_ClipboardUtil
	\ingroup _GROUP_UTILITY_
	\see CLSID_ClipboardUtil
*/
interface Ix_ClipboardUtil
{
	//! �������ı����Ƶ�������
	/*!
		\param wndOwner ��ǰ���ھ��������������������
		\param text Ҫ���Ƶ��ı����ǿ�
		\return �Ƿ������ı�
	*/
	virtual bool CopyText(HWND wndOwner, const std::wstring& text) = 0;

	//! �Ӽ������ȡ�ı�����
	/*!
		\param[in] wndOwner ��ǰ���ھ��
		\param[out] text Ҫ�����ı�
		\param[in] clear ��ȡ�ı��Ƿ��������������
		\return �Ƿ������ı�
	*/
	virtual bool PasteText(HWND wndOwner, std::wstring& text, bool clear = false) = 0;

	//! �����Ƿ����ճ���ı�
	virtual bool CanPasteText() = 0;
};

#endif // X3_UTIL_ICLIPBOARDUTIL_H_
