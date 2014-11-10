#ifndef PLOT_LV_H
#define PLOT_LV_H

#include <Kappa/DataFormats/interface/Kappa.h>
#include "PlotInterface.h"

class Plot_LV
{
public:
	Plot_LV(PlotInterface pi, const std::string title, const bool _correlation = false, const Binning ptBinning = bin_logpt_default)
		: correlation(_correlation)
	{
		Variable v_mypt(ptBinning, "p_{T} [GeV]");
		pt_spec = pi.book<TH1D>("pt_spec", "dN/dp_{T} - " + title, v_mypt);
		pt_spec_fine = pi.book<TH1D>("pt_spec_fine", "dN/dp_{T} - " + title, v_pt);
		et_spec = pi.book<TH1D>("et_spec", "dN/dE_{T} - " + title, v_et);
		y_spec = pi.book<TH1D>("y_spec", "dN/dy - " + title, v_y);
		eta_spec = pi.book<TH1D>("eta_spec", "dN/d#eta - " + title, v_eta);
		phi_spec = pi.book<TH1D>("phi_spec", "dN/d#phi - " + title, v_phi);
		m_spec = pi.book<TH1D>("m_spec", "dN/dM - " + title, v_m);
		mt_spec = pi.book<TH1D>("mt_spec", "dN/dM_{T} - " + title, v_mt);

		if (correlation)
		{
			pt_eta_corr = pi.book<TH2D>("pt_eta_corr", "p_{T} - #eta correlation - " + title, v_mypt, v_eta);
			pt_y_corr = pi.book<TH2D>("pt_y_corr", "p_{T} - y correlation - " + title,        v_mypt, v_y);
			pt_phi_corr = pi.book<TH2D>("pt_phi_corr", "p_{T} - #phi correlation - " + title, v_mypt, v_phi);
			phi_eta_corr = pi.book<TH2D>("phi_eta_corr", "#phi - y correlation - " + title,   v_phi,  v_eta);
		}
	}

	inline void Fill(const KLV &jet, const double weight)
	{
		const double pt = jet.p4.pt();
		const double eta = jet.p4.eta();
		const double phi = jet.p4.phi();

		pt_spec->Fill(pt, weight);
		pt_spec_fine->Fill(pt, weight);
		et_spec->Fill(jet.p4.Et(), weight);
		y_spec->Fill(jet.p4.Rapidity(), weight);
		eta_spec->Fill(eta, weight);
		phi_spec->Fill(phi, weight);
		m_spec->Fill(jet.p4.M(), weight);
		mt_spec->Fill(jet.p4.Mt(), weight);

		if (correlation)
		{
			pt_eta_corr->Fill(pt, eta, weight);
			pt_y_corr->Fill(pt, jet.p4.Rapidity(), weight);
			pt_phi_corr->Fill(pt, phi, weight);
			phi_eta_corr->Fill(phi, eta, weight);
		}
	}

private:
	bool correlation;
	TH1D *pt_spec, *pt_spec_fine, *et_spec, *y_spec, *eta_spec, *phi_spec, *m_spec, *mt_spec;
	TH2D *pt_eta_corr, *pt_y_corr, *pt_phi_corr, *phi_eta_corr;
};

#endif
