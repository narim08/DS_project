#include "Manager.h"

MemberQueue queue;

Manager::Manager()
{
    
}
Manager::~Manager()
{
    
}

void Manager::run(const char* command)
{
    // Open command & log file
    fcmd.open(command);
    flog.open("log.txt");
    if (!fcmd)
    {
        flog << "Fail to open command file" << endl;
        exit(-1);
    }

    // Run command
    char fstr[100]; //file string
    while (fcmd.getline(fstr, sizeof(fstr))) {
        char cmd[10]; //command
        char cmd2[21]; //print & delete cmd
        char cmd3[21]; //delete cmd
        char name[21];
        int age;
        char infoDate[12];
        char type[2];

        char* ptr = strtok(fstr, " "); //cmd
        strcpy(cmd, ptr);
       
        if (!strcmp(cmd, "LOAD")) {
            Load("data.txt"); //file name
        }
        else if (!strcmp(cmd, "ADD")) {
            ptr = strtok(NULL, " ");
            strcpy(name, ptr);
            ptr = strtok(NULL, " ");
            age = atoi(ptr);
            ptr = strtok(NULL, " ");
            strcpy(infoDate, ptr);
            ptr = strtok(NULL, " ");
            strcpy(type, ptr);

            if (type[0] == NULL) { //Error when argument format does not match
                PrintErrorCode(200);
                exit(1);
            }
            Add(name, age, infoDate, type);
        }
        else if (!strcmp(cmd, "QPOP")) {
            QPop();
        }
        else if (!strcmp(cmd, "SEARCH")) {
            ptr = strtok(NULL, " ");
            strcpy(name, ptr);
            Search(name);
        }
        else if (!strcmp(cmd, "PRINT")) {
            ptr = strtok(NULL, " ");
            strcpy(cmd2, ptr);
            Print(cmd2);
        }
        else if (!strcmp(cmd, "DELETE")) {
            ptr = strtok(NULL, " ");
            strcpy(cmd2, ptr);
            ptr = strtok(NULL, " ");
            strcpy(cmd3, ptr);
            Delete(cmd2, cmd3);
        }
        else if (!strcmp(cmd, "EXIT")) { //Program exit
            PrintSuccess("EXIT");
        }
        else { //incorrect command
            PrintErrorCode(1000);
        }
    }
    fcmd.close();
    flog.close();
    return;
}

void Manager::PrintSuccess(const char* cmd)
{
    flog << "===== " << cmd << " =====" << endl;
    flog << "Success" << endl;
    flog << "===============" << endl << endl;
}
void Manager::PrintErrorCode(int num)
{
    flog << "===== ERROR =====" << endl;
    flog << num << endl;
    flog << "=================" << endl << endl;
}

// LOAD
void Manager::Load(const char* file) {
    ifstream fdata(file);
    if (!fdata) { //Error if file does not exist
        PrintErrorCode(100);
        exit(-1);
    }
    if (!queue.empty()) { //Error if data is already entered
        PrintErrorCode(100);
        exit(-1);
    }

    flog << "===== LOAD =====" << endl;
    
    char fstr[100];
    while (fdata.getline(fstr, sizeof(fstr))) {

        string line(fstr);
        istringstream iss(line);
        string name;
        int age = 0;
        string infoDate;
        string type;

        iss >> name >> age >> infoDate >> type;
       
        flog << name << "/" << age << "/" << infoDate << "/" << type << endl;

        MemberQueueNode* newNode = new MemberQueueNode(name.c_str(), age, infoDate.c_str(), type.c_str());
        queue.push(newNode);
    }
   
    flog << "================" << endl;
    flog << endl;
    fdata.close();
}

// ADD
void Manager::Add(const char* name, int age, const char* infoDate, const char* type) {
    MemberQueueNode* newNode = new MemberQueueNode(name, age, infoDate, type);
    queue.push(newNode);

    flog << "===== ADD =====" << endl;
    flog << name << "/" << age << "/" << infoDate << "/" << type << endl;
    flog << "===============" << endl;
    flog << endl;
}

NameBST Nbst;
TermsLIST list;
TermsBST Tbst_A, Tbst_B, Tbst_C, Tbst_D;

// QPOP
void Manager::QPop() {
    while (!queue.empty()) {
        MemberQueueNode popNode = queue.pop();

        //Calculate personal information expiration date
        char inDate[20]; //infoDate
        strcpy(inDate, popNode.get_infoDate());
        
        char* ptr = strtok(inDate, "-");
        int year = atoi(ptr);
        ptr = strtok(NULL, "-");
        int month = atoi(ptr);
        ptr = strtok(NULL, " ");
        int day = atoi(ptr);

        //Calculated according to the type of subscription terms and conditions
        if (!strcmp(popNode.get_type(), "A")) { //type A: 6 months
            month += 6;
            if (month > 12) {
                year += (month / 12);
                month %= 12;
            }
        }
        else if (!strcmp(popNode.get_type(), "B")) { //type B: 1 year
            year += 1;
        }
        else if (!strcmp(popNode.get_type(), "C")) { //type C: 2 years
            year += 2;
        }
        else { //type D: 3 years
            year += 3;
        }

        // int -> char
        string sYear = to_string(year);
        char cYear[5];
        strcpy_s(cYear, 5, sYear.c_str());

        string sMonth = to_string(month);
        char cMonth[3];
        strcpy_s(cMonth, 3, sMonth.c_str());
        if (month < 10) { // If it is a single digit, convert it to the format
            cMonth[1] = cMonth[0];
            cMonth[0] = '0';
            cMonth[2] = NULL;
        }

        string sDay = to_string(day);
        char cDay[3];
        strcpy_s(cDay, 3, sDay.c_str());
        if (day < 10) { // If it is a single digit, convert it to the format
            cDay[1] = cDay[0];
            cDay[0] = '0';
            cDay[2] = NULL;
        }
        
        // Combine strings
        char endDate[12];
        for (int i = 0; i < 4; i++) {
            endDate[i] = cYear[i];
        }
        endDate[4] = '-';
        endDate[5] = cMonth[0];
        endDate[6] = cMonth[1];
        endDate[7] = '-';
        endDate[8] = cDay[0];
        endDate[9] = cDay[1];
        endDate[10] = NULL;


        // Terms_List & Terms_BST build
        TermsListNode* typeNode = new TermsListNode(popNode.get_type());
 
        if (!strcmp(popNode.get_type(), "A")) {
            Tbst_A.Insert(popNode.get_name(), popNode.get_age(), popNode.get_infoDate(), endDate);
            typeNode->setPtr(&Tbst_A);
        }
        else if (!strcmp(popNode.get_type(), "B")) {
            Tbst_B.Insert(popNode.get_name(), popNode.get_age(), popNode.get_infoDate(), endDate);
            typeNode->setPtr(&Tbst_B);
        }
        else if (!strcmp(popNode.get_type(), "C")) {
            Tbst_C.Insert(popNode.get_name(), popNode.get_age(), popNode.get_infoDate(), endDate);
            typeNode->setPtr(&Tbst_C);
        }
        else { // type D
            Tbst_D.Insert(popNode.get_name(), popNode.get_age(), popNode.get_infoDate(), endDate);
            typeNode->setPtr(&Tbst_D);
        }
        list.insert(typeNode);

        // Name_BST build
        Nbst.Insert(popNode.get_name(), popNode.get_age(), popNode.get_infoDate(), endDate, popNode.get_type());
    }
    PrintSuccess("QPOP");
}

void Manager::Search(const char* name) {
    NameBSTNode* sNode = Nbst.Search(name);
    
    if (sNode) {
        flog << "===== SEARCH =====" << endl;
        flog << sNode->get_name() << "/" << sNode->get_age() << "/" << sNode->get_infoDate() << "/" << sNode->get_endDate() << endl;
        flog << "==================" << endl;
        flog << endl;
    }
    else { // No search result
        PrintErrorCode(400);
        exit(1);
    }
}

// PRINT
void Manager::Print(const char* t) {
    if (!strcmp(t, "NAME")) {
        if (Nbst.getRoot() == nullptr) {
            PrintErrorCode(500);
        }
        else {
            flog << "===== PRINT =====" << endl;
            flog << "Name_BST" << endl;
            string NbstData = Nbst.Print(Nbst.getRoot());
            istringstream iss(NbstData);
            string tok;
            while (getline(iss, tok, ' ')) {
                flog << tok << endl;
            }
            flog << "=================" << endl;
        }
    }
    else {
        string TbstData;

        if (!strcmp(t, "A")) {
            if (Tbst_A.getRoot() == nullptr) {
                PrintErrorCode(500);
            }
            else {
                flog << "===== PRINT =====" << endl;
                flog << "Terms_BST A" << endl;
                TbstData = Tbst_A.Print(Tbst_A.getRoot());
            }
        }
        else if (!strcmp(t, "B")) {
            if(Tbst_B.getRoot() == nullptr) {
                PrintErrorCode(500);
            }
            else {
                flog << "===== PRINT =====" << endl;
                flog << "Terms_BST B" << endl;
                TbstData = Tbst_B.Print(Tbst_B.getRoot());
            }
        }
        else if (!strcmp(t, "C")) {
            if (Tbst_C.getRoot() == nullptr) {
                PrintErrorCode(500);
            }
            else {
                flog << "===== PRINT =====" << endl;
                flog << "Terms_BST C" << endl;
                TbstData = Tbst_C.Print(Tbst_C.getRoot());
            }
        }
        else if (!strcmp(t, "D")) { 
            if (Tbst_D.getRoot() == nullptr) {
                PrintErrorCode(500);
            }
            else {
                flog << "===== PRINT =====" << endl;
                flog << "Terms_BST D" << endl;
                TbstData = Tbst_D.Print(Tbst_D.getRoot());
            }
        }
        else {
            PrintErrorCode(500);
        }

        istringstream iss(TbstData);
        string tok;
        while (getline(iss, tok, ' ')) {
            flog << tok << endl;
        }
        if (TbstData!="") {
            flog << "=================" << endl;
        }
    }
    flog << endl;
}

// DELETE
void Manager::Delete(const char* cmd1, const char* cmd2) {
    // TermsBST delete
    if (!strcmp(cmd1, "DATE")) {
        //Tbst_A.DeleteTerms(cmd2);
    }
    // NameBST delete
    else if (!strcmp(cmd1, "NAME")) {
        if (Nbst.Search(cmd2) == nullptr) {
            PrintErrorCode(600);
            exit(1);
        }
        NameBSTNode* delType = Nbst.Search(cmd2);
        Nbst.Delete(cmd2);

        // Delete the node with that name from TermsBST
        if (!strcmp(delType->get_type(), "A")) {
            Tbst_A.Delete(delType->get_endDate());
        }
        else if (!strcmp(delType->get_type(), "B")) {
            Tbst_B.Delete(delType->get_endDate());
        }
        else if (!strcmp(delType->get_type(), "C")) {
            Tbst_C.Delete(delType->get_endDate());
        }
        else if (!strcmp(delType->get_type(), "D")) {
            Tbst_D.Delete(delType->get_endDate());
        }
        else {
            PrintErrorCode(600);
            exit(1);
        }
    }
    // Error
    else {
        PrintErrorCode(600);
        exit(1);
    }
}