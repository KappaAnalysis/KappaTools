#include <TFile.h>
#include <iostream>
#include "PlotTools/PlotInterface.h"
#include "KappaTools/RootTools/libKRootTools.h"

using namespace std;

int main(int, char **argv)
{
	TFile file("output2.root", "READ_ONLY");
	file.ls();
	cout << GetDirObjectsMap(&file) << endl;
//	cout << match_keys("TDirectoryFile", GetDirObjectsMap(&file)) << endl;
	cout << GetDirObjectsMap<TH1D>(&file) << endl;
	return 0;
}
