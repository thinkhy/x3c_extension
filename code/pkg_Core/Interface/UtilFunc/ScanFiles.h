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

/*! \file ScanFiles.h
 *  \brief ����ɨ��Ŀ¼�ļ��ĺ��� ScanFiles ���ص��� CScanFilesCallback
 *  \author Zhang Yun Gui, C++ Plugin Framework
 *  \date   2010.10.22
 */
#ifndef UTILFUNC_SCANFILES_H_
#define UTILFUNC_SCANFILES_H_

//! ɨ��Ŀ¼�ļ�ʱ�Ļص��ӿ�
interface IScanFilesCallback
{
	//! ɨ�赽һ����Ŀ¼��֪ͨ
	/*!
		\param[in] path ɨ�赽����Ŀ¼���ļ�ȫ����ĩβ�з�б��
		\param[in,out] recursive �Ƿ�ɨ�����Ŀ¼�µ��ļ���Ĭ��Ϊ ScanFiles() �����ֵ
		\param[in,out] cancel ���Ҫֹͣ����ɨ��������Ϊ true
	*/
	virtual void OnCheckPath(LPCWSTR path, bool& recursive, bool& cancel) = 0;

	//! ɨ�赽һ���ļ���֪ͨ
	/*!
		\param[in] filename ɨ�赽���ļ����ļ�ȫ��
		\param[in] ext ����к�׺�����Ե�ſ�ͷ������Ϊ�մ�
		\param[in,out] cancel ���Ҫֹͣ����ɨ��������Ϊ true
	*/
	virtual void OnCheckFile(LPCWSTR filename, LPCWSTR ext, bool& cancel) = 0;
};

//! ɨ��Ŀ¼�ļ�ʱ�Ļص��ӿڵ�Ĭ��ʵ����
/*!
	\ingroup _GROUP_UTILFUNC
	\see ScanFiles
*/
class CScanFilesCallback : public IScanFilesCallback
{
public:
	CScanFilesCallback() {}
	virtual ~CScanFilesCallback() {}

	virtual void OnCheckPath(LPCWSTR path, bool& recursive, bool& cancel)
		{ path; recursive; cancel; }
	virtual void OnCheckFile(LPCWSTR filename, LPCWSTR ext, bool& cancel)
		{ filename; ext; cancel; }
};

//! ɨ��Ŀ¼�µ������ļ�
/*!
	\ingroup _GROUP_UTILFUNC
	\param back ����ص��ӿڵ�ʵ�ֶ���ĵ�ַ
	\param path Ŀ¼���ļ�ȫ�����ǿգ�ĩβ�ķ�б�ſ��п���
	\param recursive �Ƿ�ɨ����Ŀ¼�µ��ļ�
	\return ɨ������ļ�����
	\see CScanFilesCallback
*/
inline long ScanFiles(IScanFilesCallback* back, 
					  LPCWSTR path, bool recursive)
{
	WIN32_FIND_DATAW fd;
	WCHAR filename[MAX_PATH];
	long count = 0;
	
	StrCpyNW(filename, path, MAX_PATH);
	PathAppendW(filename, L"*.*");
	
	HANDLE hfind = ::FindFirstFileW(filename, &fd);
	BOOL loop = (hfind != INVALID_HANDLE_VALUE);
	bool cancel = false;

	while (loop && !cancel)
	{
		if (fd.dwFileAttributes & (FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_SYSTEM))
		{
			loop = ::FindNextFileW(hfind, &fd);
			continue;
		}

		if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			if (fd.cFileName[0] != '.')
			{
				StrCpyNW(filename, path, MAX_PATH);
				PathAppendW(filename, fd.cFileName);
				PathAddBackslashW(filename);

				bool bTempRecursive = recursive;
				back->OnCheckPath(filename, bTempRecursive, cancel);
				if (bTempRecursive && !cancel)
				{
					count += ScanFiles(back, filename, recursive);
				}
			}
		}
		else
		{
			StrCpyNW(filename, path, MAX_PATH);
			PathAppendW(filename, fd.cFileName);

			count++;
			back->OnCheckFile(filename, 
				PathFindExtensionW(filename), cancel);
		}
		
		loop = ::FindNextFileW(hfind, &fd);
	}
	::FindClose(hfind);
	
	return count;
}

//! ɨ���ض���׺���ļ��Ļص���
/*!
	\ingroup _GROUP_UTILFUNC
	\see ScanFiles
*/
class CScanFilesByExtension : public CScanFilesCallback
{
public:
	//! ���캯��
	/*!
		\param files ���ڴ���ҵ����ļ�ȫ��
		\param ext �ض��ĺ�׺�����Ե�ſ�ͷ
	*/
	CScanFilesByExtension(std::vector<std::wstring>* files, const std::wstring& ext)
		: m_files(files), m_ext(ext)
	{
		ASSERT(m_files != NULL);
	}

protected:
	virtual void OnCheckFile(LPCWSTR filename, LPCWSTR ext, bool& cancel)
	{
		cancel;
		if (StrCmpIW(m_ext.c_str(), ext) == 0)
		{
			m_files->push_back(filename);
		}
	}

protected:
	std::vector<std::wstring>*	m_files;	//!< ����ҵ����ļ�ȫ��
	std::wstring				m_ext;		//!< �ض��ĺ�׺�����Ե�ſ�ͷ
};

#endif // UTILFUNC_SCANFILES_H_