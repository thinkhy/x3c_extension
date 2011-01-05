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

#ifndef X3_UNITTEST_BASETEST_H_
#define X3_UNITTEST_BASETEST_H_

const LPCWSTR PLUGINS_DIR = L"../Plugins";
interface Ix_PluginLoader;

//! ������������
class BaseTest : public CppUnit::TestFixture
{
protected:
	BaseTest();

	//! ���ز��
	/*!
		\param plugins �ɲ��������ļ�����ɣ�
			�ö��Ż�հ��ַ��ָ������硰1.dll, 2.dll������Ϊ��
		\param loadCore �Ƿ���ز������ں˵Ĳ��(LogManager.plugin.dll��)
		\return ��plugins��ָ���Ĳ���У����سɹ��Ĳ������
	*/
	long LoadPlugins(LPCWSTR plugins, bool loadCore = true);

	//! ж�����в��
	void UnloadPlugins();

	//! �õ�������ع�����󣬿����ڼ��ظ�����
	Ix_PluginLoader* GetPluginLoader();

	//! �γɲ������ݵ��ļ�ȫ��
	/*! �������ݵĸ�Ŀ¼�� UnitTests.ini ��[Path]�µ� TestData ����ָ����
		\param folder ��Ŀ¼�������硰Pdf����Ϊ����ȡΪ��ʱ���Ŀ¼��
			����ʱĿ¼�� UnitTests.ini ��[Path]�µ� Temp ����ָ����
		\param file ����ļ�����Ϊ���򷵻�Ŀ¼ȫ��
		\return �ļ���Ŀ¼��ȫ��
	*/
	std::wstring MakeDataPath(LPCWSTR folder, LPCWSTR file);

private:
	void MakeRootPath(LPWSTR path, LPCWSTR name);
};

#endif // X3_UNITTEST_BASETEST_H_
