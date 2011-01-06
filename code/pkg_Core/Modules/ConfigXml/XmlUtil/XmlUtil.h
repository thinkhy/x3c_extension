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

//! \file XmlUtil.h
//! \brief ����MSXML4.0 DOM ������CXmlUtil

#ifndef __XMLUTIL_NONMFC_INCLUDED_
#define __XMLUTIL_NONMFC_INCLUDED_
#pragma once

#include "XTPXMLhelpers.h"

//! XML�ļ��ӽ��ܵĽӿ�
interface IXmlFileCrypt
{
	//! װ��һ�����ܵ�XML�ļ�
	/*! 
		\param[out] doc ����µ�XML�ĵ�����
		\param[in] pszFileName �ļ�ȫ���������������XML���ݵ�URL��ַ
		\return �Ƿ�װ�سɹ������ʧ�ܽ���CXmlUtil����ͨ��ʽװ��
	*/
	virtual bool Decrypt(CXTPDOMDocumentPtr& doc, LPCWSTR pszFileName) = 0;

	//! ��һ���ձ����XML�ļ����м���
	/*! 
		\param[in] pszFileName ���ص��ļ�ȫ��
		\return �Ƿ�ִ�гɹ�
	*/
	virtual bool CryptFile(LPCWSTR pszFileName) = 0;
};

//! MSXML4.0 DOM ������, ����ҪMFC֧��
class CXmlUtil
{
public:
	
//--------------------------------------
// �ļ�����
//--------------------------------------
	
	//! ����һ��XML�ĵ�����
	/*! �´�����XML�ĵ�����δ���浽�ļ���
		\param[out] doc ����µ�XML�ĵ�����
		\param[in] pszRootName ���ڵ����ƣ������Զ��������ڵ�
		\param[in] pszEncoding XML���Ա��룬Ĭ��ΪUnicode��ʽ�ġ�UTF-8��
		\param[in] pszNameSpace XML�����ռ�
		\param[in] pszComment ���ڵ��˵������
		\return �Ƿ񴴽��ɹ�
	*/
	static bool NewXMLFile(
		CXTPDOMDocumentPtr& doc, 
		LPCWSTR pszRootName, 
		LPCWSTR pszEncoding = L"UTF-8", 
		LPCWSTR pszNameSpace = L"", 
		LPCWSTR pszComment = L"");
	
	//! ����һ��XML�ĵ����󣬲��õ����ڵ�
	/*! �´�����XML�ĵ�����δ���浽�ļ���
		\param[out] doc ����µ�XML�ĵ�����
		\param[in] root ������ڵ����
		\param[in] pszRootName ���ڵ����ƣ������Զ��������ڵ�
		\param[in] pszEncoding XML���Ա��룬Ĭ��ΪUnicode��ʽ�ġ�UTF-8��
		\param[in] pszNameSpace XML�����ռ�
		\return �Ƿ񴴽��ɹ�
	*/
	static bool NewXMLFile2(
		CXTPDOMDocumentPtr& doc, 
		CXTPDOMElementPtr& root, 
		LPCWSTR pszRootName, 
		LPCWSTR pszEncoding = L"UTF-8", 
		LPCWSTR pszNameSpace = L"");
	
	//! װ��һ��XML�ļ�
	/*! 
		\param[out] doc ����µ�XML�ĵ�����
		\param[in] pszFileName �ļ�ȫ���������������XML���ݵ�URL��ַ
		\param[in] pCryptHandler �ӽ��ܵĲ�������
		\return �Ƿ�װ�سɹ���ʧ��ԭ���ǲ��ܶ�ȡ�ļ����ܴ���XML�ĵ�����
	*/
	static bool LoadXMLFile(
		CXTPDOMDocumentPtr& doc, 
		LPCWSTR pszFileName, 
		IXmlFileCrypt* pCryptHandler = NULL);
	
	//! װ��һ��XML�ļ����������ڵ�
	/*! 
		\param[out] doc ����µ�XML�ĵ�����
		\param[in] pszFileName �ļ�ȫ���������������XML���ݵ�URL��ַ
		\param[in] root ������ڵ����
		\param[in] pszRootName ���ڵ�����
		\param[in] pCryptHandler �ӽ��ܵĲ�������
		\return �Ƿ�װ�سɹ���ʧ��ԭ���ǲ�����ָ���ĸ��ڵ�ȴ���
	*/
	static bool LoadXMLFile(
		CXTPDOMDocumentPtr& doc, 
		LPCWSTR pszFileName, 
		CXTPDOMElementPtr& root, 
		LPCWSTR pszRootName, 
		IXmlFileCrypt* pCryptHandler = NULL);
	
	//! ���浽һ��XML�ļ�
	/*! 
		\param[in] doc Ҫ�����XML�ĵ�����
		\param[in] pszFileName �ļ�ȫ��
		\param[in] pCryptHandler �ӽ��ܵĲ�������
		\return �Ƿ񱣴�ɹ�
	*/
	static bool SaveXMLFile(
		const CXTPDOMDocumentPtr& doc, 
		LPCWSTR pszFileName, 
		IXmlFileCrypt* pCryptHandler = NULL);
	
	//! ���ַ�����װ��XML�ļ�
	/*! 
		\param[out] doc ����´�����XML�ĵ�����
		\param[in] pszXML XML��ʽ���ַ���
		\return �Ƿ�װ�سɹ�
	*/
	static bool LoadXMLFromString(
		CXTPDOMDocumentPtr& doc, 
		LPCSTR pszXML);

	//! ���ַ�����װ��XML�ļ����Զ�����Unicodeǰ׺��־
	/*! 
		\param[out] doc ����´�����XML�ĵ�����
		\param[in] pszXML XML��ʽ���ַ���
		\return �Ƿ�װ�سɹ�
	*/
	static bool LoadXMLFromString(
		CXTPDOMDocumentPtr& doc, 
		LPCWSTR pszXML);
	
	//! ��ȡXML�ַ���
	/*! 
		\param[in] doc XML�ĵ�����
		\return XML��ʽ���ַ���
		\see GetNodeXMLString
	*/
	static std::wstring GetXMLString(
		const CXTPDOMDocumentPtr& doc);

	//! ��ȡ���ڵ�����
	/*! 
		\param[in] doc XML�ĵ�����
		\return ���ڵ�����
		\see GetTagName
	*/
	static std::wstring GetRootName(
		const CXTPDOMDocumentPtr& doc);
	
//--------------------------------------
// �ڵ����
//--------------------------------------
	
	//! �õ����ڵ�
	/*! 
		\param[out] root ���XML���ڵ����
		\param[in] doc XML�ĵ�����
		\param[in] pszRootName ���ڵ�����
		\return �Ƿ���ڸ������Ƶĸ��ڵ�
		\see GetRootName
	*/
	static bool GetRoot(
		CXTPDOMElementPtr& root, 
		const CXTPDOMDocumentPtr& doc, 
		LPCWSTR pszRootName);
	
	//! �õ��ӽڵ����
	/*! 
		\param[in] ele XMLԪ�ض���
		\param[in] pszChildName ��Ԫ������
		\return ����Ԫ��ele�µ�����ΪpszChildName���ӽڵ����
	*/
	static long GetChildCount(
		const CXTPDOMElementPtr& ele, 
		LPCWSTR pszChildName);
	
	//! �õ�һ���ӽڵ�
	/*! 
		\param[out] outEle �����Ԫ�ض���
		\param[in] parent XMLԪ�ض���
		\param[in] pszChildName ��Ԫ������
		\param[in] nIndex �ڼ�����Ԫ�أ���0��ʼ
		\return �Ƿ��ж�Ӧ����Ԫ�ض���
	*/
	static bool GetChild(
		CXTPDOMElementPtr& outEle, 
		const CXTPDOMElementPtr& parent, 
		LPCWSTR pszChildName, 
		long nIndex = 0);
	
	//! �õ��򴴽�һ���ӽڵ�
	/*! 
		\param[out] outEle �����Ԫ�ض���
		\param[in] doc XML�ĵ�����
		\param[in] parent XMLԪ�ض���
		\param[in] pszChildName ��Ԫ������
		\return �Ƿ�ִ�гɹ�
	*/
	static bool GetChildOrAdd(
		CXTPDOMElementPtr& outEle, 
		const CXTPDOMDocumentPtr& doc, 
		const CXTPDOMElementPtr& parent, 
		LPCWSTR pszChildName);
	
	//! ���һ���ӽڵ�
	/*! 
		\param[out] outEle �����Ԫ�ض���
		\param[in] doc XML�ĵ�����
		\param[in] ele XMLԪ�ض���
		\param[in] pszChildName ��Ԫ������
		\return �Ƿ�ִ�гɹ�
	*/
	static bool AddChild(
		CXTPDOMElementPtr& outEle, 
		const CXTPDOMDocumentPtr& doc, 
		const CXTPDOMElementPtr& ele, 
		LPCWSTR pszChildName);
	
	//! ɾ��һ���ӽڵ�
	/*! 
		\param[in] ele XMLԪ�ض���
		\param[in] pszChildName ��Ԫ������
		\param[in] nIndex Ҫɾ���ڼ�����Ԫ�أ���0��ʼ
		\return �Ƿ��ж�Ӧ����Ԫ�ض���ɾ��
	*/
	static bool DelChild(
		const CXTPDOMElementPtr& ele, 
		LPCWSTR pszChildName, 
		long nIndex);

	//! ɾ��һ���ӽڵ�
	/*! 
		\param[in] parent XML��Ԫ�ض���
		\param[in,out] eleDel Ҫɾ����XML��Ԫ�ض���
		\return �Ƿ��ж�Ӧ����Ԫ�ض���ɾ��
	*/
	static bool DelChild(
		const CXTPDOMElementPtr& parent, 
		CXTPDOMElementPtr& eleDel);
	
	//! ɾ�������ӽڵ�
	/*! ɾ������Ԫ���µ���������ΪpszChildName���ӽڵ�
		\param[in] ele XMLԪ�ض���
		\param[in] pszChildName ��Ԫ������
		\param[in] pszAttrName ��Ԫ�صı�ʶ����������ѡֵ
		\param[in] pszAttrValue ��ʶ��������Ӧ��ֵ��pszAttrName��Ϊ��ʱ��Ч
		\return ɾ������Ԫ�ظ���
	*/
	static long DelChildren(
		const CXTPDOMElementPtr& ele, 
		LPCWSTR pszChildName, 
		LPCWSTR pszAttrName = L"", LPCWSTR pszAttrValue = L"");
	
	//! ���ҽڵ������е��ӽڵ����
	/*! 
		\param[out] outEle ������ҵ�����Ԫ�ض���
		\param[in] parent XMLԪ�ض����ڸýڵ��²���
		\param[in] pszElement ��Ԫ������
		\param[in] pszField ��Ԫ�ص���һ��Ԫ������
		\param[in] pszValue ��Ԫ�ص���һ��Ԫ�ص�����
		\return �ҵ����ǵڼ�����Ԫ�أ�-1��ʾ�Ҳ���
	*/
	static long FindElement(
		CXTPDOMElementPtr& outEle, 
		const CXTPDOMElementPtr& parent, 
		LPCWSTR pszElement, 
		LPCWSTR pszField, 
		LPCWSTR pszValue);
	
	//! ���ҽڵ������е��ӽڵ����
	/*! ����Ԫ��parent����Ԫ�ؽڵ㣬�����Ǹ���Ԫ����������ΪpszAttr1��
		����ΪpszValue1�����Խڵ㣬��������������������\n
		��������������ʾ����\n
		��\<parent_item\>\n
		������\<item id="12" type="font" other=""\>\<otherinfo/\>\</item\>\n
		������\<item id="34" type="char" other=".."\>\<otherinfo/\>\</item\>\n
		������\<item id="34" type="para" other="info"\>\<otherinfo/\>\</item\>\n
		��\</parent_item\>\n
		����FindElement(outEle, parent, "item", "id", "34", "type", "char")����1
		
		\param[out] outEle ������ҵ�����Ԫ�ض���
		\param[in] parent XMLԪ�ض����ڸýڵ��²���
		\param[in] pszElement ��Ԫ������
		\param[in] pszAttr1 ��Ԫ�ص���������
		\param[in] pszValue1 ��Ԫ�ص�����ֵ
		\param[in] pszAttr2 ��Ԫ�ص���һ���������ƣ�Ϊ�������
		\param[in] pszValue2 ��Ԫ�ص���һ�����Զ�Ӧ��ֵ��pszAttr2��Ϊ��ʱ��Ч
		\return �ҵ����ǵڼ�����Ԫ�أ�-1��ʾ�Ҳ���
	*/
	static long FindElementByAttr(
		CXTPDOMElementPtr& outEle, 
		const CXTPDOMElementPtr& parent, 
		LPCWSTR pszElement, 
		LPCWSTR pszAttr1, 
		LPCWSTR pszValue1, 
		LPCWSTR pszAttr2, 
		LPCWSTR pszValue2);
	
//--------------------------------------
// �ڵ�����
//--------------------------------------

	//! �õ��ڵ������
	/*! 
		\param[in] ele XMLԪ�ض���
		\return �����ڵ��XML�������
		\see GetRootName
	*/
	static std::wstring GetTagName(
		const CXTPDOMElementPtr& ele);
	
	//! �õ��ڵ����ݣ�ʶ��CDATA
	/*! �ڵ�����ݼȿ����Ǽ򵥵��������ݣ�Ҳ������CDATA�ڵ�
		\param[in] pNode XMLԪ�ض���
		\param[in] pszDefault �ڵ����ݵ�Ĭ��ֵ
		\return �����ڵ������
	*/
	static std::wstring GetText(
		const CXTPDOMNodePtr& pNode, 
		LPCWSTR pszDefault = L"");

	//! �õ�һ���ڵ��CDATAֵ
	/*! 
		\param[in] ele XMLԪ�ض���
		\param[in] pszDefault �ڵ��CDATA���ݵ�Ĭ��ֵ
		\return �ýڵ��CDATA����
	*/
	static std::wstring GetTextCDATA(
		const CXTPDOMElementPtr& ele, 
		LPCWSTR pszDefault = L"");
	
	//! ���ýڵ�����
	/*! 
		\param[in] pNode XMLԪ�ض���
		\param[in] pszText �����ڵ������
		\return �Ƿ����óɹ�
	*/
	static bool SetText(
		const CXTPDOMNodePtr& pNode, 
		LPCWSTR pszText);
	
	//! ���ýڵ�����
	/*! 
		���������ڲ����Ƿ�����_UNICODE��������꣬����ֱ�����ÿ��ֽ��ַ������ݣ�
		������ANSI����ģʽ�½�LPCWSTRת��ΪBSTRʱ�Զ����б���ת�����������롣

		ʹ������������ӷ�UNICODE�ı��ļ��ж�ȡ���ֽ��ַ�������MultiByteToWideChar
		����ת��Ϊ���ֽ��ַ��������ñ��������ýڵ����ݣ��������ܽ��ض����Ա����
		����ת��ΪUNICODE��XML���ݡ�

		\param[in] pNode XMLԪ�ض���
		\param[in] pszText �����ڵ��UNICODE���ݣ�ĩβ���������
		\return �Ƿ����óɹ�
	*/
	static bool SetTextW(
		const CXTPDOMNodePtr& pNode, 
		LPCWSTR pszText);

	//! ����һ���ڵ��CDATAֵ
	/*! 
		\param[in] doc XML�ĵ�����
		\param[in] ele XMLԪ�ض���
		\param[in] pszValue �ڵ��CDATA����
		\return �Ƿ����óɹ�
	*/
	static bool SetTextCDATA(
		const CXTPDOMDocumentPtr& doc, 
		const CXTPDOMElementPtr& ele, 
		LPCWSTR pszValue);

	//! ��ȡһ���ڵ��XML�ַ���
	/*! 
		\param[in] ele XMLԪ�ض���
		\return XML�ַ���
		\see GetXMLString
	*/
	static std::wstring GetNodeXMLString(
		const CXTPDOMElementPtr& ele);

//--------------------------------------
// ���Բ���
//--------------------------------------

	//! ɾ��һ������
	/*! 
		\param[in] ele XMLԪ�ض���
		\param[in] pszName Ҫɾ������������
		\return �Ƿ�ɾ��������
	*/
	static bool DelAttribute(
		const CXTPDOMElementPtr& ele, 
		LPCWSTR pszName);
	
	//! �õ�һ�����Խڵ�����
	/*! 
		\param[in] ele XMLԪ�ض���
		\param[in] pszName ��Ԫ�ص����Խڵ�����
		\param[in] pszDefault �������ݵ�Ĭ��ֵ
		\return ��Ԫ�ص���������
	*/
	static std::wstring GetAttribute(
		const CXTPDOMElementPtr& ele, 
		LPCWSTR pszName, 
		LPCWSTR pszDefault = L"");
	
	//! �õ�һ�����Խڵ���������
	/*! 
		\param[in] ele XMLԪ�ض���
		\param[in] pszName ��Ԫ�ص����Խڵ�����
		\param[in] nDef �������ݵ�Ĭ������ֵ
		\return ��Ԫ�ص�������������ֵ
	*/
	static UINT GetAttributeInt(
		const CXTPDOMElementPtr& ele, 
		LPCWSTR pszName, 
		INT nDef = 0);
	
	//! �õ�һ�����Խڵ㲼��ֵ����
	/*! 
		\param[in] ele XMLԪ�ض���
		\param[in] pszName ��Ԫ�ص����Խڵ�����
		\param[in] bDef �������ݵ�Ĭ�ϲ���ֵ
		\return ��Ԫ�ص��������ݲ���ֵ
	*/
	static bool GetAttributeBool(
		const CXTPDOMElementPtr& ele, 
		LPCWSTR pszName, 
		BOOL bDef = FALSE);
	
	//! �õ�һ�����Խڵ㸡��������
	/*! 
		\param[in] ele XMLԪ�ض���
		\param[in] pszName ��Ԫ�ص����Խڵ�����
		\param[in] dDef �������ݵ�Ĭ�ϸ�����ֵ
		\param[out] pstrUnit ������������ַ��������������β���ĵĵ�λ����
		\return ��Ԫ�ص��������ݸ�����ֵ
	*/
	static double GetAttributeFloat(
		const CXTPDOMElementPtr& ele, 
		LPCWSTR pszName, 
		double dDef = 0, 
		std::wstring* pstrUnit = NULL);
	
	//! ����һ�����Խڵ�����
	/*! 
		\param[in] doc XML�ĵ�����
		\param[in] ele XMLԪ�ض���
		\param[in] pszName ��Ԫ�ص����Խڵ����ƣ�û�����Զ��������Խڵ�
		\param[in] pszValue ��������
		\return �Ƿ����óɹ�
	*/
	static bool SetAttribute(
		const CXTPDOMDocumentPtr& doc, 
		const CXTPDOMElementPtr& ele, 
		LPCWSTR pszName, 
		LPCWSTR pszValue);
	
	//! ����һ�����Խڵ���������
	/*! 
		\param[in] doc XML�ĵ�����
		\param[in] ele XMLԪ�ض���
		\param[in] pszName ��Ԫ�ص����Խڵ����ƣ�û�����Զ��������Խڵ�
		\param[in] nVal ���Ե���������
		\return �Ƿ����óɹ�
	*/
	static bool SetAttributeInt(
		const CXTPDOMDocumentPtr& doc, 
		const CXTPDOMElementPtr& ele, 
		LPCWSTR pszName, 
		INT nVal);
	
	//! ����һ�����Խڵ㲼��ֵ����ֵ
	/*! 
		\param[in] doc XML�ĵ�����
		\param[in] ele XMLԪ�ض���
		\param[in] pszName ��Ԫ�ص����Խڵ����ƣ�û�����Զ��������Խڵ�
		\param[in] bVal ���ԵĲ������ݣ��Զ�ת���ɡ�true����false��
		\return �Ƿ����óɹ�
	*/
	static bool SetAttributeBool(
		const CXTPDOMDocumentPtr& doc, 
		const CXTPDOMElementPtr& ele, 
		LPCWSTR pszName, 
		BOOL bVal);
	
	//! ����һ�����Խڵ㸡��������
	/*! 
		\param[in] doc XML�ĵ�����
		\param[in] ele XMLԪ�ض���
		\param[in] pszName ��Ԫ�ص����Խڵ����ƣ�û�����Զ��������Խڵ�
		\param[in] dVal ���Եĸ���������
		\param[in] pszUnit ����������β�����ӵĵ�λ���ƣ�Ϊ�������
		\param[in] decimal ����С�����ڼ�λ��������������������
		\return �Ƿ����óɹ�
	*/
	static bool SetAttributeFloat(
		const CXTPDOMDocumentPtr& doc, 
		const CXTPDOMElementPtr& ele, 
		LPCWSTR pszName, 
		double dVal, 
		LPCWSTR pszUnit = L"", 
		int decimal = 4);
	
	//! �õ�һ���ڵ������ֵ��ʶ��CDATA
	/*! �ӽڵ�����ݼȿ����Ǽ򵥵��������ݣ�Ҳ������CDATA�ڵ�
		\param[in] ele XMLԪ�ض���
		\param[in] pszFieldName ��Ԫ�ص���Ԫ�ؽڵ�����
		\param[in] pszDefault �ӽڵ����ݵ�Ĭ��ֵ
		\return ���ӽڵ������
	*/
	static std::wstring GetField(
		const CXTPDOMElementPtr& ele, 
		LPCWSTR pszFieldName, 
		LPCWSTR pszDefault = L"");
	
	//! ����һ���ڵ������ֵ
	/*! 
		\param[in] doc XML�ĵ�����
		\param[in] ele XMLԪ�ض���
		\param[in] pszFieldName ��Ԫ�ص���Ԫ�ؽڵ����ƣ�û�����Զ������ڵ�
		\param[in] pszValue �ӽڵ�����
		\return �Ƿ����óɹ�
	*/
	static bool SetField(
		const CXTPDOMDocumentPtr& doc, 
		const CXTPDOMElementPtr& ele, 
		LPCWSTR pszFieldName, 
		LPCWSTR pszValue);
	
	//! �õ�һ���ڵ����������ֵ��ʶ��ʮ��������
	/*! 
		\param[in] ele XMLԪ�ض���
		\param[in] pszFieldName ��Ԫ�ص���Ԫ�ؽڵ�����
		\param[in] nDef �ӽڵ����ݵ�Ĭ������ֵ
		\return ���ӽڵ���������ֵ
	*/
	static UINT GetFieldInt(
		const CXTPDOMElementPtr& ele, 
		LPCWSTR pszFieldName, 
		INT nDef = 0);
	
	//! �õ�һ���ڵ�Ĳ���ֵ����ֵ
	/*! 
		\param[in] ele XMLԪ�ض���
		\param[in] pszFieldName ��Ԫ�ص���Ԫ�ؽڵ�����
		\param[in] bDef �ӽڵ����ݵ�Ĭ�ϲ���ֵ
		\return ���ӽڵ����ݲ���ֵ
	*/
	static bool GetFieldBool(
		const CXTPDOMElementPtr& ele, 
		LPCWSTR pszFieldName, 
		BOOL bDef = FALSE);
	
	//! �õ�һ���ڵ�ĸ���������ֵ
	/*! 
		\param[in] ele XMLԪ�ض���
		\param[in] pszFieldName ��Ԫ�ص���Ԫ�ؽڵ�����
		\param[in] dDef �ӽڵ����ݵ�Ĭ�ϸ�����ֵ
		\param[out] pstrUnit ������������ַ�������ӽڵ�����β���ĵĵ�λ����
		\return ���ӽڵ����ݸ�����ֵ
	*/
	static double GetFieldFloat(
		const CXTPDOMElementPtr& ele, 
		LPCWSTR pszFieldName, 
		double dDef = 0, 
		std::wstring* pstrUnit = NULL);
	
	//! ����һ���ڵ����������ֵ
	/*! 
		\param[in] doc XML�ĵ�����
		\param[in] ele XMLԪ�ض���
		\param[in] pszFieldName ��Ԫ�ص���Ԫ�ؽڵ����ƣ�û�����Զ������ڵ�
		\param[in] nVal �ӽڵ����������
		\return �Ƿ����óɹ�
	*/
	static bool SetFieldInt(
		const CXTPDOMDocumentPtr& doc, 
		const CXTPDOMElementPtr& ele, 
		LPCWSTR pszFieldName, 
		INT nVal);
	
	//! ����һ���ڵ�Ĳ���ֵ����ֵ
	/*! 
		\param[in] doc XML�ĵ�����
		\param[in] ele XMLԪ�ض���
		\param[in] pszFieldName ��Ԫ�ص���Ԫ�ؽڵ����ƣ�û�����Զ������ڵ�
		\param[in] bVal �ӽڵ�Ĳ������ݣ��Զ�ת���ɡ�true����false��
		\return �Ƿ����óɹ�
	*/
	static bool SetFieldBool(
		const CXTPDOMDocumentPtr& doc, 
		const CXTPDOMElementPtr& ele, 
		LPCWSTR pszFieldName, 
		BOOL bVal);
	
	//! ����һ���ڵ�ĸ���������ֵ
	/*! 
		\param[in] doc XML�ĵ�����
		\param[in] ele XMLԪ�ض���
		\param[in] pszFieldName ��Ԫ�ص���Ԫ�ؽڵ����ƣ�û�����Զ������ڵ�
		\param[in] dVal �ӽڵ�ĸ���������
		\param[in] pszUnit ���ӽڵ�����β�����ӵĵ�λ���ƣ�Ϊ�������
		\param[in] decimal ����С�����ڼ�λ��������������������
		\return �Ƿ����óɹ�
	*/
	static bool SetFieldFloat(
		const CXTPDOMDocumentPtr& doc, 
		const CXTPDOMElementPtr& ele, 
		LPCWSTR pszFieldName, 
		double dVal, 
		LPCWSTR pszUnit = L"", 
		int decimal = 4);
	
	//! ����һ���ڵ��ʮ����������ֵ
	/*! 
		\param[in] doc XML�ĵ�����
		\param[in] ele XMLԪ�ض���
		\param[in] pszFieldName ��Ԫ�ص���Ԫ�ؽڵ����ƣ�û�����Զ������ڵ�
		\param[in] nVal �ӽڵ����������
		\param[in] nDigits ��Ϊ1��6ʱ�������ַ���������ָ�������֣���������ǰ���㣬����"0x00012A"
		\return �Ƿ����óɹ�
	*/
	static bool SetFieldHex(
		const CXTPDOMDocumentPtr& doc, 
		const CXTPDOMElementPtr& ele, 
		LPCWSTR pszFieldName, 
		INT nVal, 
		INT nDigits = 0);
	
	//! �õ�һ���ڵ��CDATA����ֵ
	/*! 
		\param[in] ele XMLԪ�ض���
		\param[in] pszFieldName ��Ԫ�ص���Ԫ�ؽڵ�����
		\param[in] pszDefault �ӽڵ��CDATA���ݵ�Ĭ��ֵ
		\return ���ӽڵ��CDATA����
	*/
	static std::wstring GetFieldCDATA(
		const CXTPDOMElementPtr& ele, 
		LPCWSTR pszFieldName, 
		LPCWSTR pszDefault = L"");
	
	//! ����һ���ڵ��CDATA����ֵ
	/*! 
		\param[in] doc XML�ĵ�����
		\param[in] ele XMLԪ�ض���
		\param[in] pszFieldName ��Ԫ�ص���Ԫ�ؽڵ����ƣ�û�����Զ������ڵ�
		\param[in] pszValue �ӽڵ��CDATA����
		\return �Ƿ����óɹ�
	*/
	static bool SetFieldCDATA(
		const CXTPDOMDocumentPtr& doc, 
		const CXTPDOMElementPtr& ele, 
		LPCWSTR pszFieldName, 
		LPCWSTR pszValue);
	
//--------------------------------------
// ��������
//--------------------------------------

	//! �����ϴε��õ�HRESULTֵ
	static HRESULT GetLastErrorResult();

	//! �ڸ��ڵ�ǰ����ע�ͽڵ�
	/*! 
		\param[in] doc XML�ĵ�����
		\param[in] pszComment ע������
		\return �Ƿ�ִ�гɹ�
	*/
	static bool CreateDocComment(
		const CXTPDOMDocumentPtr& doc, 
		LPCWSTR pszComment);

	//! ��ָ���ڵ�ǰ����ע�ͽڵ�
	/*! 
		\param[in] doc XML�ĵ�����
		\param[in] ele XMLԪ�ض���
		\param[in] pszComment ע������
		\return �Ƿ�ִ�гɹ�
	*/
	static bool CreateNodeComment(
		const CXTPDOMDocumentPtr& doc, 
		const CXTPDOMElementPtr& ele, 
		LPCWSTR pszComment);

	//! �õ�����������ַ�����ȥ��С�����ĩβ��'0'��
	/*! 
		\param[in] value Ҫת���ĸ�����
		\param[in] decimal ����С�����ڼ�λ��������������������
		\return ת������ַ���
	*/
	static std::wstring RoundStr(
		double value, 
		int decimal = 4);
};

#endif // __XMLUTIL_NONMFC_INCLUDED_