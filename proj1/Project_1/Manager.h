#pragma once
#include "MemberQueue.h"
#include "TermsList.h"
#include "TermsBST.h"
#include "NameBST.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;
class Manager
{
private:

	ifstream	fcmd;
	ofstream	flog;

public:
	Manager();
	~Manager();

	void run(const char* command);

	void PrintSuccess(const char* cmd);
	void PrintErrorCode(int num);

	// LOAD
	void Load(const char* file);

	// ADD
	void Add(const char* name, int age, const char* infoDate, const char* type);

	// QPOP
	void QPop();
	
	//SEARCH
	void Search(const char* name);

	// PRINT
	void Print(const char* t);
	
	// DELETE
	void Delete(const char* cmd1, const char* cmd2);
};
