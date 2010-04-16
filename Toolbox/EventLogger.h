#ifndef KEventLogger
#define KEventLogger

#include <vector>
#include <iostream>
#include "DataFormats/interface/KMetadata.h"

class EventID
{
public:
	unsigned long nEvent;
	unsigned long nLumi;
	unsigned long nRun;
	unsigned long nBX;
	EventID(KEventMetadata * metadata)
	{
		nEvent = metadata->nEvent;
	};
};

class EventLogger
{
	std::vector<EventID> store;
	public:
		EventLogger();
		void clear();
		void put(KEventMetadata * metadata);
		void print();
};
#endif
