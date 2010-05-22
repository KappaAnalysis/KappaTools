#include "BasePlot.h"

KappaTools::BasePlot::BasePlot()
{

}

TDirectory * KappaTools::BasePlot::getDirectory(TDirectory * tmpFile, TString tmpDirectory)
{
	//std::cout << "tmpFile:    " << tmpFile->GetPath() << "\n";
	//std::cout << "gDirectory: " << gDirectory->GetPath() << "\n";

	if (tmpDirectory=="")
	{
		tmpFile->cd();
		//std::cout << "tmpDirectory is empty... returning directory:" << tmpFile->GetPath() << "\n";
		//std::cout << "\ttmpFile:      " << tmpFile->GetPath() << "\n";
		//std::cout << "\tgDirectory:   " << gDirectory->GetPath() << "\n";
		return tmpFile;
	}

	TDirectory * outDirectory;
	if (!tmpFile->Get(tmpDirectory))
	{
		//std::cout << "directory '"<< tmpDirectory << "' doesn't exist...\n";
		outDirectory = tmpFile->mkdir(tmpDirectory);
		outDirectory->cd();
		//std::cout << "\ttmpFile:      " << tmpFile->GetPath() << "\n";
		//std::cout << "\toutDirectory: " << outDirectory->GetPath() << "\n";
		//std::cout << "\tgDirectory:   " << gDirectory->GetPath() << "\n";
	}
	else
	{
		//std::cout << "directory '"<< tmpDirectory << "' exists already...\n";
		outDirectory = tmpFile->GetDirectory(tmpDirectory);
		outDirectory->cd();
		//std::cout << "\ttmpFile:      " << tmpFile->GetPath() << "\n";
		//std::cout << "\toutDirectory: " << outDirectory->GetPath() << "\n";
		//std::cout << "\tgDirectory:   " << gDirectory->GetPath() << "\n";
	}
	return outDirectory;
}
