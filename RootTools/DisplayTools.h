#include <DataFormats/interface/Kappa.h>
#include <DataFormats/interface/KDebug.h>
#include <stdlib.h>
#include <stddef.h>
#include <cstring>

void displayWeight(KGenLumiMetadata *metaLumi, KGenEventMetadata *metaEvent);
void displayBits(KEventMetadata *meta);
void displayHLT(KLumiMetadata *metaLumi, KEventMetadata *metaEvent);

template<typename T>
void displayLVs(const std::vector<T> &vec, size_t maxN = 0)
{
	if (maxN > 0)
		maxN = min(maxN, vec.size());
	else
		maxN = vec.size();
	for (size_t j = 0; j < maxN; ++j)
		std::cout << KLVWrap<typename T::KInternalLV>(vec[j].p4) << std::endl;
}

template<typename T>
void displayJets(const std::vector<T> &vec, size_t maxN = 0)
{
	if (maxN > 0)
		maxN = min(maxN, vec.size());
	else
		maxN = vec.size();
	for (size_t j = 0; j < maxN; ++j)
		std::cout << vec[j] << std::endl;
}
