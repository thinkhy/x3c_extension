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

/*! \file Ix_FileVersion.h
 *  \brief 定义临时目录操作的接口 Ix_FileVersion
 *  \author Zhang Yun Gui, C++ Plugin Framework
 *  \date   2010.12.28
 */
#ifndef X3_UTIL_IFILEVERSION_H_
#define X3_UTIL_IFILEVERSION_H_

//! 获取文件版本号的接口
/*!
	\interface Ix_FileVersion
	\ingroup _GROUP_UTILITY_
	\see CLSID_FileUtility, FileUtility()
*/
interface Ix_FileVersion
{
	//! 获取模块的文件版本号
	/*!
		\param[out] version 填充版本号，例如“1.0.12.0”
		\param[in] filename DLL或EXE的文件全名
		\return 是否获取成功
	*/
	virtual bool GetFileVersion(std::wstring& version, const std::wstring& filename) = 0;

	//! 获取模块的文件版本号
	/*!
		\param[out] ver1 填充版本号的主版本，例如“1.2.3.0”的1
		\param[out] ver2 填充版本号的次版本，例如“1.2.3.0”的2
		\param[out] ver3 填充版本号的第三位，例如“1.2.3.0”的3
		\param[out] ver4 填充版本号的第四位，例如“1.2.3.0”的0
		\param[in] filename DLL或EXE的文件全名
		\return 是否获取成功
	*/
	virtual bool GetFileVersion(WORD& ver1, WORD& ver2, 
		WORD& ver3, WORD& ver4, const std::wstring& filename) = 0;

	//! 获取模块的文件说明
	/*!
		\param[out] description 填充文件说明
		\param[in] filename DLL或EXE的文件全名
		\return 是否获取成功
	*/
	virtual bool GetFileDescription(std::wstring& description, const std::wstring& filename) = 0;
};

#endif // X3_UTIL_IFILEVERSION_H_
