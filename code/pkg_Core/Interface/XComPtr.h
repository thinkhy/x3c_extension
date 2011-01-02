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

/*! \file XComPtr.h
 *  \brief ��������ָ���� Cx_Interface �� Cx_Ptr
 *  \author Zhang Yun Gui, C++ Plugin Framework
 *  \date   2010.10.19
 */
#ifndef X3_CORE_XCOMPTR_H_
#define X3_CORE_XCOMPTR_H_

#include "Ix_Object.h"

// ������ID��Ӧ�Ķ���. �� XModuleImpl.h �� XComCreator.h ��ʵ��
HRESULT xCreateObject(const XCLSID& clsid, Ix_Object** ppv);

// ���ص�ǰģ���DLL���. �� XModuleImpl.h �� XComCreator.h ��ʵ��
HMODULE xGetModuleHandle();

#ifndef _CPPRTTI
#error must enable RTTI (compiled with /GR)
#endif

class Cx_Ptr;

//! ��װ�ض��ӿڵ�����ָ����
/*! ģ����� IF_Type Ϊ�� Ix_Object �Ľӿ�����\n
	�����õ��� xCreateObject() �� XModuleImpl.h �� XComCreator.h ��ʵ�֡�
	\ingroup _GROUP_PLUGIN_CORE_
	\see Cx_Ptr, xCreateObject
*/
template <class IF_Type>
class Cx_Interface
{
	typedef Cx_Interface<IF_Type> thisClass;
public:
	//! ȱʡ���캯��������ն���
	Cx_Interface() : m_pInterface(NULL), m_pObj(NULL)
	{
	}

	//! ��һ��Cx_Ptr������
	Cx_Interface(const Cx_Ptr& src) : m_pInterface(NULL), m_pObj(NULL)
	{
		if (src.P())
		{
			m_pInterface = dynamic_cast<IF_Type*>(src.P());
			if (m_pInterface)
			{
				m_pObj = src.P();
				m_pObj->AddRef(xGetModuleHandle());
			}
		}
	}

#if _MSC_VER > 1200 // not VC60

	//! �������캯��
	Cx_Interface(const thisClass& src)
		: m_pInterface(src.m_pInterface), m_pObj(src.m_pObj)
	{
		if (m_pInterface)
		{
			m_pObj->AddRef(xGetModuleHandle());
		}
	}

	//! ��һ��ͬ���͵Ľӿ�ָ�빹��
	Cx_Interface(IF_Type* pInterface) : m_pInterface(pInterface), m_pObj(NULL)
	{
		if (m_pInterface)
		{
			m_pObj = dynamic_cast<Ix_Object*>(m_pInterface);
			//ASSERT(m_pObj != NULL);
			m_pObj->AddRef(xGetModuleHandle());
		}
	}

#endif // _MSC_VER
	
	//! ��һ���ӿ�ָ�빹��
	template <class IF_Type2>
	explicit Cx_Interface(IF_Type2* pInterface) : m_pInterface(NULL), m_pObj(NULL)
	{
		if (pInterface)
		{
			m_pInterface = dynamic_cast<IF_Type*>(pInterface);
			if (m_pInterface)
			{
				m_pObj = dynamic_cast<Ix_Object*>(m_pInterface);
				//ASSERT(m_pObj != NULL);
				m_pObj->AddRef(xGetModuleHandle());
			}
		}
	}

	//! ��һ������ָ�빹��
	template <class IF_Type2>
	explicit Cx_Interface(const Cx_Interface<IF_Type2>& pIF)
		: m_pInterface(NULL), m_pObj(NULL)
	{
		if (pIF)
		{
			m_pInterface = dynamic_cast<IF_Type*>(pIF.P());
			if (m_pInterface)
			{
				m_pObj = dynamic_cast<Ix_Object*>(m_pInterface);
				//ASSERT(m_pObj != NULL);
				m_pObj->AddRef(xGetModuleHandle());
			}
		}
	}
	
	//! ���������ID��������ʵ��
	explicit Cx_Interface(const XCLSID& clsid) : m_pInterface(NULL), m_pObj(NULL)
	{
		if (S_OK == xCreateObject(clsid, &m_pObj))
		{
			m_pInterface = dynamic_cast<IF_Type*>(m_pObj);
			if (NULL == m_pInterface)
			{
				m_pObj->Release(xGetModuleHandle());
				m_pObj = NULL;
			}
		}
	}
	
	//! ��������
	~Cx_Interface()
	{
		Unload();
	}
	
	
	//! ���ض���ӿ�ָ��
	inline IF_Type* P() const
	{
		return m_pInterface;
	}
	
	//! ���ö���ӿں����Ĳ�����
	inline IF_Type* operator->() const
	{
		return m_pInterface;
	}

	//! ������ֵ������������һ���ӿ�ָ��
	template <class IF_Type2>
	thisClass& operator=(IF_Type2* pInterface)
	{
		Unload();

		if (pInterface)
		{
			m_pInterface = dynamic_cast<IF_Type*>(pInterface);
			if (m_pInterface)
			{
				m_pObj = dynamic_cast<Ix_Object*>(m_pInterface);
				//ASSERT(m_pObj != NULL);
				m_pObj->AddRef(xGetModuleHandle());
			}
		}

		return *this;
	}

	//! ������ֵ������������һ������ָ��
	template <class IF_Type2>
	thisClass& operator=(const Cx_Interface<IF_Type2>& pIF)
	{
		return operator=(pIF.P());
	}

	//! ������ֵ������������ͬ���͵�����ָ��
	thisClass& operator=(const thisClass& src)
	{
		if (this != &src)
		{
			Load(src.m_pInterface);
		}

		return *this;
	}
	
	//! ������ֵ������������Cx_Ptr����ָ��
	thisClass& operator=(const Cx_Ptr& src)
	{
		Unload();

		if (src.P())
		{
			m_pInterface = dynamic_cast<IF_Type*>(src.P());
			if (m_pInterface)
			{
				m_pObj = src.P();
				m_pObj->AddRef(xGetModuleHandle());
			}
		}

		return *this;
	}

	//! ��ֵΪNULL�Ĳ�����
	thisClass& operator=(const int nul)
	{
		nul;//ASSERT(0 == nul);
		Unload();
		return *this;
	}

	//! �� NULL �Ƚ��Ƿ����
	bool operator==(const int nul) const
	{
		nul;//ASSERT(0 == nul);
		return m_pInterface == NULL;
	}

	//! �� NULL �Ƚ��Ƿ����
	bool operator!=(const int nul) const
	{
		nul;//ASSERT(0 == nul);
		return m_pInterface != NULL;
	}
	
	//! ������������ָ���Ƿ�ָ����ͬ�Ķ���
	bool operator==(const IF_Type* pInterface) const
	{
		return m_pInterface == pInterface;
	}
	
	//! ������������ָ���Ƿ�ָ��ͬ�Ķ���
	bool operator!=(const IF_Type* pInterface) const
	{
		return m_pInterface != pInterface;
	}
	
	//! ������������ָ���Ƿ�ָ����ͬ�Ķ���
	bool operator==(const thisClass& src) const
	{
		return m_pInterface == src.m_pInterface;
	}
	
	//! ������������ָ���Ƿ�ָ��ͬ�Ķ���
	bool operator!=(const thisClass& src) const
	{
		return m_pInterface != src.m_pInterface;
	}

	//! �൱�� IsNotNull ��ת������������
	inline operator bool() const
	{
		return m_pInterface != NULL;
	}

	//! �൱�� IsNull ��ת������������
	inline bool operator!() const
	{
		return NULL == m_pInterface;
	}
	
	//! �����Ƿ�û�ж���
	inline bool IsNull() const
	{
		return NULL == m_pInterface;
	}
	
	//! �����Ƿ��ж���
	inline bool IsNotNull() const
	{
		return m_pInterface != NULL;
	}
	
	
	//! �����ͷŶ���ָ�������
	/*! ����������ʱ���Զ����ñ��������������ٱ�����ʱ���Զ��ͷ�
	*/
	void Release()
	{
		Unload();
	}
	
	//! ����ӿ�ָ��
	IF_Type* DetachInterface()
	{
		IF_Type* pIF = m_pInterface;
		m_pInterface = NULL;
		m_pObj = NULL;
		return pIF;
	}
	
	//! �ӹ�һ���ӿ�ָ��
	bool AttachInterface(IF_Type* pIF)
	{
		Unload();
		m_pInterface = pIF;
		m_pObj = dynamic_cast<Ix_Object*>(m_pInterface);
		return (m_pObj != NULL || NULL == m_pInterface);
	}
	
	//! �ӹ�һ���ӿ�ָ��
	bool AttachInterface(Ix_Object* pIF)
	{
		Unload();

		if (pIF)
		{
			m_pInterface = dynamic_cast<IF_Type*>(pIF);
			if (m_pInterface)
			{
				m_pObj = dynamic_cast<Ix_Object*>(m_pInterface);
				//ASSERT(m_pObj != NULL);
			}
			else
			{
				pIF->Release(xGetModuleHandle());
				pIF = NULL;
				return false;
			}
		}

		return true;
	}
	
	//! ���������ID�����б��ӿڵĶ���ʵ��
	bool Create(const XCLSID& clsid)
	{
		Unload();
		
		if (S_OK == xCreateObject(clsid, &m_pObj))
		{
			m_pInterface = dynamic_cast<IF_Type*>(m_pObj);
			if (NULL == m_pInterface)
			{
				m_pObj->Release(xGetModuleHandle());
				m_pObj = NULL;
			}
		}
		
		return m_pInterface != NULL;
	}
	
private:
	void Unload()
	{
		if (m_pObj)
		{
			m_pObj->Release(xGetModuleHandle());
			m_pObj = NULL;
			m_pInterface = NULL;
		}
	}
	
	void Load(IF_Type* pIF)
	{
		Ix_Object* pObj = dynamic_cast<Ix_Object*>(pIF);
		if (m_pObj != pObj)
		{
			if (pObj)
			{
				pObj->AddRef(xGetModuleHandle());
			}
			if (m_pObj)
			{
				m_pObj->Release(xGetModuleHandle());
			}
			m_pObj = pObj;
			m_pInterface = pIF;
		}
	}
	
private:
	IF_Type*	m_pInterface;
	Ix_Object*	m_pObj;
};

//! ��װIx_Object�ӿڵ�����ָ����
/*! �����õ��� xCreateObject() �� XModuleImpl.h �� XComCreator.h ��ʵ�֡�
	\ingroup _GROUP_PLUGIN_CORE_
	\see Ix_Object, Cx_Interface, xCreateObject
*/
class Cx_Ptr
{
public:
	//! Ĭ�Ϲ��캯��
	Cx_Ptr() : m_pInterface(NULL)
	{
	}

	//! �������캯��
	Cx_Ptr(const Cx_Ptr& src) : m_pInterface(src.m_pInterface)
	{
		if (m_pInterface)
		{
			m_pInterface->AddRef(xGetModuleHandle());
		}
	}
	
	//! ��һ���ӿ�ָ�빹��
	template <class IF_Type>
	explicit Cx_Ptr(IF_Type* pInterface) : m_pInterface(NULL)
	{
		m_pInterface = dynamic_cast<Ix_Object*>(pInterface);
		if (m_pInterface)
		{
			m_pInterface->AddRef(xGetModuleHandle());
		}
	}

	//! ��һ���ض����͵�����ָ�빹��
	template <class IF_Type>
	explicit Cx_Ptr(const Cx_Interface<IF_Type>& pIF) : m_pInterface(NULL)
	{
		m_pInterface = dynamic_cast<Ix_Object*>(pIF.P());
		if (m_pInterface)
		{
			m_pInterface->AddRef(xGetModuleHandle());
		}
	}
	
	//! ���������ID��������ʵ��
	explicit Cx_Ptr(const XCLSID& clsid) : m_pInterface(NULL)
	{
		xCreateObject(clsid, &m_pInterface);
	}
	
	//! ��������
	~Cx_Ptr()
	{
		Unload();
	}
	
	
	//! ���ض���ӿ�ָ��
	Ix_Object* P() const
	{
		return m_pInterface;
	}
	
	//! ������ֵ������������һ���ӿ�ָ��
	template <class IF_Type>
	Cx_Ptr& operator=(IF_Type* pInterface)
	{
		Unload();

		m_pInterface = dynamic_cast<Ix_Object*>(pInterface);
		if (m_pInterface)
		{
			m_pInterface->AddRef(xGetModuleHandle());
		}

		return *this;
	}

	//! ������ֵ������������һ���ض����͵�����ָ��
	template <class IF_Type>
	Cx_Ptr& operator=(const Cx_Interface<IF_Type>& pIF)
	{
		return operator=(pIF.P());
	}
	
	//! ������ֵ������������ͬ���͵�����ָ��
	Cx_Ptr& operator=(const Cx_Ptr& src)
	{
		if (this != &src)
		{
			Load(src.m_pInterface);
		}

		return *this;
	}

	//! ��ֵΪNULL�Ĳ�����
	Cx_Ptr& operator=(const int nul)
	{
		nul;//ASSERT(0 == nul);
		Unload();
		return *this;
	}

	//! �� NULL �Ƚ��Ƿ����
	bool operator==(const int nul) const
	{
		nul;//ASSERT(0 == nul);
		return m_pInterface == NULL;
	}

	//! �� NULL �Ƚ��Ƿ����
	bool operator!=(const int nul) const
	{
		nul;//ASSERT(0 == nul);
		return m_pInterface != NULL;
	}
	
	//! ������������ָ���Ƿ�ָ����ͬ�Ķ���
	bool operator==(const Ix_Object* pInterface) const
	{
		return m_pInterface == pInterface;
	}
	
	//! ������������ָ���Ƿ�ָ��ͬ�Ķ���
	bool operator!=(const Ix_Object* pInterface) const
	{
		return m_pInterface != pInterface;
	}
	
	//! ������������ָ���Ƿ�ָ����ͬ�Ķ���
	bool operator==(const Cx_Ptr& src) const
	{
		return m_pInterface == src.m_pInterface;
	}
	
	//! ������������ָ���Ƿ�ָ��ͬ�Ķ���
	bool operator!=(const Cx_Ptr& src) const
	{
		return m_pInterface != src.m_pInterface;
	}

	//! �൱�� IsNotNull ��ת������������
	inline operator bool() const
	{
		return m_pInterface != NULL;
	}

	//! �൱�� IsNull ��ת������������
	inline bool operator!() const
	{
		return NULL == m_pInterface;
	}
	
	//! �����Ƿ�û�ж���
	inline bool IsNull() const
	{
		return NULL == m_pInterface;
	}
	
	//! �����Ƿ��ж���
	inline bool IsNotNull() const
	{
		return m_pInterface != NULL;
	}
	
	
	//! �����ͷŶ���ָ�������
	/*! ����������ʱ���Զ����ñ��������������ٱ�����ʱ���Զ��ͷ�
	*/
	void Release()
	{
		Unload();
	}
	
	//! ����ӿ�ָ��
	Ix_Object* DetachInterface()
	{
		Ix_Object* pIF = m_pInterface;
		m_pInterface = NULL;
		return pIF;
	}
	
	//! �ӹ�һ���ӿ�ָ��
	void AttachInterface(Ix_Object* pIF)
	{
		Unload();
		m_pInterface = pIF;
	}
	
	//! ���������ID��������ʵ��
	bool Create(const XCLSID& clsid)
	{
		Unload();
		return S_OK == xCreateObject(clsid, &m_pInterface);
	}
	
private:
	void Unload()
	{
		if (m_pInterface)
		{
			m_pInterface->Release(xGetModuleHandle());
			m_pInterface = NULL;
		}
	}
	
	void Load(Ix_Object* pIF)
	{
		if (m_pInterface != pIF)
		{
			if (pIF)
			{
				pIF->AddRef(xGetModuleHandle());
			}
			if (m_pInterface)
			{
				m_pInterface->Release(xGetModuleHandle());
			}
			m_pInterface = pIF;
		}
	}
	
private:
	Ix_Object*	m_pInterface;
};

#endif // X3_CORE_XCOMPTR_H_
