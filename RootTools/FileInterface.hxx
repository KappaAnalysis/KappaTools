// Get event metadata objects
template<typename T>
T *FileInterface::Get()
{
	std::cerr << "Unsupported event metadata type: " << TypeName<T>::name() << std::endl;
	return 0;
}

template<>
KEventMetadata *FileInterface::Get();
template<>
KGenEventMetadata *FileInterface::Get();

// Get lumi metadata objects
template<typename T>
T *FileInterface::Get(run_id run, lumi_id lumi)
{
	std::cerr << "Unsupported lumi metadata type: " << TypeName<T>::name() << std::endl;
	return 0;
}

template<>
KLumiMetadata *FileInterface::Get(run_id run, lumi_id lumi);
template<>
KGenLumiMetadata *FileInterface::Get(run_id run, lumi_id lumi);
template<>
KDataLumiMetadata *FileInterface::Get(run_id run, lumi_id lumi);

// Get event content from files
template<typename T>
T *FileInterface::Get(const std::string &name, const bool check, const bool def)
{
	T *result = static_cast<T*>(GetInternal(eventdata, TypeName<T>::name(), name, "", check));
	if ((result == 0) && def)
		return new T();
	return result;
}

template<typename T>
T *FileInterface::Get(const std::string &name, const std::string altName, const bool check)
{
	return static_cast<T*>(GetInternal(eventdata, TypeName<T>::name(), name, altName, check));
}

template<typename T>
std::vector<std::string> FileInterface::GetNames(bool inherited)
{
	return TreeObjects(eventdata, TypeName<T>::name(), inherited);
}

template<typename T>
std::map<std::string, T*> FileInterface::GetAll(bool inherited)
{
	std::map<std::string, T*> result;
	std::vector<std::string> names = GetNames<T>(inherited);
	for (std::vector<std::string>::const_iterator it = names.begin(); it < names.end(); ++it)
		result[*it] = Get<T>(*it);
	return result;
}

template<typename T>
std::map<std::pair<run_id, lumi_id>, T> FileInterface::GetLumis()
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
		std::auto_ptr<ProgressMonitor> pm;
		if (verbosity > 0)
			pm.reset(new ProgressMonitor(lumidata.GetEntries()));
		for (int i = 0; i < lumidata.GetEntries(); ++i)
		{
			if (pm.get())
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

template<typename T>
inline T *FileInterface::Get(KEventMetadata *meta_event)
{
	return this->Get<T>(meta_event->nRun, meta_event->nLumi);
}
