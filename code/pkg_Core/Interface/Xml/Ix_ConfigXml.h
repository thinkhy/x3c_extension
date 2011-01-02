/*! \file Ix_ConfigXml.h
 *  \brief ����XML���ó�ʼ���Ľӿ� Ix_ConfigXml
 *  \author Zhang Yun Gui, C++ Plugin Framework
 *  \date   2010.10.22
 */
#ifndef X3_XML_ICONFIGXML_H_
#define X3_XML_ICONFIGXML_H_
#pragma once

#include <XComPtr.h>

//! XML�������ݶ������ID
const XCLSID CLSID_ConfigXmlFile("c93e1e3d-0362-4856-9a4a-31c119e324f7");

interface Ix_ConfigData;
interface Ix_ConfigSection;
interface IFileCryptHandler;

//! XML�������ݳ�ʼ���Ľӿ�
/*! ʹ�� IFileCryptHandler ������XML�ļ���д����
	\interface Ix_ConfigXml
	\ingroup _GROUP_PLUGIN_XML_
	\see CLSID_ConfigXmlFile, Ix_ConfigData, Ix_ConfigTransaction
*/
interface Ix_ConfigXml
{
	//! �������ù���ӿڶ���
	virtual Ix_ConfigData* GetData() = 0;

	//! ���������ļ�ȫ��
	virtual std::wstring GetFileName() const = 0;

	//! ���������ļ�ȫ��
	/*! ��дXML�ļ�֮ǰ���������ļ�ȫ��
		\param filename �ļ�ȫ����Ҳ������WebService��URL
	*/
	virtual void SetFileName(LPCWSTR filename) = 0;

	//! ����ʵ�ʸ��ڵ�����
	/*! û��װ��XML�ļ�ʱ����ʱ����XML�ļ�
		\return ʵ�ʸ��ڵ����ƣ���û��װ��XML�ļ�ʱ��һ���� SetRootName() �Ľ����ͬ
		\see SetRootName, Reload
	*/
	virtual std::wstring GetRootName() const = 0;

	//! ���ø��ڵ����ƺ�XML���Ա���
	/*!
		\param rootName ���ڵ����ƣ������½�XML���ڶ�ȡXMLʱ���Ϸ��ԣ�
			Ϊ���򲻼��XML���ݵĸ��ڵ�
		\param encoding XML���Ա��룬�½�XML�ļ�ʱʹ��
		\param nmspace XML�����ռ䣬�½�XML�ļ�ʱʹ��
		\see GetRootName, Reload
	*/
	virtual void SetRootName(LPCWSTR rootName = L"root", 
		LPCWSTR encoding = L"UTF-8", 
		LPCWSTR nmspace = L"") = 0;

	//! �������õ�Schema�ļ���λ��
	/*! ��������˸����ԣ������½�XML�ĵ�ʱʹ��
		\param location Schema�ļ���λ�ã�����Ϊ����ļ���
		\see GetRootName, Reload
	*/
	virtual void SetSchemaLocation(LPCWSTR location) = 0;

	//! ����װ��XML�ļ�
	/*! ������ǰXML�ĵ������ݣ�����װ��XML�ĵ���
		������ù� SetRootName() ��������XML���ݵĸ��ڵ㲻ͬ�򷵻�false��
		���û�е��ù� SetRootName()�����Զ�ʶ����ڵ�����
		\return �Ƿ�ɹ�װ��XML�ļ���ʧ��ʱ���½�XML�ĵ�����
	*/
	virtual bool Reload() = 0;

	//! ����XML���ݵ�ָ�����ļ�
	/*! ���������ı��ĵ��Ĵ�����״̬��Ҳ���ܸ�״̬Ӱ��
		\param filename �ļ�ȫ�����մ���ʾʹ�õ�ǰ�ļ�ȫ��
		\return �Ƿ񱣴�ɹ�
	*/
	virtual bool Save(LPCWSTR filename = L"") const = 0;

	//! �õ������ĵ���XML����
	/*! �����δ�½������XML�ļ������Զ����� Reload()
		\param[out] content XML���ݣ�û�С�UTF-8��֮���XML���Ա��벿��
		\return �Ƿ��ȡ�ɹ�
	*/
	virtual bool GetXmlContent(std::wstring& content) const = 0;

	//! װ��XML����
	/*! ������ù� SetRootName() ��������XML���ݵĸ��ڵ㲻ͬ�򷵻�false
		\param content XML���ݣ��Զ�����Unicodeǰ׺��־
		\return �Ƿ�װ�سɹ�
	*/
	virtual bool SetXmlContent(const std::wstring& content) = 0;

	//! �õ�һ���ڵ��XML����
	/*!
		\param[out] content XML���ݣ�û�С�UTF-8��֮���XML���Ա��벿��
		\param[in] node ָ����һ���ڵ�
		\return �Ƿ��ȡ�ɹ�
	*/
	virtual bool GetXmlContent(std::wstring& content, Ix_ConfigSection* node) const = 0;

	//! ����XML�ļ��ӽ��ܵĲ�������
	/*!
		\param[in] handler �µļӽ��ܵĲ�������
		\return ԭ���ļӽ��ܵĲ�������
	*/
	virtual IFileCryptHandler* SetCryptHandler(IFileCryptHandler* handler) = 0;
};

#endif // X3_XML_ICONFIGXML_H_
