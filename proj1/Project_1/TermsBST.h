#pragma once
#include "TermsBSTNode.h"

class TermsBST
{
private:
	TermsBSTNode* root;

public:
	TermsBST();
	~TermsBST();

	TermsBSTNode* getRoot();

	// insert
	void Insert(const char* name, int age, const char* infoDate, const char* endDate);

	// print
	string Print(TermsBSTNode* pNode);

	// delete
	void Delete(const char* endDate);
	void DeleteTerms(const char* endDate);
};