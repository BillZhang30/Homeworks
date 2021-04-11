#ifndef _MS_H
#define _MS_H
#include"basic_book.h"

class Magazine :public Basic_book
{
public:
	Magazine(){}
	Magazine(char* bName, char* bNumber, char* bTime, char* bAuthor, char br = '0') :
		Basic_book(bName, bNumber, bTime, bAuthor, br){}
	~Magazine(){}
};

class Special :public Basic_book
{
public:
	Special(){}
	Special(char* bName, char* bNumber, char* bTime, char* bAuthor, char br = '0') :
		Basic_book(bName, bNumber, bTime, bAuthor, br) {}
	~Special(){}
};
#endif
