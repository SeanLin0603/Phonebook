#include "pch.h"
#include "PhoneBook.h"

using namespace std;

Contacts::Contacts()
{
	SortingMethod = "insertion";
}

bool Contacts::Display()
{
	cout << endl << "This is sorting by " << SortingMethod << " method." << endl;
	cout << endl << "#\tName\tPhone\t\tAddress\t\tEmail" << endl;
	cout << "---------------------------------------------------------------------" << endl;
	for (int i = 0; i < data.size(); i++)
	{
		cout << i + 1 << '\t' << data[i].name << "\t" << data[i].phone << "\t"
			<< data[i].address << "\t\t" << data[i].email << endl;
	}
	cout << "---------------------------------------------------------------------" << endl;
	cout << "There are " << data.size() << " contacts in your list." << endl;
	cout << endl;
	return true;
}

bool Contacts::Create(string name, string phone, string address, string email)
{
	if (Search(name) == nullptr && Search(phone) == nullptr)
	{
		Person user;
		user.name = name;
		user.phone = phone;
		user.address = address;
		user.email = email;
		data.push_back(user);
		return true;
	}
	else
	{
		cout << endl << "This username or phone number is duplicated!" << endl;
		return false;
	}
}

Person* Contacts::Search(string info)
{
	int userIdx = -1;
	string infoUpper = convert2Uppercase(info);
	for (int i = 0; i < data.size(); i++)
	{
		string name = convert2Uppercase(data[i].name);
		string phone = data[i].phone;

		if (!(infoUpper.compare(name) && infoUpper.compare(phone)))
		{
			userIdx = i;
		}
	}

	if (userIdx >= 0)
	{
		Person user = data[userIdx];
		return new Person(user);
	}
	else
	{
		return NULL;
	}
}

int Contacts::SearchIndex(string info)
{
	int userIdx = -1;
	string infoUpper = convert2Uppercase(info);
	for (int i = 0; i < data.size(); i++)
	{
		string name = convert2Uppercase(data[i].name);
		string phone = data[i].phone;

		if (!(infoUpper.compare(name) && infoUpper.compare(phone)))
		{
			userIdx = i;
		}
	}
	
	return userIdx;
}

bool Contacts::Modify(string name, string phone, string address, string email)
{
	try
	{
		int userIndex = SearchIndex(name);
		data[userIndex].name = name;
		data[userIndex].phone = phone;
		data[userIndex].address = address;
		data[userIndex].email = email;

		return true;
	}
	catch (const std::exception&)
	{
		return false;
	}
}

bool Contacts::Delete(string info)
{
	int userIndex = SearchIndex(info);
	if (userIndex >= 0)
	{
		data.erase(data.begin() + userIndex);
		return true;
	}
	else
	{
		cout << endl << "There is no existed user with that name or phone number." << endl;
		return false;
	}
}

bool Contacts::Import(string fileName)
{
	fstream file;
	file.open(fileName, ios::in);
	if (file.is_open())
	{
		string name, phone, address, email;
		
		while (file >> name >> phone >> address >> email)
		{
			cout << "Importing... " << name << ' ' << phone << ' ' << address << ' ' << email << endl;
			Create(name, phone, address, email);
		}
		file.close();
		return true;
	}
	else
	{
		cout << endl << "The file was opened failed." << endl;
		file.close();
		return false;
	}
}

bool Contacts::Export(string fileName)
{
	fstream file;
	file.open(fileName, ios::out);
	if (file.is_open())
	{
		file << endl << "This is sorting by " << SortingMethod << " method." << endl;
		file << endl << "#\tName\tPhone\t\tAddress\t\tEmail" << endl;
		file << "---------------------------------------------------------------------" << endl;
		for (int i = 0; i < data.size(); i++)
		{
			file << i + 1 << '\t' << data[i].name << "\t" << data[i].phone << "\t"
				<< data[i].address << "\t\t" << data[i].email << endl;
		}
		file << "---------------------------------------------------------------------" << endl;
		file << "There are " << data.size() << " contacts in your list." << endl;

		file.close();
		return true;
	}
	else
	{
		cout << endl << "The file was opened failed." << endl;
		file.close();
		return false;
	}
}

bool Contacts::Sorting(string column, int order)
{
	vector<Person> sortingData;
	vector<string> sortingElement;
	string colUpper = convert2Uppercase(column);

	enum scending { Ascending, Descending };

	if (order != Ascending && order != Descending)
	{
		cout << "Please be aware of 0 is for ascending, and 1 is for descending." << endl;
		return false;
	}

	if (!colUpper.compare("NAME"))
	{
		for (int i = 0; i < data.size(); i++)
		{
			sortingElement.push_back(data[i].name);
		}

		if (order == Ascending)
		{
			SortingMethod = "ascending name";
			// A-Z
			sort(sortingElement.begin(), sortingElement.end(), less<string>());
		}
		else if (order == Descending)
		{
			SortingMethod = "descending name";
			// Z-A
			sort(sortingElement.begin(), sortingElement.end(), greater<string>());
		}
		
		// moving data
		for (int i = 0; i < sortingElement.size(); i++)
		{
			for (int j = 0; j < data.size(); j++)
			{
				if (!sortingElement[i].compare(data[j].name))
				{
					sortingData.push_back(data[j]);
					data.erase(data.begin() + j, data.begin() + j + 1);
				}
			}
		}

		data.clear();
		data = sortingData;
		Display();
	}
	else if (!colUpper.compare("PHONE"))
	{
		for (int i = 0; i < data.size(); i++)
		{
			sortingElement.push_back(data[i].phone);
		}

		if (order == Ascending)
		{
			SortingMethod = "ascending phone";
			// 0-9
			sort(sortingElement.begin(), sortingElement.end(), less<string>());
		}
		else if (order == Descending)
		{
			SortingMethod = "descending phone";
			// 9-0
			sort(sortingElement.begin(), sortingElement.end(), greater<string>());
		}

		// moving data
		for (int i = 0; i < sortingElement.size(); i++)
		{
			for (int j = 0; j < data.size(); j++)
			{
				if (!sortingElement[i].compare(data[j].phone))
				{
					sortingData.push_back(data[j]);
					data.erase(data.begin() + j, data.begin() + j + 1);
				}
			}
		}

		data.clear();
		data = sortingData;
		Display();
	}
	else if (!colUpper.compare("ADDRESS"))
	{
		for (int i = 0; i < data.size(); i++)
		{
			sortingElement.push_back(data[i].address);
		}

		if (order == Ascending)
		{
			SortingMethod = "ascending address";
			// A-Z
			sort(sortingElement.begin(), sortingElement.end(), less<string>());
		}
		else if (order == Descending)
		{
			SortingMethod = "descending address";
			// Z-A
			sort(sortingElement.begin(), sortingElement.end(), greater<string>());
		}

		// moving data
		for (int i = 0; i < sortingElement.size(); i++)
		{
			for (int j = 0; j < data.size(); j++)
			{
				if (!sortingElement[i].compare(data[j].address))
				{
					sortingData.push_back(data[j]);
					data.erase(data.begin() + j, data.begin() + j + 1);
				}
			}
		}

		data.clear();
		data = sortingData;
		Display();
	}
	else if (!colUpper.compare("EMAIL"))
	{
		for (int i = 0; i < data.size(); i++)
		{
			sortingElement.push_back(data[i].email);
		}

		if (order == Ascending)
		{
			SortingMethod = "ascending email";
			// A-Z
			sort(sortingElement.begin(), sortingElement.end(), less<string>());
		}
		else if (order == Descending)
		{
			SortingMethod = "descending email";
			// Z-A
			sort(sortingElement.begin(), sortingElement.end(), greater<string>());
		}

		// moving data
		for (int i = 0; i < sortingElement.size(); i++)
		{
			for (int j = 0; j < data.size(); j++)
			{
				if (!sortingElement[i].compare(data[j].email))
				{
					sortingData.push_back(data[j]);
					data.erase(data.begin() + j, data.begin() + j + 1);
				}
			}
		}

		data.clear();
		data = sortingData;
		Display();
	}
	else
	{
		cout << "Invalid column name." << endl;
		return false;
	}
	return true;
}


Contacts::~Contacts()
{
	data.clear();
}