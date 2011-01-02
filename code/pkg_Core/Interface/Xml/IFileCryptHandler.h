/*! \file IFileCryptHandler.h
 *  \brief �����ļ����ݼӽ��ܵĽӿ� IFileCryptHandler
 *  \author Zhang Yun Gui, C++ Plugin Framework
 *  \date   2010.10.22
 */
#ifndef X3_IFILECRYPTHANDLER_H_
#define X3_IFILECRYPTHANDLER_H_
#pragma once

//! �ļ����ݼӽ��ܵĽӿ�
interface IFileCryptHandler
{
	//! ��һ�������ļ��еõ��ļ�����
	/*!
		\param[in] filename �Ѽ����ļ����ļ�ȫ��
		\param[out] buffer ����ļ����ݣ��� FreeBuffer �ͷ�
		\return S_OK ��ʾִ�гɹ��������ʾʧ��
	*/
	virtual HRESULT Decrypt(LPCWSTR filename, LPWSTR* buffer) = 0;

	//! �ͷ��� Decrypt ������ڴ���Դ
	virtual void FreeBuffer(LPWSTR buffer) = 0;

	//! ��һ���������ݵ��ļ����м���
	/*! 
		\param srcfile ���������ļ����ļ�ȫ��
		\param destfile �����ļ����ļ�ȫ��
		\return S_OK ��ʾִ�гɹ��������ʾʧ��
	*/
	virtual HRESULT CryptFile(LPCWSTR srcfile, LPCWSTR destfile) = 0;
};

#endif // X3_IFILECRYPTHANDLER_H_
