#include "stdafx.h"

// �иú���ʱ���ڲ������ʱ�ɲ�����������ã������ؼ���ʼ������
extern "C" __declspec(dllexport) bool xPluginOnLoad()
{
	return true;
}

// �иú���ʱ���ڲ��ж��ǰ�ɲ�����������ã������ͷ���Դ����
extern "C" __declspec(dllexport) void xPluginOnUnload()
{
}
