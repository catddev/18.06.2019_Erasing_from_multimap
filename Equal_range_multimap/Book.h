#pragma once
#include<string>
#include<iostream>
using namespace std;

class Book {
	string author;
	string title;
	string publish;
	int number;
public:
	Book();
	Book(string author, string title, string publish, int number);
	string getAuthor()const;
	string getYear()const;
	string getTitle()const;
	int getNumber()const;

	friend ostream& operator<<(ostream& os, Book obj);
	friend istream& operator>>(istream& is, Book& obj);
};