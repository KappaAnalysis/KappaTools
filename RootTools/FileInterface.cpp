#include "FileInterface.h"

using namespace std;

FileInterface::FileInterface(vector<string> files, bool shuffle, int verbose) :
	eventdata("Events"), lumidata("Lumis"), verbosity(verbose)
{
	if (shuffle)
		random_shuffle(files.begin(), files.end());
	for (size_t i = 0; i < files.size(); ++i)
	{
		if (verbosity)
			cout << "Loading ... " << files[i] << endl;
		eventdata.Add(files[i].c_str());
		lumidata.Add(files[i].c_str());
	}

	TBranch *b = lumidata.GetBranch("KLumiMetadata");
	if (b)
	{
		if (string(b->GetClassName()) == "KGenLumiMetadata")
			Init(&eventdata, GEN);
		if (string(b->GetClassName()) == "KDataLumiMetadata")
			Init(&eventdata, DATA);
		if (string(b->GetClassName()) == "KLumiMetadata")
			Init(&eventdata, STD);
	}

	switch (lumiInfoType)
	{
	case GEN:
		cout << endl << "Data source: Monte Carlo" << endl;
		lumimap_mc = GetLumis<KGenLumiMetadata>();
		current_event = new KGenEventMetadata();
		break;
	case STD:
		cout << endl << "Data source: default" << endl;
		lumimap_std = GetLumis<KLumiMetadata>();
		current_event = new KEventMetadata();
		break;
	case DATA:
		cout << endl << "Data source: Detector" << endl;
		lumimap_data = GetLumis<KDataLumiMetadata>();
		current_event = new KEventMetadata();
		break;
	}
	eventdata.SetBranchAddress("KEventMetadata", &current_event);
}

template<typename T>
inline bool isCompatible(const std::map<std::pair<run_id, lumi_id>, T> &lumimap, unsigned int minRun, unsigned int maxRun)
{
	for (typename std::map<std::pair<run_id, lumi_id>, T>::const_iterator it = lumimap.begin(); it != lumimap.end(); ++it)
		if ((it->first.first >= minRun || minRun == 0) && (it->first.first <= maxRun || maxRun == 0))
			return true;
	return false;
}

bool FileInterface::isCompatible(unsigned int minRun, unsigned int maxRun)
{
	switch (lumiInfoType)
	{
	case GEN:
		return ::isCompatible(lumimap_mc, minRun, maxRun);
	case STD:
		return ::isCompatible(lumimap_std, minRun, maxRun);
	case DATA:
		return ::isCompatible(lumimap_data, minRun, maxRun);
	}
	return false;
}

template<typename T>
inline std::vector<std::pair<run_id, lumi_id> > GetRunLumis(const std::map<std::pair<run_id, lumi_id>, T> &lumimap)
{
	std::vector<std::pair<run_id, lumi_id> > result;
	for (typename std::map<std::pair<run_id, lumi_id>, T>::const_iterator it = lumimap.begin(); it != lumimap.end(); ++it)
		result.push_back(it->first);
	return result;
}

std::vector<std::pair<run_id, lumi_id> > FileInterface::GetRunLumis() const
{
	switch (lumiInfoType)
	{
	case GEN:
		return ::GetRunLumis(lumimap_mc);
	case STD:
		return ::GetRunLumis(lumimap_std);
	case DATA:
		return ::GetRunLumis(lumimap_data);
	}
	return std::vector<std::pair<run_id, lumi_id> >();
}

template<>
KLumiMetadata *FileInterface::Get(run_id run, lumi_id lumi)
{
	switch (lumiInfoType)
	{
	case GEN:
		return &(lumimap_mc[std::make_pair(run, lumi)]);
	case STD:
		return &(lumimap_std[std::make_pair(run, lumi)]);
	case DATA:
		return &(lumimap_data[std::make_pair(run, lumi)]);
	}
	return 0;
}

template<>
KGenLumiMetadata *FileInterface::Get(run_id run, lumi_id lumi)
{
	if (lumiInfoType == GEN)
		return &(lumimap_mc[std::make_pair(run, lumi)]);
	return 0;
}

template<>
KDataLumiMetadata *FileInterface::Get(run_id run, lumi_id lumi)
{
	if (lumiInfoType == DATA)
		return &(lumimap_data[std::make_pair(run, lumi)]);
	return 0;
}
