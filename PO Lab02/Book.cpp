#include "Book.h"
#include <iostream>


Book::Book() 
	: author("unkown"), title("unknown")
{
	//std::cout << "Default constuctor" << std::endl;
}


Book::Book(const std::string& author, const std::string& title)
	: author(author), title(title)
{
	//std::cout << "L-reference constuctor" << std::endl;
}

Book::Book(std::string&& author, std::string&& title)
	: author(author), title(title)
{
	//std::cout << "R-reference constuctor" << std::endl;
}

std::string Book::GetAuthor() const {
	return author;
}

std::string Book::GetTitle() const {
	return title;
}

void Book::SetAuthor(const std::string& CINauthor) {
	this->author = CINauthor;
}
void Book::SetTitle(const std::string& CINtitle) {
	this->title = CINtitle;
}

void Book::SetAuthor(std::string&& CINauthor) {
	this->author = CINauthor;
}
void Book::SetTitle(std::string&& CINtitle) {
	this->title = CINtitle;
}

std::ostream& operator<<(std::ostream& os, const Book& book) {
	os << book.title << " by " << book.author;
	return os;
}


Book::Book(const Book& other)
	:author(other.author), title(other.title)
{
	//std::cout << "Copy constructor" << std::endl;
}

Book::Book(Book&& other) {
	//std::cout << "Move constructor" << std::endl;
	author = std::move(other.author);
	title = std::move(other.title);
}

Book & Book::operator=(const Book& right) {
	//std::cout << "l-reference = operator" << std::endl;
	Book tmp = right;
	std::swap(author, tmp.author);
	std::swap(title, tmp.title);
	return *this;
}
Book & Book::operator=(Book&& right) {
	//std::cout << "r-reference = operator" << std::endl;
	std::swap(author, right.author); 
	std::swap(title, right.title); 
	return *this;
}


Book::~Book(){
	//std::cout << "Destructor" << std::endl;
}