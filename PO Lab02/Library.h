#pragma once
#include "Book.h"
#include <initializer_list>

class Library {
private:
	Book* array;
	std::size_t size;
public:
	Library();
	Library(std::size_t i);
	Library(std::initializer_list<Book> list);
	Library(const Library& orig);
	Library(Library&& orig);
	Library& operator=(const Library& right);
	Library& operator=(Library&& right);
	void addBook(Book&& bk);
	void showBooks();
	void removeBook(std::string CINtitle);
	Book& operator[](std::size_t index);
	const Book& operator[](std::size_t index) const;
	std::size_t GetSize() const;
	friend std::ostream& operator<<(std::ostream& os, const Library& library);
	~Library();

};