/* Copyright (c) 2012 - All Rights Reserved
 *   Fred Stober <stober@cern.ch>
 */

#include "FileInterface2.h"
#include "RunLumiReader.h"
#include "ScaleService.h"
#include <fstream>

using namespace std;

void updateSSF(ScaleServiceFactory *ss, FileInterfaceBase::DataType dt, KLumiMetadata *meta_lumi)
{
	if (!ss)
		return;
	switch (dt)
	{
		case FileInterfaceBase::DATA:
			ss->registerData(static_cast<KDataLumiMetadata*>(meta_lumi));
			break;
		case FileInterfaceBase::GEN:
			ss->registerMC(static_cast<KGenLumiMetadata*>(meta_lumi));
			break;
		default:
			break;
	}
}

FileInterface2::FileInterface2(std::vector<std::string> files, RunLumiSelector *rls,
	bool shuffle, int verbose, ScaleServiceFactory *ss, std::string reportFn)
	: FileInterfaceBase(verbose), eventdata("Events"), lumidata(0), current_file()
{
	if (shuffle)
		random_shuffle(files.begin(), files.end());

	DataType dtAll = INVALID;
	std::vector<std::string> usedFiles;
	std::map<run_id, std::set<std::pair<lumi_id, lumi_id> > > usedLumis;

	for (size_t f = 0; f < files.size(); ++f)
	{
		if (verbosity)
			cout << "Loading ... " << files[f] << endl;

		if ((ss != 0) || (reportFn != ""))
		{
			// 1) Load lumi data from single file
			TChain lumicheck("Lumis");
			lumicheck.Add(files[f].c_str());
			BranchHolder bh(&lumicheck, "KLumiMetadata");
			KLumiMetadata *meta_lumi = (KLumiMetadata*)bh.ptr;

			DataType dt = INVALID;
			if (bh.ClassName() == "KGenLumiMetadata")
				dt = GEN;
			if (bh.ClassName() == "KDataLumiMetadata")
				dt = DATA;
			if (bh.ClassName() == "KLumiMetadata")
				dt = STD;

			// 2) acceptance with run selector
			bool accept = (rls == 0);
			for (int l = 0; l < lumicheck.GetEntries(); ++l)
			{
				lumicheck.GetEntry(l);
				if (rls)
				{
					if (rls->accept(meta_lumi->nRun, meta_lumi->nLumi))
					{
						accept = true;
						usedLumis[meta_lumi->nRun].insert(make_pair(meta_lumi->nLumi, meta_lumi->nLumi));
						updateSSF(ss, dt, meta_lumi);
					}
				}
				else
				{
					usedLumis[meta_lumi->nRun].insert(make_pair(meta_lumi->nLumi, meta_lumi->nLumi));
					updateSSF(ss, dt, meta_lumi);
				}
			}
			if (!accept)
				continue;

			usedLumis = RunLumiSelector::getMinimalJSON(usedLumis);
			if (dtAll == INVALID)
				dtAll = dt;
			assert(dtAll == dt);
		}

		// 3) add accepted files to chain / persistent lumi info list
		usedFiles.push_back(files[f]);
		eventdata.Add(files[f].c_str());
	}

	if (reportFn != "")
	{
		ofstream uf(string(reportFn + ".usedFiles").c_str(), fstream::out);
		uf << KappaTools::join("\n", usedFiles) << std::endl;
		ofstream fs(string(reportFn + ".json").c_str(), fstream::out);
		RunLumiSelector::printJSON(fs, usedLumis);
	}

	if (usedFiles.size() == 0)
	{
		std::cerr << "No files to process!" << std::endl;
		exit(1);
	}
	Init(&eventdata, dtAll);
	GetEntry(0);
	GetMetaEntry();
}

void FileInterface2::GetMetaEntry()
{
	GetMetaEntry(current_event->nRun, current_event->nLumi);
}

void FileInterface2::GetMetaEntry(run_id run, lumi_id lumi)
{
	if (eventdata.GetFile()->GetName() != current_file)
	{
		lumiIdxMap.clear();
		// Update tree reference of booked variables
		TChain *newLumiData = new TChain("Lumis");
		newLumiData->Add(eventdata.GetFile()->GetName());
		for (std::map<std::string, BranchHolder*>::iterator it = meta_branches.begin(); it != meta_branches.end(); ++it)
			it->second->UpdateTree(newLumiData);
		if (lumidata)
			delete lumidata;
		lumidata = newLumiData;
		// Rebuild lumi index map
		KLumiMetadata *meta_lumi = GetMeta<KLumiMetadata>("KLumiMetadata", true, false);
		for (int i = 0; i < lumidata->GetEntries(); ++i)
		{
			lumidata->GetEntry(i);
			lumiIdxMap[make_pair(meta_lumi->nRun, meta_lumi->nLumi)] = i;
		}
		current_file = eventdata.GetFile()->GetName();
	}
	if (lumiIdxMap.count(make_pair(run, lumi)) == 1)
		lumidata->GetEntry(lumiIdxMap[make_pair(run, lumi)]);
	else
	{
		std::cerr << "Lumi section " << run << ":" << lumi << " not found or unique!" << std::endl;
		std::cerr << eventdata.GetFile() << " " << eventdata.GetFileNumber() << " " << current_file << std::endl;
		std::cerr << lumiIdxMap << endl;
		exit(1);
	}
	// Check consistency of getMetaNames between files!
}
