#ifndef KAPPA_FILEINTERFACE_H
#define KAPPA_FILEINTERFACE_H

#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <list>

#include <Toolbox/IOHelper.h>
#include <Toolbox/ProgressMonitor.h>
#include <DataFormats/interface/Kappa.h>
#include "Directory.h"

typedef unsigned int run_id;
typedef unsigned int lumi_id;

struct FileInterface
{
	FileInterface(std::vector<std::string> files, bool shuffle = false, int verbose = 2);
	void SpeedupTree(long cache = 0);

	TChain eventdata;
	bool isMC;

	template<typename T>
	T *Get(const std::string &name, const std::string altName = "")
	{
		return static_cast<T*>(GetInternal(eventdata, TypeName<T>::name(), name, altName));
	}

	template<typename T>
	std::vector<std::string> GetNames(bool inherited = false)
	{
		return TreeObjects(eventdata, TypeName<T>::name(), inherited);
	}

	template<typename T>
	std::map<std::string, T*> GetAll(bool inherited = false)
	{
		std::map<std::string, T*> result;
		std::vector<std::string> names = GetNames<T>(inherited);
		for (std::vector<std::string>::const_iterator it = names.begin(); it < names.end(); ++it)
			result[*it] = Get<T>(*it);
		return result;
	}

	// Get event metadata objects
	KEventMetadata *GetEventMetadata();
	KGenEventMetadata *GetGenEventMetadata();
	void AssignEventPtr(KEventMetadata **meta_event, KGenEventMetadata **meta_event_gen = 0);

	// Get lumi metadata objects
	KLumiMetadata *GetLumiMetadata(run_id run, lumi_id lumi);
	KGenLumiMetadata *GetGenLumiMetadata(run_id run, lumi_id lumi);
	void AssignLumiPtr(run_id run, lumi_id lumi,
		KLumiMetadata **meta_lumi, KGenLumiMetadata **meta_lumi_gen = 0);

	// Get lumi list
	std::vector<std::pair<run_id, lumi_id> > GetRunLumis()
	{
		std::vector<std::pair<run_id, lumi_id> > result;
		if (isMC)
			for (std::map<std::pair<run_id, lumi_id>, KGenLumiMetadata>::const_iterator it = lumimap_mc.begin(); it != lumimap_mc.end(); ++it)
				result.push_back(it->first);
		else
			for (std::map<std::pair<run_id, lumi_id>, KLumiMetadata>::const_iterator it = lumimap_data.begin(); it != lumimap_data.end(); ++it)
				result.push_back(it->first);
		return result;
	}

private:
	TChain lumidata;
	int verbosity;
	KEventMetadata *current_event;

	std::list<void*> vBranchHolder;
	std::map<std::pair<run_id, lumi_id>, KGenLumiMetadata> lumimap_mc;
	std::map<std::pair<run_id, lumi_id>, KLumiMetadata> lumimap_data;

	template<typename T>
	std::map<std::pair<run_id, lumi_id>, T> GetLumis()
	{
		OStreamGuard guard(std::cout);
		if (verbosity)
			std::cout << "Reading lumi sections: " << std::endl;

		// Connect to lumi tree
		T *meta_lumi = new T();
		lumidata.SetBranchAddress("KLumiMetadata", &meta_lumi);

		// Collect lumi infos
		std::map<std::pair<run_id, lumi_id>, T> result;
		std::map<run_id, std::pair<lumi_id, lumi_id> > run_start_end;
		if (lumidata.GetEntries() > 0)
		{
			ProgressMonitor *pm = 0;
			if (verbosity > 0)
				pm = new ProgressMonitor(lumidata.GetEntries());
			for (int i = 0; i < lumidata.GetEntries(); ++i)
			{
				if (pm)
					pm->Update();
				lumidata.GetEntry(i);
				result[std::make_pair(meta_lumi->nRun, meta_lumi->nLumi)] = *meta_lumi;
				if (verbosity > 2)
					std::cout << "(" << meta_lumi->nRun << ":" << meta_lumi->nLumi << ") ";

				// Determine start/end of lumi section for run
				if (run_start_end.find(meta_lumi->nRun) == run_start_end.end())
					run_start_end[meta_lumi->nRun] = std::make_pair((lumi_id)-1, 0);
				run_start_end[meta_lumi->nRun] = std::make_pair(
					std::min(run_start_end[meta_lumi->nRun].first, meta_lumi->nLumi),
					std::max(run_start_end[meta_lumi->nRun].second, meta_lumi->nLumi)
				);
			}
			if (pm)
				delete pm;
		}
		if (verbosity > 2)
			std::cout << std::endl << std::endl;
		if (verbosity > 0)
			std::cout << "Number of unique lumi sections in dataset: " << result.size() << std::endl;
		if (verbosity > 1)
		{
			std::cout << std::endl << "Lumi ranges:" << std::endl;
			std::map<run_id, std::pair<lumi_id, lumi_id> >::const_iterator it;
			for (it = run_start_end.begin(); it != run_start_end.end(); ++it)
				std::cout << std::setw(8) << it->first << ": "
					<< std::setw(4) << it->second.first << " - "
					<< std::setw(4) << it->second.second  << std::endl;
			std::cout << std::endl;
		}
		return result;
	}

	void *GetInternal(TChain &chain, const char *cname, const std::string &name, const std::string altName = "");
};

#endif
