#include<string>
#include<cstring>
#include<string.h>
#include<map>
#include<algorithm>
#include<iostream>
#include<fstream>
#include<Windows.h>
#include<set>
#include<queue>
#include<vector>
#include"Book.h"
using namespace std;

//Написать программу учета книг в библиотеке. Сведения о книгах : ФИО автора, название, год издания, количество экземпляров.
//Обеспечить :
//		Добавление книг
//		Удаление книг
//		Вывод сведений о книгах по фамилиям авторов
//		Вывод сведений о книгах по указанному году издания
//	Использовать контейнерный класс multimap



bool asc(const Book& obj1, const Book& obj2) {
	//return (obj1.getNumber() < obj2.getNumber()); //будет сортировать по кол-ву экземпляров
	return (obj1.getYear() < obj2.getYear()); // чтобы работало по году нужно чтобы в прототипе getYear() было CONST!
}

void remove_by_property(multimap<string, Book>& mb, string prop) {
	string tmp;
	cout << "Enter your property's value" << endl;
	cin.ignore();//!
	getline(cin, tmp, '\n');

	//auto it = lib.find(author);
			//if (it != lib.end()) {
			//	if(it->second.getTitle()==title)//erasing by title
			//	lib.erase(it);
			//}

	if (prop == "author") {

		for (auto it = mb.begin(); it != mb.end(); it++) {
			if (it->second.getAuthor() == tmp) {
				if (it != mb.end()) {
					mb.erase(it);
					if (!mb.empty())
						it = mb.begin();
					else break;
				}
			}
		}
	}
	else if (prop == "title") {
		for (auto it = mb.begin(); it != mb.end(); it++)
			if (it->second.getTitle() == tmp) {
				if (it != mb.end()) {
					mb.erase(it);
					if (!mb.empty())
						it = mb.begin();
					else break;
				}
			}
	}
	else if (prop == "year") {
		for (auto it = mb.begin(); it != mb.end(); it++)
			if (it->second.getYear() == tmp) {
				if (it != mb.end()) {
					mb.erase(it);
					if (!mb.empty())
						it = mb.begin();
					else break;
				}
			}
	}
}



int main() {

	setlocale(LC_ALL, "");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);


	ifstream lib_file("library.txt");
	multimap<string, Book> lib;
	set<string> bookset;
	string str1;
	int i = 0;

	string author, title, publish;
	int number;
	vector<Book> b1;

	while (!lib_file.eof()) {
		getline(lib_file, author, '#');
		getline(lib_file, title, '#');
		getline(lib_file, publish, '#');
		lib_file >> number;
		lib_file.ignore();
		bookset.insert(author);
		lib.insert(pair<string, Book>(author, Book(author, title, publish, number)));
		b1.push_back(Book(author, title, publish, number));

	}

	while (true) {
		cout << endl << "Enter 1 to remove a book" << endl;
		cout << "Enter 2 to add a book" << endl;
		cout << "Enter 3 to get books by author" << endl;
		cout << "Enter 4 to get books by publishing year" << endl;
		cout << "Enter 5 to print the book list" << endl;
		cout << "Enter 0 to exit" << endl;
		int choice1;
		cin >> choice1;
		if (choice1 == 0)
			break;
		Book yourBook;

		switch (choice1) {
		case 1:
		{
			string property;
			cout << "Enter \"author\" to erase by author" << endl;
			cout << "Enter \"title\" to erase by title" << endl;
			cout << "Enter \"year\" to erase by publishing year" << endl;
			cin >> property;

			remove_by_property(lib, property);

			if (!lib.empty()) {
				cout << endl;
				for_each(lib.begin(), lib.end(), [](pair<string, Book> p) {
					cout << p.first << " " << p.second << endl;
				});
			}
			else
				cout << "EMPTY MAP!" << endl;

		}
		break;
		case 2:
		{
			cout << "Enter full book description to add to the library database" << endl;
			cin.ignore();
			cin >> yourBook;
			lib.insert(pair<string, Book>(yourBook.getAuthor(), yourBook));
			bookset.insert(yourBook.getAuthor());
		}
		break;
		case 3:
		{
			cout << "Enter an author" << endl;
			cin.ignore();
			getline(cin, author, '\n');

			for (auto it = bookset.begin(); it != bookset.end(); it++) {//every *it - unique author
				auto ret = lib.equal_range(*it); //*it is a key for multimap.
				//Equal_range sets only 2 ptr - first (when we "first" meet author in the multimap, and "second" when it is last book of the author in the multimap lib
				if (*it == author)//by author
					for (auto mit = ret.first; mit != ret.second; mit++)// mit is iterator for multimap
						cout << mit->second << endl;
			}
		}
		break;
		case 4:
		{
			cout << "Enter publishing year" << endl;
			cin >> publish;
			for (auto it = lib.begin(); it != lib.end(); it++) {
				if (it->second.getYear() == publish)
					cout << it->first << " " << it->second << endl;
			}
		}
		break;
		case 5:
		{
			if (!lib.empty()) {//!!!!!
				cout << endl << "БИБЛИОТЕКА:" << endl;
				for (auto it = bookset.begin(); it != bookset.end(); it++) {
					auto ret = lib.equal_range(*it);
					cout << ret.first->first << endl;
					for (auto mit = ret.first; mit != ret.second; mit++)
						cout << mit->second << endl;
				}
			}
			else
				cout << "EMPTY MAP!" << endl;
		}
		break;
		}
	}

	sort(b1.begin(), b1.end(), asc);
	for_each(b1.begin(), b1.end(), [](Book b) {
		cout << b.getAuthor() << " " << b << endl;
	});

	system("pause");
	return 0;
}