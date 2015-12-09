#ifndef BINNING_H
#define BINNING_H

#include "../../Toolbox/interface/Vector.h"
#include "../../Toolbox/interface/Memory.h"
//#include <stdlib.h>

class TAxis;

struct Binning
{
	Binning();
	Binning(const size_t _nbins, const double _min, const double _max, bool center = false);
	Binning(const TAxis *axis);
	Binning(const std::vector<double> _bins);
	Binning(const size_t _nbins, const double *_bins);
	Binning(const struct Binning _binning, const bool _mirror);

	double min, max, res;
	size_t nbins;
	double *bins; // low edges

	int findBin(double value, double *start, double *end)
	{
		if (end - start < 2)
			return bins - start;
		double *middle = start + (end - start) / 2;
		if (*middle < value)
			return findBin(value, middle, end);
		if (*middle > value)
			return findBin(value, start, middle);
		return bins - middle;
	}

protected:
	template<typename T>
	void setup(const size_t _size, const T _bins)
	{
		min = _bins[0]; max = _bins[_size - 1]; nbins = _size - 1; res = 0;
		bins = binPool.AddObject(new double[_size]);
		binPool.AddObject(bins);
		for (size_t i = 0; i < _size; ++i)
			bins[i] = _bins[i];
	}

private:
	static MemoryPool<double*> binPool;
};

struct LogBinning : public Binning
{
	LogBinning(const size_t nbins, const double min, double max, const int precision = 0);
	LogBinning(const size_t nbins, const double min, double max, Binning forced, const int precision = 0);
};

std::ostream &operator<<(std::ostream &os, const Binning &b);

struct Variable
{
	Variable(const Binning _binning, const std::string _name = "", const bool _log = false);
	Variable(const TAxis *axis, const bool _log = false);
	operator const Binning() const
	{
		return binning;
	}
	Binning binning;
	std::string name;
	bool log;
};

static const Binning bin_pt(3500, 0, 3500); // 10 Gev bins
static const Variable v_pt(bin_pt, "p_{T} [GeV]");

static const Binning bin_pt_5GeV(700, 0, 3500); // 5 Gev bins
static const Variable v_pt_5GeV(bin_pt_5GeV, "p_{T} [GeV]");

static const Binning bin_pt_10GeV(350, 0, 3500); // 10 Gev bins
static const Variable v_pt_10GeV(bin_pt_10GeV, "p_{T} [GeV]");

static const LogBinning bin_logpt_default(100, 20, 4000); // 200 log-distributed bins

static const Binning bin_m(1000, 0, 1000); // 1 Gev bins
static const Variable v_m(bin_m, "m [GeV]");
static const Variable v_mt(bin_m, "m_{T} [GeV]");

static const Binning bin_et(3500, 0, 3500); // 10 Gev bins
static const Variable v_et(bin_et, "E_{T} [GeV]");

static const Binning bin_smallpt(500, 0, 500); // 1 Gev bins
static const Variable v_smallpt(bin_smallpt, "p_{T} [GeV]");

static const Binning bin_msqr(500, 0, 1250000); // (50 Gev)^2 bins
static const Variable v_msqr(bin_msqr, "m^{2} [GeV^{2}]");

static const Binning bin_2pt(2*700, 0, 2*7000); // 10 Gev bins
static const Variable v_ht(bin_2pt, "H_{T} [GeV]");
static const Variable v_dj(bin_2pt, "m [GeV]");

static const Binning bin_pthat((ivector<double>(),
	0, 50, 80, 120, 170, 230, 300, 380, 470, 600, 800,
	1000, 1400, 1800, 2200, 2600, 3000, 3500, 5000, 7000));
static const Variable v_pthat(bin_pthat, "p_{T} [GeV]");

static const Binning bin_pt1((ivector<double>(),
	0, 50, 80, 120, 170, 230, 265, 300, 340, 380, 425, 470, 500, 540, 600, 660,
	725, 800, 900, 1000, 1200, 1400, 1800, 2200, 2600, 3000, 3500, 7000));
static const Variable v_pt1(bin_pthat, "p_{T} [GeV]");

static const Binning bin_ptJTF((ivector<double>(),
	1, 5, 6, 8, 10, 12, 15, 18, 21, 24, 28, 32, 37, 43, 49, 56, 64, 74, 84, 97,
	114, 133, 153, 174, 196, 220, 245, 272, 300, 330, 362, 395, 430, 468, 507,
	548, 592, 638, 686, 737, 790, 846, 905, 967, 1032, 1101, 1172, 1248, 1327,
	1410, 1497, 1588, 1684, 1784, 1890, 2000, 2116, 2238, 2366, 2500, 2640, 2787,
	2941, 3103, 3273, 3450, 3637, 3832, 4037, 4252, 4477, 4713, 4961, 5220, 5492,
	5777, 6076, 6389, 6717, 7000));

static const Binning bin_unf((ivector<double>(),
	0, 1, 5, 6, 8, 10, 12, 15, 18, 21, 24, 28, 32, 37, 43, 49, 56, 64, 74, 84, 97,
	114, 133, 153, 174, 196, 220, 245, 272, 300, 330, 362, 395, 430, 468, 507, 548,
	592, 638, 686, 737, 790, 846, 905, 967, 1032, 1101, 1172, 1248, 1327, 1410,
	1497, 1588, 1684, 1784, 1890, 2000, 2116, 2238, 2366, 2500, 2640, 2787, 2941,
	3103, 3273, 3450, 3637, 3832, 4037, 4252, 4477, 4713, 4961, 5220, 5492, 5777,
	6076, 6389, 6717, 7000));

static const Binning bin_ptold((ivector<double>(),
	1, 9, 18, 29, 40, 53, 67, 81, 97, 114, 133, 153, 174, 196, 220, 245, 272,
	300, 330, 362, 395, 430, 468, 507, 548, 592, 638, 686, 737, 790, 846, 905,
	967, 1032, 1101, 1172, 1248, 1327, 1410, 1497, 1588, 1684, 1784, 1890, 2000,
	2116, 2238, 2366, 2500, 2640, 2787, 2941, 3103, 3273, 3450, 3637, 3832,
	4037, 4252, 4477, 4713, 4961, 5220, 5492, 5777, 6076, 6389, 6717, 7000));

static const Binning bin_eta(240, -6, 6); // 0.05 bins
static const Variable v_eta(bin_eta, "#eta");

static const Binning bin_y(240, -6, 6); // 0.05 bins
static const Variable v_y(bin_y, "y");

static const Binning bin_eta_hcal_abs((ivector<double>(), // almost 0.087 bins
	0, 0.087, 0.174, 0.261, 0.348, 0.435, 0.522, 0.609, 0.696, 0.783, 0.870, //- no hcal between 0.870-0.879
	0.879, 0.957, 1.044, 1.131, 1.218, 1.305, 1.392, 1.479, 1.566, 1.653,
	1.740, 1.830, 1.930, 2.043, 2.172, 2.322, 2.500, 2.650, 2.853, 2.964,
	3.000, 3.139, 3.314, 3.489, 3.664, 3.839, 4.013, 4.191, 4.363, 4.538,
	4.716, 4.889, 5.191,
	5.3, 5.4, 5.5, 5.6, 5.7, 5.8, 5.9, 6.0, 6.1, 6.2,
	6.3, 6.4, 6.5, 6.6, 6.7, 6.8, 6.9, 7.0, 7.1, 7.2));
static const Binning bin_eta_hcal(bin_eta_hcal_abs, true);
static const Variable v_etacalo(bin_eta_hcal, "#eta");

static const Binning bin_ycalo((ivector<double>(), 0, 0.55, 1.1, 1.7, 2.5, 3.2, 5.0));
static const Variable v_ycalo(bin_ycalo, "y");

static const Binning bin_deltaR(500, 0, 5); // 0.01 bins
static const Variable v_deltaR(bin_deltaR, "#Delta R");

static const Binning bin_deltaeta(100, 0, 4); // 0.01 bins
static const Variable v_deltaeta(bin_deltaeta, "#Delta#eta", true);

static const double res_phi = 0.087;
static const Binning bin_angle_pi(50, -5*res_phi, 45*res_phi); // 0.087 bins
static const Variable v_delta(bin_angle_pi, "#Delta");

static const Binning bin_area(400, 0, 10);

static const Binning bin_angle_2pi(74, -37*res_phi, 37*res_phi); // 0.087 bins
static const Variable v_phi(bin_angle_2pi, "#phi");

static const Binning bin_angle_0pi(37, 0, 37*res_phi); // 0.087 bins
static const Variable v_deltaphi0Pi(bin_angle_0pi, "#Delta#phi");

static const Binning bin_angle_02pi(73, 0, 73*res_phi); // 0.087 bins
static const Variable v_deltaphi02Pi(bin_angle_02pi, "#Delta#phi");
static const Variable v_deltatheta02Pi(bin_angle_02pi, "#Delta#theta");

static const Binning bin_cos(200, -1, 1, true); // 0.01 bins
static const Variable v_cos(bin_cos, "cos #Delta");

static const Binning bin_jets(100, 0, 100, true); // 1 bins
static const Variable v_jets(bin_jets, "N_{jets}");

static const Binning bin_tracks(500, 0, 2000, true); // 1 bins
static const Variable v_tracks(bin_tracks, "N_{tracks}");

static const Binning bin_PU(160, 0, 80, true); // 1 bins
static const Variable v_PU(bin_jets, "N_{vtx}");

static const Binning bin_bool(2, 0, 1, true);
static const Variable v_bool(bin_bool, "");

static const Variable v_entries(Binning(), "Entries N");

/////////////////////////////////////////////////////////////////

static const Binning bin_ratio01(100, 0, 1, true); // 1 % bins
static const Variable v_ratio01(bin_ratio01, "Ratio");

static const Binning bin_ratiom11(200, -1, 1, true); // 1 % bins
static const Variable v_ratiom11(bin_ratiom11, "Ratio");

static const Binning bin_ratio02(200, 0, 2, true); // 0.01 bins
static const Variable v_ratio02(bin_ratio02, "Ratio");
static const Variable v_calib(bin_ratio02, "Calibration factor");

static const Binning bin_ratio005(500, 0, 0.5, true); // 0.001 bins
static const Variable v_ratio005(bin_ratio005, "Ratio");

static const Binning bin_ratio002(200, 0, 0.2, true); // 0.001 bins
static const Variable v_ratio002(bin_ratio002, "Ratio");
static const Variable v_alphas(bin_ratio002, "Calibration factor");

static const Binning bin_ratio05(500, 0, 5, true); // 0.01 bins
static const Variable v_ratio05(bin_ratio05, "Ratio");

static const Binning bin_ratiom22(400, -2, 2, true); // 0.01 bins
static const Variable v_ratiom22(bin_ratiom22, "Ratio");

static const Binning bin_ratiom55(1000, -5, 5, true); // 0.01 bins
static const Variable v_ratiom55(bin_ratiom55, "Ratio");
static const Variable v_calib1(bin_ratiom55, "Calibration factor");

#endif
