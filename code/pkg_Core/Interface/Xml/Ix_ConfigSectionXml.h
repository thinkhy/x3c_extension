/*! \file Ix_ConfigSectionXml.h
 *  \brief ����XML���ݽڵ�ӿ� Ix_ConfigSectionXml
 *  \author Zhang Yun Gui, C++ Plugin Framework
 *  \date   2010.10.22
 */
#ifndef X3_XML_ICONFIGSECTIONXML_H_
#define X3_XML_ICONFIGSECTIONXML_H_
#pragma once

//! XML���ݽڵ�ӿ�
/*! XML���ݽڵ�֧�� Ix_ConfigSectionXml �� Ix_ConfigSection �ӿ�
	\interface Ix_ConfigSectionXml
	\ingroup _GROUP_PLUGIN_XML_
	\see Ix_ConfigSection
*/
interface Ix_ConfigSectionXml
{
	//! ����ÿ���������Ƿ�Ϊ��Ԫ����
	/*! Ĭ��ֵΪfalse��ÿ���������Ӧ��һ��XML���ԣ�
		\param element true��ʾÿ��������(���� GetString(L"Name") )Ϊһ��XML��Ԫ���
			false��ʾÿ���������Ӧ��һ��XML����
	*/
	virtual void UseSubElement(bool element) = 0;

	//! �õ�������Ԫ�����֣�����������������
	/*!
		\return �������Ӧ��XML�ڵ���������ݣ�֧��CDATAֵ
	*/
	virtual std::wstring GetText() = 0;

	//! ����������Ԫ�����֣�����������������
	/*!
		\param value �������Ӧ��XML�ڵ����������
		\param cdata ����ΪCDATAֵ������ͨ����
		\return �Ƿ�ı�������
	*/
	virtual bool SetText(LPCWSTR value, bool cdata = false) = 0;

	//! �����ڲ���XMLԪ�ؽڵ�(IXMLDOMElement)
	virtual IUnknown* GetDOMElement(bool addRef = false) = 0;

	//! �����ڲ���XML�ĵ�����(IXMLDOMDocument)
	virtual IUnknown* GetDOMDocument(bool addRef = false) = 0;
};

#endif // X3_XML_ICONFIGSECTIONXML_H_
