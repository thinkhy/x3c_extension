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

/*! \file Ix_StringTable.h
 *  \brief ���屾�ػ��ַ�����Ľӿ� Ix_StringTable
 *  \author Zhang Yun Gui, C++ Plugin Framework
 *  \date   2010.10.28
 */
#ifndef X3_XML_ISTRINGTABLE_H_
#define X3_XML_ISTRINGTABLE_H_

const XCLSID CLSID_StringTable("b8c36b29-59c3-4db2-be43-fd4982e6e71d");

//! ���ػ��ַ�����Ľӿ�
/*! ���ػ��ַ���XML�ļ������������Ŀ¼�� Translations/Strings Ŀ¼��
	\interface Ix_StringTable
	\ingroup _GROUP_PLUGIN_XML_
	\see CLSID_StringTable
*/
interface Ix_StringTable
{
	//! �õ�һ��ģ���ָ��ID���ƶ�Ӧ���ַ���ֵ
	/*!
		\param[out] value ʵ���ַ���ֵ
		\param[in] name ����ģ������ID���Ƶı�ʶ������ʽΪ��@��ͷ���ϡ�Module:IDS_XXX��
		\param[out] module ���name�е�ģ����
		\param[out] id ���name�еĴ�ID����
		\return �Ƿ��ȡ���ǿ�ֵ
	*/
	virtual bool GetValue(std::wstring& value, const std::wstring& name, 
		std::wstring& module, std::wstring& id) = 0;

	//! �õ�һ��ģ���ָ��ID���ƶ�Ӧ���ַ���ֵ
	/*!
		\param[out] value ʵ���ַ���ֵ
		\param[in] module ģ����
		\param[in] id ��ID����
		\return �Ƿ��ȡ���ǿ�ֵ
	*/
	virtual bool GetValue(std::wstring& value, 
		const std::wstring& module, const std::wstring& id) = 0;

	//! ����ָ��Ŀ¼�µ��ַ���XML�ļ�
	/*!
		\param path �ַ���XML�ļ�����Ŀ¼�ľ���·��
		\return ���ص��ļ���
	*/
	virtual long LoadFiles(const std::wstring& path) = 0;

	//! �õ�һ��ģ���ָ��ID���ƶ�Ӧ���ַ���ֵ
	/*!
		\param[in] module ģ����
		\param[in] id ��ID����
		\param[out] hasvalue ����Ƿ��ȡ���ǿ�ֵ��ΪNULL�����
		\return ʵ���ַ���ֵ
	*/
	virtual std::wstring GetValue(const std::wstring& module, 
		const std::wstring& id, bool* hasvalue = NULL) = 0;
};

#ifdef X3_CORE_XCOMPTR_H_
//! �õ�һ��ģ���ָ��ID���ƶ�Ӧ���ַ���ֵ
/*!
	\param[in] module ģ����
	\param[in] id ��ID����
	\param[out] hasvalue ����Ƿ��ȡ���ǿ�ֵ��ΪNULL�����
	\return ʵ���ַ���ֵ���մ���ʾû��ֵ
*/
inline std::wstring GetStringValue(const std::wstring& module, 
	const std::wstring& id, bool* hasvalue = NULL)
{
	Cx_Interface<Ix_StringTable> pIFTable(CLSID_StringTable);
	return pIFTable ? pIFTable->GetValue(module, id, hasvalue) : std::wstring();
}
#endif

#endif // X3_XML_ISTRINGTABLE_H_
