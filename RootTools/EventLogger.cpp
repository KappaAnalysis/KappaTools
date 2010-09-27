#include "EventLogger.h"

std::ostream &operator<<(std::ostream &output, const EventID &id)
{
	return output << id.nRun << "\t" << id.nLumi << "\t" << id.nEvent << "\t" << id.nBX;
}
