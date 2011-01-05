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

/*! \file Ix_ConfigSection.h
 *  \brief �������ݽڵ��ֵ��д�ӿ� Ix_ConfigSection
 *  \author Zhang Yun Gui, C++ Plugin Framework
 *  \date   2010.10.22
 */
#ifndef X3_XML_ICONFIGSECTION_H_
#define X3_XML_ICONFIGSECTION_H_

#include <XComPtr.h>

interface Ix_ConfigData;

//! ���ݽڵ��ֵ��д�ӿ�
/*! ��ʹ�� CConfigIOSection ���������ʹ�ñ��ӿڡ�\n
	���ӿ������������ݶ����൱��������״��νṹ�е�һ�����ݽڵ㣬
	�� Ix_ConfigData ���Ӧ��ȫ�����ݽڵ㡣
	\interface Ix_ConfigSection
	\ingroup _GROUP_PLUGIN_XML_
	\see CConfigIOSection, Ix_ConfigData
*/
interface Ix_ConfigSection
{
	//! ����ӵ�������ù���ӿڶ���
	virtual Ix_ConfigData* GetData() const = 0;

	//! �����ڲ������Ƿ�Ϸ�
	/*!
		\return ���ڲ��Ƿ��ж�Ӧ��ʵ�����ݽڵ�
	*/
	virtual bool IsValid() const = 0;

	//! �õ�ֵ����Ϊ�ַ�����������
	/*!
		\param name ������������
		\param defValue Ĭ��ֵ������û�ж�Ӧ��������ʱȡΪ��ֵ
		\return ���������ֵ
		\see SetString
	*/
	virtual std::wstring GetString(LPCWSTR name, LPCWSTR defValue = L"") = 0;

	//! ����ֵ����Ϊ�ַ�����������
	/*!
		\param name ������������
		\param value �µ�ֵ
		\return �Ƿ�ı�������
		\see GetString
	*/
	virtual bool SetString(LPCWSTR name, LPCWSTR value) = 0;

	//! �õ�ֵ����Ϊ������������
	/*! ���������Զ���ȡ���ġ�true���͡�false��ת��Ϊ������
		\param name ������������
		\param defValue Ĭ��ֵ����������Ϊ�մ���û��ʱȡΪ��ֵ
		\return ���������ֵ
	*/
	virtual int GetInt(LPCWSTR name, int defValue = 0) = 0;

	//! ����ֵ����Ϊ������������
	/*!
		\param name ������������
		\param value �µ�ֵ
		\return �Ƿ�ı�������
	*/
	virtual bool SetInt(LPCWSTR name, int value) = 0;

	//! �õ�ֵ����Ϊ��������������
	/*! ����˵���ο� GetInt()
	*/
	virtual long GetInt32(LPCWSTR name, long defValue = 0) = 0;

	//! ����ֵ����Ϊ��������������
	/*! ����˵���ο� SetInt()
	*/
	virtual bool SetInt32(LPCWSTR name, long value) = 0;

	//! �õ�ֵ����Ϊ�޷��ų�������������
	/*! ����˵���ο� GetInt()
	*/
	virtual ULONG GetUInt32(LPCWSTR name, ULONG defValue = 0) = 0;

	//! ����ֵ����Ϊ�޷��ų�������������
	/*! ����˵���ο� SetInt()
	*/
	virtual bool SetUInt32(LPCWSTR name, ULONG value) = 0;

	//! �õ�ֵ����Ϊ��������������
	/*! ����˵���ο� GetInt()
	*/
	virtual short GetInt16(LPCWSTR name, short defValue = 0) = 0;

	//! ����ֵ����Ϊ��������������
	/*! ����˵���ο� SetInt()
	*/
	virtual bool SetInt16(LPCWSTR name, short value) = 0;

	//! �õ�ֵ����Ϊ�޷��Ŷ�������������
	/*! ����˵���ο� GetInt()
	*/
	virtual WORD GetUInt16(LPCWSTR name, WORD defValue = 0) = 0;

	//! ����ֵ����Ϊ�޷��Ŷ�������������
	/*! ����˵���ο� SetInt()
	*/
	virtual bool SetUInt16(LPCWSTR name, WORD value) = 0;

	//! �õ�ֵ����Ϊ������������
	/*!
		\param name ������������
		\param defValue Ĭ��ֵ����������Ϊ�մ���û��ʱȡΪ��ֵ
		\return ���������ֵ������Ϊ��������ֵ��true��ʱ����true������Ϊfalse
	*/
	virtual bool GetBool(LPCWSTR name, BOOL defValue) = 0;

	//! ����ֵ����Ϊ������������
	/*!
		\param name ������������
		\param value �µ�ֵ
		\return �Ƿ�ı�������
	*/
	virtual bool SetBool(LPCWSTR name, BOOL value) = 0;

	//! �õ�ֵ����Ϊ��������������
	/*!
		\param name ������������
		\param defValue Ĭ��ֵ����������Ϊ�մ���û��ʱȡΪ��ֵ
		\return ���������ֵ
	*/
	virtual double GetDouble(LPCWSTR name, double defValue = 0) = 0;

	//! ����ֵ����Ϊ��������������
	/*!
		\param name ������������
		\param value �µ�ֵ
		\return �Ƿ�ı�������
	*/
	virtual bool SetDouble(LPCWSTR name, double value) = 0;

	//! �õ�ֵ����Ϊ��������������
	/*!
		����˵���μ� GetDouble()
	*/
	virtual float GetFloat(LPCWSTR name, float defValue = 0) = 0;

	//! ����ֵ����Ϊ��������������
	/*!
		����˵���μ� SetDouble()
	*/
	virtual bool SetFloat(LPCWSTR name, float value) = 0;

	//! �õ�ֵ����ΪRGB��ɫ��������
	/*!
		\param name ������������
		\param defValue Ĭ��ֵ����������û�а�����������ʱȡΪ��ֵ
		\return ���������ֵ��ʹ���� RGB(r,g,b) ��
	*/
	virtual COLORREF GetRGB(LPCWSTR name, COLORREF defValue) = 0;

	//! ����ֵ����ΪRGB��ɫֵ��������
	/*!
		\param name ������������
		\param value �µ�ֵ����ȡ��6λ��������ɫ����
		\return �Ƿ�ı�������
	*/
	virtual bool SetRGB(LPCWSTR name, COLORREF value) = 0;

	//! �õ�ֵ����ΪCMYK��ɫֵ��������
	/*!
		\param[in] name ������������
		\param[out] c ��ȡ�ɹ�ʱ���CMYK��ɫֵ��C���֣�ʧ��ʱ���ı���ֵ
		\param[out] m ��ȡ�ɹ�ʱ���CMYK��ɫֵ��M���֣�ʧ��ʱ���ı���ֵ
		\param[out] y ��ȡ�ɹ�ʱ���CMYK��ɫֵ��Y���֣�ʧ��ʱ���ı���ֵ
		\param[out] k ��ȡ�ɹ�ʱ���CMYK��ɫֵ��K���֣�ʧ��ʱ���ı���ֵ
		\return �Ƿ��ȡ�ɹ�
	*/
	virtual bool GetCMYK(LPCWSTR name, WORD& c, WORD& m, WORD& y, WORD& k) = 0;

	//! ����ֵ����ΪCMYK��ɫֵ��������
	/*!
		\param name ������������
		\param c CMYK��ɫֵ��C����
		\param m CMYK��ɫֵ��M����
		\param y CMYK��ɫֵ��Y����
		\param k CMYK��ɫֵ��K����
		\return �Ƿ�ı�������
	*/
	virtual bool SetCMYK(LPCWSTR name, WORD c, WORD m, WORD y, WORD k) = 0;

	//! �õ�ֵ����Ϊ����ֵ��������
	/*!
		\param[in] name ������������
		\param[out] year ��ȡ�ɹ�ʱ������(1980-2099)��ʧ��ʱ���ı���ֵ
		\param[out] month ��ȡ�ɹ�ʱ����·�(0-12)��ʧ��ʱ���ı���ֵ
		\param[out] day ��ȡ�ɹ�ʱ�����(0-31)��ʧ��ʱ���ı���ֵ
		\return �Ƿ��ȡ�ɹ�
	*/
	virtual bool GetDate(LPCWSTR name, int& year, int& month, int& day) = 0;

	//! ����ֵ����Ϊ����ֵ��������
	/*!
		\param name ������������
		\param year ���(1980-2099)
		\param month �·�(0-12)
		\param day ��(0-31)
		\return �Ƿ�ı�������
	*/
	virtual bool SetDate(LPCWSTR name, int year, int month, int day) = 0;

	//! �õ�ֵ����Ϊ����ʱ��ֵ��������
	/*!
		\param[in] name ������������
		\param[out] year ��ȡ�ɹ�ʱ������(1980-2099)��ʧ��ʱ���ı���ֵ
		\param[out] month ��ȡ�ɹ�ʱ����·�(0-12)��ʧ��ʱ���ı���ֵ
		\param[out] day ��ȡ�ɹ�ʱ�����(0-31)��ʧ��ʱ���ı���ֵ
		\param[out] hour ��ȡ�ɹ�ʱ���Сʱ(0-24)��ʧ��ʱ���ı���ֵ
		\param[out] minute ��ȡ�ɹ�ʱ������(0-60)��ʧ��ʱ���ı���ֵ
		\param[out] second ��ȡ�ɹ�ʱ�����(0-60)��ʧ��ʱ���ı���ֵ
		\return �Ƿ��ȡ�ɹ�
	*/
	virtual bool GetDateTime(LPCWSTR name, int& year, int& month, int& day, 
		int& hour, int& minute, int& second) = 0;

	//! ����ֵ����Ϊ����ʱ��ֵ��������
	/*!
		\param name ������������
		\param year ���(1980-2099)
		\param month �·�(0-12)
		\param day ��(0-31)
		\param hour Сʱ(0-24)
		\param minute ����(0-60)
		\param second ��(0-60)
		\return �Ƿ�ı�������
	*/
	virtual bool SetDateTime(LPCWSTR name, int year, int month, int day, 
		int hour, int minute, int second) = 0;

	//! �õ�ֵ����Ϊ�����������������
	/*!
		\param[in] name ������������
		\param[out] items Ҫ���ĸ��������飬������ count ��
		\param[in] count �����Ԫ��������
		\return ��ȡ����Ԫ�ظ����������� count
	*/
	virtual long GetDoubleArray(LPCWSTR name, double* items, long count) = 0;

	//! ����ֵ����Ϊ�����������������
	/*!
		\param name ������������
		\param items Ҫ����ĸ���������
		\param count �����Ԫ�ظ���
		\return �Ƿ����óɹ�
	*/
	virtual bool SetDoubleArray(LPCWSTR name, const double* items, long count) = 0;
	
	//! �õ�ֵ����Ϊ���������������
	/*!
		\param[in] name ������������
		\param[out] items Ҫ�����������飬������ count ��
		\param[in] count �����Ԫ��������
		\return ��ȡ����Ԫ�ظ����������� count
	*/
	virtual long GetIntArray(LPCWSTR name, long* items, long count) = 0;

	//! ����ֵ����Ϊ���������������
	/*!
		\param name ������������
		\param items Ҫ�������������
		\param count �����Ԫ�ظ���
		\return �Ƿ����óɹ�
	*/
	virtual bool SetIntArray(LPCWSTR name, const long* items, long count) = 0;
	
	//! �õ�ֵ����Ϊ�����ƻ����������
	/*!
		\param[in] name ������������
		\param[out] buf Ҫ���Ļ��壬������ size �ֽ�
		\param[in] size �������󳤶�
		\return ��ȡ���Ļ����ֽڳ��ȣ������� size
	*/
	virtual long GetBinary(LPCWSTR name, LPVOID buf, long size) = 0;

	//! ����ֵ����Ϊ�����ƻ����������
	/*!
		\param name ������������
		\param buf Ҫ����Ļ���
		\param size ������ֽڳ���
		\return �Ƿ����óɹ�
	*/
	virtual bool SetBinary(LPCWSTR name, LPCVOID buf, long size) = 0;
};

#endif // X3_XML_ICONFIGSECTION_H_
