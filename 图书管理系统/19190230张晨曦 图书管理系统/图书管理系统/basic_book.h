#ifndef _BASIC_H
#define _BASIC_H
using namespace std;
#define NUM1 128           //ͼ�����ƺͱ����󳤶�
#define NUM2 50           //ͼ�����߼�������󳤶�
class Basic_book //�ṩһ������ͼ����
{
public:
	Basic_book() {}             //�޲ι��췽��	
	Basic_book(char* bName, char* bNumber, char* bTime, char* bAuthor,char br);//�вι��췽��	
	~Basic_book() {}            //��������
public:
	virtual char* GetName();//��ȡͼ������
	virtual void SetName(char* bName);//����ͼ������

	virtual char* GetNumber();//��ȡͼ����	
	virtual void SetNumber(char* bNumber);//����ͼ����	

	virtual char* GetTime();//��ȡͼ���������	
	virtual void SetPrice(char* bTime);//����ͼ���������	

	virtual char* GetAuthor();//��ȡͼ������
	virtual void SetAuthor(char* bAuthor);//����ͼ������

	virtual void Setbor(char a);//��ȡͼ�������Ϣ
	virtual char Getbor();//����ͼ�������Ϣ

	virtual void WriteData();             //д������	
	virtual void DeleteData(int iCount);  //���ϴ���	
	virtual void GetBookFromFile(int iCount);  //���ļ��ж�ȡͼ���¼
protected:
	char m_bName[NUM1];
	char m_bNumber[NUM1];
	char m_bTime[NUM2];
	char m_bAuthor[NUM2];
	char b_r;
}; 

#endif