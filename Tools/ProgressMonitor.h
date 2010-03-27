#ifndef ProgressMonitor_H
#define ProgressMonitor_H

#include <ostream>
#include <sys/time.h>
#include <signal.h>

class ProgressMonitor
{
	static bool abortProgram;
	bool bShow;
	static void CatchSignal(int sig) { abortProgram = true; };
public:
	ProgressMonitor(const unsigned long nEvents = 0);
	bool Update();
	bool Update(const unsigned long cEvent);
	void IncMax(const unsigned long nEvents);
	void Reset();
private:
	unsigned long nEvents, cEvent;
	struct timeval tStartTime;
	friend std::ostream &operator<<(std::ostream &os, const ProgressMonitor &pm);
};

std::ostream &operator<<(std::ostream &os, const ProgressMonitor &pm);

#endif

