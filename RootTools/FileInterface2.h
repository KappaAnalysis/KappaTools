/* Copyright (c) 2012 - All Rights Reserved
 *   Fred Stober <stober@cern.ch>
 */

#ifndef KAPPA_FILEINTERFACE2_H
#define KAPPA_FILEINTERFACE2_H

#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <list>

#include "../Toolbox/IOHelper.h"
#include "../Toolbox/ProgressMonitor.h"
#include <Kappa/DataFormats/interface/Kappa.h>
#include "Directory.h"
#include "FileInterfaceBase.h"

class FileInterface2 : public FileInterfaceBase
{
public:
	FileInterface2(std::vector<std::string> files, class RunLumiSelector *rls = 0,
		bool shuffle = false, int verbose = 2, class ScaleServiceFactory *ss = 0, std::string reportFn = "");
	~FileInterface2()
	{
		for (std::map<std::string, BranchHolder*>::iterator it = meta_branches.begin(); it != meta_branches.end(); ++it)
			delete it->second;
		meta_branches.clear();
		ClearCache();
		delete lumidata;
	}
	using FileInterfaceBase::Get;

	// Functions for accessing metadata objects
	void GetMetaEntry();
	void GetMetaEntry(run_id run, lumi_id lumi);

	// Functions for getting metadata objects
	template<typename T>
	T *GetMeta(std::string name, const bool check = true, const bool def = false);
	template<typename T>
	std::vector<std::string> GetMetaNames(bool inherited = false);
	template<typename T>
	std::map<std::string, T*> GetMetaAll(bool inherited = false);

	// Functions for getting metadata objects - old style
	template<typename T>
	T *Get(run_id run, lumi_id lumi);
	template<typename T>
	inline T *Get(KEventInfo *meta_event);

	TChain eventdata;

protected:
	TChain *lumidata;
	std::string current_file;
	std::map<std::string, BranchHolder*> meta_branches;
	std::map<std::pair<run_id, lumi_id>, size_t> lumiIdxMap;
};

#include "FileInterface2.hxx"

#endif
