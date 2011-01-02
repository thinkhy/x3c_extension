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

/*! \file Ix_FileUtility.h
 *  \brief �����ļ���Ŀ¼��ʵ�ò����Ľӿ� Ix_FileUtility
 *  \author Zhang Yun Gui, C++ Plugin Framework
 *  \date   2010.10.22
 */
#ifndef X3_UTIL_IFILEUTILITY_H_
#define X3_UTIL_IFILEUTILITY_H_

#include <XComPtr.h>

const XCLSID CLSID_FileUtility("933b3bf9-69d0-4be7-8e49-92b73669d8db");

//! �ļ���Ŀ¼��ʵ�ò����Ľӿ�(�ļ����)
/*!
	\interface Ix_FileUtility1
	\ingroup _GROUP_UTILITY_
	\see CLSID_FileUtility, FileUtility()
*/
interface Ix_FileUtility1
{
	//! ���һ��Ŀ¼���ļ��Ƿ����
	/*!
		\param filename Ŀ¼���ļ����ļ�ȫ���������Ŀ¼��ĩβҪ��б��
		\param checkWrite �Ƿ����д
		\return Ŀ¼���ļ��Ƿ���ڣ����checkWriteΪtrue��ͬʱҪ��ɶ�д
	*/
	virtual bool IsPathFileExists(LPCWSTR filename, bool checkWrite = false) = 0;

	//! ����Ƿ�ΪĿ¼��
	/*!
		\param filename Ŀ¼���ļ����ļ�ȫ����
			���checkExistsΪtrue��Ŀ¼ĩβ��б�ſ��п���
		\param checkExists �Ƿ����ʵ���ļ�������������Ƿ�ΪĿ¼��
		\return true:Ŀ¼, false:�ļ�
	*/
	virtual bool IsPath(LPCWSTR filename, bool checkExists = false) = 0;

	//! �����ļ��޸�����ʱ��
	/*!
		\param filename �ļ�ȫ��
		\return ����ʱ�䣬��ʽΪ��YYYY-MM-DD HH:MM:SS����ʧ��ʱΪ�մ�
	*/
	virtual std::wstring GetModifyTime(const std::wstring& filename) = 0;

	//! �����ļ���С���ֽ�
	/*!
		\param filename �ļ�ȫ��
		\return �ļ���С���ֽڣ�ʧ��ʱΪ0������4GʱΪ0xFFFFFFFF
		\see FileSizeToString
	*/
	virtual ULONG GetFileSize(const std::wstring& filename) = 0;
};

//! �ļ���Ŀ¼��ʵ�ò����Ľӿ�(�ļ��Ķ�����)
/*!
	\interface Ix_FileUtility2
	\ingroup _GROUP_UTILITY_
	\see CLSID_FileUtility, FileUtility()
*/
interface Ix_FileUtility2
{
	//! Ϊһ���ļ�ȫ�����������м�Ŀ¼
	/*! ʧ��ʱ���� LOG_ERROR2 ��¼��־
		\param filename �ļ���Ŀ¼��ȫ��
		\param isPath ������filename��·���������ļ���
		\return �Ƿ񴴽��ɹ�
	*/
	virtual bool CreateDirectory(LPCWSTR filename, bool isPath) = 0;

	//! ȷ��һ���ļ����ǿ�д��(�Զ�����Ŀ¼��ȥ��ֻ������)
	/*! ʧ��ʱ���� LOG_ERROR2 ��¼��־
		\param filename �ļ�ȫ��
		\return �Ƿ�ɴ����ļ���ɸ�д
	*/
	virtual bool VerifyFileCanWrite(LPCWSTR filename) = 0;

	//! ɾ��һ��Ŀ¼���ļ�
	/*! ʧ��ʱ���� LOG_ERROR2 ��¼��־
		\param filename Ŀ¼���ļ����ļ�ȫ��
		\param recycle true��ʾ�Ž�����վ��false��ʾֱ��ɾ��
		\return �Ƿ�ִ�гɹ�. �ļ�ȫ��Ϊ�ջ��ļ��������򷵻�true
	*/
	virtual bool DeletePathFile(LPCWSTR filename, bool recycle = false) = 0;

	//! �ƶ�һ��Ŀ¼���ļ�
	/*! ʧ��ʱ���� LOG_ERROR2 ��¼��־���Զ�����Ŀ���ļ����ļ���
		\param oldFile ԭ����Ŀ¼���ļ����ļ�ȫ��
		\param newFile �µ�Ŀ¼���ļ����ļ�ȫ��
		\return �Ƿ�ִ�гɹ�. oldFileΪ�ջ�ԭ�ļ��������򷵻�true
	*/
	virtual bool MovePathFile(LPCWSTR oldFile, LPCWSTR newFile) = 0;

	//! ������һ��Ŀ¼���ļ�
	/*! ʧ��ʱ���� LOG_ERROR2 ��¼��־
		\param oldFile ԭ����Ŀ¼���ļ����ļ�ȫ��
		\param newFile �µ�Ŀ¼���ļ����ļ�ȫ��
		\return �Ƿ�ִ�гɹ�. oldFileΪ�ջ�ԭ�ļ��������򷵻�true
	*/
	virtual bool RenamePathFile(LPCWSTR oldFile, LPCWSTR newFile) = 0;

	//! ����һ��Ŀ¼���ļ�
	/*! ʧ��ʱ���� LOG_ERROR2 ��¼��־���Զ�����Ŀ���ļ����ļ���
		\param oldFile ԭ����Ŀ¼���ļ����ļ�ȫ��
		\param newFile �µ�Ŀ¼���ļ����ļ�ȫ��
		\return �Ƿ�ִ�гɹ�. oldFileΪ�ջ�ԭ�ļ��������򷵻�true
	*/
	virtual bool CopyPathFile(LPCWSTR oldFile, LPCWSTR newFile) = 0;

	//! ������Ϣ���ӵ���ߴ���
	virtual void SetMsgBoxOwnerWnd(HWND hwnd) = 0;

	//! ������Ϣ���ӵ���ߴ���
	virtual HWND GetMsgBoxOwnerWnd() = 0;
};

//! �ļ���Ŀ¼��ʵ�ò����Ľӿ�(�ļ���ת��)
/*!
	\interface Ix_FileUtility3
	\ingroup _GROUP_UTILITY_
	\see CLSID_FileUtility, FileUtility()
*/
interface Ix_FileUtility3
{
	//! ���·��ת��Ϊ����·��
	/*! ��һ������ڸ����ο�·�������·��ת��Ϊ����·��������Ѿ��Ǿ���·���򲻱�
		\param relFile Ҫת�������·�������硰./abc������/Root������../1/2.dat��
		\param relIsFile ���·�����ļ�������·����
		\param baseFile �ο�·����������ĸ�·����ת����Ϊ����ȡEXE·��
		\param baseIsFile �ο�·�����ļ�������·����
		\return ת����ľ���·�������relIsFileΪfalse�����·��ĩβ��б��
	*/
	virtual std::wstring RelToAbs(LPCWSTR relFile, bool relIsFile, 
		LPCWSTR baseFile = NULL, bool baseIsFile = true) = 0;

	//! ����·��ת��Ϊ���·��
	/*! ��һ������·��ת��Ϊ����ڸ����ο�·�������·��
		\param absFile Ҫת���ľ���·��
		\param absIsFile ����·�����ļ�������·����
		\param baseFile �ο�·����������ĸ�·����ת����Ϊ/*! ����ȡEXE·��
		\param baseIsFile �ο�·�����ļ�������·����
		\return ת��������·�������relIsFileΪfalse�����·��ĩβ��б�ţ�
			���ʧ�����ԭ��·����ͬ
	*/
	virtual std::wstring AbsToRel(LPCWSTR absFile, bool absIsFile, 
		LPCWSTR baseFile = NULL, bool baseIsFile = true) = 0;

	//! �ı��ļ�ȫ���ĺ�׺��
	/*!
		\param[in] filename �������ļ�ȫ�������ļ��Ƿ�����޹�
		\param[in] suffix �µĺ�׺�������뺬�е��
		\return �µ��ļ�ȫ��
	*/
	virtual std::wstring ChangeFileNameSuffix(
		LPCWSTR filename, LPCWSTR suffix) = 0;

	//! ����·�����ļ�������׺���γ�һ���ļ�ȫ��
	/*!
		\param path Ŀ¼ȫ�����ǿգ�ĩβ��б�ſ��п���
		\param title �ļ������⣬�ǿգ�����·�������ext��Ϊ������Ժ�׺��
		\param ext �ļ���չ��������·�����ļ������⣬����û�е��
		\return �µ��ļ�ȫ��
	*/
	virtual std::wstring MakeFileName(const std::wstring& path, 
		const std::wstring& title, const std::wstring& ext) = 0;

	//! �����µ�����ļ���
	/*!
		\param path Ŀ¼ȫ�������ļ��ڸ�Ŀ¼��Ψһ��ĩβ��б�ſ��п���
		\param prefix �ļ���ǰ׺�����硰t������Ϊ��
		\param ext �ļ���չ������ſ��Բ��ǵ�һ���ַ���û�е������Զ����ϣ�
			���硰xml������_s.jpg��
		\param returnRel �Ƿ񷵻�����ļ�����false��ʾ�����µľ����ļ�ȫ��
		\return �µ�����ļ��������硰t12.xml��
	*/
	virtual std::wstring CreateFileName(const std::wstring& path, 
		const std::wstring& prefix, const std::wstring& ext, 
		bool returnRel = true) = 0;
};

//! �ļ���Ŀ¼��ʵ�ò����Ľӿ�(�ļ�����ȡ)
/*!
	\interface Ix_FileUtility4
	\ingroup _GROUP_UTILITY_
	\see CLSID_FileUtility, FileUtility()
*/
interface Ix_FileUtility4
{
	//! �õ��ļ������⣬��·���ͺ�׺��
	virtual std::wstring GetFileTitle(LPCWSTR filename) = 0;

	//! �õ��ļ���Ŀ¼���ļ�������·��
	virtual std::wstring GetFileName(LPCWSTR filename) = 0;

	//! �õ��ļ���չ�������е��
	virtual std::wstring GetExtension(LPCWSTR filename) = 0;

	//! �õ��ļ���Ŀ¼���ڵ�Ŀ¼��ĩβ��б��
	/*!
		\param filename �ļ���Ŀ¼���ļ�ȫ����Ŀ¼ĩβ��б�ſ��п���
		\return ���ڵ�Ŀ¼��ĩβ��б��
	*/
	virtual std::wstring GetPathOfFile(LPCWSTR filename) = 0;

	//! �ж������ļ����Ƿ���ͬ
	/*! �������Ƚ������ļ�ȫ������������ļ������Զ�����Ŀ¼�ָ���
		\param[in] filename1 ��һ���ļ��л��ļ����ļ���
		\param[in] filename2 �ڶ����ļ��л��ļ����ļ���
		\param[out] samePartCount �����ΪNULL������ļ������м���������ͬ�ģ�
			�����ļ�ȫ���ĸ�������ָ�м��ļ��������ļ�������
		\return 0��ʾ�ļ�����ͬ��1��-1��ʾ�ļ�����ͬ
	*/
	virtual int CompareFileName(LPCWSTR filename1, LPCWSTR filename2, 
		long* samePartCount = NULL) = 0;
};

//! �ļ���Ŀ¼��ʵ�ò����Ľӿ�
/*!
	\interface Ix_FileUtility
	\ingroup _GROUP_UTILITY_
	\see CLSID_FileUtility
	\see FileUtility()->xxx(), RelToAbs.h �ļ�ʵ�ú���
*/
interface Ix_FileUtility
	: public Ix_FileUtility1
	, public Ix_FileUtility2
	, public Ix_FileUtility3
	, public Ix_FileUtility4
{
};

//! �õ��ļ���������
/*!
	\ingroup _GROUP_UTILITY_
	\see RelToAbs.h �ļ�ʵ�ú���
*/
inline Cx_Interface<Ix_FileUtility> FileUtility()
{
	Cx_Interface<Ix_FileUtility> pIFUtility(CLSID_FileUtility);
	ASSERT(pIFUtility.IsNotNull());
	return pIFUtility;
}

#endif // X3_UTIL_IFILEUTILITY_H_
