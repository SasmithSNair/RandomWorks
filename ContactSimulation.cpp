#include <iostream>
#include <map>
#include <regex>
#include <sstream>

class Contacts
{
	public:
		std::map<std::string, std::string> Data;
		int size;
	Contacts()
	{
		this->size = 0;
	}
	void printContacts();
	int searchContacts(std::string subString);
	void addContacts(std::string name, std::string number);
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
		return i - 1;
	}
}

bool isValid(std::string name, std::string number)
{
	std::regex invalid("[^a-zA-Z ]");
	std::regex valid_number("^[0-9]{10}$");
	if (std::regex_search(name, invalid))
	{
		std::cout << "Invalid name." << std::endl;
		return false;
	}
	if (!std::regex_match(number, valid_number))
	{
		std::cout << "Invalid number." << std::endl;
		return false;
	}
	return true;
}

void Contacts::addContacts(std::string name, std::string number)
{
	this->Data[name] = number;
	std::cout << name << " was added to contacts." << std::endl;
	this->size++;
}

void Contacts::deleteContacts(std::string name)
{
	int sno;
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
		int length = 1;
		for (auto iterator = this->Data.begin(); iterator != this->Data.end(); ++iterator)
		{
			if (length == sno)
			{
				this->Data.erase(iterator);
				break;
			}
			length++;
		}
		this->size--;
		std::cout << "Contact deleted." << std::endl;
	}
}

void Contacts::renameContacts(std::string name)
{
	int sno;
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
		std::string Nname, original;
		std::string number;
		int length = 1;
		std::cout << "Enter new name: ";
		std::getline(std::cin, Nname);
		for (char &c : Nname) c = std::tolower(c);
		for (auto iterator = this->Data.begin(); iterator != this->Data.end(); ++iterator)
		{
			if (length == sno)
			{
				number = iterator->second;
				original = iterator->first;
				this->Data.erase(iterator);
				break;
			}
			length++;
		}
		this->Data[Nname] = number;
		std::cout << "Contact renamed from '" << original << "' to '" << Nname << "'." << std::endl;
	}
}

int main(int argc, char *argv[])
{
	Contacts C;
	int choice;
	std::string name, number;
	std::cout << "1-> Add to contacts.\n2-> Rename contact.\n3-> Search contact.\n4-> Delete contact.\n";
	std::cout << "5-> Display contact list.\n6-> Exit.\n";
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
				std::getline(std::cin, number);
				if (isValid(name, number)) C.addContacts(name, number);
				break;
			case 2:
				if (C.size != 0)
				{
					std::cout << "Enter name of contact: ";
					std::getline(std::cin, name);
					for (char &c : name) c = std::tolower(c);
					C.renameContacts(name);
				}
				else std::cout << "No contacts available." << std::endl;
				break;
			case 3:
				if (C.size != 0)
				{
					std::cout << "Enter name of contact: ";
					std::getline(std::cin, name);
					for (char &c : name) c = std::tolower(c);
					C.searchContacts(name);
				}
				else std::cout << "No contacts available." << std::endl;
				break;
			case 4:
				if (C.size != 0)
				{
					std::cout << "Enter name of the contact: ";
					std::getline(std::cin, name);
					for (char &c : name) c = std::tolower(c);
					C.deleteContacts(name);
				}
				else std::cout << "No contacts available." << std::endl;
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

