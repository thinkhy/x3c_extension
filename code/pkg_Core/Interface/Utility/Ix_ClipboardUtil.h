/*! \file Ix_ClipboardUtil.h
 *  \brief ������ʵ�ò����Ľӿ� Ix_ClipboardUtil
 *  \author Zhang Yun Gui, C++ Plugin Framework
 *  \date   2010.10.22
 */
#ifndef X3_UTIL_ICLIPBOARDUTIL_H_
#define X3_UTIL_ICLIPBOARDUTIL_H_
#pragma once

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
