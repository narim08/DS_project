#pragma once
#include <iostream>
using namespace std;

class NameBSTNode
{
private:

	NameBSTNode* left;
	NameBSTNode* right;

	char name[21]; //Member name
	int age; //Member age
	char infoDate[12]; //Personal information collection date
	char endDate[12]; //Personal information expiration date
	char type[2]; //Type of subscription terms and conditions

public:
	NameBSTNode(const char* name, int age, const char* infoDate, const char* endDate, const char* type) {
		strcpy_s(this->name, 21, name);
		this->age = age;
		strcpy_s(this->infoDate, 12, infoDate);
		strcpy_s(this->endDate, 12, endDate);
		strcpy_s(this->type, 2, type);
		left = nullptr;
		right = nullptr;
	}
	~NameBSTNode() {}

	const char* get_name() const { return this->name; }
	int get_age() const { return this->age; }
	const char* get_infoDate() const { return this->infoDate; }
	const char* get_endDate() const { return this->endDate; }
	const char* get_type() const { return this->type; }

	NameBSTNode* getLeft() { return left; }
	NameBSTNode* getRight() { return right; }

	void setLeft(NameBSTNode* left) { this->left = left; }
	void setRight(NameBSTNode* right) { this->right = right; }
	void setName(const char* name){ strcpy_s(this->name, 21, name); }
};