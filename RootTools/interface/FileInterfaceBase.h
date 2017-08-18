/* Copyright (c) 2011 - All Rights Reserved
 *   Fred Stober <stober@cern.ch>
 */

#ifndef KAPPA_FILEINTERFACEBASE_H
#define KAPPA_FILEINTERFACEBASE_H

#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <list>

#include <Kappa/DataFormats/interface/Kappa.h>
#include "BranchHolder.h"

class FileInterfaceBase
{
public:
	enum DataType {STD, GEN, DATA, INVALID} lumiInfoType;
	FileInterfaceBase(int verbose = 2);
	void ClearCache()
	{
		for (std::map<std::string, BranchHolder*>::iterator it = branches.begin(); it != branches.end(); ++it)
			delete it->second;
		branches.clear();
	}
	void Init(TChain *_eventdata, DataType _lumiInfoType);

	void SpeedupTree(long cache = 0);
	TChain *eventdata;

	inline long long GetEntries()
	{
		return eventdata->GetEntries();
	}
	inline void GetEntry(long long entry)
	{
		eventdata->GetEntry(entry);
	}

	// Functions for getting metadata objects
	template<typename T>
	T *Get();

	// Get event content of files
	template<typename T>
	T *Get(const std::string &name, const bool check = true, const bool def = false);
	template<typename T>
	std::vector<std::string> GetNames(bool inherited = false);
	template<typename T>
	std::map<std::string, T*> GetAll(bool inherited = false);

	bool isMC() const;

protected:
	int verbosity;
	KEventInfo *current_event;
	std::map<std::string, BranchHolder*> branches;

	void *GetInternal(TTree *tree, std::map<std::string, BranchHolder*> &bmap,
		const std::string cname, const std::string &name, const bool check = true);
};

#include "FileInterfaceBase.hxx"

#endif
