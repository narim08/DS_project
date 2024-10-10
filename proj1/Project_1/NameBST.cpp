#define _CRT_SECURE_NO_WARNINGS
#include "NameBST.h"
#include "Manager.h"

NameBST::NameBST() : root(nullptr)
{

}
NameBST::~NameBST()
{
	
}

NameBSTNode* NameBST::getRoot()
{
	return root;
}

// insert
void NameBST::Insert(const char* name, int age, const char* infoDate, const char* endDate, const char* type)
{
	NameBSTNode* newNode = new NameBSTNode(name, age, infoDate, endDate, type);
	string Name = newNode->get_name();
	
	if (root==nullptr) {
		root = newNode;
	}
	else {
		NameBSTNode* pCurr = root;
		NameBSTNode* pP = nullptr; //Parent node

		while (pCurr) {
			pP = pCurr;
			string newName = pCurr->get_name();

			if (Name.compare(newName) < 0) {
				pCurr = pCurr->getLeft();
			}
			else {
				pCurr = pCurr->getRight();
			}
		}

		string newName = pP->get_name();
		if (Name.compare(newName) < 0) {
			pP->setLeft(newNode);
		}
		else {
			pP->setRight(newNode);
		}
	}
}

// search
NameBSTNode* NameBST::Search(const char* name) {
	NameBSTNode* pCurr = root;
	
	while (pCurr->get_name() != NULL && strcmp(pCurr->get_name(), name) != 0) {
		if (strcmp(pCurr->get_name(), name) > 0) {
			pCurr = pCurr->getLeft();
		}
		else {
			pCurr = pCurr->getRight();
		}
	}
	return pCurr;
}

// print (in-order traversal)
string NameBST::Print(NameBSTNode* pNode) {
	string nData;

	if (pNode) {
		nData += Print(pNode->getLeft());

		string pName = pNode->get_name();
		string pAge = to_string(pNode->get_age());
		string pInDate = pNode->get_infoDate();
		string pEndDate = pNode->get_endDate();
		string data = pName + '/' + pAge + '/' + pInDate + '/' + pEndDate + " ";
		nData += data;

		nData += Print(pNode->getRight());
	}

	return nData;
}

// delete
void NameBST::Delete(const char* name) {
	NameBSTNode* pP = nullptr; // parent of pCurr
	NameBSTNode* pCurr = root;

	while (pCurr && strcmp(pCurr->get_name(), name) != 0) {
		pP = pCurr;
		if (strcmp(pCurr->get_name(), name) > 0) {
			pCurr = pCurr->getLeft();
		}
		else {
			pCurr = pCurr->getRight();
		}
	}
	if (pCurr == nullptr) { //not found
		return;
	}

	// pCurr is leaf node
	if (pCurr->getLeft() == nullptr && pCurr->getRight() == nullptr) {
		if (pCurr != root) {
			if (pP->getLeft() == pCurr) {
				pP->setLeft(nullptr);
			}
			else {
				pP->setRight(nullptr);
			}
		}
		else {
			root = nullptr;
		}
		delete pCurr;
	}
	// pCurr only has right child
	else if (pCurr->getLeft()==nullptr) {
		if (pCurr != root) {
			if (pCurr == pP->getLeft()) {
				pP->setLeft(pCurr->getRight());
			}
			else {
				pP->setRight(pCurr->getRight());
			}
		}
		else {
			root = pCurr->getRight();
		}
		delete pCurr;
	}
	// pCurr only has left child
	else if (pCurr->getRight() == nullptr) {
		if (pCurr != root) {
			if (pCurr == pP->getLeft()) {
				pP->setLeft(pCurr->getLeft());
			}
			else {
				pP->setRight(pCurr->getLeft());
			}
		}
		else {
			root = pCurr->getLeft();
		}
		delete pCurr;
	}
	// pCurr has left and right child
	else {
		NameBSTNode* pPrevprev = pCurr;
		NameBSTNode* pPrev = pCurr->getRight();
		NameBSTNode* curr = pCurr->getRight()->getLeft();

		while (curr) {
			pPrevprev = pPrev;
			pPrev = curr;
			curr = curr->getLeft();
		}
		pCurr->setName(pPrev->get_name());
		if (pPrevprev == pCurr) {
			pPrevprev->setRight(pPrev->getRight());
		}
		else {
			pPrevprev->setLeft(pPrev->getRight());
		}
		delete pPrev;
	}
}