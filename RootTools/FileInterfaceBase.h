#ifndef KAPPA_FILEINTERFACEBASE_H
#define KAPPA_FILEINTERFACEBASE_H

#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <list>

#include "../Toolbox/IOHelper.h"
#include <Kappa/DataFormats/interface/Kappa.h>
#include "Directory.h"

class FileInterfaceBase
{
public:
	enum DataType {STD, GEN, DATA} lumiInfoType;
	FileInterfaceBase(int verbose = 2);
	void Init(TChain *_eventchain, DataType _lumiInfoType);

	void SpeedupTree(long cache = 0);
	TChain *eventchain;

	// Functions for getting metadata objects
	template<typename T>
	T *Get();

	// Get event content of files
	template<typename T>
	T *Get(const std::string &name, const bool check, const bool def = false);
	template<typename T>
	T *Get(const std::string &name, const std::string altName = "", const bool check = true);
	template<typename T>
	std::vector<std::string> GetNames(bool inherited = false);
	template<typename T>
	std::map<std::string, T*> GetAll(bool inherited = false);

	bool isMC() const;

protected:
	int verbosity;
	KEventMetadata *current_event;

	std::list<void*> vBranchHolder;
	std::map<std::string, void*> objCache;

	void *GetInternal(TChain *chain, const char *cname, const std::string &name, const std::string altName = "", const bool check = true);
};

#include "FileInterfaceBase.hxx"

#endif
