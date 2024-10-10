#pragma once
#include "TermsListNode.h"

class TermsLIST
{
private:
	TermsListNode* head;
	TermsListNode* Tail;

public:
	TermsLIST();
	~TermsLIST();

	TermsListNode* getHead();

	// insert
	void insert(TermsListNode* newNode);

	// Search
	TermsListNode* Search(const char* type);
	
	// delete
	void Delete(TermsListNode* delNode);
};