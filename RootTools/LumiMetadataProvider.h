#ifndef KAPPA_LUMIMETADATAPROVIDER_H
#define KAPPA_LUMIMETADATAPROVIDER_H

#include "DataFormats/interface/KMetadata.h"
#include <map>
#include <iostream>
#include <string>
#include "TTree.h"
#include <algorithm>

namespace KappaTools
{
	class LumiMetadataProvider
	{
		private:
			std::map< std::pair<unsigned long,unsigned long> , KLumiMetadata > tmpLumiMetadatas;
		public:
			LumiMetadataProvider(TTree * lumis_tree);
			KLumiMetadata * get(KEventMetadata * eventMetadata);
	};
}

#endif
