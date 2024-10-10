#pragma warning (disable: 4996)
#include "Manager.h"

void Manager::run(const char* command)
{
	fin.open(command);
	flog.open("log.txt", ios::app);
	if (!fin)
	{
		flog << "File Open Error" << endl;
		return;
	}

	char fstr[100];
	while (fin.getline(fstr, sizeof(fstr))) // Read file line by line
	{
		string line(fstr);
		istringstream iss(line);
		
		string cmd;
		string cmd2; //book name, search1
		string cmd3; //search2
		string name;
		int code=0;
		string author;
		int year=0;
		int loan_count=0;

		iss >> cmd;

		if (cmd=="LOAD") {
			if (LOAD()) {
				printSuccessCode("LOAD");
			}
			else {
				printErrorCode(100);
			}
		}
		else if (cmd == "ADD") {
			char* ptr = strtok(fstr, " ");
			cmd = ptr;
			ptr = strtok(NULL, "\t");
			name = ptr;
			ptr = strtok(NULL, "\t");
			code = atoi(ptr);
			ptr = strtok(NULL, "\t");
			author = ptr;
			ptr = strtok(NULL, "\t");
			year = atoi(ptr);

			if (!ADD(name, code, author, year)) {
				printErrorCode(200);
			}
		}
		else if (cmd == "SEARCH_BP") {
			iss >> cmd2;
			if (iss >> cmd3)
			{
				if (!SEARCH_BP_RANGE(cmd2, cmd3))
				{
					printErrorCode(300);
				}
			}
			else
			{
				if (!SEARCH_BP_BOOK(cmd2))
				{
					printErrorCode(300);
				}
			}
		}
		else if (cmd == "PRINT_BP") {
			if (!PRINT_BP()) {
				printErrorCode(400);
			}
		}
		else if (cmd == "PRINT_ST") {
			iss >> code;
			if (!PRINT_ST()) {
				printErrorCode(500);
			}
		}
		else if (cmd == "DELETE") {
			if (!DELETE()) {
				printErrorCode(600);
			}
		}
		else if (cmd == "EXIT") {
			printSuccessCode("EXIT");
		}
		else { // Incorrect command
			printErrorCode(700);
		}
		
	}
	fin.close();
	flog.close();
	return;
}

bool Manager::LOAD()
{
	ifstream fdata("loan_book.txt"); //open data file
	if (!fdata) { //Error if file does not exist
		return false;
	}
	
	char fstr[100];
	while (fdata.getline(fstr, sizeof(fstr))) {
		string name;
		int code=0;
		string author;
		int year=0;
		int loan_count;

		char* ptr = strtok(fstr, "\t");
		name = ptr;
		ptr=strtok(NULL, "\t");
		code = atoi(ptr);
		ptr = strtok(NULL, "\t");
		author = ptr;
		ptr = strtok(NULL, "\t");
		year = atoi(ptr);
		ptr = strtok(NULL, "\t");
		loan_count = atoi(ptr);

		cout << name << '/' << code << '/' << author << '/' << year << '/' << loan_count << endl;

		LoanBookData* newData = new LoanBookData();
		newData->setBookData(name, code, author, year);
		bptree->Insert(newData);
	}
	return true;
}

bool Manager::ADD(string name, int code, string author, int year)
{
	if (year == 0) { // Error when argument format does not match
		return false;
	}

	LoanBookData* newData = new LoanBookData();
	newData->setBookData(name, code, author, year);
	cout << name << '/' << code << '/' << author << '/' << year << '/' << endl;
	flog << "========" << "ADD" << "========" << endl;
	flog << name << '/' << code << '/' << author << '/' << year << endl;
	flog << "===================" << endl;
	flog << endl;
	bptree->Insert(newData);
	return true;
}

bool Manager::SEARCH_BP_BOOK(string book)
{
	if (!bptree->searchBook(book)) {
		return false;
	}
	return true;
}

bool Manager::SEARCH_BP_RANGE(string s, string e)
{
	if (!bptree->searchRange(s, e)) {
		return false;
	}
	return true;
}

bool Manager::PRINT_BP()
{

	return false;
}

bool Manager::PRINT_ST()
{

	return false;
}

bool Manager::DELETE()
{

	return false;
}

void Manager::printErrorCode(int n) {				//ERROR CODE PRINT
	flog << "========ERROR========" << endl;
	flog << n << endl;
	flog << "=====================" << endl << endl;
}

void Manager::printSuccessCode(const char* cmd) {//SUCCESS CODE PRINT 
	flog << "========"<< cmd <<"========" << endl;
	flog << "Success" << endl;
	flog << "====================" << endl << endl;
}
