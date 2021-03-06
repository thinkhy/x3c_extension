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

/*! \file Ix_TempFolder.h
 *  \brief 定义临时目录操作的接口 Ix_TempFolder
 *  \author Zhang Yun Gui, C++ Plugin Framework
 *  \date   2010.10.22
 */
#ifndef X3_UTIL_ITEMPFOLDER_H_
#define X3_UTIL_ITEMPFOLDER_H_

#include <Ix_Object.h>

const XCLSID CLSID_TempFolder("6d215195-061e-4c03-827d-8c692c293617");

//! 临时目录操作的接口
/*!
	\interface Ix_TempFolder
	\ingroup _GROUP_UTILITY_
	\see CLSID_TempFolder
*/
interface Ix_TempFolder
{
	//! 设置根目录，影响后续所有新创建的对象
	/*!
		\param path 根目录的全名
	*/
	virtual void SetRootPath(const std::wstring& path) = 0;

	//! 删除创建的临时目录
	/*! 如果不调用本函数，该临时子目录会在本对象销毁时或程序退出时也会自动删除
		\return 是否删除成功
	*/
	virtual bool DeleteFolder() = 0;

	//! 创建临时目录，初始化
	/*! 该临时子目录会在本对象销毁时或程序退出时自动删除
		\param prefix 子目录名的前缀，例如“pdf”
		\return 临时目录的全名，返回串长度小于2时表示失败
	*/
	virtual std::wstring CreateFolder(const std::wstring& prefix) = 0;

	//! 返回临时目录的全名
	virtual std::wstring GetPath() const = 0;

	//! 计算新的临时文件名
	/*!
		\param prefix 文件名前缀，可为空
		\param ext 文件扩展名，例如“xml”、“_s.jpg”
		\return 新的文件全名
	*/
	virtual std::wstring CreateFileName(const std::wstring& prefix, 
		const std::wstring& ext) = 0;
};

#endif // X3_UTIL_ITEMPFOLDER_H_
