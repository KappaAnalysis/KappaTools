#include "BranchHolder.h"
#include <iostream>

BranchHolder::BranchHolder(TTree *_tree, const std::string _bname, std::string cname, const bool check)
	: ptr(0), tree(_tree), bname(_bname)
{
	TBranch *branch = tree->GetBranch(bname.c_str());
	if (branch)
	{
		if (cname == "")
			cname = branch->GetClassName();
		// Consistency check
		if (CheckBranch(branch, cname, check))
		{
			// Allocate correct instance and set pointer
			ptr = TClass::GetClass(branch->GetClassName())->New();
			tree->SetBranchAddress(bname.c_str(), &ptr);
		}
	}
	else
		std::cerr << "Requested branch not found: " << bname << std::endl;
}

std::string BranchHolder::ClassName()
{
	TBranch *branch = tree->GetBranch(bname.c_str());
	if (branch)
		return branch->GetClassName();
	return "";
}

void BranchHolder::UpdateTree(TTree *newTree)
{
	if (ptr)
	{
		TBranch *branch = tree->GetBranch(bname.c_str());
		tree->ResetBranchAddress(branch);
		newTree->SetBranchAddress(bname.c_str(), &ptr);
	}
	tree = newTree;
}

BranchHolder::~BranchHolder()
{
	if (ptr)
	{
		TBranch *branch = tree->GetBranch(bname.c_str());
		tree->ResetBranchAddress(branch);
		TClass::GetClass(branch->GetClassName())->GetDelete()(ptr);
	}
}
