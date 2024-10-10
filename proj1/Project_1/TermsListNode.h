#pragma once
#include <iostream>
#include "TermsBST.h"
using namespace std;

class TermsListNode
{
private:
	char type[2]; //Type of subscription terms
	int memNum; //number of members
	TermsBST* bPtr;
	
	TermsListNode* next;

public:
	TermsListNode(const char* type) :memNum(0), bPtr(nullptr) {
		strcpy_s(this->type, 2, type);
	}
	~TermsListNode() {}

	TermsListNode* getNext() { return next; }
	const char* getType() { return this->type; }
	const int getNum() { return this->memNum; }
	TermsBST* getPtr() { return this->bPtr; }

	void setNum() { this->memNum++; } //increase number of member
	void setPtr(TermsBST* ptr) { this->bPtr = ptr; }
	void setNext(TermsListNode* next) { this->next = next; }
};