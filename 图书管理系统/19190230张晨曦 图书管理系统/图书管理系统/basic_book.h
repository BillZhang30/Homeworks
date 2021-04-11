#ifndef _BASIC_H
#define _BASIC_H
using namespace std;
#define NUM1 128           //图书名称和编号最大长度
#define NUM2 50           //图书作者及日期最大长度
class Basic_book //提供一个基础图书类
{
public:
	Basic_book() {}             //无参构造方法	
	Basic_book(char* bName, char* bNumber, char* bTime, char* bAuthor,char br);//有参构造方法	
	~Basic_book() {}            //析构函数
public:
	virtual char* GetName();//获取图书名称
	virtual void SetName(char* bName);//设置图书名称

	virtual char* GetNumber();//获取图书编号	
	virtual void SetNumber(char* bNumber);//设置图书编号	

	virtual char* GetTime();//获取图书入库日期	
	virtual void SetPrice(char* bTime);//设置图书入库日期	

	virtual char* GetAuthor();//获取图书作者
	virtual void SetAuthor(char* bAuthor);//设置图书作者

	virtual void Setbor(char a);//获取图书借阅信息
	virtual char Getbor();//设置图书借阅信息

	virtual void WriteData();             //写入数据	
	virtual void DeleteData(int iCount);  //报废处理	
	virtual void GetBookFromFile(int iCount);  //从文件中读取图书记录
protected:
	char m_bName[NUM1];
	char m_bNumber[NUM1];
	char m_bTime[NUM2];
	char m_bAuthor[NUM2];
	char b_r;
}; 

#endif