/* Contacts simulation in C++ */

#include <iostream>
#include <map>
#include <regex>
#include <sstream>

class Contacts
{
	public:
		std::map<std::string, int> Data;
		int size;

	Contacts()
	{
		this->size = 0;
	}
	Contacts(std::string name, int number)
	{
		this->Data[name] = number;
	}
	void printContacts();
	int searchContacts(std::string subString);
	void addContacts(std::string name, int number);
	void deleteContacts(std::string name);
	void renameContacts(std::string name);
};

void Contacts::printContacts()
{
	if (this->size == 0)
	{
		std::cout << "No contacts available." << std::endl;
	}
	else
	{
		std::cout << "Contacts:" << std::endl;
		for (const auto &iterator : this->Data) std::cout << iterator.first << ":\t" << iterator.second << std::endl;
	}		
}

int Contacts::searchContacts(std::string subString)
{
	bool Found = false;
	std::regex pattern(subString);
	std::cout << "Found:";
	int i = 1;
	for (const auto &iterator : this->Data)
	{
		if (std::regex_search(iterator.first, pattern))
		{
			Found = true;
			std::putchar('\n');
			std::cout << i++ << ". " << iterator.first << ":\t" << iterator.second;
		}
	}
	if (Found == false)
	{
		std::cout << "None." << std::endl;
		return -1;
	}
	else
	{
		std::cout << std::endl;
		return i;
	}
}

int isValid(std::string name, std::string number)
{
	std::regex Pattern("[0-9.-]");
	if (std::regex_search(name, Pattern))
	{
		std::cout << "Invalid name." << std::endl;
		return -1;
	}
	else
	{
		if (number.length() != 10)
		{
			std::cout << "Invalid number." << std::endl;
			return -1;
		}
		else
		{
			std::regex pattern("[0-9]");
			if (std::regex_search(number, pattern))
			{
				int Number;
				std::stringstream ss(number);
				ss >> Number;
				return Number;
			}
			else
			{
				std::cout << "Invalid number." << std::endl;
				return -1;
			}
		}
	}
}

void Contacts::addContacts(std::string name, int number)
{
	this->Data[name] = number;
	std::cout << name << " was added to contacts." << std::endl;
	this->size++;
}

void Contacts::deleteContacts(std::string name)
{

	int length = 0, sno;
	int no = this->searchContacts(name);
	std::cout << "Enter serial number of the contact to be deleted: ";
	std::cin >> sno;
	std::getchar();
	if (sno > no || sno <= 0)
	{
		std::cout << "Invalid serial number." << std::endl;
	}
	else
	{
		for (const auto &iterator : this->Data)
		{
			length++;
			if (length == sno)	
			{
				this->Data.erase(iterator.first);
				break;
			}
		}
		this->size--;
		std::cout << "Contact deleted." << std::endl;
	}
}

void Contacts::renameContacts(std::string name)
{

	int length = 0, sno;
	int no = this->searchContacts(name);
	std::cout << "Enter serial number of the contact to be renamed: ";	
	std::cin >> sno;
	std::getchar();
	if (sno > no || sno <= 0)
	{
		std::cout << "Invalid serial number." << std::endl;
	}
	else
	{
		std::string Nname;
		int number;
		std::cout << "Enter new name: ";
		std::getline(std::cin, Nname);
		for (auto &iterator : this->Data)
		{
			length++;
			if (length == sno)
			{
				number = iterator.second;
				this->Data.erase(iterator.first);
				break;
			}
		}
		this->Data[Nname] = number;
		std::cout << "Contact renamed from '" << name << "' to '" << Nname << "'." << std::endl;
	}
}

int main(int argc, char *argv[])
{
	Contacts C;
	int choice, Number;
	std::string name, number;
	std::cout << "1-> Add to contacts.\n2-> Rename contact.\n3-> Search contact.\n4-> Delete contact.\n";
	std::cout << "5-> Display contact list.\n6-> Exit\n";
	
	while (1)
	{
		std::cout << ">>> ";
		std::cin >> choice;
		std::getchar();
		switch (choice)
		{
			case 1:
				std::cout << "Enter name: ";
				std::getline(std::cin, name);
				for (char &c : name) c = std::tolower(c);
				std::cout << "Enter number: ";
				std::cin >> number;
				std::getchar();
				Number = isValid(name, number);
				if (Number > 0)
				{
					C.addContacts(name, Number);
				}
				break;
			case 2:
				if (C.size != 0)
				{
					std::cout << "Enter name of contact: ";
					std::getline(std::cin, name);
					for (char &c : name) c = std::tolower(c);
					C.renameContacts(name);	
				}
				else
				{
					std::cout << "No contacts available." << std::endl;
				}
				break;
			case 3:
				if (C.size != 0)
				{
					std::cout << "Enter name of contact: ";
					std::getline(std::cin, name);
					for (char &c : name) c = std::tolower(c);
					C.searchContacts(name);
				}
				else
				{
					std::cout << "No contacts available." << std::endl;
				}
				break;
			case 4:
				if (C.size != 0)
				{
					std::cout << "Enter name of the contact: ";
					std::getline(std::cin, name);
					for (char &c : name) c = std::tolower(c);
					C.deleteContacts(name);
				}
				else
				{
					std::cout << "No contacts available." << std::endl;
				}
				break;
			case 5:
				C.printContacts();	
				break;
			case 6:
				goto exit;
			default:
				std::cout << "Invalid choice." << std::endl;
		}
	}
	exit:
		std::cout << "[+] Program terminated." << std::endl;
		return 0;
}