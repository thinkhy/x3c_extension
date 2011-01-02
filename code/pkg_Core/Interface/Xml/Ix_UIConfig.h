/*! \file Ix_UIConfig.h
 *  \brief 定义界面配置数据读写接口 Ix_UIConfig
 *  \author Zhang Yun Gui, C++ Plugin Framework
 *  \date   2010.11.2
 */
#ifndef X3_VIEW_IUICONFIG_H_
#define X3_VIEW_IUICONFIG_H_
#pragma once

#include <ConfigIOSection.h>

const XCLSID CLSID_UIConfig("4472ba6d-d833-40b9-899f-edc017ec9166");

//! 界面配置数据读写接口
/*!
	\interface Ix_UIConfig
	\ingroup _GROUP_APPUI_
	\see CLSID_UIConfig
*/
interface Ix_UIConfig
{
	//! 返回界面配置数据对象，非空
	virtual Ix_ConfigData* GetUIConfig() = 0;

	//! 返回指定名称的界面配置节点
	virtual CConfigIOSection GetUISection(LPCWSTR name) = 0;

	//! 立即保持改变了的配置数据
	virtual bool Save() = 0;
};

#endif // X3_VIEW_IUICONFIG_H_
