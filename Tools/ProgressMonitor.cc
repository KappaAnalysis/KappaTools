#include <iostream>
#include <iomanip>
#include "ProgressMonitor.h"

using namespace std;

bool ProgressMonitor::abortProgram = false;

ProgressMonitor::ProgressMonitor(const unsigned long nEvents)
{
	signal(SIGINT, CatchSignal);
	this->nEvents = nEvents;
	bShow = isatty(1);
	Reset();
}

bool ProgressMonitor::Update()
{
	return Update(++(this->cEvent));
}

bool ProgressMonitor::Update(const unsigned long cEvent)
{
	this->cEvent = cEvent;
	if (bShow && (this->cEvent % 10000 == 0))
	{
		cout << "Status: ";
		cout << *this;
		cout << "\r";
		cout.flush();
	}
	return !abortProgram;
}

void ProgressMonitor::IncMax(const unsigned long nEvents)
{
	this->nEvents += nEvents;
	Reset();
}

void ProgressMonitor::Reset()
{
	cEvent = 0;
	gettimeofday(&tStartTime, 0);
}

struct SecTime
{
	SecTime(const long _sec) : sec(_sec) {}
	long sec;
};

ostream &operator<<(ostream &os, const SecTime &st)
{
	return os
		<< setw(2) << setfill('0') << st.sec / 3600 << ":"
		<< setw(2) << setfill('0') << (st.sec / 60) % 60 << ":"
		<< setw(2) << setfill('0') << st.sec % 60;
}

ostream &operator<<(ostream &os, const ProgressMonitor &pm)
{
	struct timeval now;
	gettimeofday(&now, 0);
	double speed = pm.cEvent / (double)(now.tv_sec - pm.tStartTime.tv_sec + 1.0e-6 * (now.tv_usec - pm.tStartTime.tv_usec));
	unsigned long sec = (unsigned long)((pm.nEvents - pm.cEvent) / speed);
	os << pm.cEvent << "/" << pm.nEvents << " - "
		<< SecTime(sec) << "/" << SecTime((int)(pm.nEvents / speed)) << " - "
		<< (int)speed << " events / s" << " - ";
	if ((int)(100.0 * pm.cEvent / pm.nEvents + 0.5) < 100)
		return os << setw(3) << setfill(' ') << setprecision(2) << 100.0 * pm.cEvent / pm.nEvents << "%    ";
	else
		return os << "100%    ";
}
