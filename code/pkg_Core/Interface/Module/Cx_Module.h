/*! \file Cx_Module.h
 *  \brief ������ģ��ʵ���� Cx_Module
 *  \author Zhang Yun Gui, C++ Plugin Framework
 *  \date   2010.10.19
 */
#ifndef X3_PLUGINIMPL_MODULE_H_
#define X3_PLUGINIMPL_MODULE_H_

#include "Ix_Module.h"

/*! \ingroup _GROUP_PLUGIN_CORE2_
 *  \brief ���ģ��ʵ���࣬���ڲ�ʹ��
 *  \note  ÿ�����ģ������Ψһ�ı�������� XModuleImpl.h �ж����˸ö���
 */
class Cx_Module : public Ix_Module
{
public:
	Cx_Module();
	~Cx_Module();

	//! ��ʼ����������� _xGetModuleInterface() ����
	void Initialize(Ix_ObjectFactory* pFactory, HMODULE hModule);

public:
	void ClearModuleItems();
	long GetUnfreeObjectCount();
	Ix_ObjectFactory* GetObjectFactory() const { return m_pFactory; }
	HMODULE GetModuleInstance() const { return m_hModule; }
	HMODULE GetModuleResourceHandle() const { return m_hResource; }
	HMODULE SetModuleResourceHandle(HMODULE hResource);

private:
	Ix_ObjectFactory*	m_pFactory;
	HMODULE			m_hModule;
	HMODULE			m_hResource;
};

#endif // X3_PLUGINIMPL_MODULE_H_
