#include "BasePlot.h"

KappaTools::BasePlot::BasePlot()
{

}

TDirectory * KappaTools::BasePlot::getDirectory(TDirectory * tmpFile, TString tmpDirectory)
{
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
