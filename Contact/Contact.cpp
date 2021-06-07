#include "pch.h"
#include "Utilities.h"
#include "PhoneBook.h"

using namespace std;

int main()
{
	int choice = 0;
	Contacts phoneBook;

	cout << "***Welcome to Contact Management System ***" << endl << endl << endl;

	while (true)
	{
		cout << "Main Menu" << endl;
		cout << "========================================" << endl;
		cout << "[1]\t Add a new contact" << endl;
		cout << "[2]\t List all contacts" << endl;
		cout << "[3]\t Search for contact" << endl;
		cout << "[4]\t Edit a contact" << endl;
		cout << "[5]\t Delete a contact" << endl;
		cout << "[6]\t Import from file" << endl;
		cout << "[7]\t Export to file" << endl;
		cout << "[8]\t eee..." << endl;
		
		cout << endl << "[0]\t Exit" << endl;
		cout << "========================================" << endl;
		cout << "Enter the choice:";
		cin >> choice;
		cout << endl;
		
		if (choice == 0)
		{
			// EXIT
			cout << "88" << endl;
			break;
		}
		else if (choice == 1)
		{
			// CREATE
			int num = 0;
			string numStr;
			string name, phone, address, email;
			cout << "Usage of Create : Name Phone Address Email" << endl;
			cout << "Example:Amy 0912345678 Taiwan amy@example.com.tw" << endl;
			cout << "---------------------------------------------------------------------" << endl;
			cout << "How many users do you want to create:";
			cin >> numStr;
			while (!IsNumber(numStr))
			{
				cout << "How many users do you want to create:";
				cin >> numStr;
			}

			num = stoi(numStr);
			for (int i = 0; i < num; i++)
			{
				cout << "Please input new user information:";
				cin >> name >> phone >> address >> email;
				if (phoneBook.Create(name, phone, address, email))
				{
					cout << "Created an user successfully!" << endl;
				}
				else
				{
					cout << "Created an user failed!" << endl;
				}
				cout << endl;
			}
		}
		else if (choice == 2)
		{
			// DISPLAY
			phoneBook.Display();
			cout << endl;
		}
		else if (choice == 3)
		{
			// SEARCH
			string info;
			cout << "Usage of Search : Name or Phone" << endl;
			cout << "Example:Amy or 0912345678" << endl;
			cout << "Please input user information:";
			cin >> info;

			Person *user = phoneBook.Search(info);
			cout << endl;

			if (user == nullptr)
			{
				cout << "There is no existed user with that name or phone number." << endl;
			}
			else
			{
				cout << "Here is the user information:" << endl << endl;
				cout << "Name\tPhone\t\tAddress\t\tEmail" << endl;
				cout << "---------------------------------------------------------------------" << endl;
				cout << user->name << "\t" << user->phone << "\t"
					<< user->address << "\t\t" << user->email << endl;
				cout << "---------------------------------------------------------------------" << endl;
			}

			cout << endl;
		}
		else if (choice == 4)
		{
			// MODIFY
			string info;
			cout << "Usage of Modify : Name or Phone" << endl;
			cout << "Example:Amy or 0912345678" << endl;
			cout << "Please input user information:";
			cin >> info;

			Person *user = phoneBook.Search(info);
			cout << endl;

			if (user == nullptr)
			{
				cout << "There is no existed user with that name or phone number." << endl;
			}
			else
			{
				cout << "Here is the user information:" << endl << endl;
				cout << "Name\tPhone\t\tAddress\t\tEmail" << endl;
				cout << "---------------------------------------------------------------------" << endl;
				cout << user->name << "\t" << user->phone << "\t"
					<< user->address << "\t\t" << user->email << endl;
				cout << "---------------------------------------------------------------------" << endl << endl;

				string name, phone, address, email;
				cout << "Usage:Name Phone Address Email" << endl;
				cout << "Example:Amy 0912345678 Taiwan amy@example.com.tw" << endl;
				cout << "Please input new information of user:";
				cin >> name >> phone >> address >> email;
				
				if (phoneBook.Modify(name, phone, address, email))
				{
					cout << "Modified the user successfully!" << endl;

					phoneBook.Display();
					cout << endl;
				}
				else
				{
					cout << "Modified the user failed!" << endl;
				}
			}
			cout << endl;
		}
		else if (choice == 5)
		{
			// DELETE
			string info;
			cout << "Usage of Delete : Name or Phone" << endl;
			cout << "Example:Amy or 0912345678" << endl;
			cout << "Please input user information:";
			cin >> info;

			Person *user = phoneBook.Search(info);
			cout << endl;

			if (user == nullptr)
			{
				cout << "There is no existed user with that name or phone number." << endl;
			}
			else
			{
				char check = 'n';
				cout << "Name\tPhone\t\tAddress\t\tEmail" << endl;
				cout << "---------------------------------------------------------------------" << endl;
				cout << user->name << "\t" << user->phone << "\t"
					<< user->address << "\t\t" << user->email << endl;
				cout << "---------------------------------------------------------------------" << endl << endl;
				cout << "Are you sure to delete this user (y/n) ? ";
				cin >> check;

				if (check == 'Y' || check == 'y')
				{
					if (phoneBook.Delete(info))
					{
						cout << "Deleted the user successfully!" << endl;

						phoneBook.Display();
						cout << endl;
					}
					else
					{
						cout << "Deleted the user failed!" << endl;
					}
				}
			}
			cout << endl;
		}
		else if (choice == 6)
		{
			// IMPORT
			string filePath;
			cout << "Usage of Import : filepath" << endl;
			cout << "Example:./book.txt" << endl;
			cout << "Please input the filepath:";
			cin >> filePath;
			cout << endl;

			if (phoneBook.Import(filePath))
			{
				cout << "Imported the file successfully!" << endl;

				phoneBook.Display();
				cout << endl;
			}
			else
			{
				cout << "Imported the file failed!" << endl;
			}
			cout << endl;
		}
		else if (choice == 7)
		{
			// EXPORT
			string filePath;
			cout << "Usage of Export : filepath" << endl;
			cout << "Example:./book.txt" << endl;
			cout << "Please input the filepath:";
			cin >> filePath;
			cout << endl;

			if (phoneBook.Export(filePath))
			{
				cout << "Exported the file successfully!" << endl;
				cout << endl;
			}
			else
			{
				cout << "Exported the file failed!" << endl;
			}
			cout << endl;
		}
		else if (choice == 8)
		{
			// SORT
			cout << "Usage of Sorting : Column Order" << endl;
			cout << "Example:Name Ascending" << endl;
			cout << "Please input your sorting parameter:";
			
			string column, order;
			cin >> column >> order;
			string columnUpper = convert2Uppercase(column);
			string orderUpper = convert2Uppercase(order);

			//enum title { Name, Phone, Address, Email };
			//enum scending { Ascending, Descending };

			int col;
			int ord;

			if (!columnUpper.compare("NAME")) col = Name;
			else if (!columnUpper.compare("PHONE")) col = Phone;
			else if (!columnUpper.compare("ADDRESS")) col = Address;
			else if (!columnUpper.compare("EMAIL")) col = Email;
			else
			{
				cout << endl;
			}

			if (!orderUpper.compare("ASCENDING")) ord = Ascending;
			else if (!orderUpper.compare("DESCENDING")) ord = Descending;
			else
			{
				cout << endl;
			}

			phoneBook.Sorting();

		}
		else
		{
			cout << "Invalid input!" << endl;
		}
	}
}
