#pragma once
#include "LoanBookData.h"

class BpTreeNode
{
private:
	BpTreeNode* pParent;
	BpTreeNode* pMostLeftChild;
	BpTreeNode* pLeftChild;
	BpTreeNode* pMidChild;
	BpTreeNode* pRightChild;
	string name;

public:
	BpTreeNode() {
		pParent = NULL;
		pMostLeftChild = NULL;
		pLeftChild = NULL;
		pMidChild = NULL;
		pRightChild = NULL;
	}
	~BpTreeNode() {

	}

	void setMostLeftChild(BpTreeNode* pN) { pMostLeftChild = pN; }
	void setParent(BpTreeNode* pN) { pParent = pN; }
	void setLeftChild(BpTreeNode* pN) { pLeftChild = pN; }
	void setMidChild(BpTreeNode* pN) { pMidChild = pN; }
	void setRightChild(BpTreeNode* pN) { pRightChild = pN; }
	void setName(string name) { this->name = name; }

	BpTreeNode* getParent() { return pParent; }
	BpTreeNode* getMostLeftChild() { return pMostLeftChild; }
	BpTreeNode* getLeftChild() { return pLeftChild; }
	BpTreeNode* getMidChild() { return pMidChild; }
	BpTreeNode* getRightChild() { return pRightChild; }
	string getName() { return name; }

	virtual void setNext(BpTreeNode* pN) {}
	virtual void setPrev(BpTreeNode* pN) {}
	virtual BpTreeNode* getNext() { return NULL; }
	virtual BpTreeNode* getPrev() { return NULL; }

	virtual void insertDataMap(string n, LoanBookData* pN) {}
	virtual void insertIndexMap(string n, BpTreeNode* pN) {}
	virtual void deleteMap(string n) {}

	virtual map<string, BpTreeNode*>* getIndexMap() { return {}; }
	virtual map<string, LoanBookData*>* getDataMap() { return {}; }

};