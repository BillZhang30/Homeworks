#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <fstream>

#include"general_book.h"
#include"Mag_Sp.h"
#include "basic_book.h"

#define CMD_COLS 80
#define CMD_LINES 25
using namespace std;

void SetScreenGrid();//设置屏幕显示的行数和列数
void ClearScreen();//清除屏幕信息
void SetSysCaption(const char *pText);//设置窗体标题栏
void ShowWelcome();//显示欢迎信息
void ShowRootMenu();//显示开始菜单
void WaitView(int iCurPage);//浏览数据时等待用户操作
void WaitUser();//等待用户操作
void GuideInputA();//使用向导添加一般图书信息
void GuideInputB();//使用向导添加杂志图书信息
void GuideInputC();//使用向导添加特殊图书信息
void Bookbro();//借书
void Bookret();//还书
int GetSelect();//获得用户菜单选择
long GetFileLength(ifstream &ifs);//获取文件长度
void ViewData(int iSelPage);//浏览所有图书记录
void DeleteBookFromFile();//在文件中产生图书信息
void mainloop();//主循环

void main()
{
	SetScreenGrid();
	SetSysCaption("图书管理系统");
	mainloop();
}

void SetScreenGrid() 
{
	char sysSetBuf[80];
	sprintf(sysSetBuf, "mode con cols=%d lines=%d", CMD_COLS, CMD_LINES);
	system(sysSetBuf);
}
void SetSysCaption()
{ 
	system("title Sample"); 
}
void SetSysCaption(const char* pText)
{ 
	char sysSetBuf[80];	
	sprintf(sysSetBuf, "title %s", pText);
	system(sysSetBuf); 
} 
void ClearScreen() 
{ 
	system("cls");
} 
void ShowWelcome() 
{ 
	for (int i = 0; i < 7; i++)
	{ 
		cout << endl;
	}	
	cout << setw(40);	
	cout << "******************" << endl;	cout << setw(40);	
	cout << "***图书管理系统***" << endl;	cout << setw(40);	
	cout << "******************" << endl; 
}
void ShowRootMenu()
{ 
	cout << setw(35);	
	cout << "请选择功能" << endl;	
	cout << endl;	
	cout << setw(35);
	cout << "1 普通书籍相关" << endl;
	cout << endl;	
	cout << setw(35);
	cout << "2 添加杂志期刊" << endl;	
	cout << endl;
	cout << setw(35);
	cout << "3 添加特殊书籍" << endl;	
	cout << endl;
	cout << setw(35);
	cout << "4 浏览全部图书" << endl;	
	cout << endl;	
	cout << setw(35);	
	cout << "5 删除图书记录" << endl;	
	cout << endl; 
}

void WaitUser()
{
	int iInputPage = 0;
	cout << "enter 返回主菜单 q退出" << endl;
	char buf[256];
	gets_s(buf);
	if (buf[0] == 'q')
		system("exit");
}

void mainloop()
{
	//ShowWelcome();
	while (1)
	{
		//ClearScreen();
		ShowWelcome();
		ShowRootMenu();
		switch (GetSelect())
		{
		case 1:
			ClearScreen();
			cout << setw(35);
			cout << "请选择功能" << endl;
			cout << endl;
			cout << setw(35);
			cout << "1 添加普通书籍" << endl;
			cout << endl;
			cout << setw(35);
			cout << "2 借出普通图书" << endl;
			cout << endl;
			cout << setw(35);
			cout << "3 归还普通图书" << endl;
			cout << endl;
			switch (GetSelect())
			{
			case 1:
				ClearScreen();
				GuideInputA();
				break;
			case 2:
				ClearScreen();
				Bookbro();
				break;
			case 3:
				ClearScreen();
				Bookret();
				break;
			}
			break;
		case 2:
			ClearScreen();
			GuideInputB();
			break;
		case 3:
			ClearScreen();
			GuideInputC();
			break;
		case 4:
			ClearScreen();
			ViewData(1);
			break;
		case 5:
			ClearScreen();
			DeleteBookFromFile();
			break;
		}
	}
}

int GetSelect() 
{
	char buf[256];
	gets_s(buf);
	return atoi(buf);
}

void GuideInputA()
{
	char inName[NUM1];	
	char inNumber[NUM1];	
	char inTime[NUM2];	
	char inAuthor[NUM2]; 
	char inbr = '0';
	cout << "输入书名" << endl;	
	cin >> inName;	
	cout << "输入编号" << endl;	
	cin >> inNumber;
	cout << "输入入库日期" << endl;	
	cin >> inTime;
	cout << "输入作者" << endl;
	cin >> inAuthor;
	General_book A(inName, inNumber, inTime, inAuthor,inbr);
	A.WriteData();
	cout << "Write Finish" <<endl;
	WaitUser();
}

void GuideInputB()
{
	char inName[NUM1];
	char inNumberA[NUM1];
	char inNumber[NUM1];
	char inTime[NUM2];
	char inAuthor[NUM2];
	char inbr = '0';
	cout << "输入书名" << endl;
	cin >> inName;
	cout << "输入编号" << endl;
	cin >> inNumber;
	cout << "输入入库日期" << endl;
	cin >> inTime;
	cout << "输入作者" << endl;
	cin >> inAuthor;
	for (int i = 0; i < NUM1 ; i++)//将普通图书加上标记码P
	{
		inNumberA[i + 1] = inNumber[i];
	}
	inNumberA[0] = 'P';
	Magazine B(inName, inNumberA, inTime, inAuthor, inbr);
	 B.WriteData();
	cout << "Write Finish" << endl;
	WaitUser();
}

void GuideInputC()
{
	char inName[NUM1];
	char inNumber[NUM1];
	char inTime[NUM2];
	char inAuthor[NUM2];
	char inbr = '0';
	cout << "输入书名" << endl;
	cin >> inName;
	cout << "输入编号" << endl;
	cin >> inNumber;
	cout << "输入入库日期" << endl;
	cin >> inTime;
	cout << "输入作者" << endl;
	cin >> inAuthor;
	Special C(inName, inNumber, inTime, inAuthor, inbr);
	C.WriteData();
	cout << "Write Finish" << endl;
	WaitUser();
}

void Bookbro()
{
	General_book T;
	cout << "请输入借阅图书编号(仅普通图书,即编号前缀P)" << endl;
	cin >> T.Bnum;
	if (T.Bnum[0] != 'P')
	{
		cout << "不是规范书籍编号,请输入q返回"<< endl;
		char buf[256];
		cin >> buf;
		if (buf[0] == 'q')
			system("exit");
	}
	else
	{
		cout << "请输入借阅图书日期" << endl;
		cin >> T.g_bDate;
		cout << "请在3个月内归还" << endl;
		T.Setbdate();
	}

}

void Bookret()
{
	General_book TTT;
	cout << "请输入归还图书编号(仅普通图书,即编号前缀P)" << endl;
	cin >> TTT.Bnum;
	while (TTT.Bnum[0] != 'P' && TTT.Bnum[0] !='q')
	{
		cout << "请输入普通书籍编号，或按'q'+Enter键退出" << endl;
		cin >> TTT.Bnum;
	}
	cout << "请输入借阅图书日期" << endl;
	cin >> TTT.g_rDate;
	cout << "归还日期为"<<TTT.Getrdate() << endl;
}

void ViewData(int iSelPage = 1)//浏览图书
{	
	int iPage = 0;//总页数	
	int iCurPage = 0;//当前页数	
	int iDataCount = 0;//总书数
	char inName[NUM1];	
	char inNumber[NUM1];
	char inTime[NUM2];	
	char inAuthor[NUM2];
	char inbr;
	bool bIndex = false;	
	int iFileLength;
	iCurPage = iSelPage;	
	ifstream ifile;	
	ifile.open("book.dat", ios::binary);	
	iFileLength = GetFileLength(ifile);	
	iDataCount = iFileLength / (NUM1 + NUM1 + NUM2 + NUM2+1);//根据文件长度，计算文件中总记录数	
	if (iDataCount >= 1)		
		bIndex = true;
	iPage = iDataCount / 20 + 1;	
	ClearScreen();//清除屏幕信息	
	cout << "共有记录" << iDataCount << " ";	
	cout << "共有页数" << iPage << " ";	
	cout << "当前页数" << iCurPage << " ";
	cout << "n 显示下一页 m 返回" <<endl;	
	cout << setw(3) << "Index";
	cout << setw(20) << "Name"<<setw(24)<<"Number";	
	cout << setw(12) << "Time" << setw(10) << "Author"<<setw(5)<<"b/r";	
	cout << endl;
	try
	{		//根据图书记录编号查找在文件中的位置		
		ifile.seekg((iCurPage - 1) * 20 * (NUM1 + NUM1 + NUM2 + NUM2+1), ios::beg);//偏移量=页数*基本量，从文件头开始	
		if (!ifile.fail())
		{		
			for (int i = 1; i < 21; i++)
			{			
				memset(inName, 0, 128);//清零		
				memset(inNumber, 0, 128);	
				memset(inTime, 0, 50);			
				memset(inAuthor, 0, 50);	
				memset(&inbr, 0, 50);
				if (bIndex) {//找到了书			
					cout << setw(3) << ((iCurPage - 1) * 20 + i);				
					ifile.read(inName, NUM1);				
					cout << setw(24) << inName;			
					ifile.read(inNumber, NUM1);					
					cout << setw(24) << inNumber;
					ifile.read(inTime, NUM2);			
					cout << setw(10) << inTime;
					ifile.read(inAuthor, NUM2);				
					cout << setw(10) << inAuthor;	
					ifile.read(&inbr, 1);
					cout << setw(5) << inbr;
					cout << endl;				
				}				
				if (ifile.tellg() < 0)		
					bIndex = false;			
				else				
					bIndex = true;		
			}		
		}	
	}	
	catch (...) 
	{		
		cout << "throw file exception" << endl;		
		throw "file error occurred";//抛出异常		
		ifile.close();	
	}	
	if (iCurPage < iPage)
	{	
		iCurPage = iCurPage + 1;	
		WaitView(iCurPage);//等待用户处理	
	}
	else 
	{	
		WaitView(iCurPage);
	}	
	ifile.close();
}

long GetFileLength(ifstream& ifs)
{ 
	long temppos;	
	long respos;	temppos = ifs.tellg();
	ifs.seekg(0, ios::end);	
	respos = ifs.tellg();
	ifs.seekg(temppos, ios::beg);	
	return respos; 
}
void DeleteBookFromFile() 
{
	int iDelCount;	
	cout << "Input delete index" << endl;	
	cin >> iDelCount;
	Basic_book tmpbook;
	tmpbook.DeleteData(iDelCount);	
	cout << "Delete Finish" << endl;
	WaitUser();
}
void WaitView(int iCurPage)
{	
	char buf[256];	
	gets_s(buf);	
	if (buf[0] == 'q')		
		system("exit");	
	if (buf[0] == 'm')	
		mainloop();	
	if (buf[0] == 'n')		
		ViewData(iCurPage);
}
