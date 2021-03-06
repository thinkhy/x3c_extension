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

/*! \file Ix_ConfigData.h
 *  \brief 定义配置数据接口 Ix_ConfigData
 *  \author Zhang Yun Gui, C++ Plugin Framework
 *  \date   2010.10.22
 */
#ifndef X3_XML_ICONFIGDATA_H_
#define X3_XML_ICONFIGDATA_H_

#include "Ix_ConfigSection.h"

//! 配置数据接口
/*! 本接口所操作的数据对象相当于是在树状层次结构中的全部数据节点，
	而 CConfigIOSection 则对应于一个数据节点。\n
	立即保存可使用 CConfigTransaction 转换本对象和保存。
	\interface Ix_ConfigData
	\ingroup _GROUP_PLUGIN_XML_
*/
interface Ix_ConfigData
{
	//! 一个数据节点，同辅助类 CConfigIOSection
	typedef Cx_Interface<Ix_ConfigSection> ConfigIOSection;

	//! 得到根节点下的一个数据节点对象
	/*!
		\param name 数据节点名称，以正斜号或反斜号分隔多级绝对路径.
			为空串则返回根节点的数据节点
		\param autoCreate 不存在时是否自动添加数据节点
		\return 新的数据节点，不存在时根据autoCreate自动添加
	*/
	virtual ConfigIOSection GetSection(
		LPCWSTR name, bool autoCreate = true) = 0;
	
	//! 得到带整数标识属性参数的一个数据节点
	/*!
		\param parent 上一级的数据节点，为NULL则取根节点
		\param name 数据节点名称，以正斜号或反斜号分隔多级相对路径
		\param attrName 标识一个子数据节点的属性名称
		\param attrValue 该标识项对应的属性值
		\param autoCreate 不存在时是否自动添加数据节点
		\return 新的数据节点，不存在则自动添加
	*/
	virtual ConfigIOSection GetSection(
		Ix_ConfigSection* parent, LPCWSTR name, 
		LPCWSTR attrName, ULONG attrValue, 
		bool autoCreate = true) = 0;

	//! 得到带属性参数的一个数据节点
	/*!
		\param parent 上一级的数据节点，为NULL则取根节点
		\param name 数据节点名称，以正斜号或反斜号分隔多级相对路径
		\param attrName 标识一个子数据节点的属性名称
		\param attrValue 该标识项对应的属性值
		\param autoCreate 不存在时是否自动添加
		\return 新的数据节点，不存在则自动添加
	*/
	virtual ConfigIOSection GetSection(
		Ix_ConfigSection* parent, LPCWSTR name, 
		LPCWSTR attrName, LPCWSTR attrValue, 
		bool autoCreate = true) = 0;

	//! 得到带属性参数的一个数据节点
	/*!
		\param parent 上一级的数据节点，为NULL则取根节点
		\param name 数据节点名称，以正斜号或反斜号分隔多级相对路径
		\param attrName 标识一个子数据节点的第一个属性名称
		\param attrValue 该标识项对应的属性值
		\param attrName2 标识一个子数据节点的第二个属性名称
		\param attrValue2 该标识项对应的attrName2的属性值
		\param autoCreate 不存在时是否自动添加
		\return 新的数据节点，不存在则自动添加
	*/
	virtual ConfigIOSection GetSection(
		Ix_ConfigSection* parent, LPCWSTR name, 
		LPCWSTR attrName, LPCWSTR attrValue, 
		LPCWSTR attrName2, LPCWSTR attrValue2, 
		bool autoCreate = true) = 0;

	//! 得到带整数标识属性参数的一个数据节点
	/*!
		\param parent 上一级的数据节点，为NULL则取根节点
		\param name 数据节点名称，以正斜号或反斜号分隔多级相对路径
		\param attrName 标识一个子数据节点的第一个属性名称
		\param attrValue 该标识项对应的属性值
		\param attrName2 标识一个子数据节点的第二个属性名称
		\param attrValue2 该标识项对应的attrName2的属性值
		\param autoCreate 不存在时是否自动添加
		\return 新的数据节点，不存在则自动添加
	*/
	virtual ConfigIOSection GetSection(
		Ix_ConfigSection* parent, LPCWSTR name, 
		LPCWSTR attrName, ULONG attrValue, 
		LPCWSTR attrName2, ULONG attrValue2, 
		bool autoCreate = true) = 0;

	//! 得到节点名对应的子节点个数
	/*!
		\param parent 上一级的数据节点，为NULL则取根节点
		\param name 数据节点名称，以正斜号或反斜号分隔多级相对路径
		\return 子数据节点的个数
		\see GetSectionByIndex
	*/
	virtual long GetSectionCount(
		Ix_ConfigSection* parent, LPCWSTR name) = 0;

	//! 在节点名对应的子节点中得到指定序号的子数据节点
	/*!
		\param parent 上一级的数据节点，为NULL则取根节点
		\param name 数据节点名称，以正斜号或反斜号分隔多级相对路径
		\param index 要取的子数据节点的序号
		\return 新的数据节点，如果不存在则对该对象的读写操作将忽略，可以用 IsValid() 来检查是否为无效节点
		\see GetSectionCount
	*/
	virtual ConfigIOSection GetSectionByIndex(
		Ix_ConfigSection* parent, LPCWSTR name, long index) = 0;
	
	//! 添加一个数据节点
	/*!
		\param parent 上一级的数据节点，为NULL则取根节点
		\param name 数据节点名称，以正斜号或反斜号分隔多级相对路径
		\return 新的数据节点
	*/
	virtual ConfigIOSection AddSection(
		Ix_ConfigSection* parent, LPCWSTR name) = 0;

	//! 删除一个数据节点
	/*!
		\param sec 要删除的数据节点对象，只清除其内部数据，不释放该对象
		\return 是否删除成功
	*/
	virtual bool RemoveSection(Ix_ConfigSection* sec) = 0;
	
	//! 删除指定的数据节点的所有子节点
	/*!
		\param parent 要删除节点的上一级数据节点
		\param name 子节点名称，不能包含正斜号或反斜号
		\param attrName 子节点的标识属性名，可选值
		\param attrValue 标识属性名对应的值，attrName不为空时有效
		\return 删除的子节点个数
	*/
	virtual long RemoveChildren(Ix_ConfigSection* parent, LPCWSTR name, 
		LPCWSTR attrName = L"", LPCWSTR attrValue = L"") = 0;

	//! 删除指定的数据节点的所有子节点
	/*!
		\param parent 要删除节点的上一级数据节点
		\param name 子节点名称，不能包含正斜号或反斜号
		\param attrName 子节点的标识属性名，不为空
		\param attrValue 标识属性名attrName对应的值
		\return 删除的子节点个数
	*/
	virtual long RemoveChildren(Ix_ConfigSection* parent, LPCWSTR name, 
		LPCWSTR attrName, ULONG attrValue) = 0;

	//! 得到一个数据节点的上一级节点
	/*!
		\param sec 指定的数据节点对象
		\return 上一级数据节点对象，如果sec为根节点，则返回节点为无效节点(IsValid()==false)
	*/
	virtual ConfigIOSection GetParentSection(Ix_ConfigSection* sec) = 0;
};

#endif // X3_XML_ICONFIGDATA_H_
