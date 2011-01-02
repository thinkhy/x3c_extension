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

#ifndef _X3_CORE_CHANGEMANAGER_H
#define _X3_CORE_CHANGEMANAGER_H

#include <Ix_ChangeManager.h>

class Cx_ChangeManager : public Ix_ChangeManager
{
protected:
	Cx_ChangeManager();
	virtual ~Cx_ChangeManager();

protected:
	virtual void RegisterObserver(const char* type, Ix_ChangeObserver* observer);
	virtual void UnRegisterObserver(const char* type, Ix_ChangeObserver* observer);
	virtual void ChangeNotify(const char* type, ChangeNotifyData* data);

private:
	bool IsUniqueObserverType(DWORD key, const char* type);

private:
	typedef std::multimap<DWORD, Ix_ChangeObserver*> ObserverMap;
	typedef std::pair<DWORD, Ix_ChangeObserver*> ObserverPair;
	typedef ObserverMap::iterator MAP_IT;
	ObserverMap		m_observers;
	std::map<DWORD, std::string>	m_types;
};

#endif // _X3_CORE_CHANGEMANAGER_H
