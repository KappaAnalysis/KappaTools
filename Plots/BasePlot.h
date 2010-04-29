#ifndef KAPPA_BASEPLOT_H
#define KAPPA_BASEPLOT_H

#include "TDirectory.h"

namespace KappaTools
{
	class BasePlot
	{
		protected:
			TDirectory * outFile;
			TDirectory * outDirectory, * outSubDirectory;
		
		public:
			BasePlot();
			TDirectory * getDirectory(TDirectory * tmpFile, TString tmpDirectory, TString tmpSubDirectory);
	};
}
#endif
