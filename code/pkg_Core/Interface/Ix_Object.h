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

/*! \file Ix_Object.h
 *  \brief �����������ӿ� Ix_Object �� XCLSID
 *  \author Zhang Yun Gui, C++ Plugin Framework
 *  \date   2010.10.19
 */
#ifndef X3_CORE_IOBJECT_H_
#define X3_CORE_IOBJECT_H_

//! \cond IGNORED
#ifndef interface
#include <objbase.h>
#endif
//! \endcond

/*! \interface Ix_Object
 *  \ingroup _GROUP_PLUGIN_CORE2_
 *  \brief ��������ӿ�
 *  \note  ��粻Ҫֱ�ӵ�����ӿں�����\n ��������඼ͨ�� Cx_Object �� Cx_SingletonObject ��
 *         ģ������ʵ�ָýӿڣ��ýӿڹ�����ָ���� Cx_Ptr �� Cx_Interface ʹ�á�
 *  \see ����ָ����: Cx_Ptr, Cx_Interface
 */
interface Ix_Object
{
	//! �������ü���, ������ָ�������
	virtual void AddRef(HMODULE fromdll) = 0;

	//! �������ü���, �Զ��ͷŶ���, ������ָ�������
	virtual void Release(HMODULE fromdll) = 0;

	//! ��ȡ��Ӧ�Ķ�������
	virtual const char* GetClassName() const = 0;
};

//! �����Ψһ���
/*! \ingroup _GROUP_PLUGIN_CORE_
    ���� \code
	const XCLSID CLSID_ExampleTool("97380b78-a3b4-4784-ba07-c928561988c8");
	\endcode
*/
class XCLSID
{
public:
	//! Ĭ�Ϲ��캯��
	XCLSID()
	{
		m_clsid[0] = 0;
	}

	//! ����UUID������
	XCLSID(const char* clsid)
	{
		lstrcpynA(m_clsid, clsid ? clsid : "", 40);
	}

	//! �������캯��
	XCLSID(const XCLSID& src)
	{
		lstrcpyA(m_clsid, src.m_clsid);
	}

	//! ��ֵΪһ��UUID���Ĳ���������
	XCLSID& operator=(const char* clsid)
	{
		lstrcpynA(m_clsid, clsid ? clsid : "", 40);
		return *this;
	}

	//! ��ֵ����������
	XCLSID& operator=(const XCLSID& src)
	{
		lstrcpyA(m_clsid, src.m_clsid);
		return *this;
	}

	//! ��Ȳ���������
	bool operator==(const XCLSID& src) const
	{
		return lstrcmpA(m_clsid, src.m_clsid) == 0;
	}

	//! ����Ȳ���������
	bool operator!=(const XCLSID& src) const
	{
		return lstrcmpA(m_clsid, src.m_clsid) != 0;
	}

	//! ���ڲ���������
	bool operator>(const XCLSID& src) const
	{
		return lstrcmpA(m_clsid, src.m_clsid) > 0;
	}

	//! С�ڲ���������
	bool operator<(const XCLSID& src) const
	{
		return lstrcmpA(m_clsid, src.m_clsid) < 0;
	}

	//! �����ڲ���ID��ֵ
	const char* str() const
	{
		return m_clsid;
	}

	//! �����Ƿ�Ϊ�ǿյ�UUID��
	bool valid() const
	{
		return m_clsid[0] != 0;
	}

private:
	char m_clsid[40];
};

#endif // X3_CORE_IOBJECT_H_
