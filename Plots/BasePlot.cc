#include "BasePlot.h"

KappaTools::BasePlot::BasePlot()
{

}

TDirectory * KappaTools::BasePlot::getDirectory(TDirectory * tmpFile, TString tmpDirectory, TString tmpSubDirectory)
{
	outFile=tmpFile;
	
	if (tmpDirectory=="")
		return outFile;
	
	// remove trailing whitespaces and replace all other whitespaces by an underscore
	tmpDirectory = ((TString)(tmpDirectory.Strip())).ReplaceAll(" ","_");
	tmpSubDirectory = ((TString)(tmpSubDirectory.Strip())).ReplaceAll(" ","_");

	// create directory if necessary
	if (!outFile->GetDirectory(tmpDirectory))
	{
		//std::cout << "create directory.." << tmpDirectory << "\n";
		outDirectory = outFile->mkdir(tmpDirectory);
	}
	else
	{
		//std::cout << "change to directory.." << tmpDirectory << "\n";
		outDirectory = (TDirectory * )outFile->GetDirectory(tmpDirectory);
	}
	outDirectory->cd();
	
	if (tmpSubDirectory=="")
		return outDirectory;
		
	if (!outDirectory->GetDirectory(tmpSubDirectory))
	{
		//std::cout << "create subdirectory.." << tmpSubDirectory << "\n";
		outSubDirectory = outDirectory->mkdir(tmpSubDirectory);
	}
	else
	{
		//std::cout << "change to subdirectory.." << tmpSubDirectory << "\n";
		outSubDirectory = (TDirectory * )outDirectory->GetDirectory(tmpSubDirectory);
	}
	outSubDirectory->cd();
	
	return outSubDirectory;
}
