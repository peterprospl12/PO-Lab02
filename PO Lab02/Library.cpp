#include "Library.h"
#include <iostream>
#include <initializer_list>


Library::Library()
	:size(0), array(new Book[0])
{}

Library::Library(std::size_t i) 
	: size(i), array{ new Book[i] }
{}

Library::Library(std::initializer_list<Book> list)
	: size{ list.size() }, array{ new Book[list.size()] }
{
	std::size_t i = 0;
	for (Book v : list)
	{
		array[i] = v;
		i++;
	}
}

Library::Library(const Library& orig) 
	: size(orig.size), array{ new Book[orig.size] } 
{
	//std::cout << "Copy constructor" << std::endl;

	for (std::size_t i = 0; i < size; i++)
		array[i] = orig.array[i];
}

Library::Library(Library&& orig) {
	//std::cout << "Move constructor" << std::endl;
	array = orig.array;
	size = orig.size;
	orig.array = nullptr;
	orig.size = 0;
}

Library& Library::operator=(const Library& right) {
	//std::cout << "L-reference operator=" << std::endl;
	Library tmp = right;
	std::swap(array, tmp.array);
	std::swap(size, tmp.size);
	return *this;
}

Library& Library::operator=(Library&& right) {
	//std::cout << "R-reference operator=" << std::endl;
	std::swap(array, right.array);
	std::swap(size, right.size);
	return *this;
}

Book& Library::operator[](std::size_t index) {
	//std::cout << "R-reference operator[]" << std::endl;
	return array[index];
}

const Book& Library::operator[](std::size_t index) const {
	//std::cout << "L-reference operator[]" << std::endl;
	return array[index];
}

std::size_t Library::GetSize() const {
	//std::cout << "Get Size" << std::endl;
	return size;
}

std::ostream& operator<<(std::ostream& os, const Library& v) {
	os << "Library{";
	for (std::size_t i = 0; i < v.GetSize(); i++)
	{
		if (i > 0)
			os << ',';
		os << v[i];
	}
	os << '}' << std::endl;
	return os;
}

void Library::addBook(Book&& book) {
	Book* tmp_array = new Book[size + 1];
	for (int i = 0; i < size; i++) {
		tmp_array[i] = std::move(array[i]);
	}
	tmp_array[size] = std::move(book);
	delete[] array;
	array = tmp_array;
	size++;
}

void Library::showBooks() {
	std::cout << *this << std::endl;
}

void Library::removeBook(std::string CINtitle) {
	bool found = false;
	for (int i = 0; i < size; i++) {
		if (array[i].GetTitle() == CINtitle) {
			for (int j = i; j < size - 1; j++) {
				array[j] = std::move(array[j + 1]);
			}
			size--;
			found = true;
			break;
		}
	}
	if (!found) {
		std::cout << "No book in library" << std::endl;
	}
	else {
		std::cout << "Book removed" << std::endl;
	}
}


Library::~Library(){
	//std::cout << "Destructor" << std::endl;
	if (array != nullptr)
	{
		std::cout << "Releasing memory " << array << std::endl;
		delete[] array;
	}

}