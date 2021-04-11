#ifndef _GENERAL_H
#define _GENERAL_H
#include "basic_book.h"
#define NUM1 128           //图书名称和编号最大长度
#define NUM2 50           //图书作者及日期最大长度
using namespace std;
#include<string>
class General_book :public Basic_book
{
public:
	char Bnum[NUM1]="none";
	char g_bDate[NUM2] = "none";
	char g_rDate[NUM2] = "none";
public:
	General_book() {}
	General_book(char* bName, char* bNumber, char* bTime, char* bAuthor, char br);
	~General_book() {}
	void Setbdate();//从库中查找并标记借阅,记录借书日期(输入借书编号及日期)
	char* Getrdate();////从库中查找并标记已还,返回还书日期(输入还书编号及日期)
};
#endif
