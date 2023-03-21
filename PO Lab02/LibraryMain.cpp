#include "Library.h"
#include <iostream>

using namespace std;

int main() {
	//Library e;
	//cout << "e: " << e << endl;
	//3-5 ksi¹¿ek
	Library l1 = { {"Andrzej Sapkowski", "Wiedzmin"},
	{"Stephen King", "Green Mile"},
	{"J.R.R. Tolkien", "Hobbit"} };
	cout << "l1: " << l1 << endl;
	l1.addBook({ "123", "123" });
	cout << "l1: " << l1 << endl;
	l1.showBooks();
	l1.removeBook({ "Hobbit" });
	l1.showBooks();

	/*cout << "l1: " << l1 << endl;
	Library l2(2);
	cout << "l2: " << l2 << endl;
	l2[0] = { "Antoine’a de Saint-Exupéry’ego", "The Little Prince" };
	l2[1] = { "George Orwell", "1984" };
	cout << "l2: " << l2 << endl;
	e = std::move(l2);
	cout << "e: " << e << " l2: " << l2 << endl;
	l1[0] = std::move(e[1]);
	cout << "l1: " << l1 << " e: " << e << endl;*/
}