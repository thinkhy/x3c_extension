/*! \file Ix_ObjectFactory.h
 *  \brief ���崴������Ľӿ� Ix_ObjectFactory
 *  \author Zhang Yun Gui, C++ Plugin Framework
 *  \date   2010.10.19
 */
#ifndef X3_CORE_IOBJECTFACTORY_H_
#define X3_CORE_IOBJECTFACTORY_H_

#include "Ix_Object.h"

/*! \ingroup _GROUP_PLUGIN_CORE_
 *  \interface Ix_ObjectFactory
 *  \brief ��������ӿڶ���Ľӿ�
 *  \see   Ix_Object, Ix_Module
 */
interface Ix_ObjectFactory
{
	//! ����ָ����������Ƿ��Ѽ���
	virtual bool IsCreatorRegister(const XCLSID& clsid) = 0;

	//! ����һ�������ID��Ӧ�Ķ���ʵ��
	virtual HRESULT CreateObject(const XCLSID& clsid, Ix_Object** ppv, HMODULE fromdll) = 0;

	//! �����в��ģ���д����ض��ӿڵĵ�ʵ������
	/*!
		\param iid ָ���Ľӿ�ID
		\return ֧�ָýӿڵĲ���ĸ����������Ƿ��Ѵ���
	*/
	virtual long CreateSpecialInterfaceObjects(const char* iid) = 0;

	//! �õ�ָ����ŵĲ��ģ���е�ָ���ӿڵĵ�ʵ������
	/*!
		\param[in] index ָ���Ĳ����ţ�����ʵ�ʼ���˳���йأ�С�ڲ������
		\param[in] iid ָ���Ľӿ�ID
		\param[in,out] ppv ��������ĵ�ַ�����ش����Ķ���ΪNULL��ȥ����
		\return ָ���Ĳ�����Խ��ʱ����false�����򷵻�true������ֵ��ppv�޹�
	*/
	virtual bool QuerySpecialInterfaceObject(long index, const char* iid, Ix_Object** ppv) = 0;

	//! �����Ƿ����๤���������滻
	virtual bool HasCreatorReplaced(const XCLSID& clsid) = 0;
};

#endif // X3_CORE_IOBJECTFACTORY_H_
