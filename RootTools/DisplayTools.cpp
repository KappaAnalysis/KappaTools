#include "DisplayTools.h"

void displayWeight(KGenLumiMetadata *metaLumi, KGenEventMetadata *metaEvent)
{
	std::cout << "Ext: " << metaLumi->xSectionExt << " Int: " << metaLumi->xSectionInt
		<< " W: " << metaEvent->weight << std::endl;
}

void displayBits(KEventMetadata *meta)
{
	std::cout << "      " << " 6 6 5 5 5 5 5 4 4 4 4 4 3 3 3 3 3 2 2 2 2 2 1 1 1 1 1" << std::endl;
	std::cout << "      " << " 2 0 8 6 4 2 0 8 6 4 2 0 8 6 4 2 0 8 6 4 2 0 8 6 4 2 0 8 6 4 2 0" << std::endl;
	std::cout << "      " << "-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+" << std::endl;
	std::cout << "  L1: " << bitset<64>(meta->bitsL1) << std::endl;
	std::cout << " HLT: " << bitset<64>(meta->bitsHLT) << std::endl;
	std::cout << "Flag: " << bitset<64>(meta->bitsUserFlags) << std::endl;
}

void displayHLT(KLumiMetadata *metaLumi, KEventMetadata *metaEvent)
{
	for (size_t hltIdx = 0; hltIdx < metaLumi->hltNames.size(); ++hltIdx)
		if (metaEvent->bitsHLT & ((unsigned long long)1 << hltIdx))
			std::cout << hltIdx << ":" << metaLumi->hltNames[hltIdx] << " ";
		std::cout << std::endl;
}
