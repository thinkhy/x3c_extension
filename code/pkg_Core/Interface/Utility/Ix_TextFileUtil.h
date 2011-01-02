/*! \file Ix_TextFileUtil.h
 *  \brief �����ı��ļ���д�����Ľӿ� Ix_TextFileUtil
 *  \author Zhang Yun Gui, C++ Plugin Framework
 *  \date   2010.11.4
 */
#ifndef X3_UTIL_ITEXTFILEUTIL_H_
#define X3_UTIL_ITEXTFILEUTIL_H_
#pragma once

#include <ClsID_TextUtil.h>

//! �ı��ļ���д�����Ľӿ�
/*!
	\interface Ix_TextFileUtil
	\ingroup _GROUP_UTILITY_
	\see CLSID_TextUtil, TextFileUtil()
*/
interface Ix_TextFileUtil
{
	//! ��ȡһ���ı��ļ�
	/*!
		\param[out] content ��ȡ��������
		\param[in] filename �ļ�ȫ��
		\param[in] limitMB �ļ��������ޣ���λΪMB��������ض�
		\param[in] codepage ����ļ���ǰ��ANSI���룬��ָ�������ֱ��룬
			���� CP_UTF8 ��ʾUTF-8��ʽ���룬Ĭ��ΪCP_ACP
		\return �Ƿ�ȡ��������
		\see GetLineCount, SaveTextFile
	*/
	virtual bool ReadTextFile(std::wstring& content, 
		const std::wstring& filename, 
		ULONG limitMB = 16, UINT codepage = CP_ACP) = 0;

	//! ��һ�����ַ������ݱ��浽�ļ���
	/*!
		\param content Ҫ���������
		\param filename �ļ�ȫ��
		\param utf16 �ļ������ʽ, true: UTF16, false: ANSI/ASCII
		\param codepage ���Ҫ����ΪANSI�����ļ�����ָ�������ֱ��룬
			���� CP_UTF8 ��ʾUTF-8��ʽ���룬Ĭ��ΪCP_ACP
		\return �Ƿ񱣴�ɹ�
		\see ReadTextFile
	*/
	virtual bool SaveTextFile(const std::wstring& content, 
		const std::wstring& filename, 
		bool utf16 = true, UINT codepage = CP_ACP) = 0;

	//! ��һ��ANSI�ַ������ݱ��浽�ļ���
	/*!
		\param content Ҫ���������
		\param filename �ļ�ȫ��
		\param utf16 �ļ������ʽ, true: UTF16, false: ANSI/ASCII
		\param codepage ���Ҫ����ΪUNICODE�����ļ�(UTF16)����ָ������
			��content�����ֱ��룬���� CP_UTF8 ��ʾUTF-8��ʽ���룬Ĭ��ΪCP_ACP
		\return �Ƿ񱣴�ɹ�
	*/
	virtual bool SaveTextFile(const std::string& content, 
		const std::wstring& filename, 
		bool utf16 = true, UINT codepage = CP_ACP) = 0;

	//! ���һ���ļ��Ƿ�ΪUNICODE�ļ�
	/*! ����ļ�ǰ�漸���ַ��Ƿ�ΪFFFE���� UTF-16 (little-endian)
		\param[in] filename �ļ�ȫ��
		\param[out] utf16 �ļ������ʽ, true: UTF16, false: ANSI/ASCII
		\return �Ƿ���ɹ�
	*/
	virtual bool IsUTF16File(const std::wstring& filename, bool& utf16) = 0;

	//! ���һ���ļ��Ƿ�ΪUTF8��ANSI��ʽ�ļ�
	/*! ����ļ�ǰ�漸���ַ��Ƿ�ΪEFBBBF���� UTF-8
		\param[in] filename �ļ�ȫ��
		\param[out] utf8 �ļ������ʽ�Ƿ�ΪUTF8
		\return �Ƿ���ɹ�
	*/
	virtual bool IsUTF8File(const std::wstring& filename, bool& utf8) = 0;

	//! �����UTF16�ļ���ת��Ϊָ�������ANSI�����ļ�
	/*!
		\param filename �ļ�ȫ��
		\param codepage Ҫ����Ϊ���ֱ����ANSI�����ļ���
			���� CP_UTF8 ��ʾUTF-8��ʽ���룬Ĭ��ΪCP_ACP
		\return �Ƿ�ִ�гɹ�
	*/
	virtual bool UnicodeToAnsi(const std::wstring& filename, UINT codepage = CP_ACP) = 0;

	//! �����ANSI�����ļ���ת��ΪUTF16�ļ�
	/*!
		\param filename �ļ�ȫ��
		\param codepage ����ļ���ǰ��ANSI���룬��ָ�������ֱ��룬
			���� CP_UTF8 ��ʾUTF-8��ʽ���룬Ĭ��ΪCP_ACP
		\return �Ƿ�ִ�гɹ�
	*/
	virtual bool AnsiToUnicode(const std::wstring& filename, UINT codepage = CP_ACP) = 0;

	//! �õ��ı����ݵ�����
	virtual long GetLineCount(const std::wstring& text) = 0;

	//! �õ��ı����ݵ�һ������
	/*!
		\param[in] text �ı�����
		\param[in] line �кţ�0��ʾ��һ��
		\param[out] nextLine �����һ������(����NULL)����ʼ��ַ��ΪNULL�����
		\return ���кŶ�Ӧ��һ������
		\see ReadTextFile
	*/
	virtual std::wstring GetLine(const std::wstring& text, 
		long line, LPCWSTR* nextLine = NULL) = 0;

	//! �����Ƿ�Ϊ�հ������У��ɰ�ǿո�ȫ�ǿո񡢻��з���ɣ�
	virtual bool IsSpaceLine(const std::wstring& text) = 0;
};

//! �õ��ı�ת����������
/*!
	\ingroup _GROUP_UTILITY_
*/
inline Cx_Interface<Ix_TextFileUtil> TextFileUtil()
{
	Cx_Interface<Ix_TextFileUtil> pIFUtility(CLSID_TextUtil);
	ASSERT(pIFUtility.IsNotNull());
	return pIFUtility;
}

#endif // X3_UTIL_ITEXTFILEUTIL_H_
