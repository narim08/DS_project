#pragma once
#include "NameBSTNode.h"

class NameBST
{
private:
	NameBSTNode* root;

public:
	NameBST();
	~NameBST();

	NameBSTNode* getRoot();

	// insert
	void Insert(const char* name, int age, const char* infoDate, const char* endDate, const char* type);

	// search
	NameBSTNode* Search(const char* name);

	// print
	string Print(NameBSTNode* pNode);

	// delete
	void Delete(const char* name);
};
