#ifndef _BpTree_H_
#define _BpTree_H_

#include "BpTreeDataNode.h"
#include "BpTreeIndexNode.h"
#include "LoanBookData.h"
#include "LoanBookHeap.h"
#include <fstream>
#include <iostream>
#include <sstream>

class BpTree {
private:
	BpTreeNode* root;
	int			order;		// m children
	ofstream* fout;

public:
	BpTree(ofstream* fout, int order = 3) {
		root = NULL;
		this->order = order;
		this->fout = fout;
	}
	~BpTree() {}
	/* essential */
	bool		Insert(LoanBookData* newData);
	bool		excessDataNode(BpTreeNode* pDataNode);
	bool		excessIndexNode(BpTreeNode* pIndexNode);
	void		splitDataNode(BpTreeNode* pDataNode);
	void		splitIndexNode(BpTreeNode* pIndexNode);
	BpTreeNode* getRoot() { return root; }
	BpTreeNode* searchDataNode(string name);

	bool searchBook(string name);
	bool searchRange(string start, string end);
	bool Lcount(LoanBookData* pN); //Check books that cannot be borrowed
}; 

class mQueueNode {
private:
	LoanBookData* LData;

public:
	mQueueNode(LoanBookData* newData):pNext(nullptr) {
		this->LData = newData;
	}

	~mQueueNode() {}

	LoanBookData* get_Data() const { return this->LData; }
	mQueueNode* pNext;
};

class mQueue {
private:
	mQueueNode* f;
	mQueueNode* r;
	int size;

public:
	mQueue() {
		f = nullptr;
		r = nullptr;
		size = 0;
	}
	~mQueue() {
		while (!empty()) {
			pop();
		}
	}
	int getSize() {
		return this->size;
	}

	bool empty()
	{
		return f == nullptr;
	}

	void push(mQueueNode* newNode) {
		size++;
		if (empty()) {
			f = newNode;
			r = newNode;
		}
		else {
			r->pNext = newNode;
			r = newNode;
		}
	}
	mQueueNode pop() {
		size--;
		mQueueNode* delNode = f;
		f = f->pNext;

		mQueueNode delNodeData(delNode->get_Data());
		delete delNode;

		return delNodeData;
	}
};

#endif