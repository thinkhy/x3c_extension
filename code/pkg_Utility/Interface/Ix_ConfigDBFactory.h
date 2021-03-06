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

/*! \file Ix_ConfigDBFactory.h
 *  \brief 定义配置数据的创建接口 Ix_ConfigDBFactory
 *  \author Zhang Yun Gui, C++ Plugin Framework
 *  \date   2010.10.22
 */
#ifndef X3_UTIL_ICONFIGDBFACTORY_H_
#define X3_UTIL_ICONFIGDBFACTORY_H_

#include <XComPtr.h>

const XCLSID CLSID_ConfigDBFactory("6f3ca83f-6193-48ce-a188-24b2afb45432");

//! 数据库数据读写对象的创建接口
/*! 将数据库的增删改查以数据节点(Ix_ConfigData, CConfigIOSection)的简化方式进行操作。\n
	Ix_ConfigData接口的部分含义重新定义了，见 Cx_CfgDatabase 对应函数的说明。\n
	在增加记录时可以使用 \@NEWID 标记某个字段取值为(最大ID+1)；\n
	在增加或修改记录时可以使用以@开头的函数名，例如 CURDATE(), CURTIME(), NOW() ，内部会自动换为对应的数据库函数名。
	\interface Ix_ConfigDBFactory
	\ingroup _GROUP_UTILITY_
	\see CLSID_ConfigDBFactory, Cx_CfgDatabase
*/
interface Ix_ConfigDBFactory
{
	//! 打开Access数据库文件
	/*!
		\param filename 数据库文件全名(*.mdb, *.accdb)
		\param dbuser 数据库用户名
		\param password 该用户对应的密码
		\return 数据库数据访问对象(Ix_ConfigData)，为空对象时表示失败
		\see Ix_ConfigData, Ix_ConfigTransaction, Cx_CfgDatabase
	*/
	virtual Cx_Ptr OpenAccessDB(
		const std::wstring& filename, 
		const std::wstring& dbuser = L"", 
		const std::wstring& password = L"") = 0;

	//! 打开SQLServer数据库
	/*!
		\param server 数据库服务器名
		\param database 数据库名
		\param dbuser 数据库用户名
		\param password 该用户对应的密码
		\return 数据库数据访问对象(Ix_ConfigData)，为空对象时表示失败
		\see Ix_ConfigData, Ix_ConfigTransaction, Cx_CfgDatabase
	*/
	virtual Cx_Ptr OpenSQLServerDB(
		const std::wstring& server, 
		const std::wstring& database, 
		const std::wstring& dbuser = L"", 
		const std::wstring& password = L"") = 0;
};

#endif // X3_UTIL_ICONFIGDBFACTORY_H_
