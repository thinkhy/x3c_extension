#pragma once

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
