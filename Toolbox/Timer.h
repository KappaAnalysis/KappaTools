#ifndef TBTIMER_H
#define TBTIMER_H

#include <sys/time.h>

class Timer
{
public:
	Timer() { gettimeofday(&now, 0); }
	static double diff(const Timer &a, const Timer &b)
	{
		return fabs(a.now.tv_sec - b.now.tv_sec + 1.0e-6 * (a.now.tv_usec - b.now.tv_usec));
	}
private:
	struct timeval now;
};

#endif
