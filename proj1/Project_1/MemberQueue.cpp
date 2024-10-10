#include "MemberQueue.h"

Manager m;

MemberQueue::MemberQueue() : f(nullptr), r(nullptr), size(0) {}

MemberQueue::~MemberQueue()
{
	while (!empty()) {
		pop();
	}
}

bool MemberQueue::empty()
{
	return f == nullptr;
}

bool MemberQueue::full()
{
	return size == 100; //queue size: 100
}

void MemberQueue::push(MemberQueueNode* newNode)
{
	if (full()) { //Error: queue is full
		m.PrintErrorCode(200);
		exit(-1);
	}

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

MemberQueueNode MemberQueue::pop()
{
	if (empty()) { //Error: queue is empty
		m.PrintErrorCode(300);
		exit(-1);
	}

	size--;
	MemberQueueNode* delNode = f;
	f = f->pNext;

	MemberQueueNode delNodeData(delNode->get_name(), delNode->get_age(), delNode->get_infoDate(), delNode->get_type());
	delete delNode;
	
	return delNodeData;
}

MemberQueueNode MemberQueue::front()
{
	return *f;
}