#pragma warning (disable: 4996)
#include "Manager.h"
#include "GraphMethod.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

Manager::Manager()
{
	graph = nullptr;
	fout.open("log.txt", ios::app);
	load = 0;	//Anything is not loaded
}

Manager::~Manager()
{
	if (load)	//if graph is loaded, delete graph
		delete graph;
	if (fout.is_open())	//if fout is opened, close file
		fout.close();	//close log.txt File
}

void Manager::run(const char* command_txt) {
	ifstream fin;	//Command File Input File Stream
	fin.open(command_txt, ios_base::in);//File open with read mode

	if (!fin) { //If command File cannot be read, Print error
		fout << "command file open error" << endl;
		return;	//Return
	}

	char fstr[100];
	while (fin.getline(fstr, sizeof(fstr))) { // Read file line by line
		string line(fstr);
		istringstream iss(line);

		string cmd;
		char option;
		int vertex, s_vertex, e_vertex;
		char* file;

		iss >> cmd;

		if (cmd == "LOAD") {
			char* ptr = strtok(fstr, " ");
			cmd = ptr;
			ptr = strtok(NULL, " ");
			file = ptr;
			if (LOAD(file)) {
				printSuccessCode("LOAD");
			}
			else {
				printErrorCode(100);
			}
		}
		else if (cmd == "PRINT") {
			if (!PRINT()) {
				printErrorCode(200);
			}
		}
		else if (cmd == "BFS") {
			char* ptr = strtok(fstr, " ");
			cmd = ptr;
			ptr = strtok(NULL, " ");
			option = ptr[0];
			ptr = strtok(NULL, " ");
			vertex = atoi(ptr);
			if (!mBFS(option, vertex)) {
				printErrorCode(300);
			}
		}
		else if (cmd == "DFS") {
			char* ptr = strtok(fstr, " ");
			cmd = ptr;
			ptr = strtok(NULL, " ");
			option = ptr[0];
			ptr = strtok(NULL, " ");
			vertex = atoi(ptr);
			if (!mDFS(option, vertex)) {
				printErrorCode(400);
			}
		}
		else if (cmd == "KRUSKAL") {
			if (!mKRUSKAL()) {
				printErrorCode(600);
			}
		}
		else if (cmd == "DIJKSTRA") {
			char* ptr = strtok(fstr, " ");
			cmd = ptr;
			ptr = strtok(NULL, " ");
			option = ptr[0];
			ptr = strtok(NULL, " ");
			vertex = atoi(ptr);
			if (!mDIJKSTRA(option, vertex)) {
				printErrorCode(700);
			}
		}
		else if (cmd == "BELLMANFORD") {
			char* ptr = strtok(fstr, " ");
			cmd = ptr;
			ptr = strtok(NULL, " ");
			option = ptr[0];
			ptr = strtok(NULL, " ");
			s_vertex = atoi(ptr);
			ptr = strtok(NULL, " ");
			e_vertex = atoi(ptr);
			if (!mBELLMANFORD(option, s_vertex, e_vertex)) {
				printErrorCode(800);
			}
		}
		else if (cmd == "FLOYD") {
			char* ptr = strtok(fstr, " ");
			cmd = ptr;
			ptr = strtok(NULL, " ");
			option = ptr[0];
			if (!mFLOYD(option)) {
				printErrorCode(900);
			}
		}
		else if (cmd == "KwangWoon") {
			char* ptr = strtok(fstr, " ");
			cmd = ptr;
			if (!mKwoonWoon()) {
				printErrorCode(500);
			}
		}
		else if (cmd == "EXIT") {
			printSuccessCode("EXIT");
		}
		else { //Incorrect command
			printErrorCode(1000);
		}
	}
	fin.close();
	return;
}

bool Manager::LOAD(const char* filename)
{
	ifstream fdata(filename); //open data file
	if (!fdata) { //Error if file does not exist
		return false;
	}
	if (load) { //Delete existing graph
		delete graph;
	}

	int mType = 0;
	int mSize = 0;
	int to = 0;
	int from = 0;
	int weight = 0;

	string type;
	getline(fdata, type); //type checking
	string fstr;

	if (type == "L") { //List graph
		getline(fdata, fstr);
		mSize = stoi(fstr);
		graph = new ListGraph(mType, mSize); //Create a new List graph

		for (int i = 0; i <= mSize; i++) {
			while (i <= mSize) {
				getline(fdata, fstr);

				if (fstr.find(' ') == string::npos) { //If there is no space, save starting point
					from = stoi(fstr);
					break;
				}

				stringstream ss(fstr); //Separate strings based on spaces
				getline(ss, fstr, ' ');
				to = stoi(fstr);

				getline(ss, fstr);
				weight = stoi(fstr);

				graph->insertEdge(from, to, weight); //insert List graph
			}
		}
	}
	else if (type == "M") { //Matrix graph
		mType = 1;
		getline(fdata, fstr);
		mSize = stoi(fstr);
		graph = new MatrixGraph(mType, mSize); //Create a new Matrix graph

		for (int i = 1; i <= mSize; i++) { //row
			for (int j = 1; j <= mSize; j++) { //column
				if (j == mSize) { //Skip to next line
					getline(fdata, fstr);
				}
				else {
					getline(fdata, fstr, ' ');
				}
				weight = stoi(fstr);

				if (weight) { //Insert if connection exists
					graph->insertEdge(i, j, weight);
				}
			}
		}
	}
	else { //invalid type
		return false;
	}

	load++;
	return true;
}

bool Manager::PRINT()
{
	if (!graph) { //When the graph does not exist
		return false;
	}
	graph->printGraph(&fout);
	return true;
}

bool Manager::mBFS(char option, int vertex)
{
	if (!graph || vertex > graph->getSize()) { //graph does not exist or no starting point
		return false;
	}
	if (option != 'Y' && option != 'N') { //invalid argument
		return false;
	}

	fout << "========BFS========" << endl;
	if (option == 'Y') {
		fout << "Directed Graph BFS result" << endl;
	}
	else if (option == 'N') {
		fout << "Undirected Graph BFS result" << endl;
	}
	fout << "startvertex: " << vertex << endl;
	BFS(graph, option, vertex);
	fout << "===================" << endl;
	fout << endl;
	return true;
}

bool Manager::mDFS(char option, int vertex)
{
	if (!graph || vertex > graph->getSize()) { //graph does not exist or no starting point
		return false;
	}
	if (option != 'Y' && option != 'N') { //invalid argument
		return false;
	}

	fout << "========DFS========" << endl;
	if (option == 'Y') {
		fout << "Directed Graph DFS result" << endl;
	}
	else if (option == 'N') {
		fout << "Undirected Graph DFS result" << endl;
	}
	fout << "startvertex: " << vertex << endl;
	DFS(graph, option, vertex);
	fout << "===================" << endl;
	fout << endl;
	return true;
}

bool Manager::mDIJKSTRA(char option, int vertex)
{
	if (!graph || vertex > graph->getSize()) { //graph does not exist
		return false;
	}
	fout << "======== DIJKSTRA ========" << endl;
	if (option == 'Y') {
		fout << "Directed Graph Dijkstra result" << endl;
	}
	else if (option == 'N') {
		fout << "Undirected Graph Dijkstra result" << endl;
	}
	fout << "startvertex: " << vertex << endl;
	Dijkstra(graph, option, vertex);
	fout << "==========================" << endl;
	fout << endl;
	return true;
}

bool Manager::mKRUSKAL()
{
	if (!graph || !Kruskal(graph)) { //graph does not exist
		return false;
	}
	return true;
}

bool Manager::mBELLMANFORD(char option, int s_vertex, int e_vertex)
{
	if (!graph) {
		return false;
	}
	fout << "======== Bellman-Ford ========" << endl;
	if (option == 'Y') {
		fout << "Directed Graph Bellman-Ford result" << endl;
	}
	else if (option == 'N') {
		fout << "Undirected Graph Bellman-Ford result" << endl;
	}
	Bellmanford(graph, option, s_vertex, e_vertex);
	fout << "==========================" << endl;
	fout << endl;
	return true;
}

bool Manager::mFLOYD(char option)
{
	if (!graph) {
		return false;
	}
	fout << "======== FLOYD ========" << endl;
	if (option == 'Y') {
		fout << "Directed Graph FLOYD result" << endl;
	}
	else if (option == 'N') {
		fout << "Undirected Graph FLOYD result" << endl;
	}
	FLOYD(graph, option);
	fout << "==========================" << endl;
	fout << endl;
	return true;
}

bool Manager::mKwoonWoon() {
	if (!graph) {
		return false;
	}
	fout << "======== KWANGWOON ========" << endl;
	fout << "startvertex: 1" << endl;
	KWANGWOON(graph);
	fout << "==========================" << endl;
	fout << endl;
	return true;
}

void Manager::printErrorCode(int n) //ERROR CODE PRINT
{
	fout << "========ERROR=======" << endl;
	fout << n << endl;
	fout << "====================" << endl << endl;
}

void Manager::printSuccessCode(const char* cmd) { //SUCCESS CODE PRINT 
	fout << "========" << cmd << "========" << endl;
	fout << "Success" << endl;
	fout << "====================" << endl << endl;
}
