#ifndef KAPPA_EVENTLOGGER_H
#define KAPPA_EVENTLOGGER_H

#include <vector>
#include <iostream>
#include "DataFormats/interface/KMetadata.h"

class EventID
{
public:
	event_id nEvent;
	lumi_id nLumi;
	run_id nRun;
	bx_id nBX;
	EventID(KEventMetadata * metadata) :
		nEvent(metadata->nEvent), nLumi(metadata->nLumi),
		nRun(metadata->nRun), nBX(metadata->nBX) {};
};

class EventLogger
{
public:
	EventLogger();
	void clear();
	void put(KEventMetadata * metadata);
	void print();

private:
	std::vector<EventID> store;
};

#endif
