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
	ofile.open("book.dat", ios::binary | ios::app);//以二进制格式(binary)打开book.dat, app:每次写操作前均定位到文件末尾	
	try 
	{		
		ofile.write(m_bName, NUM1);//写入图书的信息		
		ofile.write(m_bNumber, NUM1);
		ofile.write(m_bTime, NUM2);
		ofile.write(m_bAuthor, NUM2);
		ofile.write(&b_r, 1);
	}	
	catch (...) //catch(…)能够捕获多种数据类型的异常对象		
	{
		throw "file error occurred";		
		ofile.close();	
	}	
	ofile.close();
}
void Basic_book::DeleteData(int iCount)//删掉第iCount条记录	
{
	long respos;	
	int iDataCount = 0;	
	fstream file;	fstream tmpfile;	
	ofstream ofile;	char cTempBuf[NUM1 + NUM1 + NUM2 + NUM2+1];	
	file.open("book.dat", ios::binary | ios::in | ios::out);//二进制/读/写
	tmpfile.open("temp.dat", ios::binary | ios::out | ios::in | ios::trunc);	
	file.seekg(0, ios::end); //对输入文件定位
	respos = file.tellg();//返回当前定位指针的位置
	iDataCount = respos / (NUM1 + NUM1 + NUM2 + NUM2+1);//总记录数=文件大小/基本量
	if (iCount<0 || iCount>iDataCount)
	{		
		throw "Input number error";	
	}	
	else //从第iCount+1条记录开始，将以后的记录先存至中间文件变量tmpfile，后将tmpfile的内容覆盖掉iCount条记录之后的内容，相当于删掉了第iCount条记录		
	{
		file.seekg((iCount)*(NUM1 + NUM1 + NUM2 + NUM2+1), ios::beg);//读写指针指向第iCount条记录的起始位置		
		for (int j = 0; j < (iDataCount - iCount); j++)//将第iCount条记录后的记录先存入tmpfile		
		{	
			memset(cTempBuf, 0, NUM1 + NUM1 + NUM2 + NUM2+1);//将cTempBuf清零			
			file.read(cTempBuf, NUM1 + NUM1 + NUM2 + NUM2+1);//将file中的一条记录读入cTempBuf		
			tmpfile.write(cTempBuf, NUM1 + NUM1 + NUM2 + NUM2+1);//将cTempBuf中的一条记录写入tmpfile		
		}		
		file.close();		
		tmpfile.seekg(0, ios::beg);//将指针定位在文件头		
		ofile.open("book.dat");		
		ofile.seekp((iCount - 1)*(NUM1 + NUM1 + NUM2 + NUM2+1), ios::beg);//将指针定位到第iCount-1条记录的结束位置		
		for (int i = 0; i < (iDataCount - iCount); i++) 
		{			
			memset(cTempBuf, 0, NUM1 + NUM1 + NUM2 + NUM2+1);			
			tmpfile.read(cTempBuf, NUM1 + NUM1 + NUM2 + NUM2+1);		
			ofile.write(cTempBuf, NUM1 + NUM1 + NUM2 + NUM2+1);//将cTempBuf中的一条记录写入ofile		
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