#pragma once
#include "SelectionTree.h"
#include "BpTree.h"
using namespace std;

class Manager
{
private:
	char* cmd;
	BpTree* bptree;
	SelectionTree* stree;

public:
	Manager(int bpOrder)	//constructor
	{
		bptree = new BpTree(&flog, bpOrder);
		stree = new SelectionTree(&flog);
	}

	~Manager()//destructor
	{
		if (bptree != nullptr) {
			delete bptree;
		}
		if (stree != nullptr) {
			delete stree;
		}
	}

	ifstream fin;
	ofstream flog;


	void run(const char* command);
	bool LOAD();
	bool ADD(string name, int code, string author, int year);

	bool SEARCH_BP_BOOK(string book);
	bool SEARCH_BP_RANGE(string start, string end);

	bool PRINT_BP();
	bool PRINT_ST();

	bool DELETE();

	void printErrorCode(int n);
	void printSuccessCode(const char* cmd);

};