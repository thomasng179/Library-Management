#include "Library.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

Book::Book() {};
Person::Person() {};
ChildrenBook::ChildrenBook() {};
ComputerBook::ComputerBook() {};
Novel::Novel() {};

Person::Person(int id, string name, int count) {
	this->id = id;
	this->name = name;
	this->count = count;
}

Student::Student(int id, string name, int count, int code1, int code2) : Person(id, name, count) {
	code[0] = code1;
	code[1] = code2;
}

Teacher::Teacher(int id, string name, int count, int code1, int code2, int code3) : Person(id, name, count) {
	code[0] = code1;
	code[1] = code2;
	code[2] = code3;
}


Book::Book(int code, string title, int available, int rented) {
	this->code = code;
	this->title = title;
	this->available = available;
	this->rented = rented;
}

ChildrenBook::ChildrenBook(Book* book, int age) : Book(book->getCode(), book->getTitle(), book->getAvailable(), book->getRented()) {
	this->age = age;
}

int Book::getCode() {
	return code;
}

string Book::getTitle() {
	return title;
}

int Book::getAvailable() {
	return available;
}

int Book::getRented() {
	return rented;
}

int Book::getAge() {
	return 0;
}

int Book::getPublishDate() {
	return 0;
}

string Book::getPublisher() {
	return 0;
}

int ChildrenBook::getAge() {
	return age;
}

int Novel::getPublishDate() {
	return publishDate;
}

void Person::setCode(int num) {
	num = num;
}

string ComputerBook::getPublisher() {
	return publisher;
}

ChildrenBook::ChildrenBook(int code, string title, int available, int rented, int age) : Book(code, title, available, rented) {
	this->age = age;
}

ComputerBook::ComputerBook(int code, string title, int available, int rented, string publisher) : Book(code, title, available, rented) {
	this->publisher = publisher;
}

Novel::Novel(int code, string title, int available, int rented, int publishDate) : Book(code, title, available, rented) {
	this->publishDate = publishDate;
}

void Book::subRented() {
    rented--;;
}

void Book::addRented() {
    rented++;
}

void Book::addAvailable() {
    available++;
}

void Book::subAvailable() {
    available--;
}

BookNode* Book::getLibrary(int i) {
	return library[i];
}

string Person::getName() {
	return name;
}

int Person::getId() {
	return id;
}

Teacher::Teacher() {};

void Teacher::setCode(int num) {
    for (int i = 0; i < 3; i++) {
        if (code[i] == 0) {
            code[i] = num;
            break;
        }
    }
}

Student::Student() {};

int Person::getCount() {
	return count;
}

void Person::addCount() {
	count++;
}

void Person::subCount() {
	count--;
}

void Student::setCode(int num) {
    for (int i = 0; i < 2; i++) {
        if (code[i] == 0) {
            code[i] = num;
            break;
        }
    }
}

void Student::returnCode(int num) {
    for (int i = 0; i < 2; i++) {
        if (code[i] == num) {
            code[i] = 0;
        }
    }
}

void Teacher::returnCode(int num) {
    for (int i = 0; i < 3; i++) {
        if (code[i] == num) {
            code[i] = 0;
        }
    }
}

void Person::returnCode(int num) {
    num = num;
}

int Person::getCode(int i) {
	return 0;
}

int Teacher::getCode(int i) {
	return code[i];
}

int Student::getCode(int i) {
	return code[i];
}

//creates the student and teacher linked list
void Person::createClass() {
	ifstream inFile;
	inFile.open("person.txt");

	PersonNode* classPeople[2] = { NULL, NULL };
	PersonNode* ptr = NULL;
	PersonNode* temp = NULL;

	//reads file to create the list
	while (!inFile.eof()) {
		int tempID, tempCode1 = 0, tempCode2 = 0, tempCode3 = 0, tempRented;
		string tempName;
		inFile >> tempID >> tempName >> tempRented;
		if (tempRented == 1) {
			inFile >> tempCode1;
		}
		else if (tempRented == 2) {
			inFile >> tempCode1 >> tempCode2;
		}
		else if (tempRented == 3) {
			inFile >> tempCode1 >> tempCode2 >> tempCode3;
		}

		//creates the teacher linked list
		if (tempID > 1 && tempID <= 100) {
			Person* person = new Teacher(tempID, tempName, tempRented, tempCode1, tempCode2, tempCode3);
			ptr = new PersonNode;
			ptr->person = person;
			ptr->link = NULL;

			if (classPeople[0] == NULL) {
				classPeople[0] = ptr;
				temp = classPeople[0];
			}
			else if (classPeople[0]->person->id > ptr->person->id) {
				ptr->link = classPeople[0];
				classPeople[0] = ptr;
			}
			else {
				temp = classPeople[0];
				while ((temp->link != NULL) && (temp->link->person->id < ptr->person->id)) {
					temp = temp->link;
				}
				ptr->link = temp->link;
				temp->link = ptr;
			}
		}
		
		//creates the student linked list
		else if (tempID > 100 && tempID <= 300) {
			Person* person = new Student(tempID, tempName, tempRented, tempCode1, tempCode2);
			for (int i = 0; i < 3; i++) {

			}
			ptr = new PersonNode;
			ptr->person = person;
			ptr->link = NULL;

			if (classPeople[1] == NULL) {
				classPeople[1] = ptr;
				temp = classPeople[1];
			}
			else if (classPeople[1]->person->id > ptr->person->id) {
				ptr->link = classPeople[1];
				classPeople[1] = ptr;
			}
			else {
				temp = classPeople[1];
				while ((temp->link != NULL) && (temp->link->person->id < ptr->person->id)) {
					temp = temp->link;
				}
				ptr->link = temp->link;
				temp->link = ptr;
			}
		}
	}

	inFile.close();
	this->person[0] = classPeople[0];
	this->person[1] = classPeople[1];
}

//creates the 3 linked list for the books
void Book::createLibrary() {
	ifstream inFile;
	inFile.open("book.txt");

	BookNode* library[3] = { NULL, NULL, NULL };
	BookNode* ptr = NULL;
	BookNode* temp = NULL;

	//reads file to create list
	while (!inFile.eof()) {
		int tempCode, tempAvail, tempRented, tempAge, tempPublishDate;
		string tempTitle, tempPublisher;
		inFile >> tempCode;

		//creates the children book linked list
		if (tempCode > 1000 && tempCode <= 2000) {
			inFile >> tempTitle >> tempAge >> tempAvail >> tempRented;

			Book* book = new ChildrenBook(tempCode, tempTitle, tempAvail, tempRented, tempAge);
			ptr = new BookNode;
			ptr->book = book;
			ptr->link = NULL;

			if (library[0] == NULL) {
				library[0] = ptr;
				temp = library[0];
			} else if (library[0]->book->code > ptr->book->code) {
				ptr->link = library[0];
				library[0] = ptr;
			} else {
				temp = library[0];
				while ((temp->link != NULL) && (temp->link->book->code < ptr->book->code)) {
					temp = temp->link;
				}
				ptr->link = temp->link;
				temp->link = ptr;
			}
		//creates the computer book linked list
		} else if (tempCode > 2000 && tempCode <= 3000) {
			inFile >> tempTitle >> tempPublisher >> tempAvail >> tempRented;

			Book* book = new ComputerBook(tempCode, tempTitle, tempAvail, tempRented, tempPublisher);
			ptr = new BookNode;
			ptr->book = book;
			ptr->link = NULL;

			if (library[1] == NULL) {
				library[1] = ptr;
				temp = library[0];
			}
			else if (library[1]->book->code > ptr->book->code) {
				ptr->link = library[1];
				library[1] = ptr;
			}
			else {
				temp = library[1];
				while ((temp->link != NULL) && (temp->link->book->code < ptr->book->code)) {
					temp = temp->link;
				}
				ptr->link = temp->link;
				temp->link = ptr;
			}
		//creates the novel linked list
		} else if (tempCode > 3000 && tempCode <= 4000) {
			inFile >> tempTitle >> tempPublishDate >> tempAvail >> tempRented;

			Book* book = new Novel(tempCode, tempTitle, tempAvail, tempRented, tempPublishDate);
			ptr = new BookNode;
			ptr->book = book;
			ptr->link = NULL;

			if (library[2] == NULL) {
				library[2] = ptr;
				temp = library[2];
			}
			else if (library[2]->book->code > ptr->book->code) {
				ptr->link = library[2];
				library[2] = ptr;
			}
			else {
				temp = library[2];
				while ((temp->link != NULL) && (temp->link->book->code < ptr->book->code)) {
					temp = temp->link;
				}
				ptr->link = temp->link;
				temp->link = ptr;
			}
		}
	}

	inFile.close();
	this->library[0] = library[0];
	this->library[1] = library[1];
	this->library[2] = library[2];
}

void Book::tryCatchsearchBook(int i, int codeSearch, string titleSearch, string& foundTitle, int& foundCode) {
	for (BookNode* ptr = library[i]; ptr != NULL; ptr = ptr->link) {
		if (ptr->book->title == titleSearch) {
			foundTitle = "yes";
		}
		if (ptr->book->code == codeSearch) {
			foundCode = 1;
		}
	}
}

void Book::searchInputBook(int codeSearch) {
	if (codeSearch > 1000 && codeSearch <= 2000) {
		for (BookNode* ptr = library[0]; ptr != NULL; ptr = ptr->link) {
			if (ptr->book->code == codeSearch) {
				cout << ptr->book->title << "(" << ptr->book->code << ") exists\n";
				cout << "Category : Children Book\n";
				cout << "Age : " << ptr->book->getAge() << '\n';
				cout << ptr->book->available << " available, " << ptr->book->rented << " rented\n";
			}
		}
	}

	//searches the computer book linked list for the input book
	else if (codeSearch > 2000 && codeSearch <= 3000) {
		for (BookNode* ptr = library[1]; ptr != NULL; ptr = ptr->link) {
			if (ptr->book->getCode() == codeSearch) {
				cout << ptr->book->getTitle() << "(" << ptr->book->getCode() << ") exists\n";
				cout << "Category : Computer Book\n";
				cout << "Publisher : " << ptr->book->getPublisher() << '\n';
				cout << ptr->book->getAvailable() << " available, " << ptr->book->getRented() << " rented\n";
			}
		}
	}

	//searches the novel book linked list for the input book
	else if (codeSearch > 3000 && codeSearch <= 4000) {
		for (BookNode* ptr = library[2]; ptr != NULL; ptr = ptr->link) {
			if (ptr->book->code == codeSearch) {
				cout << ptr->book->title << "(" << ptr->book->code << ") exists\n";
				cout << "Category : Novel\n";
				cout << "Published Date : " << ptr->book->getPublishDate() << '\n';
				cout << ptr->book->available << " available, " << ptr->book->rented << " rented\n";
			}
		}
	}
}

void Book::searchBook() {
	string titleSearch, foundTitle = "no";
	int codeSearch, foundCode = 0;
	bool both = false;
	cout << "Enter code : \n";
	cin >> codeSearch;
	cout << "Enter title : \n";
	cin >> titleSearch;

	//searches the library linked list to see if the title and code are in the list
	for (int i = 0; i < 3; i++) {
		tryCatchsearchBook(i, codeSearch, titleSearch, foundTitle, foundCode);
	}

	if ((foundCode == 0) && (foundTitle == "no"))
		both = true;

	//checks to see if the title and code are found, if not throws the exception
	try {
		if (both == true)
			throw both;
		if (foundCode == 0)
			throw foundCode;
		if (foundTitle == "no")
			throw foundTitle;
	}
	catch (bool both) {
		cout << "No match (code and title do not match.)\n";
		return;
	}
	catch (int foundCode) {
		cout << "No such code.\n";
		return;
	}
	catch (string foundTitle) {
		cout << "No such title.\n";
		return;
	}

	//searches the children book linked list for the input book
	searchInputBook(codeSearch);
}

void Book::searchAvailability(int i, string inputBook, string& foundTitle, int& noMore, int& targetCode) {
	for (BookNode* ptr = library[i]; ptr != NULL; ptr = ptr->link) {
		if (ptr->book->getTitle() == inputBook) {
			foundTitle = "yes";
			targetCode = ptr->book->getCode();
			if (ptr->book->getAvailable() == 0) {
				noMore = 0;
			}
		}
	}
}

void Person::rentBookSearch(int inputID, string inputBook, int& noMore, int targetCode, Book& library) {
	string role;
	char inputAnswer;
	int maxBook, i;
	if (inputID > 1 && inputID<= 100) {
		role = "teacher";
		i = 0;
		maxBook = 3;
	}
	else if (inputID > 100 && inputID <= 300) {
		role = "student";
		i = 1;
		maxBook = 2;
	}
	for (PersonNode* ptr = person[i]; ptr != NULL; ptr = ptr->link) {
		if (inputID == ptr->person->id) {
			cout << "You are " << ptr->person->name << ". You rented " << ptr->person->count << " book.\n";
			cout << "Do you want to rent '" << inputBook << "'" << " (y/n)? ";
			cin >> inputAnswer;
			//checks if the teacher rented more than 3 books and if the book is still available. if not throws exception
			try {
				if (role == "teacher" && ptr->person->count == 3)
					throw role;

				if (role == "student" && ptr->person->count == 2)
					throw role;

				if (noMore == 0) {
					throw noMore;
				}

				//updates the children book linked list for the number available and amount rented
				if (inputAnswer == 'y') {
					if (targetCode > 1000 && targetCode <= 2000) {
						for (BookNode* ptr = library.getLibrary(0); ptr != NULL; ptr = ptr->link) {
							if (ptr->book->getCode() == targetCode) {
								ptr->book->addRented();
								ptr->book->subAvailable();
							}
						}
						//updates the teacher linked list for what books are rented
						for (int i = 0; i < 3; i++) {
							if (ptr->person->getCode(i) != 0) {
								ptr->person->setCode(targetCode);
								break;
							}
						}
						//updates the teacher linked list to update the amount of books rented
						ptr->person->addCount();
						cout << "***** Rent Succeed. Check your info!\n";
						return;
					}
					//updates the computer book linked list for the number available and amount rented
					else if (targetCode > 2000 && targetCode <= 3000) {
						for (BookNode* ptr = library.getLibrary(1); ptr != NULL; ptr = ptr->link) {
							if (ptr->book->getCode() == targetCode) {
								ptr->book->addRented();
								ptr->book->subAvailable();
							}
						}
						//updates the teacher linked list for what books are rented
						for (int i = 0; i < 3; i++) {
							if (ptr->person->getCode(i) != 0) {
								ptr->person->setCode(targetCode);
								break;
							}
						}
						//updates the teacher linked list for amount of books rented
						ptr->person->addCount();
						cout << "***** Rent Succeed. Check your info!\n";
						return;
					}
					//updates the novel book linked list for the number available and amount rented
					else if (targetCode > 3000 && targetCode <= 4000) {
						for (BookNode* ptr = library.getLibrary(2); ptr != NULL; ptr = ptr->link) {
							if (ptr->book->getCode() == targetCode) {
								ptr->book->addRented();
								ptr->book->subAvailable();
							}
						}
						//update the teacher linked list for what books are rented
						for (int i = 0; i < 3; i++) {
							if (ptr->person->getCode(i) != 0) {
								ptr->person->setCode(targetCode);
								break;
							}
						}
						//updates the teacher linked list for amount of books rented
						ptr->person->addCount();
						cout << "***** Rent Succeed. Check your info!\n";
						return;
					}
				}
			}
			catch (string teacher) {
				cout << "You already rented " << maxBook << " books.\n";
				return;
			}
			catch (int noMore) {
				cout << "The book is not available since it's all rented out.\n";
				return;
			}
		}
	}
}

void Person::rentBook(Book& library) {
	int inputID, targetCode{}, noMore = 1;
	string foundTitle = "none";
	int foundID = 0;
	bool both = false;
	string inputBook, teacher, student;
	char inputAnswer;
	cout << "Enter your ID" << setw(15) << ": ";
	cin >> inputID;
	cout << "Enter book title : ";
	cin >> inputBook;

	//searches the library linked list to see if the book title exists and if it's still available
	for (int i = 0; i < 3; i++) {
		library.searchAvailability(i, inputBook, foundTitle, noMore, targetCode);
	}

	//searches the teacher linked list to see if the ID exists
	for (PersonNode* ptr = person[0]; ptr != NULL; ptr = ptr->link) {
		if (ptr->person->getId() == inputID) {
			foundID = 1;
		}
	}

	//searches the student linked list to see if the ID exists
	for (PersonNode* ptr = person[1]; ptr != NULL; ptr = ptr->link) {
		if (ptr->person->getId() == inputID) {
			foundID = 1;
		}
	}

	if ((foundTitle == "none") && (foundID == 0)) {
		both = true;
	}

	//checks to see if the title and ID are found, if not throw exception
	try {
		if (both == true)
			throw both;

		if (foundTitle == "none")
			throw foundTitle;

		if (foundID == 0)
			throw foundID;

	} catch (bool both) {
		cout << "No such ID or title.\n";
		return;
	}
	catch (string foundTitle) {
		cout << "No such title.\n";
		return;
	}
	catch (int foundID) {
		cout << "No such ID.\n";
		return;
	}

	//searches the teacher linked list to see how many books the teacher rented and what the name is
	rentBookSearch(inputID, inputBook, noMore, targetCode, library);
}

void Person::rentBookExist(int i, int& foundID, int inputBook, int& bookCode, int inputID) {
	for (PersonNode* ptr = person[i]; ptr != NULL; ptr = ptr->link) {
		if (ptr->person->getId() == inputID) {
			foundID = 1;
		}
		for (int j = 0; j < 3; j++) {
			if (ptr->person->getCode(j) == inputBook) {
				bookCode = inputBook;
			}
		}
	}
}

void Person::rentBookLibrarySearch(int i, Book& library, int inputBook, string& foundCode, int bookCode, string& bookTitle) {
	for (BookNode* ptr = library.getLibrary(i); ptr != NULL; ptr = ptr->link) {
		if (ptr->book->getCode() == inputBook) {
			foundCode = "yes";
		}
		if (bookCode == ptr->book->getCode()) {
			bookTitle = ptr->book->getTitle();
		}
	}
}

void Person::rentBookUpdatePerson(int i, Book& library, int inputID, string bookTitle, int bookCode, int inputBook) {
	char inputAnswer;
	int notFound = 0;

	for (PersonNode* ptr = person[i]; ptr != NULL; ptr = ptr->link) {
		if (inputID == ptr->person->id) {
			cout << "Do you want to return '" << bookTitle << "'" << " (y/n)? ";
			cin >> inputAnswer;
			//checks to see if the teacher rented the book, if not then throw exception
			try {
				for (int j = 0; j < 3; j++) {
					if (ptr->person->getCode(j) == bookCode) {
						bookCode = bookCode;
						notFound = 1;
					}
					else if (j == 2 && notFound == 0) {
						bookCode = 0;
					}
				}

				if (bookCode == 0)
					throw bookCode;

				//updates the children book linked list for amount rented and available
				if (inputAnswer == 'y') {
					if (bookCode > 1000 && bookCode <= 2000) {
						for (BookNode* ptr = library.getLibrary(0); ptr != NULL; ptr = ptr->link) {
							if (ptr->book->getCode() == bookCode) {
								ptr->book->subRented();
								ptr->book->addAvailable();
							}
						}
						//updates the teacher linked list for what books are rented
						for (int i = 0; i < 3; i++) {
							if (ptr->person->getCode(i) == bookCode) {
								ptr->person->returnCode(inputBook);
							}
						}
						//updates the teacher linked list for amount of books rented
						ptr->person->subCount();
						cout << "***** Return Succeed. Check your info!\n";
					}
					//update the computer book linked list for amount rented and available
					else if (bookCode > 2000 && bookCode <= 3000) {
						for (BookNode* ptr = library.getLibrary(1); ptr != NULL; ptr = ptr->link) {
							if (ptr->book->getCode() == bookCode) {
								ptr->book->subRented();
								ptr->book->addAvailable();
							}
						}
						//updates the teacher linked list for what books are rented
						for (int i = 0; i < 3; i++) {
							if (ptr->person->getCode(i) == bookCode) {
								ptr->person->returnCode(inputBook);
							}
						}
						//updates the teacher linked list for amount of books rented
						ptr->person->subCount();
						cout << "***** Return Succeed. Check your info!\n";
					}
					//update the novel book linked list for amount rented and available
					else if (bookCode > 3000 && bookCode <= 4000) {
						for (BookNode* ptr = library.getLibrary(2); ptr != NULL; ptr = ptr->link) {
							if (ptr->book->getCode() == bookCode) {
								ptr->book->subRented();
								ptr->book->addAvailable();
							}
						}
						//update the teacher linked list for what books are rented
						for (int i = 0; i < 3; i++) {
							if (ptr->person->getCode(i) == bookCode) {
								ptr->person->returnCode(inputBook);
							}
						}
						//update the teacher linked list for amount of books rented
						ptr->person->subCount();
						cout << "***** Return Succeed. Check your info!\n";
					}
				}
			}
			catch (int bookCode) {
				cout << "You did not rent the book.\n";
				return;
			}
		}
	}
}

void Person::returnBook(Book& library) {
	int inputID, inputBook, bookCode = 0, j = 0;
	string foundCode = "none", bookTitle;
	int foundID = 0;
	bool both = false;
	string teacher, student;
	char inputAnswer;
	cout << "Enter your ID" << setw(15) << ": ";
	cin >> inputID;
	cout << "Enter the book code to return : ";
	cin >> inputBook;

	//searches the person linked list to see if the book id and book code exists
	for (int i = 0; i < 2; i++) {
		rentBookExist(i, foundID, inputBook, bookCode, inputID);
	}

	//searches the children book linked list to see if the code exists in the library
	for (int i = 0; i < 3; i++) {
		rentBookLibrarySearch(i, library, inputBook, foundCode, bookCode, bookTitle);
	}

	if ((foundCode == "none") && (foundID == 0)) {
		both = true;
	}

	//checks to see if the book code and book id exists, if not throw exception
	try {
		if (both == true)
			throw both;

		if (foundCode == "none")
			throw foundCode;

		if (foundID == 0)
			throw foundID;

	}
	catch (bool both) {
		cout << "No such ID or code.\n";
		return;
	}
	catch (string foundCode) {
		cout << "No such code.\n";
		return;
	}
	catch (int foundID) {
		cout << "No such ID.\n";
		return;
	}

	//checks to see if it is a teacher
	if (inputID > 1 && inputID <= 100) {
		//searches the teacher linked list for the certain teacher
		j = 0;
	}
	else if (inputID > 100 && inputID <= 300) {
		j = 1;
	}
	rentBookUpdatePerson(j, library, inputID, bookTitle, bookCode, inputBook);
}

//shows all 3 linked list for all the books
void Book::showLibrary() {
	cout << "-----------------------------------------------------------------------------------------\n" << setw(40) << "Children Books\n" << "-----------------------------------------------------------------------------------------\n";
	cout << "Code" << setw(30) << "Title" << setw(25) << "Age" << setw(15) << "Available" << setw(15) << "Rented\n";
	cout << "-----------------------------------------------------------------------------------------\n";
	for (BookNode* ptr = library[0]; ptr != NULL; ptr = ptr->link) {
		string tempTitle = ptr->book->title;
		for (int i = 0; i < tempTitle.length(); i++) {
			if (tempTitle[i] == '-' || tempTitle[i] == '_')
				tempTitle[i] = ' ';
		}
		cout << ptr->book->code << setw(35) << tempTitle << setw(20) << ptr->book->getAge() << setw(10) << ptr->book->available << setw(17) << ptr->book->rented << '\n';
	}

	cout << "-----------------------------------------------------------------------------------------\n" << setw(40) << "Computer Books\n" << "-----------------------------------------------------------------------------------------\n";
	cout << "Code" << setw(30) << "Title" << setw(25) << "Publisher" << setw(15) << "Available" << setw(15) << "Rented\n";
	cout << "-----------------------------------------------------------------------------------------\n";
	for (BookNode* ptr = library[1]; ptr != NULL; ptr = ptr->link) {
		string tempPublisher = ptr->book->getPublisher();
		for (int i = 0; i < tempPublisher.length(); i++) {
			if (tempPublisher[i] == '-' || tempPublisher[i] == '_')
				tempPublisher[i] = ' ';
		}
		string tempTitle1 = ptr->book->title;
		for (int i = 0; i < tempTitle1.length(); i++) {
			if (tempTitle1[i] == '-' || tempTitle1[i] == '_')
				tempTitle1[i] = ' ';
		}
		cout << ptr->book->code << setw(35) << tempTitle1 << setw(20) << tempPublisher << setw(10) << ptr->book->available << setw(17) << ptr->book->rented << '\n';
	}

	cout << "-----------------------------------------------------------------------------------------\n" << setw(40) << "Novel Books\n" << "-----------------------------------------------------------------------------------------\n";
	cout << "Code" << setw(30) << "Title" << setw(25) << "Published Date" << setw(15) << "Available" << setw(15) << "Rented\n";
	cout << "-----------------------------------------------------------------------------------------\n";
	for (BookNode* ptr = library[2]; ptr != NULL; ptr = ptr->link) {
		string tempTitle2 = ptr->book->title;
		for (int i = 0; i < tempTitle2.length(); i++) {
			if (tempTitle2[i] == '-' || tempTitle2[i] == '_')
				tempTitle2[i] = ' ';
		}
		cout << ptr->book->code << setw(35) << tempTitle2<< setw(20) << ptr->book->getPublishDate() << setw(10) << ptr->book->available << setw(17) << ptr->book->rented << '\n';
	}
}


void Person::showInformationSearchPerson(int j, int inputID, Book& library) {
	int iter = 0;
	//searches the teacher linked list for the information
	for (PersonNode* ptr = person[j]; ptr != NULL; ptr = ptr->link) {
		if (ptr->person->getId() == inputID) {
			cout << "You rented " << ptr->person->getCount() << " books.\n";
			//loops through the private member of the teacher to go through all the books they rented
			for (int i = 0; i < 3; i++) {
				if (ptr->person->getCode(i) != 0) {
					//checks to see if it is a children book to know if we go through the children book linked list
					if (ptr->person->getCode(i) > 1000 && ptr->person->getCode(i) <= 2000) {
						iter = 0;
						//checks to see if it is a computer book to know if we go through the computer book linked list
					}
					else if (ptr->person->getCode(i) > 2000 && ptr->person->getCode(i) <= 3000) {
						iter = 1;
						//checks to see if it is a novel book to know if we go through the novel book linked list
					}
					else if (ptr->person->getCode(i) > 3000 && ptr->person->getCode(i) <= 4000) {
						iter = 2;
					}
					//searches through the 3 library linked list for the child class information of the book
					for (BookNode* ptr1 = library.getLibrary(iter); ptr1 != NULL; ptr1 = ptr1->link) {
						if (ptr1->book->getCode() == ptr->person->getCode(i)) {
							cout << "* " << ptr1->book->getTitle() << "(" << ptr1->book->getCode() << ") - ";
							if (ptr1->book->getCode() > 1000 && ptr1->book->getCode() <= 2000) {
								cout << "Age - " << ptr1->book->getAge() << '\n';
							}
							else if (ptr1->book->getCode() > 2000 && ptr1->book->getCode() <= 3000) {
								cout << "Publisher - " << ptr1->book->getPublisher() << '\n';
							}
							else if (ptr1->book->getCode() > 3000 && ptr1->book->getCode() <= 4000) {
								cout << "Published Date - " << ptr1->book->getPublishDate() << '\n';
							}
						}
					}
				}
			}
		}
	}
}
//shows the searched person's information
void Person::showInformation(Book& library) {
    int inputID, iter = 0, idExists = 0, j;
    string inputName, both = "no";
    bool nameExists = false;
    cout << "Enter your ID : ";
    cin >> inputID;
    cout << "Enter your name : ";
    cin >> inputName;
    
	//checks to see if the id and name exists in the teacher linked list
    for (PersonNode* ptr = person[0]; ptr != NULL; ptr = ptr->link) {
        if (ptr->person->getId() == inputID) {
            idExists = 1;
        }
        if (ptr->person->getName() == inputName) {
            nameExists = true;
        }
    }
    
	//checks to see if the id and name exists in the student linked list
    for (PersonNode* ptr = person[1]; ptr != NULL; ptr = ptr->link) {
        if (ptr->person->getId() == inputID) {
            idExists = 1;
        }
        if (ptr->person->getName() == inputName) {
            nameExists = true;
        }
    }
    
    if (nameExists == false && idExists == 0)
        both = "yes";
    
	//if name and id doesn't exist, throw exception
    try {
        if (both == "yes")
            throw both;
        if (idExists == 0)
            throw idExists;
        if (nameExists == false)
            throw nameExists;
    } catch (string both) {
        cout << "No match (ID and name  do not match.)\n";
		return;
    }
    catch (int idExists) {
        cout << "No such id or name.\n";
		return;
    } catch (bool nameExists) {
        cout << "No such id or name.\n";
		return;
    }
    
	//checks to see if it is a teacher or student
	if (inputID > 1 && inputID <= 100) {
		j = 0;
	}
	else if (inputID > 100 && inputID <= 300) {
		j = 1;
	}
	//searches the teacher linked list for the information
	showInformationSearchPerson(j, inputID, library);
}

//show the menu
void showMenu(Book& book, Person& person) {
    int input = 0;
    book.createLibrary();
    person.createClass();
    do {
        cout << "---------------------------\n" << setw(15) << "Menu" << '\n' << "---------------------------\n";
        cout << "1. Search a book\n";
        cout << "2. Rent a book\n";
        cout << "3. Return a book\n";
        cout << "4. Show my information\n";
        cout << "5. Show all books\n";
        cout << "6. Exit\n";
        
        cout << "Select (1~6) : ";
        cin >> input;
        if (input == 1) {
            cout << '\n';
            book.searchBook();
            cout << '\n';
        } else if (input == 2) {
            cout << '\n';
            person.rentBook(book);
            cout << '\n';
        } else if (input == 3) {
            cout << '\n';
            person.returnBook(book);
            cout << '\n';
        } else if (input == 4) {
            cout << '\n';
            person.showInformation(book);
            cout << '\n';
        } else if (input == 5) {
            cout << '\n';
            book.showLibrary();
            cout << '\n';
        }
    } while (input != 6);
}
