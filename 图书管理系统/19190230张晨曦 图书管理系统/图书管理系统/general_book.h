#ifndef _GENERAL_H
#define _GENERAL_H
#include "basic_book.h"
#define NUM1 128           //ͼ�����ƺͱ����󳤶�
#define NUM2 50           //ͼ�����߼�������󳤶�
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
	void Setbdate();//�ӿ��в��Ҳ���ǽ���,��¼��������(��������ż�����)
	char* Getrdate();////�ӿ��в��Ҳ�����ѻ�,���ػ�������(���뻹���ż�����)
};
#endif
