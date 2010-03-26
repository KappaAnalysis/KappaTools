#ifndef KBasePlot_h
#define KBasePlot_h

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
