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

/*! \file XModuleItem.h
 *  \brief ���嵥ʵ��������࣬�ڲ��ļ�
 *  \author Zhang Yun Gui, C++ Plugin Framework
 *  \date   2010.10.19
 */
#ifndef X3_PLUGINIMPL_MODULEITEM_H_
#define X3_PLUGINIMPL_MODULEITEM_H_

/*! \ingroup _GROUP_PLUGIN_CORE2_
 *  \brief ��ģ���ڵ�ʵ��������࣬���ڲ�ʹ��
 */
class CModuleItem
{
protected:
	CModuleItem() : m_index(-1)
	{
	}
	virtual ~CModuleItem()
	{
	}

	//! ���������ʵ����������
	void AddModuleItem()
	{
		m_index = InterlockedDecrement(&Index());	// �����߳̿�ͬʱ���
		if (m_index >= 0)
		{
			// Items[index] ֻ�ᱻһ���̲߳���
			Items()[m_index] = this;
		}
	}

public:
	//! �ڱ�ģ��ж��ʱ���ͷ�(delete)���е�ʵ������
	static void ClearModuleItems()
	{
		if (Items())
		{
			for (int i = Index(); i < MaxCount(); i++)
			{
				if (i >= 0 && Items()[i] )
				{
					delete Items()[i];
					Items()[i] = NULL;
				}
			}
			Index() = 0;

			delete[] Items();
			Items() = NULL;
		}
	}

	//! ��ʼ����ʵ�������ջ( _xGetModuleInterface ����ñ�����)
	static void InitModuleItems(long nCount)
	{
		if (NULL == Items() && nCount > 0)
		{
			MaxCount() = max(nCount, MaxCount());
			Index() = MaxCount();
			Items() = new CModuleItem*[MaxCount()];
		}
	}

private:
	long	m_index;	//!< �ڵ�ʵ�������ջ�е�˳��Խ��Խ��

	static long& MaxCount()
	{
		static long s_count = 0;
		return s_count;
	}
	static long& Index()
	{
		static long s_index = 0;
		return s_index;
	}
	static CModuleItem**& Items()
	{
		static CModuleItem** s_pItems = NULL;
		return s_pItems;
	}
};

#endif // X3_PLUGINIMPL_MODULEITEM_H_
