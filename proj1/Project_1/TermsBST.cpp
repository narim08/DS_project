#include "TermsBST.h"
#include "Manager.h"

TermsBST::TermsBST() : root(nullptr)
{

}
TermsBST::~TermsBST()
{

}


TermsBSTNode* TermsBST::getRoot()
{
	return root;
}


// insert
void TermsBST::Insert(const char* name, int age, const char* infoDate, const char* endDate) {
	TermsBSTNode* newNode = new TermsBSTNode(name, age, infoDate, endDate);

	string EndDate = newNode->get_endDate();
	
	if (root == nullptr) {
		root = newNode;
	}
	else {
		TermsBSTNode* pCurr = root;
		TermsBSTNode* pP = nullptr; //Parent node

		while (pCurr) {
			pP = pCurr;
			string newEndDate = pCurr->get_endDate();

			if (EndDate.compare(newEndDate) < 0) {
				pCurr = pCurr->getLeft();
			}
			else {
				pCurr = pCurr->getRight();
			}
		}

		string newEndDate = pP->get_endDate();
		if (EndDate.compare(newEndDate) < 0) {
			pP->setLeft(newNode);
		}
		else {
			pP->setRight(newNode);
		}
	}
}

// print (in-order traversal)
string TermsBST::Print(TermsBSTNode* pNode) {
	string tData;

	if (pNode) {
		tData += Print(pNode->getLeft());

		string pName = pNode->get_name();
		string pAge = to_string(pNode->get_age());
		string pInDate = pNode->get_infoDate();
		string pEndDate = pNode->get_endDate();
		string data = pName + '/' + pAge + '/' + pInDate + '/' + pEndDate + " ";
		tData += data;

		tData += Print(pNode->getRight());
	}

	return tData;
}

// delete
void TermsBST::Delete(const char* endDate) {
	TermsBSTNode* pP = nullptr; // parent of pCurr
	TermsBSTNode* pCurr = root;

	while (pCurr && strcmp(pCurr->get_endDate(), endDate) != 0) {
		pP = pCurr;
		if (strcmp(pCurr->get_endDate(), endDate) > 0) {
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
	else if (pCurr->getLeft() == nullptr) {
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
		TermsBSTNode* pPrevprev = pCurr;
		TermsBSTNode* pPrev = pCurr->getRight();
		TermsBSTNode* curr = pCurr->getRight()->getLeft();

		while (curr) {
			pPrevprev = pPrev;
			pPrev = curr;
			curr = curr->getLeft();
		}
		pCurr->setEndDate(pPrev->get_endDate());
		if (pPrevprev == pCurr) {
			pPrevprev->setRight(pPrev->getRight());
		}
		else {
			pPrevprev->setLeft(pPrev->getRight());
		}
		delete pPrev;
	}
}

/*
void TermsBST::DeleteTerms(const char* endDate) {
	//반복문으로 처음부터 탐색하면서 endDate보다
	//현재 가리키는 노드가 이전 날짜일 경우
	//그 날짜를 Delete로 보냄

	TermsBSTNode* pCurr = root;
	string EndDate = endDate;
	while (pCurr) {
		string pEndDate = pCurr->get_endDate();
		if (pEndDate.compare(EndDate) < 0) {
			Delete(pEndDate.c_str());
			pCurr = pCurr->getLeft();
		}
		else {
			pCurr = pCurr->getLeft();
		}
	}
}*/