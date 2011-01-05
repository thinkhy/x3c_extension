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

/*! \file Ix_StringConvert.h
 *  \brief �����ı�ת��ʵ�ò����Ľӿ� Ix_StringConvert
 *  \author Zhang Yun Gui, C++ Plugin Framework
 *  \date   2010.12.28
 */
#ifndef X3_UTIL_ISTRINGCONVERT_H_
#define X3_UTIL_ISTRINGCONVERT_H_

#include <ClsID_TextUtil.h>

//! �ı�ת��ʵ�ò����Ľӿ�
/*!
	\interface Ix_StringConvert
	\ingroup _GROUP_UTILITY_
	\see CLSID_TextUtil, StringConvert(), ConvStr.h
*/
interface Ix_StringConvert
{
	//! ȥ���������˵Ŀհ��ַ�����ǿո�ȫ�ǿո񡢻��з���
	/*!
		\param[in,out] text ��ת�����ַ���
		\param[in] targets Ҫȥ���ַ����ַ����ϣ�ΪNULL��ȡΪĬ�ϵĿհ��ַ�
		\return �Ƿ�ı����ı�
	*/
	virtual bool TrimSpace(std::wstring& text, LPCWSTR targets = NULL) = 0;

	//! ȥ�����ֿ�ͷ�Ŀհ��ַ�����ǿո�ȫ�ǿո񡢻��з���
	/*!
		\param[in,out] text ��ת�����ַ���
		\param[in] targets Ҫȥ���ַ����ַ����ϣ�ΪNULL��ȡΪĬ�ϵĿհ��ַ�
		\return �Ƿ�ı����ı�
	*/
	virtual bool TrimLeft(std::wstring& text, LPCWSTR targets = NULL) = 0;

	//! ȥ������ĩβ�Ŀհ��ַ�����ǿո�ȫ�ǿո񡢻��з���
	/*!
		\param[in,out] text ��ת�����ַ���
		\param[in] targets Ҫȥ���ַ����ַ����ϣ�ΪNULL��ȡΪĬ�ϵĿհ��ַ�
		\return �Ƿ�ı����ı�
	*/
	virtual bool TrimRight(std::wstring& text, LPCWSTR targets = NULL) = 0;

	//! ȥ���Ƿ��ַ�
	/*! ȥ��ASCII��С��0x20���ַ����Ʊ�������з��ͻس������⣩
		\param[in,out] text �����ת�����ַ���
		\param[in] targets Ҫȥ���ַ����ַ����ϣ�ΪNULL��ȡΪС��0x20���ַ�
		\return �Ƿ�ı����ı�
	*/
	virtual bool RemoveInvalidChars(std::wstring& text, LPCWSTR targets = NULL) = 0;

	//! �滻�ı������ҵ��������Ӵ��滻Ϊ�µ�����
	/*!
		\param[in,out] text ���滻���ַ���
		\param[in] match ƥ������
		\param[in] newtext ��ƥ�䵽�����ݻ�Ϊ��������
		\return �Ƿ�ı����ı�
	*/
	virtual bool ReplaceAll(std::wstring& text, 
		const std::wstring& match, 
		const std::wstring& newtext) = 0;

	//! ��һ���ı��е��ض��ַ��滻Ϊ��Ӧ�������ַ�
	/*! ��text�в���match�е��κ��ַ������ҵ����ַ��滻Ϊchars�ж�Ӧ��ŵ��ַ�
		\param[in,out] text ���滻���ַ���
		\param[in] match ƥ�����ݣ�ֻҪ�������κ�һ���ַ���ͬ����ƥ��ɹ�
		\param[in] chars Ҫ�滻�ɵ����ַ��ļ��ϣ��ַ��������match��ͬ
		\return �Ƿ�ı����ı�
	*/
	virtual bool ReplaceChar(std::wstring& text, 
		const std::wstring& match, 
		const std::wstring& chars) = 0;

	//! ��ȫ���ַ�ת��Ϊ����ַ�
	/*!
		\param[in,out] text ��ת�����ַ���
		\param[in] punct �Ƿ���ͬ������Ҳһ��ת��
		\return �Ƿ�ı����ı�
	*/
	virtual bool ToDBC(std::wstring& text, bool punct = false) = 0;

	//! UNICODE��ת��ΪANSI��
	/*!
		\param text Ҫת�������ݣ�ΪUNICODE������UTF16����
		\param codepage Ҫ�������ֱ����ANSI���봮��
			���� CP_UTF8 ��ʾUTF-8��ʽ���룬Ĭ��ΪCP_ACP
		\return ANSI���봮
	*/
	virtual std::string ToAnsi(const std::wstring& text, UINT codepage = CP_ACP) = 0;

	//! ANSI��ת��ΪUNICODE��
	/*!
		\param text Ҫת�������ݣ�ΪANSI���������Ϊcodepage
		\param codepage textΪ���ֱ��룬���� CP_UTF8 ��ʾUTF-8��ʽ���룬Ĭ��ΪCP_ACP
		\return UNICODE������UTF16����
	*/
	virtual std::wstring ToUnicode(const std::string& text, UINT codepage = CP_ACP) = 0;
};

//! �õ��ı�ת����������
/*!
	\ingroup _GROUP_UTILITY_
*/
inline Cx_Interface<Ix_StringConvert> StringConvert()
{
	Cx_Interface<Ix_StringConvert> pIFUtility(CLSID_TextUtil);
	ASSERT(pIFUtility.IsNotNull());
	return pIFUtility;
}

#endif // X3_UTIL_ISTRINGCONVERT_H_
