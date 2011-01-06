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

/*! \file Ix_PluginLoader.h
 *  \brief ���������صĽӿ� Ix_PluginLoader
 *  \author Zhang Yun Gui, C++ Plugin Framework
 *  \date   2010.10.28
 */
#ifndef X3_MANAGER_IPLUGINLOADER_H_
#define X3_MANAGER_IPLUGINLOADER_H_

#include "Ix_Object.h"

/*! \ingroup _GROUP_PLUGIN_CORE_
 *  \interface Ix_PluginLoader
 *  \brief ������صĽӿ�
 *  \see   Ix_ObjectFactory
 */
interface Ix_PluginLoader
{
	//! ����ָ��DLL��ĳ����Ŀ¼�µ����в��
	/*!
		\param instance ����ָ��Ŀ¼��ģ������ΪNULL��ȡEXE·��
		\param path ���Ŀ¼����ĩβ���Բ���б�ţ����硰Plugins��
		\param ext ����ĺ�׺��������ƥ�������������ִ�Сд��
			���ǰ�����������ַ��������ʺź��Ǻţ����硰.plugin������.plugin.dll������_core.dll��
		\param recursive Ϊtrueʱͬʱ����������Ŀ¼�Ĳ��
		\return ���سɹ��Ĳ������
		\note ��������Ҫ���� InitializePlugins() �Ա�ִ���¼��ز���ĳ�ʼ������
		\see InitializePlugins, LoadPlugins, LoadPluginFiles
	*/
	virtual long LoadPlugins(HMODULE instance, LPCWSTR path, 
		LPCWSTR ext = L".plugin.dll", bool recursive = true) = 0;

	//! ���ص�ǰEXE��ָ��Ŀ¼�µ����в��
	/*!
		\param path Ŀ¼�������Ŀ¼�����·����ĩβ���Բ���б�ţ����硰Plugins��
		\param ext ����ĺ�׺��������ƥ�������������ִ�Сд��
			���ǰ�����������ַ��������ʺź��Ǻţ����硰.plugin������.plugin.dll������_core.dll��
		\param recursive Ϊtrueʱͬʱ����������Ŀ¼�Ĳ��
		\return ���سɹ��Ĳ������
		\note ��������Ҫ���� InitializePlugins() �Ա�ִ���¼��ز���ĳ�ʼ������
		\see InitializePlugins, LoadPlugins, LoadPluginFiles
	*/
	virtual long LoadPlugins(LPCWSTR path, 
		LPCWSTR ext = L".plugin.dll", bool recursive = true) = 0;

	//! ����ָ��ģ���ͬĿ¼�µĶ�����
	/*!
		\param path ���Ŀ¼����մ������硰Plugins�����մ���ʾͬĿ¼
		\param files �ɲ��������ļ�����ɣ��ö��Ż�հ��ַ��ָ������硰1.dll, 2.dll��
		\param instance ����ָ��Ŀ¼��ģ������һ������ģ�飬ΪNULL��ȡEXE·��
		\return ���سɹ��Ĳ������
		\note ��������Ҫ���� InitializePlugins() �Ա�ִ���¼��ز���ĳ�ʼ������
		\see InitializePlugins, LoadPlugins
	*/
	virtual long LoadPluginFiles(LPCWSTR path, LPCWSTR files, HMODULE instance = NULL) = 0;

	//! ��ʼ�������¼��صĲ��
	/*! ���ò���� InitializePlugin �����������ظ���ʼ�����в��
		\return �³�ʼ���Ĳ���ĸ���(�ɹ����� InitializePlugin ������δʵ�ָú�����)
	*/
	virtual long InitializePlugins() = 0;

	//! ע��һ�����
	/*! ��ע�������๤�������������ھ�̬���ӵĶ�̬��������ò������������ģ��
		\param instance Ҫע��Ĳ����ģ����
		\return �Ƿ�ע��ɹ�
		\note ��������Ҫ���� InitializePlugins() �Ա�ִ���¼��ز���ĳ�ʼ������
		\see InitializePlugins
	*/
	virtual bool RegisterPlugin(HMODULE instance) = 0;

	//! ����һ�����
	/*! ʹ��LoadLibraryEx���м��أ�ͬʱע����(RegisterPlugin)
		\param filename ������ļ�ȫ�����������EXE������ļ���
		\return �Ƿ���سɹ�
		\note ��������Ҫ���� InitializePlugins() �Ա�ִ���¼��ز���ĳ�ʼ������
		\see InitializePlugins
	*/
	virtual bool LoadPlugin(LPCWSTR filename) = 0;

	//! ж��ָ�����ƵĲ��
	/*!
		\param name ����ļ�����û��·�������硰MyData.plugin.dll��
		\return �Ƿ�ж�سɹ�
	*/
	virtual bool UnloadPlugin(LPCWSTR name) = 0;

	//! ж�����в��
	/*! ������Ҫ���ʱ���ã�һ���ڳ����˳�ʱ����
		\return ������ж�صĲ������
	*/
	virtual long UnloadPlugins() = 0;
};

#endif // X3_MANAGER_IPLUGINLOADER_H_
