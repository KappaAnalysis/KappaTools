#ifndef TBPROGRESSMONITOR_H
#define TBPROGRESSMONITOR_H

#include <ostream>
#include <sys/time.h>

class ProgressMonitor
{
public:
	ProgressMonitor(const unsigned long nPos = 0);
	~ProgressMonitor();
	bool Update();
	bool Update(const unsigned long cPos);
	void IncMax(const unsigned long nPos);
	void Reset();
private:
	bool bShow;
	unsigned long nPos, cPos;
	struct timeval tStartTime;
	static bool bAbort;
	static void CatchSignal(int);
	friend std::ostream &operator<<(std::ostream &os, const ProgressMonitor &pm);
};

std::ostream &operator<<(std::ostream &os, const ProgressMonitor &pm);

#endif
