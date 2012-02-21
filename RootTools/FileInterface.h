#ifndef KAPPA_FILEINTERFACE_H
#define KAPPA_FILEINTERFACE_H

#include "../Toolbox/ProgressMonitor.h"
#include "../Toolbox/IOHelper.h"
#include "FileInterfaceBase.h"

class FileInterface : public FileInterfaceBase
{
public:
	FileInterface(std::vector<std::string> files, bool shuffle = false, int verbose = 2);
	~FileInterface()
	{
		ClearCache();
	}
	using FileInterfaceBase::Get;

	// Functions for getting metadata objects
	template<typename T>
	T *Get(run_id run, lumi_id lumi);
	template<typename T>
	inline T *Get(KEventMetadata *meta_event);

	// Get lumi list
	std::vector<std::pair<run_id, lumi_id> > GetRunLumis() const;
	bool isCompatible(unsigned int minRun, unsigned int maxRun);

	TChain eventdata;
private:
	TChain lumidata;
	int verbosity;

	std::map<std::pair<run_id, lumi_id>, KGenLumiMetadata> lumimap_mc;
	std::map<std::pair<run_id, lumi_id>, KLumiMetadata> lumimap_std;
	std::map<std::pair<run_id, lumi_id>, KDataLumiMetadata> lumimap_data;

	template<typename T>
	std::map<std::pair<run_id, lumi_id>, T> GetLumis();
};

#include "FileInterface.hxx"

#endif
