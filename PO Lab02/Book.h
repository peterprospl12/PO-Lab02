#pragma once
#include <iostream>

class Book {
private:
	std::string author;
	std::string title;
public:
	Book();
	Book(const std::string& author, const std::string& title);
	Book(std::string&& author, std::string&& title);

	std::string GetAuthor() const;
	std::string GetTitle() const;

	void SetAuthor(const std::string& CINauthor);
	void SetTitle(const std::string& CINtitle);
	
	void SetAuthor(std::string&& CINauthor);
	void SetTitle(std::string&& CINtitle);

	friend std::ostream& operator<<(std::ostream& os, const Book& book);
	
	Book(const Book& other);
	Book(Book&& other);

	Book& operator=(const Book& right);
	Book& operator=(Book&& right);

	~Book();

};

