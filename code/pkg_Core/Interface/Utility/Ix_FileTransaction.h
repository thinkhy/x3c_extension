/*! \file Ix_FileTransaction.h
 *  \brief �����ļ�����ʵ�ò����Ľӿ� Ix_FileTransaction
 *  \author Zhang Yun Gui, C++ Plugin Framework
 *  \date   2010.10.22
 */
#ifndef X3_UTIL_IFILETRANSACTION_H_
#define X3_UTIL_IFILETRANSACTION_H_
#pragma once

#include <Ix_Object.h>

const XCLSID CLSID_FileTransaction("66087749-6a2d-40b7-86d9-687664f91e1b");

//! �ļ���������Ľӿ�
/*!
	\interface Ix_FileTransaction
	\ingroup _GROUP_UTILITY_
	\see CLSID_FileTransaction
*/
interface Ix_FileTransaction
{
	//! �ӹ���״̬�ع�����
	virtual void Rollback() = 0;

	//! �õ��������������
	virtual long GetLevel() const = 0;

	//! �����Ƿ����ڻع�����
	virtual bool IsRollbacking() const = 0;

	//! ɾ��һ��Ŀ¼���ļ�
	/*!
		\param filename Ŀ¼���ļ����ļ�ȫ��
		\param recycle true��ʾ�Ž�����վ��false��ʾֱ��ɾ��
		\return �Ƿ���ɾ����Ŀ¼���ļ�. �ļ�ȫ��Ϊ�ջ��ļ��������򷵻�true
	*/
	virtual bool DeletePathFile(LPCWSTR filename, bool recycle = false) = 0;
};

#endif // X3_UTIL_IFILETRANSACTION_H_
