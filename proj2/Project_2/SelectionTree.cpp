#include "SelectionTree.h"

bool SelectionTree::Insert(LoanBookData* newData) {
	SelectionTreeNode* newNode = new SelectionTreeNode();
	newNode->setBookData(newData);

	if (!root) { //first node
		root = newNode;
		return true;
	}
	else {
		SelectionTreeNode* pCurr = root; //current
		SelectionTreeNode* pa = nullptr; //parent

		while (pCurr) { //Find location 
			pa = pCurr;
			if (newData->getName().compare(pCurr->getBookData()->getName())<=0) {
				pCurr = pCurr->getLeftChild();
			}
			else {
				pCurr = pCurr->getRightChild();
			}
		}
		if (pa->getLeftChild() == nullptr) {
			pa->setLeftChild(newNode);
		}
		else {
			pa->setRightChild(newNode);
		}
	}
	return true;
}

bool SelectionTree::Delete() {

	return true;
}

bool SelectionTree::printBookData(int bookCode) {

	return true;
}