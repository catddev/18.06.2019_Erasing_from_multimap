#include "Book.h"

Book::Book()
{
	author = "";
	title = "";
	publish = "";
	number = 2019;
}

Book::Book(string author, string title, string publish, int number)
{
	this->author = author;
	this->title = title;
	this->publish = publish;
	this->number = number;
}

string Book::getAuthor() const
{
	return author;
}

string Book::getYear() const
{
	return publish;
}

string Book::getTitle() const
{
	return title;
}

int Book::getNumber() const
{
	return number;
}

ostream & operator<<(ostream & os, Book obj)
{
	os << "\t" << obj.title << " " << obj.publish << " " << obj.number;
	return os;
}

istream & operator>>(istream & is, Book & obj)
{
	getline(is, obj.author, '#');
	getline(is, obj.title, '#');
	getline(is, obj.publish, '#');
	is >> obj.number;
	return is;
}