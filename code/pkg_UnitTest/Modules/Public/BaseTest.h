#pragma once

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
