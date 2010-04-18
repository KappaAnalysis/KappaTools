#include "EventLogger.h"

EventLogger::EventLogger()
{

}

void EventLogger::clear()
{
	store.clear();
}

void EventLogger::put(KEventMetadata * metadata)
{
	store.push_back(EventID(metadata));
}

void EventLogger::print()
{
	for (std::vector<EventID>::iterator it = store.begin(); it != store.end(); it++)
	{
		std::cout << it->nRun << "\t" << it->nLumi << "\t" << it->nEvent << "\t" << it->nBX << "\n";
	}
}
