/* Copyright (c) 2010 - All Rights Reserved
 *   Fred Stober <stober@cern.ch>
 */

#include <TRandom3.h>
#include <Kappa/DataFormats/interface/Kappa.h>
#include <Kappa/DataFormats/interface/KDebug.h>
#include "../../Toolbox/interface/libKToolbox.h"
#include "../../RootTools/interface/libKRootTools.h"

using namespace std;

void test(vector<KLV> &gen, vector<KLV> &reco)
{
	matchSort_deltaR metric(1.0);
	cout << "===========" << endl;
	vector<int> result = matchSort_Matrix(gen, gen.size(), reco, reco.size(), metric);
	cout << "GEN: " << gen << endl;
	cout << "----" << endl;
	cout << "REC: " << reco << endl;
	cout << "----" << endl;
	cout << result << endl;
	displayMatching(&gen, &reco, result);
	cout << "=FINISH=" << endl << endl;
/*
	Timer start;
	for (size_t i = 0; i < 100000; ++i)
		matchSort_Matrix(gen, gen.size(), reco, reco.size(), metric);
	cout << "Time: " << Timer::diff(start) << endl;
*/
}

int main()
{
	// Manual input:
	if (true)
	{
		vector<KLV> gen(4); // pt eta phi m
		gen[1].p4.SetCoordinates(30,  1.0, 0.5, 0);
		gen[3].p4.SetCoordinates(25, -1.0, 2.5, 0);
		gen[2].p4.SetCoordinates(15,  2.1, 1.1, 0);
		gen[0].p4.SetCoordinates(10,  2.3, 1.0, 0);
		vector<KLV> rec(3);
		rec[2].p4.SetCoordinates(20,  1.3, 0.4, 0);
		rec[0].p4.SetCoordinates(18, -0.9, 2.2, 0);
		rec[1].p4.SetCoordinates(13,  2.2, 1.1, 0);
		test(gen, rec);
	}

	// Automatic input
	TRandom3 rnd;
	for (size_t i = 0; i < 4; ++i)
	{
		vector<KLV> gen, rec;
		// GEN stuff
		for (size_t j = 0; j < (size_t)rnd.Poisson(10); ++j)
		{
			gen.push_back(KLV());
			gen.back().p4.SetCoordinates(rnd.Uniform(5, 100), rnd.Gaus(0, 5), rnd.Uniform(-M_PI, +M_PI), rnd.Gaus(0, 10));
			// RECO efficiency
			if (rnd.Uniform(0, 1) > 0.05)
			{
				rec.push_back(KLV());
				rec.back().p4.SetCoordinates(
					gen.back().p4.pt() * fabs(rnd.Gaus(0.8, 0.1)),
					gen.back().p4.eta() * fabs(rnd.Gaus(1, 0.1)),
					gen.back().p4.phi() + rnd.Uniform(0, 0.1),
					gen.back().p4.mass() * rnd.Gaus(1, 0.1));
			}
		}
		// RECO noise
		for (size_t j = 0; j < (size_t)rnd.Poisson(5); ++j)
		{
			rec.push_back(KLV());
			rec.back().p4.SetCoordinates(rnd.Uniform(1, 10), rnd.Gaus(0, 5), rnd.Uniform(-M_PI, +M_PI), rnd.Gaus(0, 10));
		}
		test(gen, rec);
	}
}
