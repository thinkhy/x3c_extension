/*! \file Ix_FileVersion.h
 *  \brief ������ʱĿ¼�����Ľӿ� Ix_FileVersion
 *  \author Zhang Yun Gui, C++ Plugin Framework
 *  \date   2010.12.28
 */
#ifndef X3_UTIL_IFILEVERSION_H_
#define X3_UTIL_IFILEVERSION_H_
#pragma once

//! ��ȡ�ļ��汾�ŵĽӿ�
/*!
	\interface Ix_FileVersion
	\ingroup _GROUP_UTILITY_
	\see CLSID_FileUtility, FileUtility()
*/
interface Ix_FileVersion
{
	//! ��ȡģ����ļ��汾��
	/*!
		\param[out] version ���汾�ţ����硰1.0.12.0��
		\param[in] filename DLL��EXE���ļ�ȫ��
		\return �Ƿ��ȡ�ɹ�
	*/
	virtual bool GetFileVersion(std::wstring& version, const std::wstring& filename) = 0;

	//! ��ȡģ����ļ��汾��
	/*!
		\param[out] ver1 ���汾�ŵ����汾�����硰1.2.3.0����1
		\param[out] ver2 ���汾�ŵĴΰ汾�����硰1.2.3.0����2
		\param[out] ver3 ���汾�ŵĵ���λ�����硰1.2.3.0����3
		\param[out] ver4 ���汾�ŵĵ���λ�����硰1.2.3.0����0
		\param[in] filename DLL��EXE���ļ�ȫ��
		\return �Ƿ��ȡ�ɹ�
	*/
	virtual bool GetFileVersion(WORD& ver1, WORD& ver2, 
		WORD& ver3, WORD& ver4, const std::wstring& filename) = 0;

	//! ��ȡģ����ļ�˵��
	/*!
		\param[out] description ����ļ�˵��
		\param[in] filename DLL��EXE���ļ�ȫ��
		\return �Ƿ��ȡ�ɹ�
	*/
	virtual bool GetFileDescription(std::wstring& description, const std::wstring& filename) = 0;
};

#endif // X3_UTIL_IFILEVERSION_H_
