/* Copyright (c) 2010 - All Rights Reserved
 *   Manuel Zeise <zeise@cern.ch>
 */

#include "BasePlot.h"

KappaTools::BasePlot::BasePlot()
{

}

TDirectory * KappaTools::BasePlot::getDirectory(TDirectory * tmpFile, TString tmpDirectory)
{
	tmpDirectory = tmpDirectory.ReplaceAll(" ","_").ReplaceAll(".","").ReplaceAll("<","").ReplaceAll(">","").ReplaceAll(":","").ReplaceAll(",","");
	if (tmpDirectory=="")
	{
		tmpFile->cd();
		return tmpFile;
	}

	TDirectory * outDirectory;
	if (!tmpFile->Get(tmpDirectory))
	{
		outDirectory = tmpFile->mkdir(tmpDirectory);
		outDirectory->cd();
	}
	else
	{
		outDirectory = tmpFile->GetDirectory(tmpDirectory);
		outDirectory->cd();
	}
	return outDirectory;
}
