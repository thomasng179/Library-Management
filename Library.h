#ifndef Library_h
#define Library_h

#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;

class Book {
    friend class BookNode;
    friend void showMenu(Book& book, class Person& person);
public:
    Book();
    Book(int code, string title, int available, int rented);
    int getCode();
    string getTitle();
    int getAvailable();
    int getRented();
    struct BookNode* getLibrary(int i);
    void subRented();
    void addRented();
    void addAvailable();
    void subAvailable();
    void createLibrary();
    void showLibrary();
    void searchBook();
    void tryCatchsearchBook(int i, int, string, string&, int&);
    void searchInputBook(int codeSearch);
    void searchAvailability(int i, string inputBook, string& foundTitle, int& noMore, int& targetCode);
    virtual int getAge();
    virtual string getPublisher();
    virtual int getPublishDate();
private:
    struct BookNode* library[3];
    int code;
    string title;
    int available;
    int rented;
};
class ChildrenBook : public Book {
public :
    ChildrenBook();
    ChildrenBook(int code, string title, int available, int rented, int age);
    ChildrenBook(Book* book, int age);
    int getAge();
private:
    int age;
};

class ComputerBook : public Book {
public:
    ComputerBook();
    ComputerBook(int code, string title, int available, int rented, string publisher);
    string getPublisher();
private:
    string publisher;
};

class Novel : public Book {
public:
    Novel();
    Novel(int code, string title, int available, int rented, int publishDate);
    int getPublishDate();
private:
    int publishDate;
};

class Person {
    friend class PersonNode;
    friend void showMenu(Book& book, class Person& person);
public:
    Person();
    Person(int id, string name, int count);
    int getId();
    string getName();
    int getCount();
    void addCount();
    void subCount();
    virtual void setCode(int code);
    virtual void returnCode(int code);
    virtual int getCode(int i);
    void createClass();
    void rentBook(Book& library);
    void returnBook(Book& library);
    void showInformation(Book& library);
    void rentBookSearch(int inputID, string inputBook, int& noMore, int targetCode, Book& library);
    void rentBookExist(int i, int& foundID, int inputBook, int& bookCode, int inputID);
    void rentBookLibrarySearch(int i, Book& library, int inputBook, string& foundCode, int bookCode, string& bookTitle);
    void rentBookUpdatePerson(int i, Book& library, int inputID, string bookTitle, int bookCode, int inputBook);
    void showInformationSearchPerson(int i, int inputID, Book& library);
private:
    struct PersonNode* person[2];
    int id;
    string name;
    int count;
};

class Student : public Person {
public:
    Student();
    void setCode(int code);
    int getCode(int i);
    void returnCode(int code);
    Student(int id, string name, int count, int code1, int code2);
private:
    int code[2];
};

class Teacher : public Person {
public:
    Teacher();
    void setCode(int code);
    int getCode(int i);
    void returnCode(int code);
    Teacher(int id, string name, int count, int code1, int code2, int code3);
private:
    int code[3];
};

struct PersonNode {
    Person* person;
    PersonNode* link;
};

struct BookNode {
    Book* book;
    BookNode* link;
};

#endif
