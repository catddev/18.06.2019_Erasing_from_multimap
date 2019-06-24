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


void remove_by_property(multimap<string, Book>& mb, int prop) {
	string tmp;
	cout << "Enter your property's value" << endl;
	cin.ignore();//!
	getline(cin, tmp, '\n');

	auto it = mb.begin();

	if (prop == 1) {
		//здесь всегда перепрыгивает НОВЫЙ первый итератор, поэтому по циклу вводим один итератор, а удаляем по другому итератору
		//do {
		//	it++;
		//	auto nit = mb.find(tmp);//author is a key
		//	if (nit != mb.end()) {
		//		if (nit->first == tmp) {
		//			mb.erase(nit);
		//			if (!mb.empty())
		//				it = mb.begin();
		//			else break;
		//		}
		//	}
		//} while (it != mb.end());
		//исп do-while чтобы входил последний случай когда it==mb.end()
		mb.erase(tmp); //если erase по ключу, то удаляет сразу все элементы с таким ключом
	}
	else if (prop == 2) {
		for (auto it = mb.begin(); it != mb.end();/*здесь пусто, без шага цикла, для multimap не сработает */) {
			auto nit = it++;//пересохраняем итератор иначе будет ошибка cannot increment value-initialized iterator it, т.е. без nit просто it++ нельзя
			if (nit->second.getTitle() == tmp)
				mb.erase(nit);
		}
	}
	else if (prop == 3) {
		for (auto it = mb.begin(); it != mb.end();) {
			auto nit = it++;
			if (nit->second.getYear() == tmp)
				mb.erase(nit);	
		}
	}
}


int main() {

	setlocale(LC_ALL, "");

	ifstream lib_file("library.txt");
	multimap<string, Book> lib;
	set<string> bookset;
	string str1;
	int i = 0;

	string author, title, publish;
	int number;
	vector<Book> v;

	while (!lib_file.eof()) {
		getline(lib_file, author, '#');
		getline(lib_file, title, '#');
		getline(lib_file, publish, '#');
		lib_file >> number;
		lib_file.ignore();
		bookset.insert(author);
		lib.insert(pair<string, Book>(author, Book(author, title, publish, number)));
		v.push_back(Book(author, title, publish, number));
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
		system("cls");//clear screen

		if (choice1 == 0)
			break;
		Book yourBook;

		switch (choice1) {
		case 1:
		{
			int property;
			cout << "Enter 1 to erase by author" << endl;
			cout << "Enter 2 to erase by title" << endl;
			cout << "Enter 3 to erase by publishing year" << endl;
			cin >> property;

			remove_by_property(lib, property);

			if (!lib.empty()) {
				cout << endl;
				for_each(lib.begin(), lib.end(), [](pair<string, Book> p) {
					cout << p.first << " " << p.second << endl;
				});
			}
			else
				cout << endl << "EMPTY MAP!" << endl;
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

			for (auto it = bookset.begin(); it != bookset.end(); it++) {
				auto ret = lib.equal_range(*it);
				if (*it == author)
					for (auto mit = ret.first; mit != ret.second; mit++)
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
			if (!lib.empty()) {
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

	system("pause");
	return 0;
}