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

void SetScreenGrid();//������Ļ��ʾ������������
void ClearScreen();//�����Ļ��Ϣ
void SetSysCaption(const char *pText);//���ô��������
void ShowWelcome();//��ʾ��ӭ��Ϣ
void ShowRootMenu();//��ʾ��ʼ�˵�
void WaitView(int iCurPage);//�������ʱ�ȴ��û�����
void WaitUser();//�ȴ��û�����
void GuideInputA();//ʹ�������һ��ͼ����Ϣ
void GuideInputB();//ʹ���������־ͼ����Ϣ
void GuideInputC();//ʹ�����������ͼ����Ϣ
void Bookbro();//����
void Bookret();//����
int GetSelect();//����û��˵�ѡ��
long GetFileLength(ifstream &ifs);//��ȡ�ļ�����
void ViewData(int iSelPage);//�������ͼ���¼
void DeleteBookFromFile();//���ļ��в���ͼ����Ϣ
void mainloop();//��ѭ��

void main()
{
	SetScreenGrid();
	SetSysCaption("ͼ�����ϵͳ");
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
	cout << "***ͼ�����ϵͳ***" << endl;	cout << setw(40);	
	cout << "******************" << endl; 
}
void ShowRootMenu()
{ 
	cout << setw(35);	
	cout << "��ѡ����" << endl;	
	cout << endl;	
	cout << setw(35);
	cout << "1 ��ͨ�鼮���" << endl;
	cout << endl;	
	cout << setw(35);
	cout << "2 �����־�ڿ�" << endl;	
	cout << endl;
	cout << setw(35);
	cout << "3 ��������鼮" << endl;	
	cout << endl;
	cout << setw(35);
	cout << "4 ���ȫ��ͼ��" << endl;	
	cout << endl;	
	cout << setw(35);	
	cout << "5 ɾ��ͼ���¼" << endl;	
	cout << endl; 
}

void WaitUser()
{
	int iInputPage = 0;
	cout << "enter �������˵� q�˳�" << endl;
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
			cout << "��ѡ����" << endl;
			cout << endl;
			cout << setw(35);
			cout << "1 �����ͨ�鼮" << endl;
			cout << endl;
			cout << setw(35);
			cout << "2 �����ͨͼ��" << endl;
			cout << endl;
			cout << setw(35);
			cout << "3 �黹��ͨͼ��" << endl;
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
	cout << "��������" << endl;	
	cin >> inName;	
	cout << "������" << endl;	
	cin >> inNumber;
	cout << "�����������" << endl;	
	cin >> inTime;
	cout << "��������" << endl;
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
	cout << "��������" << endl;
	cin >> inName;
	cout << "������" << endl;
	cin >> inNumber;
	cout << "�����������" << endl;
	cin >> inTime;
	cout << "��������" << endl;
	cin >> inAuthor;
	for (int i = 0; i < NUM1 ; i++)//����ͨͼ����ϱ����P
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
	cout << "��������" << endl;
	cin >> inName;
	cout << "������" << endl;
	cin >> inNumber;
	cout << "�����������" << endl;
	cin >> inTime;
	cout << "��������" << endl;
	cin >> inAuthor;
	Special C(inName, inNumber, inTime, inAuthor, inbr);
	C.WriteData();
	cout << "Write Finish" << endl;
	WaitUser();
}

void Bookbro()
{
	General_book T;
	cout << "���������ͼ����(����ͨͼ��,�����ǰ׺P)" << endl;
	cin >> T.Bnum;
	if (T.Bnum[0] != 'P')
	{
		cout << "���ǹ淶�鼮���,������q����"<< endl;
		char buf[256];
		cin >> buf;
		if (buf[0] == 'q')
			system("exit");
	}
	else
	{
		cout << "���������ͼ������" << endl;
		cin >> T.g_bDate;
		cout << "����3�����ڹ黹" << endl;
		T.Setbdate();
	}

}

void Bookret()
{
	General_book TTT;
	cout << "������黹ͼ����(����ͨͼ��,�����ǰ׺P)" << endl;
	cin >> TTT.Bnum;
	while (TTT.Bnum[0] != 'P' && TTT.Bnum[0] !='q')
	{
		cout << "��������ͨ�鼮��ţ���'q'+Enter���˳�" << endl;
		cin >> TTT.Bnum;
	}
	cout << "���������ͼ������" << endl;
	cin >> TTT.g_rDate;
	cout << "�黹����Ϊ"<<TTT.Getrdate() << endl;
}

void ViewData(int iSelPage = 1)//���ͼ��
{	
	int iPage = 0;//��ҳ��	
	int iCurPage = 0;//��ǰҳ��	
	int iDataCount = 0;//������
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
	iDataCount = iFileLength / (NUM1 + NUM1 + NUM2 + NUM2+1);//�����ļ����ȣ������ļ����ܼ�¼��	
	if (iDataCount >= 1)		
		bIndex = true;
	iPage = iDataCount / 20 + 1;	
	ClearScreen();//�����Ļ��Ϣ	
	cout << "���м�¼" << iDataCount << " ";	
	cout << "����ҳ��" << iPage << " ";	
	cout << "��ǰҳ��" << iCurPage << " ";
	cout << "n ��ʾ��һҳ m ����" <<endl;	
	cout << setw(3) << "Index";
	cout << setw(20) << "Name"<<setw(24)<<"Number";	
	cout << setw(12) << "Time" << setw(10) << "Author"<<setw(5)<<"b/r";	
	cout << endl;
	try
	{		//����ͼ���¼��Ų������ļ��е�λ��		
		ifile.seekg((iCurPage - 1) * 20 * (NUM1 + NUM1 + NUM2 + NUM2+1), ios::beg);//ƫ����=ҳ��*�����������ļ�ͷ��ʼ	
		if (!ifile.fail())
		{		
			for (int i = 1; i < 21; i++)
			{			
				memset(inName, 0, 128);//����		
				memset(inNumber, 0, 128);	
				memset(inTime, 0, 50);			
				memset(inAuthor, 0, 50);	
				memset(&inbr, 0, 50);
				if (bIndex) {//�ҵ�����			
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
		throw "file error occurred";//�׳��쳣		
		ifile.close();	
	}	
	if (iCurPage < iPage)
	{	
		iCurPage = iCurPage + 1;	
		WaitView(iCurPage);//�ȴ��û�����	
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
