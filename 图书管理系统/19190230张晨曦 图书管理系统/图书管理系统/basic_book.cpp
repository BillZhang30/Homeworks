#include<iostream>
#include"basic_book.h"
#include<fstream>
#include <iomanip>
using namespace std;

Basic_book::Basic_book(char* bName, char*bNumber, char* bTime, char* bAuthor,char br)
{
	strncpy(m_bName, bName, NUM1);	
	strncpy(m_bNumber, bNumber, NUM1);
	strncpy(m_bTime, bTime, NUM2);
	strncpy(m_bAuthor, bAuthor, NUM2); 
	b_r = br;
}
char* Basic_book::GetName()
{ 
	return m_bName;
}void
Basic_book::SetName(char* bName)
{ 
	strncpy(m_bName, bName, NUM1);
}

char* Basic_book::GetNumber()
{ 
	return m_bNumber;
}
void Basic_book::SetNumber(char* bNumber)
{
	strncpy(m_bNumber, bNumber, NUM1);
}

char* Basic_book::GetTime()
{
	return m_bTime; 
}
void Basic_book::SetPrice(char* bTime)
{ 
	strncpy(m_bTime, bTime, NUM2); 
}

char* Basic_book::GetAuthor()
{
	return m_bAuthor; 
}
void Basic_book::SetAuthor(char* bAuthor)
{ 
	strncpy(m_bAuthor, bAuthor, NUM2);
}

void Basic_book::Setbor(char a)
{
	b_r = a;
}
char Basic_book::Getbor()
{
	return b_r;
}


void Basic_book::WriteData()
{
	ofstream ofile;	
	ofile.open("book.dat", ios::binary | ios::app);//�Զ����Ƹ�ʽ(binary)��book.dat, app:ÿ��д����ǰ����λ���ļ�ĩβ	
	try 
	{		
		ofile.write(m_bName, NUM1);//д��ͼ�����Ϣ		
		ofile.write(m_bNumber, NUM1);
		ofile.write(m_bTime, NUM2);
		ofile.write(m_bAuthor, NUM2);
		ofile.write(&b_r, 1);
	}	
	catch (...) //catch(��)�ܹ���������������͵��쳣����		
	{
		throw "file error occurred";		
		ofile.close();	
	}	
	ofile.close();
}
void Basic_book::DeleteData(int iCount)//ɾ����iCount����¼	
{
	long respos;	
	int iDataCount = 0;	
	fstream file;	fstream tmpfile;	
	ofstream ofile;	char cTempBuf[NUM1 + NUM1 + NUM2 + NUM2+1];	
	file.open("book.dat", ios::binary | ios::in | ios::out);//������/��/д
	tmpfile.open("temp.dat", ios::binary | ios::out | ios::in | ios::trunc);	
	file.seekg(0, ios::end); //�������ļ���λ
	respos = file.tellg();//���ص�ǰ��λָ���λ��
	iDataCount = respos / (NUM1 + NUM1 + NUM2 + NUM2+1);//�ܼ�¼��=�ļ���С/������
	if (iCount<0 || iCount>iDataCount)
	{		
		throw "Input number error";	
	}	
	else //�ӵ�iCount+1����¼��ʼ�����Ժ�ļ�¼�ȴ����м��ļ�����tmpfile����tmpfile�����ݸ��ǵ�iCount����¼֮������ݣ��൱��ɾ���˵�iCount����¼		
	{
		file.seekg((iCount)*(NUM1 + NUM1 + NUM2 + NUM2+1), ios::beg);//��дָ��ָ���iCount����¼����ʼλ��		
		for (int j = 0; j < (iDataCount - iCount); j++)//����iCount����¼��ļ�¼�ȴ���tmpfile		
		{	
			memset(cTempBuf, 0, NUM1 + NUM1 + NUM2 + NUM2+1);//��cTempBuf����			
			file.read(cTempBuf, NUM1 + NUM1 + NUM2 + NUM2+1);//��file�е�һ����¼����cTempBuf		
			tmpfile.write(cTempBuf, NUM1 + NUM1 + NUM2 + NUM2+1);//��cTempBuf�е�һ����¼д��tmpfile		
		}		
		file.close();		
		tmpfile.seekg(0, ios::beg);//��ָ�붨λ���ļ�ͷ		
		ofile.open("book.dat");		
		ofile.seekp((iCount - 1)*(NUM1 + NUM1 + NUM2 + NUM2+1), ios::beg);//��ָ�붨λ����iCount-1����¼�Ľ���λ��		
		for (int i = 0; i < (iDataCount - iCount); i++) 
		{			
			memset(cTempBuf, 0, NUM1 + NUM1 + NUM2 + NUM2+1);			
			tmpfile.read(cTempBuf, NUM1 + NUM1 + NUM2 + NUM2+1);		
			ofile.write(cTempBuf, NUM1 + NUM1 + NUM2 + NUM2+1);//��cTempBuf�е�һ����¼д��ofile		
		}	
	}	
	tmpfile.close();	
	ofile.close();	
	remove("temp.dat");
}
void Basic_book::GetBookFromFile(int iCount) 
{
	char cName[NUM1];	
	char cNumber[NUM1];	
	char cTime[NUM2];	
	char cAuthor[NUM2];	
	char cb_r;
	ifstream ifile;	
	ifile.open("book.dat", ios::binary);	
	try 
	{ 
		ifile.seekg(iCount * (NUM1 + NUM1 + NUM2 + NUM2+1), ios::beg);	
		ifile.read(cName, NUM1);	
		if (ifile.tellg() > 0)		
			strncpy(m_bName, cName, NUM1);	
		ifile.read(cNumber, NUM1);		
		if (ifile.tellg() > 0)			
			strncpy(m_bNumber, cNumber, NUM1);		
		ifile.read(cTime, NUM2);		
		if (ifile.tellg() > 0)			
			strncpy(m_bTime, cTime, NUM2);
		ifile.read(cAuthor, NUM2);		
		if (ifile.tellg() > 0)			
			strncpy(m_bAuthor, cAuthor, NUM2); 
		ifile.read(&cb_r, NUM2);
		if (ifile.tellg() > 0)
			strncpy(&b_r, &cb_r, NUM2);
	} 
	catch (...) 
	{
		throw "file error occured";		
		ifile.close();
	}	
	ifile.close(); 
}