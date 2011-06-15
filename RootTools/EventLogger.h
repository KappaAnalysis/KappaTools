#ifndef KAPPA_EVENTLOGGER_H
#define KAPPA_EVENTLOGGER_H

#include <iostream>
#include <Kappa/DataFormats/interface/KMetadata.h>

class EventID
{
public:
	EventID(const KEventMetadata *metadata) :
		nEvent(metadata->nEvent), nLumi(metadata->nLumi),
		nRun(metadata->nRun), nBX(metadata->nBX) {};

	bool operator<(const EventID &other) const
	{
		if (nRun < other.nRun)
			return true;
		else if (nLumi < other.nLumi)
			return true;
		else if (nEvent < other.nEvent)
			return true;
		else if (nBX < other.nBX)
			return true;
		else
			return false;
	}

	event_id nEvent;
	lumi_id nLumi;
	run_id nRun;
	bx_id nBX;
};

std::ostream &operator<<(std::ostream &output, const EventID &id);

template<typename TContainer>
class EventLogger
{
public:
	EventLogger() {}
	void clear() { store.clear(); }
	bool has(const KEventMetadata *metadata) { return store.find(typename TContainer::value_type(metadata)) != store.end(); }
	void put(const KEventMetadata *metadata) { store.insert(store.begin(), typename TContainer::value_type(metadata)); }
	void print()
	{
		for (typename TContainer::const_iterator it = store.begin(); it != store.end(); ++it)
			std::cout << *it << std::endl;
	}
private:
	TContainer store;
};

#endif
