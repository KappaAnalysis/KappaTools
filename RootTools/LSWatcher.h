#ifndef LSWATCHER_H
#define LSWATCHER_H

#include <DataFormats/interface/KMetadata.h>

class LSWatcher
{
public:
	LSWatcher();
	bool Changed(KEventMetadata *meta_event = 0);
private:
	bool changed;
	run_id run;
	lumi_id lumi;
};

#endif
