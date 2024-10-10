#include "TermsList.h"

TermsLIST::TermsLIST() : head(nullptr), Tail(nullptr) {}

TermsLIST::~TermsLIST()
{
	while (head) {
		TermsListNode* delNode = head;
		head = head->getNext();
		delete delNode;
	}
}

TermsListNode* TermsLIST::getHead()
{
	return head;
}

// insert
void TermsLIST::insert(TermsListNode* newNode) {
	if (head == nullptr) { //first node
		head = newNode;
		Tail = newNode;
		newNode->setNum();
	}
	else {
		TermsListNode* pCurr = head;
		string newType = newNode->getType();

		while (pCurr) {
			string cType = pCurr->getType();
			
			// same type, number of members increases
			if (cType.compare(newType)) {
				pCurr->setNum();
				break;
			}
			// new type node, add list
			else if (pCurr->getNext() == nullptr) {
				Tail->setNext(newNode);
				Tail = newNode;
				newNode->setNum();
				break;
			}
			else {
				pCurr = pCurr->getNext();
			}
		}
	}
}

// Search
TermsListNode* TermsLIST::Search(const char* type) {
	TermsListNode* pCurr = head;
	while (pCurr) {
		if (!strcmp(pCurr->getType(), type)) {
			return pCurr;
		}
		pCurr = pCurr->getNext();
	}
	return nullptr;
}

// delete
void TermsLIST::Delete(TermsListNode* delNode) {
	if (head == nullptr) return;
	else if (head == delNode) {
		head = head->getNext();
		return;
	}
	else {
		TermsListNode* pCurr = head;
		TermsListNode* del = nullptr;
		while (pCurr->getNext()) {
			if (pCurr->getNext() == delNode) {
				del = pCurr->getNext();
				pCurr->setNext(del->getNext());
				delete del;
				return;
			}
			pCurr = pCurr->getNext();
		}
	}
}