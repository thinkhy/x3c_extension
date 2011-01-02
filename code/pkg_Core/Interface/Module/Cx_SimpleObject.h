/*! \file Cx_SimpleObject.h
 *  \brief �����ֱ��ʵ�����ļ�ģ���� Cx_SimpleObject
 *  \author Zhang Yun Gui, C++ Plugin Framework
 *  \date   2010.10.19
 */
#ifndef X3_PLUGINIMPL_SIMPLEOBJECT_H_
#define X3_PLUGINIMPL_SIMPLEOBJECT_H_

#include "Cx_Object.h"
#include "XComPtr.h"

//! ��ֱ��ʵ�����ļ�ģ����
/*! ʹ��ʾ��: \code
	Cx_Ptr MyFunc()
	{
		Cx_Ptr objRet;
		Cx_SimpleObject<Cx_MyInternal>* p = Cx_SimpleObject<Cx_MyInternal>::Create(objRet);

		p->Init();

		return objRet;
	}
	\endcode
	����� XBEGIN_DEFINE_MODULE ������б��аѸ�ʵ����Ǽ��ϣ�
	�����Ϳ����ⲿģ���Ƿ�������������磺 \code
	XBEGIN_DEFINE_MODULE()
		XDEFINE_CLASSMAP_ENTRY(XCLSID(), Cx_MyInternal)
	XEND_DEFINE_MODULE()
	\endcode
	\ingroup _GROUP_PLUGIN_CORE2_
*/
template <class ClsType>
class Cx_SimpleObject : public Cx_Object<ClsType>
{
public:
	//! ����һ�����󣬲���Cx_Ptr�ӹ�
	static Cx_SimpleObject<ClsType>* Create(Cx_Ptr& objOwner)
	{
		Cx_SimpleObject<ClsType>* p = new Cx_SimpleObject<ClsType>();
		objOwner.AttachInterface(p);
		return p;
	}
	
	//! ����һ�����󣬲���Cx_Interface�ӹ�
	template <class IF_Type>
	static Cx_SimpleObject<ClsType>* Create(Cx_Interface<IF_Type>& pIFOwner)
	{
		Cx_SimpleObject<ClsType>* p = new Cx_SimpleObject<ClsType>();
		return pIFOwner.AttachInterface(static_cast<Ix_Object*>(p)) ? p : NULL;
	}

private:
	Cx_SimpleObject() {}
	Cx_SimpleObject(const Cx_SimpleObject&);
};

#endif // X3_PLUGINIMPL_SIMPLEOBJECT_H_
