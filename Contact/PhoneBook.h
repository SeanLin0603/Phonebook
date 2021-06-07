#pragma once
#include "pch.h"
#include "Utilities.h"

using namespace std;

struct Person
{
	string name;
	string phone;
	string address;
	string email;
};

class Contacts
{
public:
	Contacts();

	bool Display();
	bool Create(string name, string phone, string address, string email);
	Person* Search(string info);
	int SearchIndex(string info);
	bool Modify(string name, string phone, string address, string email);
	bool Delete(string info);
	bool Import(string fileName);
	bool Export(string fileName);
	bool Sorting(string column, string order);
	string SortingMethod;
	~Contacts();

private:
	vector<Person> data;
};
