#include <iostream>
#include <vector>
#include <map>
#include <regex>
#include <exception>
class manager {
	public:
		std::map<std::string, std::vector<std::string>> directories;
		size_t directories_count;
	manager() {
		this->directories_count = 0;
	}
	void adddirectory(const std::string &directoryname);
	void addfile(const std::string &directoryname, const std::string &filename);
	void renamedirectory(const std::string &olddirectoryname, const std::string &newdirectoryname);
	void renamefile(const std::string &directoryname, const std::string &oldfilename, const std::string &newfilename);
	void deletedirectory(const std::string &directoryname);
	void deletefile(const std::string &directoryname);
	void searchdirectory(const std::string &directoryname);
	void searchfile(const std::string &filename);
	void displaytree();
	void help();
};
void manager::adddirectory(const std::string &directoryname) {
	try {
		for (const std::pair<const std::string, const std::vector<std::string>> &directory : this->directories) {
			if (directory.first == directoryname) {
				throw std::runtime_error("DIRECTORY " + directoryname + " ALREADY EXIST.");
			}
		}
		this->directories[directoryname] = {};
		this->directories_count++;
		std::cout << "DIRECTORY " << directoryname << " CREATED." << std::endl;
	} catch (const std::exception &e) {
		std::cout << e.what() << std::endl;
	}
}
void manager::addfile(const std::string &directoryname, const std::string &filename) {
	try {
		for (const std::pair<const std::string, const std::vector<std::string>> directory : this->directories) {
			if (directory.first == directoryname) {
				goto next;
			}
		}
		throw std::runtime_error("DIRECTORY " + directoryname +" DOESN'T EXIST.\nFILE: " + filename + " WASN'T CREATED.");
		next:
			for (const std::string file : this->directories[directoryname]) {
				if (file == filename) {
					throw std::runtime_error("FILE: " + filename + " ALREADY EXIST.");
				}
			}
			this->directories[directoryname].push_back(filename);
			std::cout << "FILE: " << filename << " CREATED IN " << directoryname << "." << std::endl;
	} catch (const std::exception &e) {
		std::cout << e.what() << std::endl;
	}
}
void manager::renamedirectory(const std::string &olddirectoryname, const std::string &newdirectoryname) {
	try {
		for (const std::pair<const std::string, const std::vector<std::string>> directory : this->directories) {
			if (directory.first == olddirectoryname) {
				goto next;
			}
		}
		throw std::runtime_error("DIRECTORY: " + olddirectoryname + " DOES NOT EXIST.");
		next:
			std::vector<std::string> files;
			for (const std::string file : this->directories[olddirectoryname]) {
				files.push_back(file);
			}
			this->directories.erase(olddirectoryname);
			this->directories[newdirectoryname] = files;
			std::cout << "DIRECTORY " << olddirectoryname << " RENAMED TO: " << newdirectoryname << std::endl;
	} catch(const std::exception &e) {
		std::cout << e.what() << std::endl;
	}
}
void manager::renamefile(const std::string &directoryname, const std::string &oldfilename, const std::string &newfilename) {
	try {
		for (const std::pair<const std::string, const std::vector<std::string>> &directory : this->directories) {
			if (directory.first == directoryname) {
				goto next;
			}
		}
		throw std::runtime_error("DIRECTORY: " + directoryname + " DOES NOT EXIST.");
		next:
			bool found = false;
			for (std::string &file : this->directories[directoryname]) {
				if (file == oldfilename) {
					found = true;
					file = newfilename;
					std::cout << "FILE: " << oldfilename << " IN DIRECTORY " << directoryname;
					std::cout << " RENAMED TO: " << newfilename << std::endl; 
				}
			}
			if (found == false) throw std::runtime_error("FILE: " + oldfilename + " NOT FOUND.");
	} catch (const std::exception &e) {
		std::cout << e.what() << std::endl;
	}
}
void manager::deletedirectory(const std::string &directoryname) {
	bool found = false;
	try {
		for (const std::pair<const std::string, const std::vector<std::string>> &directory : this->directories) {
			if (directory.first == directoryname) {
				found = true;
				this->directories.erase(directoryname);
				this->directories_count--;
				std::cout << "DIRECTORY: " << directoryname << " DELETED." << std::endl;
				break;
			}
		}
		if (found == false) throw std::runtime_error("DIRECTORY: " + directoryname + " NOT FOUND.");
	} catch (const std::exception &e) {
		std::cout << e.what() << std::endl;
	}
}
void manager::deletefile(const std::string &directoryname) {
	bool directoryfound = false, filefound = false;
	std::string filename;
	try {
		for (const std::pair<const std::string, const std::vector<std::string>> &directory : this->directories) {
			if (directory.first == directoryname) {
				directoryfound = true;
				if (this->directories[directoryname].size() > 0) {
					std::cout << "[+] AVAILABLE FILES:" << std::endl;
					for (const std::string &file : this->directories[directoryname]) {
						std::cout << "\t-> " << file << std::endl;
					}
					std::cout << "ENTER FILENAME TO BE DELETED: ";
					std::getline(std::cin, filename);
					for (char &c : filename) c = std::tolower(c);
					std::vector<std::string> temp = {};
					for (const std::string &file : this->directories[directoryname]) {
						if (file != filename) {
							temp.push_back(file);
						} else {
							filefound = true;
						}
					}
					this->directories[directoryname] = temp;
					std::cout << "[+] FILE: " << filename << " DELETED." << std::endl;
				} else {
					std::cout << "[+] NO FILE(S) AVAILABLE IN DIRECTORY: " << directoryname << std::endl;
					filefound = true;
				}
			}
		}
		if (filefound == false) throw std::runtime_error("FILE: " + filename + " NOT FOUND.");
		if (directoryfound == false) throw std::runtime_error("DIRECTORY: " + directoryname + " NOT FOUND.");
	} catch (const std::exception &e) {
		std::cout << e.what() << std::endl;
	}
}
void manager::searchdirectory(const std::string &directoryname) {
	bool found = false;
	try {
		std::cout << "SEARCH RESULT(S): " << std::endl;
		std::regex pattern(directoryname);
		for (const std::pair<const std::string, const std::vector<std::string>> &directory : this->directories) {
			if (std::regex_search(directory.first, pattern)) {
				found = true;
				std::cout << "$" <<  directory.first << std::endl;
			}
		}
		if (found == false) std::runtime_error("DIRECTORY: " + directoryname + " NOT FOUND.");
	} catch (const std::exception &e) {
		std::cout << e.what() << std::endl;
	}
}
void manager::searchfile(const std::string &filename) {
	bool found, foundnone = true;
	try {
		std::regex pattern(filename);
		for (const std::pair<const std::string, const std::vector<std::string>> &directory : this->directories) {
			std::cout << "$" << directory.first << std::endl;
			for (const std::string file : directory.second) {
				found = false;
				if (std::regex_search(file, pattern)) {
					found = true;
					foundnone = false;
					std::cout << "\t-> " << file << std::endl;
				}
				if (found == false) std::cout << "\tNONE." << std::endl;
			}
		}
		if (foundnone == true) throw std::runtime_error("FILE: " + filename + " NOT FOUND.");
	} catch (const std::exception &e) {
		std::cout << e.what() << std::endl;
	}
}
void manager::displaytree() {
	if (this->directories_count == 0) {
		std::cout << "NONE." << std::endl;
	} else {
		for (const std::pair<const std::string, const std::vector<std::string>> &directory : this->directories) {
			std::cout << "$" << directory.first << std::endl;
			for (const std::string &file : directory.second) {
				std::cout << "\t-> " << file << std::endl;
			}
		}
	}
}
void manager::help() {
	int choice;
	std::cout << "IN WHICH DO YOU NEED HELP?" << std::endl;
	std::cout << "\t1\t-> CREATE DIRECTORY\n\t2\t-> CREATE FILE\n\t3\t-> RENAME DIRECTORY\n";
	std::cout << "\t4\t-> RENAME FILE\n\t5\t-> DELETE DIRECTORY\n\t6\t-> DELETE FILE\n";
	std::cout << "\t7\t-> SEARCH DIRECTORY\n\t8\t-> SEARCH FILE\n\t9\t-> TREE.\n>>> ";
	std::cin >> choice;
	std::cin.ignore();
	switch (choice) {
		case 1:
			std::cout << "1. ENTER 1 IN THE CONSOLE.\n";
			std::cout << "2. ENTER YOUR DESIRED DIRECTORY NAME AND THE DIRECTORY WILL BE CREATED." << std::endl;
			break;
		case 2:
			std::cout << "1. ENTER 2 IN THE CONSOLE.\n";
			std::cout << "2. ENTER THE DIRECTORY NAME IN WHICH YOU NEED TO ADD A FILE.\n";
			std::cout << "3. ENTER YOUR DESIRED FILENAME AND FILE WILL BE CREATED IN THAT DIRECTORY." << std::endl;
			break;
		case 3:
			std::cout << "1. ENTER 3 IN THE CONSOLE.\n";
			std::cout << "2. ENTER THE NAME OF DIRECTORY TO BE RENAMED.\n";
			std::cout << "3. ENTER NEW NAME FOR THE DIRECTORY AND IT WILL BE RENAMED." << std::endl;
			break;
		case 4:
			std::cout << "1. ENTER 4 IN THE CONSOLE.\n";
			std::cout << "2. ENTER THE DIRECTORY NAME IN WHICH YOU HAVE THE FILE TO BE RENAMED.\n";
			std::cout << "3. ENTER THE FILENAME TO BE RENAMED.\n";
			std::cout << "4. ENTER NEW NAME FOR THAT FILE AND IT WILL BE RENAMED." << std::endl;
			break;
		case 5:
			std::cout << "1. ENTER 5 IN THE CONSOLE.\n";
			std::cout << "2. ENTER THE DIRECTORY NAME TO BE DELETED." << std::endl;
			break;
		case 6:
			std::cout << "1. ENTER 6 IN THE CONSOLE.\n";
			std::cout << "2. ENTER NAME OF DIRECTORY IN WHICH THE FILE EXIST.\n";
			std::cout << "3. ENTER FILENAME TO BE DELETED." << std::endl;
			break;
		case 7:
			std::cout << "1. ENTER 7 IN THE CONSOLE.\n";
			std::cout << "2. ENTER DIRECTORY NAME TO SEARCH AND ALL RELEVENT RESULT(S) WILL BE SHOWN." << std::endl;
			break;
		case 8:
			std::cout << "1. ENTER 8 IN THE CONSOLE.\n";
			std::cout << "2. ENTER FILENAME TO SEARCH AND ALL RELEVENT RESULT(S) FROM ALL DIRECTORIES\
			WILL APPEAR" << std::endl;
			break;
		case 9:
			std::cout << "1. ENTER 9 IN THE CONSOLE.\n";
			std::cout << "2. IT WILL SHOW YOU THE FILE STRUCTURE CREATED." << std::endl;
			break;
		default:
			std::cout << "[+] INVALID CHOICE." << std::endl;
			break;
	}
}
int main(int argc, char *argv[]) {
	manager fm;
	std::string directoryname, filename, olddirectoryname, newdirectoryname, oldfilename, newfilename;
	int choice;
	bool run = true;
	std::cout << "1\t-> CREATE DIRECTORY\n2\t-> CREATE FILE\n3\t-> RENAME DIRECTORY\n4\t-> RENAME FILE\n";
	std::cout << "5\t-> DELETE DIRECTORY\n6\t-> DELETE FILE\n7\t-> SEARCH DIRECTORY\n8\t-> SEARCH FILE\n";
	std::cout << "9\t-> DISPLAY TREE\n10\t-> HELP\n11\t-> EXIT\n";
	while (run) {
		std::cout << ">>> ";
		std::cin >> choice;
		std::cin.ignore();
		switch (choice) {
			case 1:
				std::cout << "ENTER NAME FOR NEW DIRECTORY: ";
				std::getline(std::cin, directoryname);
				for (char &c : directoryname) c = std::tolower(c);
				fm.adddirectory(directoryname);
				break;
			case 2:
				if (fm.directories.size() == 0) {
					std::cout << "[+] NO DIRECTORY AVAILABLE." << std::endl;
					break;
				}
				std::cout << "[+] AVAILABLE DIRECTORIES:" << std::endl;
				for (const std::pair<const std::string, const std::vector<std::string>>&directory:fm.directories){
					std::cout << "\t-> " << directory.first << std::endl;
				}
				std::cout << "ENTER NAME OF DIRECTORY TO BE STORED IN: ";
				std::getline(std::cin, directoryname);
				for (char &c : directoryname) c = std::tolower(c);
				std::cout << "ENTER NAME FOR NEW FILE: ";
				std::getline(std::cin, filename);
				for (char &c : filename) c = std::tolower(c);
				fm.addfile(directoryname, filename);
				break;
			case 3:
				if (fm.directories.size() > 0) {
					std::cout << "[+] AVAILABLE DIRECTORIES:" << std::endl;
					for (const std::pair<const std::string, const std::vector<std::string>>\
					&directory:fm.directories){
						std::cout << "\t-> " << directory.first << std::endl;
					}
					std::cout << "ENTER NAME OF DIRECTORY TO BE RENAMED: ";
					std::getline(std::cin, olddirectoryname);
					for (char &c : olddirectoryname) c = std::tolower(c);
					std::cout << "ENTER NEW NAME: ";
					std::getline(std::cin, newdirectoryname);
					for (char &c : newdirectoryname) c = std::tolower(c);
					fm.renamedirectory(olddirectoryname, newdirectoryname);
				} else {
					std::cout << "[+] NO DIRECTORY AVAILABLE." << std::endl;
				}
				break;
			case 4:
				if (fm.directories.size() > 0) {
					std::cout << "[+] AVAILABLE DIRECTORIES:" << std::endl;
					for (const std::pair<const std::string, const std::vector<std::string>>&directory:\
					fm.directories){
						std::cout << "\t-> " << directory.first << std::endl;
					}
					std::cout << "ENTER NAME OF THE DIRECTORY IN WHICH TO MODIFY FILE: ";
					std::getline(std::cin, directoryname);
					for (char &c : directoryname) c = std::tolower(c);
					try {
						for (const std::pair<std::string,std::vector<std::string>>dir:fm.directories) {
							if (directoryname == dir.first) {
								goto next;
							}
						}
						throw std::runtime_error("DIRECTORY" + directoryname + " NOT FOUND.");
						next:
							if (fm.directories[directoryname].size() > 0) {
								std::cout << "[+] AVAILABLE FILE(S):" << std::endl;
								for (const std::string file : fm.directories[directoryname]) {
									std::cout << "\t-> " << file << std::endl;
								}
								std::cout << "ENTER FILENAME TO BE RENAMED: ";
								std::getline(std::cin, oldfilename);
								for (char &c : oldfilename) c = std::tolower(c);
								std::cout << "ENTER NEW FILENAME: ";
								std::getline(std::cin, newfilename);
								for (char &c : newfilename) c = std::tolower(c);
								fm.renamefile(directoryname, oldfilename, newfilename);
								} else {
									std::cout << "[+] NO FILE(S) AVAILABLE IN DIRECTORY: "\
									<< directoryname << std::endl;
								}
					} catch (const std::exception &e) {
						std::cout << e.what() << std::endl;
					}
				} else {
					std::cout << "[+] NO DIRECTORY AVAILABLE." << std::endl;
				}
				break;
			case 5:
				if (fm.directories.size() > 0) {
					std::cout << "[+] AVAILABLE DIRECTORIES:" << std::endl;
					for (const std::pair<const std::string,const std::vector<std::string>>&directory:\
					fm.directories) {
						std::cout << "\t-> " << directory.first << std::endl;
					}
					std::cout << "ENTER NAME OF DIRECTORY TO BE DELETED: ";
					std::getline(std::cin, directoryname);
					fm.deletedirectory(directoryname);
				} else {
					std::cout << "[+] NO DIRECTORY AVAILABLE." << std::endl;
				}
				break;
			case 6:
				if (fm.directories.size() > 0) {
					std::cout << "[+] AVAILABLE DIRECTORIES:" << std::endl;
					for (const std::pair<const std::string, const std::vector<std::string>>&directory:\
					fm.directories){
						std::cout << "\t-> " << directory.first << std::endl;
					}
					std::cout << "ENTER NAME OF DIRECTORY IN WHICH FILE EXISTS: ";
					std::getline(std::cin, directoryname);
					for (char &c : directoryname) std::tolower(c);
					fm.deletefile(directoryname);
				} else {
					std::cout << "[+] NO DIRECTORY AVAILABLE." << std::endl;
				}
				break;
			case 7:
				if (fm.directories.size() > 0) {
					std::cout << "ENTER DIRECTORY NAME TO SEARCH: ";
					std::getline(std::cin, directoryname);
					for (char &c : directoryname) c = std::tolower(c);
					fm.searchdirectory(directoryname);
					break;
				} else {
					std::cout << "[+] NO DIRECTORY AVAILABLE." << std::endl;
				}
				break;
			case 8:
				if (fm.directories.size() > 0) {
					std::cout << "ENTER FILENAME TO SEARCH: ";
					std::getline(std::cin, filename);
					for (char &c : filename) c = std::tolower(c);
					fm.searchfile(filename);
					break;
				} else {
					std::cout << "[+] NO DIRECTORY AVAILABLE." << std::endl;
				}
				break;
			case 9:
				if (fm.directories.size() > 0) {
					std::cout << "TREE:" << std::endl;
					fm.displaytree();
				} else {
					std::cout << "[+] NO DIRECTORY AVAILABLE." << std::endl;
				}
				break;
			case 10:
				fm.help();
				break;
			case 11:
				std::cout << "[+] PROGRAM TERMINATED." << std::endl;
				run = false;
				break;
			default:
				std::cout << "[+] INVALID INPUT." << std::endl;
				break;
		}
	}
	return 0;
}
