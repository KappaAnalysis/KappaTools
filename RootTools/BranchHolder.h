#ifndef KAPPA_BRANCHHOLDER_H
#define KAPPA_BRANCHHOLDER_H

#include <TTree.h>
#include "Directory.h"

struct BranchHolder
{
	BranchHolder(TTree *_tree, const std::string _bname, std::string cname = "", const bool check = true);
	~BranchHolder();

	std::string ClassName();
	void UpdateTree(TTree *newTree);

	void *ptr;
private:
	TTree *tree;
	std::string bname;
};

#endif
