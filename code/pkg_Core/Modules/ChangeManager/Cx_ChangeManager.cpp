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

#include "StdAfx.h"
#include "Cx_ChangeManager.h"

static DWORD HashKey(const char* str)
{
	DWORD value = 0;
	for ( ; *str; ++str)
	{
		value = (value<<5) + value + *str;
	}
	return value;
}

Cx_ChangeManager::Cx_ChangeManager()
{
}

Cx_ChangeManager::~Cx_ChangeManager()
{
}

bool Cx_ChangeManager::IsUniqueObserverType(DWORD key, const char* type)
{
	std::map<DWORD, std::string>::iterator it = m_types.find(key);

	if (it == m_types.end())
	{
		m_types[key] = type;
	}
	else if (it->second.compare(type) != 0)
	{
		LOG_EVENT_ANSI("The observer type is conflicted.", 
			it->second << L", " << type, kLogType_Fatal, __FILE__, __LINE__);
		ASSERT_MESSAGE(false, "The observer type is conflicted.");
		return false;
	}

	return true;
}

void Cx_ChangeManager::RegisterObserver(const char* type, Ix_ChangeObserver* observer)
{
	ASSERT(observer && type);

	DWORD key = HashKey(type);
	std::pair<MAP_IT, MAP_IT> range (m_observers.equal_range(key));

	VERIFY(IsUniqueObserverType(key, type));

	for (MAP_IT it = range.first; it != range.second; ++it)
	{
		if (NULL == it->second)
		{
			it->second = observer;
			return;
		}
	}

	m_observers.insert(ObserverPair(key, observer));
}

void Cx_ChangeManager::UnRegisterObserver(const char* type, Ix_ChangeObserver* observer)
{
	std::pair<MAP_IT, MAP_IT> range (m_observers.equal_range(HashKey(type)));

	for (MAP_IT it = range.first; it != range.second; ++it)
	{
		if (it->second == observer)
		{
			it->second = NULL;	//m_observers.erase(it);
			break;
		}
	}
}

void Cx_ChangeManager::ChangeNotify(const char* type, ChangeNotifyData* data)
{
	ASSERT(data != NULL);

	DWORD key = HashKey(type);
	std::pair<MAP_IT, MAP_IT> range (m_observers.equal_range(key));

	for (ObserverMap::const_iterator it = range.first; it != range.second; ++it)
	{
		if (it->second)
		{
			it->second->Update(data);
		}
	}
}
