#include "LoanBookHeap.h"

void LoanBookHeap::heapifyUp(LoanBookHeapNode* pN) {
	while (pN->getParent()) {
		//Sort if smaller than parent node
		if (pN->getBookData()->getName() < pN->getParent()->getBookData()->getName()) {
			//Change parent node and child node
			LoanBookHeapNode* pa = pN->getParent();
			LoanBookData* temp = pN->getBookData();
			pN->setBookData(pa->getBookData());
			pa->setBookData(temp);
			pN = pa;
		}
		else {
			break;
		}
	}
}

void LoanBookHeap::heapifyDown(LoanBookHeapNode* pN) {
	while (pN->getLeftChild() || pN->getRightChild()) {
		LoanBookHeapNode* leftChild = pN->getLeftChild();
		LoanBookHeapNode* rightChild = pN->getRightChild();
		LoanBookHeapNode* sChild = nullptr; //small node

		//Find small node
		if (!rightChild) {
			sChild = leftChild;
		}
		else if (leftChild && leftChild->getBookData()->getName() < rightChild->getBookData()->getName()) {
			sChild = leftChild;
		}
		else {
			sChild = rightChild;
		}

		//If the pN is large, move down
		if (pN->getBookData()->getName() > sChild->getBookData()->getName()) {
			LoanBookData* temp = pN->getBookData();
			pN->setBookData(sChild->getBookData());
			sChild->setBookData(temp);
			pN = sChild;
		}
		else {
			break;
		}
	}
}

bool LoanBookHeap::Insert(LoanBookData* data) {
	LoanBookHeapNode* newNode = new LoanBookHeapNode();
	newNode->setBookData(data);

	if (!root) { //first node
		root = newNode;
	}
	else {
		LoanBookHeapNode* pCurr = root;
		while (pCurr->getLeftChild()) { //Go down to the leaf node
			pCurr = pCurr->getLeftChild();
		}
		pCurr->setLeftChild(newNode);
		newNode->setParent(pCurr);

		heapifyUp(newNode); //Align to the correct position
	}

	return true;
}