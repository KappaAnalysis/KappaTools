#ifndef KAPPA_FILEINTERFACE_H
#define KAPPA_FILEINTERFACE_H

#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <list>

#include "../Toolbox/IOHelper.h"
#include "../Toolbox/ProgressMonitor.h"
#include <Kappa/DataFormats/interface/Kappa.h>
#include "Directory.h"
#include "FileInterfaceBase.h"

typedef unsigned int run_id;
typedef unsigned int lumi_id;

class FileInterface : public FileInterfaceBase
{
public:
	FileInterface(std::vector<std::string> files, bool shuffle = false, int verbose = 2);
	~FileInterface();

	// Functions for getting metadata objects
	template<typename T>
	T *Get(run_id run, lumi_id lumi);
	template<typename T>
	inline T *Get(KEventMetadata *meta_event);

	using FileInterfaceBase::Get;

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
	std::map<std::string, void*> objCache;

	template<typename T>
	std::map<std::pair<run_id, lumi_id>, T> GetLumis();
};

#include "FileInterface.hxx"

#endif
