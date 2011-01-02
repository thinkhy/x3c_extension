/*! \file Ix_CreateWnd.h
 *  \brief ���崰�ڴ����Ľӿ� Ix_CreateWnd
 *  \author Zhang Yun Gui, C++ Plugin Framework
 *  \date   2010.10.28
 */
#ifndef X3_VIEW_ICREATEWND_H_
#define X3_VIEW_ICREATEWND_H_
#pragma once

//! ���ڴ����Ľӿ�
/*! ��������� Cx_CreateWnd ��ʵ�ֱ��ӿڣ����������ڴ����Ӵ���ʱ����Ҫ�����Ӵ������ͺ�ϸ�ڡ�
	\interface Ix_CreateWnd
	\ingroup _GROUP_VIEW_
*/
interface Ix_CreateWnd
{
	//! ���ش��ھ��
	virtual HWND GetWindow() const = 0;
	
	//! ��������
	virtual bool CreateWnd(HWND hwndParent, UINT nID) = 0;

	//! ���ٴ���
	virtual void DestroyWnd() = 0;
	
	//! ���� OnCmdMsg ֪ͨ
	virtual BOOL DoCmdMsg(UINT nID, int nCode, void* pExtra, void* pInfo) = 0;

	//! ˢ����ʾ����
	virtual void Refresh() = 0;
};

#endif // X3_VIEW_ICREATEWND_H_
