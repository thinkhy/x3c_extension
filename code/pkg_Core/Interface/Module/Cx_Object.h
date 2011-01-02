/*! \file Cx_Object.h
 *  \brief ������ͨ������ģ��ʵ���� Cx_Object
 *  \author Zhang Yun Gui, C++ Plugin Framework
 *  \date   2010.10.19
 */
#ifndef X3_PLUGINIMPL_OBJECT_H_
#define X3_PLUGINIMPL_OBJECT_H_

#include "Ix_Object.h"
#include <typeinfo.h>

HMODULE xGetModuleHandle();

/*! \ingroup _GROUP_PLUGIN_CORE2_
 *  \brief ��ͨ������ģ��ʵ���࣬�ڲ�ʹ��
 *  \note  ���� XDEFINE_CLASSMAP_ENTRY ʹ�ã�ģ����� ClsType Ϊĳ���ӿ�ʵ����
 *  \see   Cx_SingletonObject, XDEFINE_CLASSMAP_ENTRY
 */
template <class ClsType>
class Cx_Object
	: public ClsType
	, public Ix_Object
{
protected:
	Cx_Object(bool bRef = true) : m_lRefCount(bRef ? 1 : 0)
	{
		InterlockedIncrement(&ObjectCount());
	}

	virtual ~Cx_Object()
	{
		InterlockedDecrement(&ObjectCount());
	}

protected:
	virtual void AddRef(HMODULE fromdll)
	{
		if (fromdll != xGetModuleHandle())
		{
			InterlockedIncrement(&RefCountByOthers());
		}
		InterlockedIncrement(&m_lRefCount);
	}

	virtual void Release(HMODULE fromdll)
	{
		if (fromdll != xGetModuleHandle())
		{
			InterlockedDecrement(&RefCountByOthers());
		}
		if (0 == InterlockedDecrement(&m_lRefCount))
		{
			delete this;
		}
	}

	virtual const char* GetClassName() const
	{
		return typeid(*this).name();
	}

public:
	static Ix_Object* STDMETHODCALLTYPE CreateObject(HMODULE fromdll)
	{
		Cx_Object<ClsType>* p = new Cx_Object<ClsType>(false);
		p->AddRef(fromdll);
		return p;
	}

	static long STDMETHODCALLTYPE GetObjectCount()
	{
		return ObjectCount();
	}

	static long STDMETHODCALLTYPE GetRefCountByOthers()
	{
		return RefCountByOthers();
	}

private:
	long		m_lRefCount;

	static long& ObjectCount()
	{
		static long s_lObjCount = 0;
		return s_lObjCount;
	}

	static long& RefCountByOthers()
	{
		static long s_lRefCount = 0;
		return s_lRefCount;
	}
};

#endif // X3_PLUGINIMPL_OBJECT_H_
