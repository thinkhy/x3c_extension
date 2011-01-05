#include "stdafx.h"
#include <PluginManager.h>

void Test();

int main()
{
	CPluginManager loader;

	if (loader.LoadPluginManager(L"../Plugins"))
	{
		loader.GetPluginLoader()->LoadPluginFiles(L"../Plugins", 
			L"Win32DllTempl.plugin.dll");
		loader.GetPluginLoader()->InitializePlugins();

		Test();

		loader.Unload();
	}

	return 0;
}


#include <Ix_Example.h>

void MyFunc2(const Cx_Ptr& obj)
{
    // Cx_Interface��Cx_Ptr��ת��תΪ�ض��ӿ�
    Cx_Interface<Ix_Example> pIFExample(obj);
    if (pIFExample)
    {
        pIFExample->Foo();
    }
}

void Test()
{
	// ʹ����ID�ͽӿڴ�������
    Cx_Interface<Ix_Example> pIFExample(CLSID_Example);
    if (pIFExample)
    {
        pIFExample->Foo();    // ���ýӿں���
    }

    // ת��Ϊ�����ӿ�
    Cx_Interface<Ix_Example2> pIFExample2(pIFExample);
    if (pIFExample2.IsNotNull())
    {
        pIFExample2->Foo2();
    }

    // תΪ�޽ӿ����͵�Cx_Ptr���ɱ��⺯������ʱ������������ӿ��ļ�
    MyFunc2(Cx_Ptr(pIFExample2));
}
