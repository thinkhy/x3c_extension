#include "stdafx.h"

// ����б����������ڲ������ʱ�ɲ�����������ã�����ע��ȹؼ���ʼ������
extern "C" __declspec(dllexport) bool InitializePlugin()
{
	return true;
}

// ����б����������ڲ��ж��ǰ�ɲ�����������ã������ͷ���Դ��ע������
extern "C" __declspec(dllexport) void UninitializePlugin()
{
}
