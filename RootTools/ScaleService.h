#ifndef SCALESERVICE_H
#define SCALESERVICE_H

#include <Kappa/DataFormats/interface/Kappa.h>
#include <set>
#include <TH1D.h>
typedef int hlt_prescale_id;

class ScaleService
{
public:
	ScaleService(const unsigned long long _events, const double _xsec_mc, const double _lumi_est, const double _lumi_db,
		const std::map<run_id, std::map<lumi_id, double> > &_recorded,
		const std::map<std::string, hlt_prescale_id> &_prescaleIDs,
		const std::map<run_id, std::map<hlt_prescale_id, int> > &_prescale,
		const std::map<run_id, std::map<hlt_prescale_id, std::map<lumi_id, int> > > &_prescaleDetail,
		const std::vector<double> &_pileup_weight)
		: events(_events), xsec_mc(_xsec_mc), lumi_est(_lumi_est), lumi_db(_lumi_db),
			recorded(_recorded), prescaleIDs(_prescaleIDs), prescale(_prescale), prescaleDetail(_prescaleDetail),
			pileup_weight(_pileup_weight)
	{
	}

	void print();

	inline int prescale_DataDB(size_t hltIdx, KLumiMetadata *meta_lumi) const
	{
		std::map<std::string, hlt_prescale_id>::const_iterator itIdx =
			prescaleIDs.find(meta_lumi->hltNames[hltIdx]);
		assert(itIdx != prescaleIDs.end());
		hlt_prescale_id psIdx = itIdx->second;

		run_id nRun = meta_lumi->nRun;
		std::map<run_id, std::map<hlt_prescale_id, int> >::const_iterator itPSRun =
			prescale.find(nRun);
		assert(itPSRun != prescale.end());
		std::map<hlt_prescale_id, int>::const_iterator itPSHLT =
			itPSRun->second.find(psIdx);
		assert(itPSHLT != itPSRun->second.end());

		int ps = itPSHLT->second;

		std::map<run_id, std::map<hlt_prescale_id, std::map<lumi_id, int> > >::const_iterator itPSDRun =
			prescaleDetail.find(nRun);
		if (itPSDRun == prescaleDetail.end())
			return ps;
		std::map<hlt_prescale_id, std::map<lumi_id, int> >::const_iterator itPSDHLT =
			itPSDRun->second.find(psIdx);
		if (itPSDHLT == itPSDRun->second.end())
			return ps;
		lumi_id nLumi = meta_lumi->nLumi;
		std::map<lumi_id, int>::const_iterator itPSDLumi =
			itPSDHLT->second.find(nLumi);
		if (itPSDLumi == itPSDHLT->second.end())
			return ps;
		return itPSDLumi->second;
	}

	inline double weight_Data(size_t hltIdx, KLumiMetadata *meta_lumi)
	{
		int ps_meta = meta_lumi->hltPrescales[hltIdx];
		if (prescaleIDs.size() == 0)
			return ps_meta;
		int ps_db = prescale_DataDB(hltIdx, meta_lumi);
		if (ps_db != ps_meta)
		{
//			std::cerr << "Differing prescales found! " << ps_db << " " << ps_meta << " in "
//				<< meta_lumi->nRun << ":" << meta_lumi->nLumi << std::endl;
			brokenPS[meta_lumi->nRun].insert(meta_lumi->nLumi);
//			exit(1);
		}
//		assert(ps_db == ps_meta);
		return ps_meta;
	}

	inline double weight_MC(KGenEventMetadata *meta_event_gen) const
	{
		return meta_event_gen->weight * pileup_weight[int(meta_event_gen->numPUInteractionsTruth)];
	}

	inline double scale_Data() const
	{
		return lumi_db;
	}

	inline double scale_MC() const
	{
		return 1.0 / (xsec_mc / events);
	}

	const std::map<run_id, std::set<lumi_id> > &getBrokenPS()
	{
		return brokenPS;
	}

private:
	unsigned long long events;
	double xsec_mc, lumi_est, lumi_db;

	std::map<run_id, std::set<lumi_id> > brokenPS;

	const std::map<run_id, std::map<lumi_id, double> > &recorded;

	const std::map<std::string, hlt_prescale_id> &prescaleIDs;
	const std::map<run_id, std::map<hlt_prescale_id, int> > &prescale;
	const std::map<run_id, std::map<hlt_prescale_id, std::map<lumi_id, int> > > &prescaleDetail;

	const std::vector<double> &pileup_weight;
};

class ScaleServiceFactory
{
public:
	ScaleServiceFactory(const bool _doPrescales = true, TH1D *pu_data = 0, TH1D *pu_mc = 0) {};

	void registerMC(KGenLumiMetadata *meta_lumi) {};
	void registerData(KDataLumiMetadata *meta_lumi) {};
	void registerLF(std::string lumiPath) {};
	ScaleService *finish(unsigned long long events, const double userXsec = -1, const double userLumi = -1) {};

private:
	bool doPrescales;
	unsigned long long mc_counter;
	double sum_int, sum_ext, sum_lumi_est, sum_lumi_db;

	std::map<run_id, std::map<lumi_id, double> > recorded;

	std::map<std::string, hlt_prescale_id> prescaleIDs;
	std::map<run_id, std::map<hlt_prescale_id, int> > prescale;
	std::map<run_id, std::map<hlt_prescale_id, std::map<lumi_id, int> > > prescaleDetail;

	std::vector<double> pileup_weight;
};

#endif
