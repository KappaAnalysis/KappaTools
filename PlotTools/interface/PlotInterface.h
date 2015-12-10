#ifndef PLOTINTERFACE_H
#define PLOTINTERFACE_H

#include "BookPlots.h"
#include "../../RootTools/interface/Directory.h"
#include "../../Toolbox/interface/IOHelper.h"

/*
class PlotHolderBase
{
public:
	virtual ~PlotHolderBase() {};
	virtual void Write() = 0;
};
*/

class PlotInterface
{
public:
	enum FileOpenType { update, reset, readonly };

	PlotInterface(const std::string filename, const FileOpenType fot = update);
	PlotInterface(const PlotInterface &pi);
	~PlotInterface();

	PlotInterface dir(std::string name);

	std::vector<std::string> dirs()
	{
		return getFirst<std::map<std::string, TDirectory*>, std::string>(GetDirObjectsMap<TDirectory>(root));
	}

	template<typename T>
	std::map<std::string, T*> getAll(bool recursive = false)
	{
		// TODO: make static to refresh only once in case of read only mode
		std::map<std::string, T*> result = GetDirObjectsMap<T>(root);
		if (recursive)
		{
			std::vector<std::string> subdirs = dirs();
			for (size_t i = 0; i < subdirs.size(); ++i)
			{
				std::map<std::string, T*> tmp = dir(subdirs[i]).getAll<T>(recursive);
				for (typename std::map<std::string, T*>::const_iterator it = tmp.begin(); it != tmp.end(); ++it)
					result.insert(make_pair(subdirs[i] + "/" + it->first, it->second));
			}
		}
		return result;
	}

	template<typename T>
	T *get(std::string name)
	{
		std::string _dir;
		if (splitDirFromName(name, _dir))
			return dir(_dir).get<T>(name);
		std::map<std::string, T*> hStore = getAll<T>();
		if (hStore.find(name) == hStore.end())
		{
			std::cout << red << name << " was not found!" << reset << std::endl;
			std::cout << hStore << std::endl;
			return 0;
		}
		return hStore[name];
	}

	template<typename T>
	T *clone(const std::string name, T *base)
	{
		return insert<T>(name, RawPlotInterface::clone<T>(KappaTools::basename(name), base));
	}

	template<typename T, typename P1>
	T *book(const std::string name, const P1 p1)
	{
		return insert<T>(name, RawPlotInterface::book<T>(KappaTools::basename(name), p1));
	}

	template<typename T, typename P1, typename P2>
	T *book(const std::string name, const P1 p1, const P2 p2)
	{
		return insert<T>(name, RawPlotInterface::book<T>(KappaTools::basename(name), p1, p2));
	}

	template<typename T, typename P1, typename P2, typename P3>
	T *book(const std::string name, const P1 p1, const P2 p2, const P3 p3)
	{
		return insert<T>(name, RawPlotInterface::book<T>(KappaTools::basename(name), p1, p2, p3));
	}

	template<typename T, typename P1, typename P2, typename P3, typename P4>
	T *book(const std::string name, const P1 p1, const P2 p2, const P3 p3, const P4 p4)
	{
		return insert<T>(name, RawPlotInterface::book<T>(KappaTools::basename(name), p1, p2, p3, p4));
	}

	template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5>
	T *book(const std::string name, const P1 p1, const P2 p2, const P3 p3, const P4 p4, const P5 p5)
	{
		return insert<T>(name, RawPlotInterface::book<T>(KappaTools::basename(name), p1, p2, p3, p4, p5));
	}

	template<typename T>
	T *insert(std::string name, T *plot)
	{
		std::string _dir;
		if (splitDirFromName(name, _dir))
			return dir(_dir).insert(name, plot);
		plot->SetName(_S(KappaTools::basename(name)));
		return insert<T>(plot);
	}

	template<typename T>
	T *insert(T *plot)
	{
		plot->SetDirectory(root);
		return plot;
	}


	TFile *plotfile;
	TDirectory *root;
	FileOpenType fot;
/*
	void registerWriteCallback(PlotHolderBase *phb)
	{
		PlotInterface::cbList[plotfile].push_back(phb);
	}
	void unregisterWriteCallback(PlotHolderBase *phb)
	{
		std::vector<PlotHolderBase*> &phbList = PlotInterface::cbList[plotfile];
		phbList.erase(std::find(phbList.begin(), phbList.end(), phb));
	}
*/
	static std::map<TFile*, int> refCount;
private:
//	static std::map<TFile*, std::vector<PlotHolderBase*> > cbList;
	PlotInterface(TFile *pf, TDirectory *r, FileOpenType t);
	bool splitDirFromName(std::string &name, std::string &dir);

};

#include <TGraph.h>
template<>
TGraph *PlotInterface::insert(TGraph *plot);

#endif
