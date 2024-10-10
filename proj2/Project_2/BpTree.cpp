#include "BpTree.h"
mQueue mq; 
mQueue mqPa; //parent queue
LoanBookHeap heap100;
LoanBookHeap heap200;
LoanBookHeap heap300;
LoanBookHeap heap400;
LoanBookHeap heap500;
LoanBookHeap heap600;
LoanBookHeap heap700;
map<string, LoanBookData*> m;

bool BpTree::Insert(LoanBookData* newData) {
	if (!root) { //first data
		BpTreeNode* p = new BpTreeNode();
		p->insertDataMap(newData->getName(), newData);
		p->setName(newData->getName());
		m.insert(pair<string, LoanBookData*>(newData->getName(), newData));
		mQueueNode* queueNode = new mQueueNode(newData);
		mq.push(queueNode);
		root = p;
	}
	else if(!(root->getLeftChild())) { //2~3 data
		if (root->getName() == newData->getName()) { //if same name, replace after increasing the count
			newData->updateCount();
			root->deleteMap(newData->getName());
			if (!Lcount(newData)) { //Check books that cannot be borrowed
				return true;
			}
			root->insertDataMap(newData->getName(), newData);
			return true;
		}
		root->insertDataMap(newData->getName(), newData);
		m.insert(pair<string, LoanBookData*>(newData->getName(), newData));
		mQueueNode* queueNode = new mQueueNode(newData);
		mq.push(queueNode);
		if (mq.getSize()>order-1) { //If there are more than 3 keys, split
			splitDataNode(root);
		}
	}
	else { //The height of the tree is greater than 1
		if (root->getName() == newData->getName()) { //if same name, replace after increasing the count
			newData->updateCount();
			root->deleteMap(newData->getName());
			if (!Lcount(newData)) { ////Check books that cannot be borrowed
				return true;
			}
			root->insertDataMap(newData->getName(), newData);
			return true;
		}
		if (newData->getName().compare(root->getName())>0) { //rightchild
			root->getRightChild()->insertDataMap(newData->getName(), newData);
			m.insert(pair<string, LoanBookData*>(newData->getName(), newData));
			mQueueNode* queueNode = new mQueueNode(newData);
			mq.push(queueNode);
			if (mq.getSize() > order - 1) { //If there are more than 3 keys, split
				splitDataNode(root->getRightChild());
			}
		}
	}
	return true;
}

bool BpTree::excessDataNode(BpTreeNode* pDataNode) {
	if (pDataNode->getDataMap()->size() > order - 1) return true;//order is equal to the number of elements 
	else return false;
}

bool BpTree::excessIndexNode(BpTreeNode* pIndexNode) {
	if (pIndexNode->getIndexMap()->size() > order - 1)return true;//order is equal to the number of elements 
	else return false;
}

void BpTree::splitDataNode(BpTreeNode* pDataNode) {
	mQueueNode popData1 = mq.pop(); //first key
	LoanBookData* newDataNode = popData1.get_Data();
	BpTreeNode* p = new BpTreeNode();

	//After splitting the first key, store it on the new node
	p->insertDataMap(newDataNode->getName(), newDataNode);
	p->setName(newDataNode->getName());
	pDataNode->deleteMap(newDataNode->getName());
	
	mQueueNode popData2 = mq.pop(); //second key = parent node
	LoanBookData* paDataNode = popData2.get_Data();
	BpTreeNode* pa = new BpTreeNode();
	pa->insertIndexMap(paDataNode->getName(), pa);
	
	if (pDataNode == root) {
		pa->setName(paDataNode->getName());
	}
	
	mQueueNode* queueNode2 = new mQueueNode(paDataNode); //queue sort
	mq.push(queueNode2);
	//mqPa.push(queueNode2);

	mQueueNode popData3 = mq.pop();
	LoanBookData* DataNode3 = popData3.get_Data();
	mQueueNode* queueNode3 = new mQueueNode(DataNode3);
	mq.push(queueNode3);
	
	pDataNode->setName(paDataNode->getName());
	p->setNext(pDataNode); //DataNode list
	pDataNode->setPrev(p);
	p->setParent(pa); //tree connection
	pDataNode->setParent(pa);
	if (pDataNode == root) {
		pa->setLeftChild(p);
	}
	else {
		pa->setMidChild(p);
	}
	pa->setRightChild(pDataNode);
	root = pa;

	if (mqPa.getSize() > order - 1) { //indexNode split
		splitIndexNode(pa);
	}
}

void BpTree::splitIndexNode(BpTreeNode* pIndexNode) {
	mQueueNode popData1 = mqPa.pop(); //1 data
	LoanBookData* s1 = popData1.get_Data();
	BpTreeNode* p1 = new BpTreeNode();
	p1->insertIndexMap(s1->getName(), p1);
	p1->setName(s1->getName());
	p1->setLeftChild(root->getLeftChild());
	p1->setRightChild(root->getLeftChild()->getNext());

	mQueueNode popData2 = mqPa.pop(); //2 data
	LoanBookData* s2 = popData2.get_Data();
	BpTreeNode* p2= new BpTreeNode();
	p2->insertIndexMap(s2->getName(), p2);
	p2->setName(s2->getName());

	mQueueNode popData3 = mqPa.pop(); //3 data
	LoanBookData* s3 = popData3.get_Data();
	BpTreeNode* p3 = new BpTreeNode();
	p3->insertIndexMap(s3->getName(), p3);
	p3->setName(s3->getName());
	p3->setLeftChild(root->getRightChild());
	p3->setRightChild(root->getRightChild()->getNext());

	p2->setLeftChild(p1);
	p2->setRightChild(p3);

	root->deleteMap(s1->getName());
	root->deleteMap(s2->getName());
	root->deleteMap(s3->getName());
	root = p2;
}

BpTreeNode* BpTree::searchDataNode(string name) {
	BpTreeNode* pCur = root;
	while (pCur && pCur->getName() != name) {
		if (name.compare(pCur->getName()) < 0) { //left
			if (pCur->getLeftChild()) {
				pCur = pCur->getLeftChild();
			}
			else break;
		}
		else { //right 
			if (pCur->getRightChild()) {
				pCur = pCur->getRightChild();
			}
			else break;
		}
	}
	return pCur;
}

bool BpTree::searchBook(string name) {
	BpTreeNode* pCur = root;
	while (pCur && pCur->getName() != name) {
		if (name.compare(pCur->getName()) < 0) { //left
			if (pCur->getLeftChild()) {
				pCur = pCur->getLeftChild();
			}
			else break;
		}
		else { //right 
			if (pCur->getRightChild()) {
				pCur = pCur->getRightChild();
			}
			else break;
		}
	}
	map<string, LoanBookData*>* ma = pCur->getDataMap();
	LoanBookData* Ld = m.find(name)->second;
	if (!Ld) {
		return false;
	}
	*fout << "========SEARCH_BP========" << endl;
	*fout << Ld->getName() << "/" << Ld->getCode() << "/" << Ld->getAuthor() << "/" << Ld->getYear() << "/" << Ld->getLoanCount() << endl;
	*fout << "=========================" << endl;
	*fout << endl;

	return true;
}

bool BpTree::searchRange(string start, string end) {

	return false;
}


bool BpTree::Lcount(LoanBookData* pN) { //Check books that cannot be borrowed
	int r = 0; //result

	switch (pN->getCode())
	{
	case 000:
		if (pN->getLoanCount() == 3) {
			r = 1;
			heap100.Insert(pN);
		}
		break;
	case 100:
		if (pN->getLoanCount() == 3) {
			r = 1;
			heap200.Insert(pN);
		}
		break;
	case 200:
		if (pN->getLoanCount() == 3) {
			r = 1;
			heap200.Insert(pN);
		}
		break;
	case 300:
		if (pN->getLoanCount() == 4) {
			r = 1;
			heap300.Insert(pN);
		}
		break;
	case 400:
		if (pN->getLoanCount() == 4) {
			r = 1;
			heap400.Insert(pN);
		}
		break;
	case 500:
		if (pN->getLoanCount() == 2) {
			r = 1;
			heap500.Insert(pN);
		}
		break;
	case 600:
		if (pN->getLoanCount() == 2) {
			r = 1;
			heap600.Insert(pN);
		}
		break;
	case 700:
		if (pN->getLoanCount() == 2) {
			r = 1;
			heap700.Insert(pN);
		}
		break;
	default:
		break;
	}

	if (r == 1) {
		return false;
	}
	else {
		return true;
	}
}