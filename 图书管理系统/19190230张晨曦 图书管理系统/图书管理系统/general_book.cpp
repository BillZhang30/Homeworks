#include"general_book.h"
#include<iostream>
#include<fstream>
using namespace std;

General_book::General_book(char* bName, char* bNumber, char* bTime, char* bAuthor, char br= '0') :Basic_book(bName, bNumber, bTime, bAuthor, br){}

void General_book::Setbdate()
{
	char booknote[NUM1];
	char Temp[NUM1 + NUM1 + NUM2 + NUM2 + 1];
	char temp[NUM1];
	strncpy(booknote, Bnum, NUM1);
	const char boo = '1';
	fstream ofile;
	ofile.open("book.dat", ios::binary|ios::in|ios::out );//�����ݿ�
	if (!ofile)
	{
		cout << "error open he file" << endl;
		exit(1);
	}
	while (!ofile.eof())
	{
		ofile.read(temp, sizeof(temp));//�ҵ���Ҫ���ĵ��鼮
		if (*temp == *booknote)
		{
			ofile.seekg(sizeof(Temp) - sizeof(temp) - 1, ios::cur);//��λ����¼λ��
			ofile.seekp(ofile.tellg());
			ofile.write(&boo, sizeof(boo));//��д�������
			break;
		}
		else
			cout << "can't find the book" << endl;
	}
	ofile.close();
}

char* General_book::Getrdate()
{
	char booknote[NUM1];
	char Temp[NUM1 + NUM1 + NUM2 + NUM2 + 1];
	char temp[NUM1];
	strncpy(booknote, Bnum, NUM1);
	const char boo = '0';
	fstream ofile;
	ofile.open("book.dat", ios::binary | ios::in | ios::out);//�����ݿ�
	if (!ofile)
	{
		cout << "error open he file" << endl;
		exit(1);
	}
	while (!ofile.eof())
	{
		ofile.read(temp, sizeof(temp));//�ҵ���Ҫ�黹���鼮
		if (*temp == *booknote)
		{
			ofile.seekg(sizeof(Temp) - sizeof(temp) - 1, ios::cur);//��λ����¼λ��
			ofile.seekp(ofile.tellg());
			ofile.write(&boo, sizeof(boo));//��д�������
			break;
		}
		else
			cout << "can't find the book" << endl;
	}
	return g_rDate;
	ofile.close();
}