/*! \file Ix_ConfigData.h
 *  \brief �����������ݽӿ� Ix_ConfigData
 *  \author Zhang Yun Gui, C++ Plugin Framework
 *  \date   2010.10.22
 */
#ifndef X3_XML_ICONFIGDATA_H_
#define X3_XML_ICONFIGDATA_H_
#pragma once

#include "Ix_ConfigSection.h"

//! �������ݽӿ�
/*! ���ӿ������������ݶ����൱��������״��νṹ�е�ȫ�����ݽڵ㣬
	�� CConfigIOSection ���Ӧ��һ�����ݽڵ㡣\n
	���������ʹ�� CConfigTransaction ת��������ͱ��档
	\interface Ix_ConfigData
	\ingroup _GROUP_PLUGIN_XML_
*/
interface Ix_ConfigData
{
	//! һ�����ݽڵ㣬ͬ������ CConfigIOSection
	typedef Cx_Interface<Ix_ConfigSection> ConfigIOSection;

	//! �õ����ڵ��µ�һ�����ݽڵ����
	/*!
		\param name ���ݽڵ����ƣ�����б�Ż�б�ŷָ��༶����·��.
			Ϊ�մ��򷵻ظ��ڵ�����ݽڵ�
		\param autoCreate ������ʱ�Ƿ��Զ�������ݽڵ�
		\return �µ����ݽڵ㣬������ʱ����autoCreate�Զ����
	*/
	virtual ConfigIOSection GetSection(
		LPCWSTR name, bool autoCreate = true) = 0;
	
	//! �õ���������ʶ���Բ�����һ�����ݽڵ�
	/*!
		\param parent ��һ�������ݽڵ㣬ΪNULL��ȡ���ڵ�
		\param name ���ݽڵ����ƣ�����б�Ż�б�ŷָ��༶���·��
		\param attrName ��ʶһ�������ݽڵ����������
		\param attrValue �ñ�ʶ���Ӧ������ֵ
		\param autoCreate ������ʱ�Ƿ��Զ�������ݽڵ�
		\return �µ����ݽڵ㣬���������Զ����
	*/
	virtual ConfigIOSection GetSection(
		Ix_ConfigSection* parent, LPCWSTR name, 
		LPCWSTR attrName, ULONG attrValue, 
		bool autoCreate = true) = 0;

	//! �õ������Բ�����һ�����ݽڵ�
	/*!
		\param parent ��һ�������ݽڵ㣬ΪNULL��ȡ���ڵ�
		\param name ���ݽڵ����ƣ�����б�Ż�б�ŷָ��༶���·��
		\param attrName ��ʶһ�������ݽڵ����������
		\param attrValue �ñ�ʶ���Ӧ������ֵ
		\param autoCreate ������ʱ�Ƿ��Զ����
		\return �µ����ݽڵ㣬���������Զ����
	*/
	virtual ConfigIOSection GetSection(
		Ix_ConfigSection* parent, LPCWSTR name, 
		LPCWSTR attrName, LPCWSTR attrValue, 
		bool autoCreate = true) = 0;

	//! �õ������Բ�����һ�����ݽڵ�
	/*!
		\param parent ��һ�������ݽڵ㣬ΪNULL��ȡ���ڵ�
		\param name ���ݽڵ����ƣ�����б�Ż�б�ŷָ��༶���·��
		\param attrName ��ʶһ�������ݽڵ�ĵ�һ����������
		\param attrValue �ñ�ʶ���Ӧ������ֵ
		\param attrName2 ��ʶһ�������ݽڵ�ĵڶ�����������
		\param attrValue2 �ñ�ʶ���Ӧ��attrName2������ֵ
		\param autoCreate ������ʱ�Ƿ��Զ����
		\return �µ����ݽڵ㣬���������Զ����
	*/
	virtual ConfigIOSection GetSection(
		Ix_ConfigSection* parent, LPCWSTR name, 
		LPCWSTR attrName, LPCWSTR attrValue, 
		LPCWSTR attrName2, LPCWSTR attrValue2, 
		bool autoCreate = true) = 0;

	//! �õ���������ʶ���Բ�����һ�����ݽڵ�
	/*!
		\param parent ��һ�������ݽڵ㣬ΪNULL��ȡ���ڵ�
		\param name ���ݽڵ����ƣ�����б�Ż�б�ŷָ��༶���·��
		\param attrName ��ʶһ�������ݽڵ�ĵ�һ����������
		\param attrValue �ñ�ʶ���Ӧ������ֵ
		\param attrName2 ��ʶһ�������ݽڵ�ĵڶ�����������
		\param attrValue2 �ñ�ʶ���Ӧ��attrName2������ֵ
		\param autoCreate ������ʱ�Ƿ��Զ����
		\return �µ����ݽڵ㣬���������Զ����
	*/
	virtual ConfigIOSection GetSection(
		Ix_ConfigSection* parent, LPCWSTR name, 
		LPCWSTR attrName, ULONG attrValue, 
		LPCWSTR attrName2, ULONG attrValue2, 
		bool autoCreate = true) = 0;

	//! �õ��ڵ�����Ӧ���ӽڵ����
	/*!
		\param parent ��һ�������ݽڵ㣬ΪNULL��ȡ���ڵ�
		\param name ���ݽڵ����ƣ�����б�Ż�б�ŷָ��༶���·��
		\return �����ݽڵ�ĸ���
		\see GetSectionByIndex
	*/
	virtual long GetSectionCount(
		Ix_ConfigSection* parent, LPCWSTR name) = 0;

	//! �ڽڵ�����Ӧ���ӽڵ��еõ�ָ����ŵ������ݽڵ�
	/*!
		\param parent ��һ�������ݽڵ㣬ΪNULL��ȡ���ڵ�
		\param name ���ݽڵ����ƣ�����б�Ż�б�ŷָ��༶���·��
		\param index Ҫȡ�������ݽڵ�����
		\return �µ����ݽڵ㣬�����������Ըö���Ķ�д���������ԣ������� IsValid() ������Ƿ�Ϊ��Ч�ڵ�
		\see GetSectionCount
	*/
	virtual ConfigIOSection GetSectionByIndex(
		Ix_ConfigSection* parent, LPCWSTR name, long index) = 0;
	
	//! ���һ�����ݽڵ�
	/*!
		\param parent ��һ�������ݽڵ㣬ΪNULL��ȡ���ڵ�
		\param name ���ݽڵ����ƣ�����б�Ż�б�ŷָ��༶���·��
		\return �µ����ݽڵ�
	*/
	virtual ConfigIOSection AddSection(
		Ix_ConfigSection* parent, LPCWSTR name) = 0;

	//! ɾ��һ�����ݽڵ�
	/*!
		\param sec Ҫɾ�������ݽڵ����ֻ������ڲ����ݣ����ͷŸö���
		\return �Ƿ�ɾ���ɹ�
	*/
	virtual bool RemoveSection(Ix_ConfigSection* sec) = 0;
	
	//! ɾ��ָ�������ݽڵ�������ӽڵ�
	/*!
		\param parent Ҫɾ���ڵ����һ�����ݽڵ�
		\param name �ӽڵ����ƣ����ܰ�����б�Ż�б��
		\param attrName �ӽڵ�ı�ʶ����������ѡֵ
		\param attrValue ��ʶ��������Ӧ��ֵ��attrName��Ϊ��ʱ��Ч
		\return ɾ�����ӽڵ����
	*/
	virtual long RemoveChildren(Ix_ConfigSection* parent, LPCWSTR name, 
		LPCWSTR attrName = L"", LPCWSTR attrValue = L"") = 0;

	//! ɾ��ָ�������ݽڵ�������ӽڵ�
	/*!
		\param parent Ҫɾ���ڵ����һ�����ݽڵ�
		\param name �ӽڵ����ƣ����ܰ�����б�Ż�б��
		\param attrName �ӽڵ�ı�ʶ����������Ϊ��
		\param attrValue ��ʶ������attrName��Ӧ��ֵ
		\return ɾ�����ӽڵ����
	*/
	virtual long RemoveChildren(Ix_ConfigSection* parent, LPCWSTR name, 
		LPCWSTR attrName, ULONG attrValue) = 0;

	//! �õ�һ�����ݽڵ����һ���ڵ�
	/*!
		\param sec ָ�������ݽڵ����
		\return ��һ�����ݽڵ�������secΪ���ڵ㣬�򷵻ؽڵ�Ϊ��Ч�ڵ�(IsValid()==false)
	*/
	virtual ConfigIOSection GetParentSection(Ix_ConfigSection* sec) = 0;
};

#endif // X3_XML_ICONFIGDATA_H_
