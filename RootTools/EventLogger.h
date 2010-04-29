#ifndef KAPPA_EVENTLOGGER_H
#define KAPPA_EVENTLOGGER_H

#include <vector>
#include <iostream>
#include "DataFormats/interface/KMetadata.h"

class EventID
{
public:
	unsigned int nEvent;
	unsigned int nLumi;
	unsigned int nRun;
	int nBX;
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
