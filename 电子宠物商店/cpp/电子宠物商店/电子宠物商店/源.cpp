/*������̣�
1.1��9��1�հ汾����
ʵ�֣� ��������
1.2��9��2�հ汾����
��ӣ�����״̬��ʾ�����麯��ʵ�ֶ�����������or��ʳ�ȣ�����仯���������ֵ�仯�������䲻ͬ��
            �����۳���ȱ��ѭ������ķ����������³�
���ԣ������浵����
1.3��9��3�հ汾����
���ƣ� �����浵���ܣ���������ʱ�޷���������;�����ָ�����⣻���ڲ�ǰ�����⣻���䱩�����⣻
��ӣ� ҳ��˵�����ƣ���������淨��*/
#include<iostream>
#include<string>
#include<time.h>
#include<Windows.h>
#include<stdlib.h>
#include<fstream>
#include <iomanip>

#define CMD_COLS 80//��Ļ����
#define CMD_LINES 25
using namespace std;
string keep[12];//����浵��Ϣ
/*-------------------------------------���Ƿָ���--------------------------------------------------------------------------*/
//����˵��
void instruction()
{
    cout << "-------------------------------------------------------------------------------" << endl;
    cout << "��Ϸ˵����" << endl;
    cout << endl;
    cout << "      ��Ϸ���㽫����һ��Ϊ����������ϰ�򹤵ĵ�Ա��" << endl;
    cout << "��Ա����Ϊ�����׬Ǯ��ÿ������һֻ���" << endl;
    cout << "��ֻ���ｫ��Ϊ�����ӡ���������ڼ�Ϊ������ṩ�۳����̵����棬ֱ����������" << endl;
    cout << "���������������³�����������Ա������������Ϸ����������ѡ��ʹ�ö�����ʽ�ؿ�����" << endl;
    cout << endl;
    cout << "-------------------------------------------------------------------------------" << endl;
    cout << "����˵����" << endl;
    cout << endl;
    cout << "ÿ��ʱ�����Ϊ���˵�������5���ж��㣬δʹ�ÿ��Դ浽��һ��ʱ��Σ���ʼ��10�㡣" << endl;
    cout << endl;
    cout << "���ж����൱��ʱ(���͹��ȶ����������������ϰ����)������bad ending������������" << endl;
    cout << endl;
    cout << "ÿ��������ʱ��Σ�����Խ���9�������" << endl;
    cout << endl;
    cout << "1.ιʳ 2.ιˮ 3.���� 4.��ˣ 5.������� 6.���� 7.���۳����� 8.ɶҲ���� 9.ѡ��˵�" << endl;
    cout << endl;
    cout << "�ж����Ӧ�����ģ�ιʳ-5��ιˮ-3������-5����ˣ-5" << endl;
    cout << endl;
    cout << "������ֵ���ڿ�ֵ�൱�ߣ����߽���ָ���൱�͵�ʱ�򣬻����bad ending������������" << endl;
    cout << endl;
    cout << "���������䵽����������ʱ������happy ending���������ޣ�" << endl;
    cout << endl;
    cout << "�����ͨ��������������һ���Ͷ����߳��۳�������ȡ��Ǯ" << endl;
    cout << endl;
    cout << "��һֻ�����������޻����������ѡ���˳������������һֻ" << endl;
    cout << endl;
    cout << "���������˳�����û�н�Ǯ������һֻ����ʱ��Ϸ����" << endl;
    cout << endl;
    cout << "�����ͨ��ѡ��˵��˳���Ϸ�򴢴����" << endl;
    cout << endl;
    cout << "���ѣ���ͬ�������Գ��������ͽ���ֵ����Ӱ���Ŷ��" << endl;
    cout << endl;
    cout << "�ڲ�ͬ�����н��и���������������������磺���츧��������ֵ��˫��Ŷ����" << endl;
    cout << endl;
    cout << "-------------------------------------------------------------------------------" << endl;
}
//�����Ļ
void ClearScreen()
{
    system("cls");
}

//���ô�������
void SetSysCaption(const char* pText)
{
    char sysSetBuf[80];
    sprintf(sysSetBuf, "title %s", pText);
    system(sysSetBuf);
}

//������Ļ��ʾ
void SetScreenGrid()
{
    char sysSetBuf[80];
    sprintf(sysSetBuf, "mode con cols=%d lines=%d", CMD_COLS, CMD_LINES);
    system(sysSetBuf);
}

//��ʾ���˵�
void ShowRootMenu()
{
    cout << setw(45);
    cout << "======���ӳ����̵�ϵͳ======" << endl;
    cout << setw(35);
    cout << "1.�µ���Ϸ" << endl;
    cout << setw(35);
    cout << "2.��ȡ�浵" << endl;
    cout << setw(35);
    cout << "3.��Ϸָ��" << endl;
    cout << setw(35);
    cout << "4.�˳�ϵͳ" << endl;
    cout << setw(45);
    cout << "==�γ�==-by������֮-==���==" << endl;
}

//�û�ѡ��
int GetSelect()
{
    char buf[256];
    gets_s(buf);
    return atoi(buf);
}

//�˳�ϵͳ
int quit()
{
    int t = 1;
    for (int i = 1; i < 100; i++)
    {
        cout << "\n\n\t\t\t\t��лʹ�õ��ӳ���ϵͳ�������˳�" << endl;
        for (int m = 1; m <= t; m++)
        {
            printf(".");
        }
        if (t == 8)
        {
            t = 1;
        }
        t++;
        for (int n = 0; n < 30000; n++);
        ClearScreen();
    }
    exit(0);
    return 0;
}

//���ò���ʾ����
int remake_weather()
{
    int w;
    srand((unsigned)time(0));
    w = rand() % 5;
    switch (w)
    {
    case 0:
        cout << "��������" << endl;
        break;
    case 1:
        cout << "��������" << endl;
        break;
    case 2:
        cout << "����������" << endl;
        break;
    case 3:
        cout << "������С��" << endl;
        break;
    case 4:
        cout << "����������" << endl;
        break;
    }
    return w;
}

//��ֵ����ʾʱ��
void remak_time(int t)
{
    switch (t)
    {
    case 0:cout << "#�糿#" << endl;
        break;
    case 1:cout << "#����#" << endl;
        break;
    case 2:cout << "#����#" << endl;
        break;
    }
}

//��ȡ��ʼ
int R_start();

//�˵��ж�ȡ
int M_r_start();

//��ʼ����
int S_start();
/*-------------------------------------���Ƿָ���--------------------------------------------------------------------------*/
//�û���
class User
{
public:
    int money;//�û������
    string m_name;  //�û�����
public:
    void Id();//�û���Ϣע��
    User(int m = 0)
    {
        money = m;
    }
    void set_money()
    {
        money = 300;
    }
};
void User::Id()
{
    cout << "-------------------------------------------------------------------------------" << endl;
    cout << "ע���û���Ϣ" << endl;
    cout << "Name:";
    cin >> m_name;
    cout << "ע����ɣ�" << endl;
    cout << "������300ö���" << endl;
    set_money();
    cout << "-------------------------------------------------------------------------------" << endl;
    system("pause");
}

/*-------------------------------------���Ƿָ���--------------------------------------------------------------------------*/
//��������
class Owner:public User
{
public:
    int select_t=0; //ѡ��ĳ�����
    string name;//����   
public:
    void choose(int sel);//����
    int ready();//ѡ�������ĳ���
};
int Owner::ready()
{
    int a;
    cout << "���̵껹�����³���ɹ�ѡ��1������($50)  2��è����($50)  3������($80)" << endl;
    cout << "��ѡ��һ����Ϊ��ĳ���ɣ�";
    cin >> select_t;
    //���ó����̵�ĺ���
    choose(select_t);
    cout << "����ĳ���������ְɣ�";
    cin >> name;
    cout << "���Ѿ��ɹ�������һֻ����" << name << "�ĳ���" << endl;
    cout << "���Ƿ�Ҫ�鿴����˵���أ� 1���� 2����" << endl;
    cout << "��ѡ��";
    cin >> a;
    if (a == 1)
        instruction();
    system("pause");
    return select_t;
}

void Owner::choose(int sel)
{
    switch (sel)
    {
    case 1:
        cout << "��ϲ�����Ѿ�������һֻ����" << endl;
        cout << "-------------------------------------------------------------------------------" << endl;
        cout << " \ )" << endl;
        cout << "/ /                |\\" << endl;
        cout << "/ /     . - `````-. / ^ `-." << endl;
        cout << "\ \ / \_ / { | } `o" << endl;
        cout << "\ \ / .-- - .   \\ _, --'" << endl;
        cout << " \/   /     \, \(`^ ^ ^" << endl;
        cout << " \   \ / \      (\)" << endl;
        cout << "\) \) \ )" << endl;
        cout << ") / __ \__  ) (\ \___" << endl;
        cout << "(___)))__))(__))(__)))" << endl;
        cout << "-------------------------------------------------------------------------------" << endl;
        money = money - 50;
        cout << "ʣ���ң�" << money << endl;
        break;
    case 2:
        cout << "��ϲ�����Ѿ�������һֻè����" << endl;
        cout << "-------------------------------------------------------------------------------" << endl;
        cout << "���ܣߣߨq�q�q�q�q�ߣߣ���" << endl;
        cout << "��������������������������" << endl;
        cout << "��������������������������" << endl;
        cout << "�����񡡡������������񡡩�" << endl;
        cout << "���ԡ����t�ЩЩШs�����ԩ�" << endl;
        cout << "�����������t���s����������" << endl;
        cout << "�t�����Уϡ������ϩС����s" << endl;
        cout << "-------------------------------------------------------------------------------" << endl;
        money = money - 50;
        cout << "ʣ���ң�" << money << endl;
        break;
    case 3:
        cout << "��ϲ�����Ѿ�������һֻ����" << endl;
        cout << "-------------------------------------------------------------------------------" << endl;
        cout << ".-- - . .---------- -" << endl;
        cout << "/ \ __ / ------" << endl;
        cout << "/ / \() / ---- -" << endl;
        cout << "////// ' \/ ` ---" << endl;
        cout << "//// / // : : --- " << endl;
        cout << "// / / /` '-- " << endl;
        cout << "// //..\\ " << endl;
        cout << "============ = UU====UU====" << endl;
        cout << "'//||\\` " << endl;
        cout << "''``" << endl;
        cout << "-------------------------------------------------------------------------------" << endl;
        money = money - 80;
        cout << "ʣ���ң�" << money << endl;
        break;
    }
}

/*-------------------------------------���Ƿָ���--------------------------------------------------------------------------*/
//����������
class Pet:public Owner
{
public:
    int step;//����
    int age;//����
    int hunger;//��ʳ��
    int thirst;//��ˮ��
    int mood;//�����
    int fitness;//����ָ��
    int offspring;//�����
    int date;//��������
public:
    Pet(int a = 0, int st = 10, int h = 10, int t = 10, int  m = 10, int f = 10, int o = 0,int d=0)
    {
        age = a;
        step = st;
        hunger = h;
        thirst = t;             
        mood = m;         
        fitness = f;      
        offspring = o;
        date = d;
    }
    void hname();
    int get_age() { return age; }
    int get_hunger() { return hunger; }
    int get_thirst() { return thirst; }
    int get_mood() { return mood; }
    int get_fitness() { return fitness; }
    int get_step() { return step; }
    void change();           //�����ʡ�������ʱ��仯�ĺ���
    void show();               //ÿ��ֵ����ʾ����
    void feed();               //ιʳ
    void drink();               //ιˮ
    void touch(int w);             //����
    virtual void play(int w)=0;      //��ˣ�����麯����
    virtual void work(int w)=0;    //����򹤣����麯����
    void doctor(int w);            //��ҽ��
    virtual void birth()=0;                        //��������麯����
    int emergency(int w);   //����״̬����
    virtual int getl()=0;              //��ȡ����ֵ
    virtual int action(int act, int w, int emg)=0 {}; //���˵ĸ��ֶ��������麯����

    int menu();//ѡ��˵�
    void Save_game();//����
    void Load_game();//��ȡ
};

void Pet::hname()
{
    cout << "Ϊ����³�ȡ�����ְɣ�" << endl;
    cin >> name;
}

void Pet::change()
{
    int m;
    m = rand() % 20;
    if (m < 5)
        mood = mood - 2;
    else if (m < 10)
        mood--;
    else
        mood++;
    age++;
    hunger--;
    thirst--;
    int x = rand() % 10;
    if (age > 5 && x <= 3)
    {
        offspring++;
    }
}

inline void Pet::show()
{
    cout << "*******************************" << endl;
    cout << name<<"���ڵ�״̬��" << endl;
    cout << "��" << money << endl;
    cout << "���䣺" << age << endl;
    cout << "��ʳ�ȣ�" << hunger << endl;
    cout << "��ˮ�ȣ�" << thirst << endl;
    cout << "����ȣ�" << mood << endl;
    cout << "����ָ����" << fitness << endl;
    cout << "���������" << offspring << endl;
    cout << "*******************************" << endl;
}

inline void Pet::feed()
{
    int n;
    step = step - 4;
    mood++;
    thirst--;
    cout << endl;
    cout << "�����Ͷι��ʳ���У�" << endl;
    cout << "1.(>^��^<)����ͨ��ʳ��($5)   2.����($15)    3.Ӫ���ײ�($20)    4.�����Ʊ�����($30)" << endl;
    cout << "��ѡ��";
    cin >> n;
    switch (n)
    {
    case 1:
        money = money - 5;
        hunger =hunger+2;
        cout << "*******************************" << endl;
        cout << "̫�ó�����лл���ˡ�" << endl;
        cout << "*******************************" << endl;
        cout << "��������" << money << endl;
        system("pause");
        break;
    case 2:
        money = money - 15;
        hunger = hunger + 4;
        cout << "*******************************" << endl;
        cout << "Ӫ������ż���" << endl;
        cout << "*******************************" << endl;
        cout << "��������" << money << endl;
        system("pause");
        break;
    case 3:
        money = money - 20;
        hunger = hunger + 5;
        cout << "*******************************" << endl;
        cout << "�ۣ������ը���ˣ�" << endl;
        cout << "*******************************" << endl;
        cout << "��������" << money << endl;
        system("pause");
        break;
    case 4:
        money = money - 30;
        hunger = hunger + 10;
        cout << "*******************************" << endl;
        cout << "�������䣡����" << endl;
        cout << "*******************************" << endl;
        cout << "��������" << money << endl;
        system("pause");
        break;
    }
}

inline void Pet::drink()
{
    step = step - 3;
    int n;
    cout << endl;
    cout << "�����Ͷι��ʳ���У�" << endl;
    cout << "1.���׿�($0)   2.��Ȫˮ($2)    3.����($3)    4.����ũ����ȭ($10)" << endl;
    cout << "��ѡ��";
    cin >> n;
    switch (n)
    {
    case 1:
        thirst ++;
        cout << "*******************************" << endl;
        cout << "���˹��ˡ�" << endl;
        cout << "*******************************" << endl;
        cout << "��������" << money << endl;
        system("pause");
        break;
    case 2:
        money = money - 20;
        thirst = thirst + 2;
        cout << "*******************************" << endl;
        cout << "���˹��˹���" << endl;
        cout << "*******************************" << endl;
        cout << "��������" << money << endl;
        system("pause");
        break;
    case 3:
        money = money - 35;
        thirst = thirst + 5;
        mood = mood + 5;
        fitness--;
        cout << "*******************************" << endl;
        cout << "�ֶֶֶֶֶֶ�(*^��^*)" << endl;
        cout << "*******************************" << endl;
        cout << "��������" << money << endl;
        system("pause");
        break;
    case 4:
        money = money - 10;
        thirst = thirst + 10;
        mood++;
        cout << "*******************************" << endl;
        cout << "��������һ������ˮ" << endl;
        cout << "*******************************" << endl;
        cout << "��������" << money << endl;
        system("pause");
        break;
    }
}

inline void Pet::touch(int w)
{
    step = step - 3;
    switch (w)
    {
    case 0:
        mood = mood + 2;
        cout << "*******************************" << endl;
        cout << "(�ݡ��)�������" << endl; 
        cout << "*******************************" << endl;
        system("pause");
        break;
    case 1:
        mood++;
        cout << "*******************************" << endl;
        cout << "��(^o^)��" << endl;
        cout << "*******************************" << endl;
        system("pause");
        break;
    case 2:
        mood++;
        cout << "*******************************" << endl;
        cout << "*^__^*" << endl;
        cout << "*******************************" << endl;
        system("pause");
        break;
    case 3:
        mood++;
        thirst--;
        cout << "*******************************" << endl;
        cout << "��ʪ(*>�n<*)" << endl;
        cout << "*******************************" << endl;
        system("pause");
        break;
    case 4:
        mood--;
        hunger--;
        cout << "*******************************" << endl;
        cout << "����������������������@_@" << endl;
        cout << "*******************************" << endl;
        system("pause");
        break;
    }
}

inline void Pet::doctor(int w)
{
    int a;
    step = step - 6;
    cout << endl;
    cout << "1����ҩ��-$20��  2�����루-$30��  3�����Σ�-$40��" << endl;
    cout << "��ѡ��";
    cin >> a;
    switch (a)
    {
    case 1:
        money = money - 20;
        mood--;
        fitness = fitness + 2;
        cout << "*******************************" << endl;
        cout << "�ÿడ><��" << endl;
        cout << "*******************************" << endl;
        cout << "��������" << money << endl;
        system("pause");
        break;
    case 2:
        money = money - 30;
        mood=mood-2;
        fitness = fitness + 4;
        cout << "*******************************" << endl;
        cout << "����ݩn�ܡ�" << endl;
        cout << "*******************************" << endl;
        cout << "��������" << money << endl;
        system("pause");
        break;
    case 3:
        money = money - 40;
        fitness = fitness + 8;
        hunger--;
        thirst--;
        cout << "*******************************" << endl;
        cout << "��ˮ�õÿ찡~.~��" << endl;
        cout << "*******************************" << endl;
        cout << "*��" << money << endl;
        system("pause");
        break;
    }
}

inline int Pet::emergency(int emg)
{
    step = step + 5;
    if (emg == 20)
    {
        fitness--;
        cout << endl;
        cout << "!!!���С����������" << endl;
        system("pause");
    }

    if (hunger <= 3 && hunger > 0)
    {
        mood--;
        cout << endl;
        cout << "!!!���ˣ����Ѿ��ܶ��ˡ�" << endl;
        system("pause");
    }
    if (hunger >= 10 && hunger < 12)
    {
        mood--;
        cout << endl;
        cout << "!!!���ˣ����Ѿ��ܱ��ˡ�" << endl;
        system("pause");
    }
    if (hunger <= 0 && hunger > -2)
    {
        mood = mood - 2;
        fitness--;
        cout << endl;
        cout << "!!!�ٲ����ҳԶ������ҾͶ�������" << endl;
        system("pause");
    }
    if (hunger >= 12)
    {
        mood = mood - 2;
        fitness--;
        cout << endl;
        cout << "!!!�ٸ��ҳԶ������Ҿ�Ҫ��������" << endl;
        system("pause");
    }
    if (thirst > -1 && thirst < 0)
    {
        mood--;
        cout << endl;
        cout << "���ˣ��Һÿʡ�" << endl;
        system("pause");
    }
    if (thirst <= 10 && thirst > 12)
    {
        mood--;
        cout << endl;
        cout << "���ٸ��Һ�ˮ���Ҿ�Ҫ������" << endl;
        system("pause");
    }
    if (thirst <= -1&&thirst>=-2 )
    {
        mood = mood - 2;
        fitness--;
        cout << endl;
        cout << "���˿���Һ�������ԴȪ�ɣ��ҿ��������" << endl;
        system("pause");
    }
    if (thirst >= 12 && thirst < 14)
    {
        fitness--;
        cout << endl;
        cout << "�Ҳ�Ҫ�ٺ�ˮ����" << endl;
        system("pause");
    }
    if (hunger >= 14 || thirst >= 14||hunger<=-4||thirst<=-3)
    {
        age = 100;
        cout << endl;
        cout << "*******************************" << endl;
        cout << "������ɶ�����ˣ�����������" << endl;
        cout << "*******************************" << endl;
        cout << "���ڹ������ƣ����Ѿ���а������ϰ忪������game over��" << endl;
        system("pause");
        cout << "�������������������һ����Ǹ��ң�ż�������Σ�" << endl;
        cout << "Ȼ�󣬿�ʼ�ո�һ�յı�������û���������ĳ����" << endl;
        cout << "�Ҳ����˽⣬������绹��������һ���㣬ֻ���������˻�ζ��Ҳֻ�������������" << endl;
        cout << "�������������������Ҳ������ţ���һ���˿��԰ٿ����ᣬ��һ����һ��ʶ�;�����ܰ��" << endl;
        system("pause");
        return 2;
    }
    if (fitness < -6)
    {
        cout << endl;
        cout << "��ɰ��ĳ��￴�������һ�ۣ������ص����ˡ�" << endl;
        cout << "���ڹ������ƣ����Ѿ���а������ϰ忪����(game over)" << endl;
        system("pause");
        cout << "һֱ��Ϊ�Ҹ���Զ�����ڿ���׷���δ����" << endl;
        cout << "�����ŷ��֣���Щӵ�������ˣ��չ����֡������ĸ衢�������ᡢ" << endl;
        cout << "�������ˡ���ν�������������Ҹ�����������ҹ�˵���Ļ���" << endl;
        cout << "����ĵ绰��˼������ˡ����������ᡭ�������Ļ򿴲����ĸж���" << endl;
        cout << "���Ƕ���������Ȼ����ʱ��Ĵ����У�һ�г�Ϊ�����㣡" << endl;
        system("pause");
        return 2;
    }
    return 0;
}

int  Pet::menu()
{
    cout << "****ѡ��˵�****" << endl;
    cout << "1.�淨˵��" << endl;
    cout << "2.����" << endl;
    cout << "3.��ȡ" << endl;
    cout << "4.�˳������˵�" << endl;
    cout << "5.�˳���ϵͳ" << endl;
    cout << "*****************" << endl;
    int k;
    cin >> k;
    switch (k)
    {
    case 1:
        ClearScreen();
        instruction();
        system("pause");
        break;
    case 2:
        ClearScreen();
        Save_game();
        system("pause");
        break;
    case 3:
        ClearScreen();
        Load_game();
        break;
    case 4:
        ClearScreen();
        return 3;
        break;
    case 5:
        ClearScreen();
        quit();
        break;
        ClearScreen();
    }
    return 0;//���÷���ֵ�����˳�ѭ��
}

void Pet::Save_game()
{
    int ca;
    cout << "******�˵�******" << endl;
    cout << "��ѡ��浵λ��" << endl;
    cout << "1          or           2" << endl;
    cout << "*****************" << endl;
    cin >> ca;
    ofstream file;
    switch (ca)
    {
    case 1:
        file.open("�浵1.txt");
        if (!file)
        {
            cout << "*�浵�ļ���������ϵ������" << endl;
            break;
        }
        //һ��һ�����ݣ������ȡ
        file << m_name << '\n' << money << '\n' << select_t << '\n' <<name << '\n' << date << '\n' << step << '\n'
            << age << '\n' << hunger << '\n' << thirst << '\n' << mood << '\n' << fitness << '\n' << offspring << endl;
        file.close();
            break;
    case 2:
        file.open("�浵2.txt");
        if (!file)
        {
            cout << "*�浵�ļ���������ϵ������" << endl;
            break;
        }
        file << m_name << '\n' << money << '\n' <<select_t << '\n' <<name << '\n' <<date<< '\n' << step << '\n' 
            << age << '\n'<< hunger << '\n' << thirst << '\n' << mood << '\n' << fitness << '\n' << offspring << endl;
        file.close();
    }
}

void Pet::Load_game()
{
    int ca;
    cout << "******�˵�******" << endl;
    cout << "��ѡ��浵��ȡ" << endl;
    cout << "1          or           2" << endl;
    cout << "*****************" << endl;
    cin >> ca;
    string temp;
    ifstream file;
    int i=0;
    switch (ca)
    {
    case 1:
        file.open("�浵1.txt");
        if (!file)
        {
            cout << "*�浵�ļ���������ϵ������" << endl;
            break;
        }
        while (getline(file, temp))
        {
            keep[i] = temp;
            i++;
        }
        file.close();
        R_start();
        break;
    case 2:
        file.open("�浵2.txt");
        if (!file)
        {
            cout << "*�浵�ļ���������ϵ������" << endl;
            break;
        }
        while (getline(file, temp))//�����ݶ��������keep��
        {
            keep[i] = temp;
            i++;
        }
        file.close();
        R_start();
        break;
    }
}

/*-------------------------------------���Ƿָ���--------------------------------------------------------------------------*/
//������Ĺ���
class Dog :public Pet
{
private:
    int life;
public:
    Dog(int l = 30)
    {
        life = l;
    }
    int getl()
    {
        return life;
    }
    void play(int w) ;      //��ˣ
    void work(int w) ;    //�����
    void birth() ;         //���
    int action(int act, int w, int emg);  //���˵Ķ�������
};

inline int Dog::action(int act, int w, int emg)
{
    int k = 0;
    switch (act)
    {
    case 1:
        feed();
        break;
    case 2:
        drink();
        break;
    case 3:
        touch(w);
        break;
    case 4:
        play(w);
        break;
    case 5:
        work(w);
        break;
    case 6:
        doctor(w);
        break;
    case 7:
        birth();
        break;
    case 8:
        break;
    case 9:
        ClearScreen();
        k = menu();
        if (k == 3)
            return 3;
        system("pause");
        break;
        ClearScreen();
    }
    return 0;
}

void Dog::play(int w)
{
    int a;
    step = step - 2;
    hunger--;
    thirst--;
    cout << endl;
    cout << "*��������Ҫ��������Ĺ��ӣ�" << endl;
    cout << "1.ɢ�� 2.�ӷ��� 3.���� 4.���" << endl;
    cin >> a;
    switch (a)
    {
    case 1:
        cout << "*******************************" << endl;
        cout << "yeah!" << endl;
        cout << "*******************************" << endl;
        mood++;
        break;
    case 2:
        cout << "*******************************" << endl;
        cout << "yeah!yeah!" << endl;
        cout << "*******************************" << endl;
        mood = mood + 2;
        break;
    case 3:
        cout << "*******************************" << endl;
        cout << "yeah!yeah!yeah!" << endl;
        cout << "*******************************" << endl;
        mood = mood + 3;
        break;
    case 4:
        cout << "*******************************" << endl;
        cout << "yeah!yeah!yeah!yeah!" << endl;
        cout << "*******************************" << endl;
        mood = mood + 4;
        break;
    }
    switch (w)
    {
    case 0:
        mood ++;
        break;
    case 1:
        break;
    case 2:
        break;
    case 3:
        break;
    case 4:
        hunger--;
        thirst--;
        fitness--;
        break;
    }
}

void Dog::work(int w)
{
    int a;
    step = step - 3;
    mood --;
    hunger = hunger - 2;
    thirst = thirst - 2;
    cout << "*******************************" << endl;
    cout << "���ˣ��ҿ���Ϊ��׬ȡ���Ŷ��" << endl;
    cout << "*******************************" << endl;
    cout << " 1����ƿ�ӣ�+$20�� 2�����һ�Ժ��+$30�� 3����äȮ��+$60)" << endl;
    cout << "��ѡ�����Ĵ����ͣ�";
    cin >> a;
    switch (a)
    {
    case 1:
        money = money + 20;
        cout << "�װ������ˣ��������������һ�����棬����ա�" << endl;
        cout << "------------��" << money << endl;
        break;
    case 2:
        money = money + 30;
        cout << "����Ҳ��Ŭ���򹤵�һ�졣" << endl;
        cout << "------------��" << money << endl;
        break;
    case 3:
        money = money + 60;
        cout << "����äȮ����Ŷ�����ˡ�" << endl;
        cout << "------------��" << money << endl;
        break;
    }
    switch (w)
    {
    case 0:
        mood++;
        break;
    case 1:
        break;
    case 2:
        break;
    case 3:
        mood--;
        break;
    case 4:
        hunger--;
        thirst--;
        fitness--;
        break;
    }
}

void Dog::birth()
{
    int n, g;
    cout << "*�����Ƿ��۳�" << name << "�ĺ��" << endl;
    cout << "�ǣ�1��/��2����" << endl;
    cin >> n;
    if (n == 1)
    {
        cout << "*��Ҫ�۳�����С���ӣ�" << "��������ӵ��" << offspring << "����" << endl;
        cin >> g;
        if (g <= offspring && g >= 0)
        {
            money = g * 80;
            cout << "------------��" << money << endl;
        }
        else
            cout << "�����������۳�ʧ��" << endl;
    }
}

//����������
class Parrot :public Pet
{
private:
    int life;
public:
    Parrot(int l = 20)
    {
        life = l;
    }
    int getl()
    {
        return life;
    }
    void play(int w);      //��ˣ
    void work(int w);    //�����
    void birth();         //���
    int action(int act, int w, int emg);  //���˵Ķ�������
};

inline int Parrot::action(int act, int w, int emg)
{
    int k = 0;
    switch (act)
    {
    case 1:
        feed();
        break;
    case 2:
        drink();
        break;
    case 3:
        touch(w);
        break;
    case 4:
        play(w);
        break;
    case 5:
        work(w);
        break;
    case 6:
        doctor(w);
        break;
    case 7:
        birth();
        break;
    case 8:
        break;
    case 9:
        ClearScreen();
        k = menu();
        if (k == 3)
            return 3;
        system("pause");
        break;
        ClearScreen();
    }
    return 0;
}

void Parrot::play(int w)
{
    int a;
    step = step - 2;
    hunger--;
    thirst--;
    cout << endl;
    cout << "*��������Ҫ������������ģ�" << endl;
    cout << "1.���� 2.��˵�� 3.���� 4.���ɵķ���" << endl;
    cin >> a;
    switch (a)
    {
    case 1:
        cout << "*******************************" << endl;
        cout << "yeah!" << endl;
        cout << "*******************************" << endl;
        mood++;
        break;
    case 2:
        cout << "*******************************" << endl;
        cout << "yeah!yeah!" << endl;
        cout << "*******************************" << endl;
        mood = mood + 2;
        break;
    case 3:
        cout << "*******************************" << endl;
        cout << "yeah!yeah!yeah!" << endl;
        cout << "*******************************" << endl;
        mood = mood + 3;
        break;
    case 4:
        cout << "*******************************" << endl;
        cout << "yeah!yeah!yeah!yeah!" << endl;
        cout << "*******************************" << endl;
        mood = mood + 4;
        break;
    }
    switch (w)
    {
    case 0:
        mood++;
        break;
    case 1:
        break;
    case 2:
        break;
    case 3:
        break;
    case 4:
        hunger--;
        thirst--;
        fitness--;
        break;
    }
}

void Parrot::work(int w)
{
    int a;
    step = step - 3;
    mood--;
    hunger = hunger - 2;
    thirst = thirst - 2;
    cout << "*******************************" << endl;
    cout << "���ˣ��ҿ���Ϊ��׬ȡ���Ŷ��" << endl;
    cout << "*******************************" << endl;
    cout << " 1�������ͣ�+$30�� 2������ѧ�ࣨ+$40�� 3��ѧ�̰�˿���裨+$100)" << endl;
    cout << "��ѡ�����Ĵ����ͣ�";
    cin >> a;
    switch (a)
    {
    case 1:
        money = money + 20;
        cout << "�װ������ˣ����ĸ��������һ�����棬����ա�" << endl;
        cout << "------------��" << money << endl;
        break;
    case 2:
        money = money + 30;
        cout << "����Ҳ��Ŭ���򹤵�һ�졣" << endl;
        cout << "------------��" << money << endl;
        break;
    case 3:
        money = money + 60;
        cout << "����������Ŷ�����ˡ�" << endl;
        cout << "------------��" << money << endl;
        break;
    }
    switch (w)
    {
    case 0:
        mood++;
        break;
    case 1:
        break;
    case 2:
        break;
    case 3:
        mood--;
        break;
    case 4:
        hunger--;
        thirst--;
        fitness--;
        break;
    }
}

void Parrot::birth()
{
    int n, g;
    cout << "*�����Ƿ��۳�" << name << "�ĺ��" << endl;
    cout << "�ǣ�1��/��2����" << endl;
    cin >> n;
    if (n == 1)
    {
        cout << "*��Ҫ�۳�����С���ģ�" << "��������ӵ��" << offspring << "����" << endl;
        cin >> g;
        if (g <= offspring && g >= 0)
        {
            money = g * 100;
            cout << "------------��" << money << endl;
        }
        else
            cout << "�����������۳�ʧ��" << endl;
    }
}

//�������è����
class Cat :public Pet
{
private:
    int life;
public:
    Cat(int l = 30)
    {
        life = l;
    }
    int getl()
    {
        return life;
    }
    void play(int w);      //��ˣ
    void work(int w);    //�����
    void birth();         //���
    int action(int act, int w, int emg);  //���˵Ķ�������
};

inline int Cat::action(int act, int w, int emg)
{
    int k = 0;
    switch (act)
    {
    case 1:
        feed();
        break;
    case 2:
        drink();
        break;
    case 3:
        touch(w);
        break;
    case 4:
        play(w);
        break;
    case 5:
        work(w);
        break;
    case 6:
        doctor(w);
        break;
    case 7:
        birth();
        break;
    case 8:
        break;
    case 9:
        ClearScreen();
        k=menu();
        if (k == 3)
            return 3;
        system("pause");
        break;
        ClearScreen();
    }
    return 0;
}

void Cat::play(int w)
{
    int a;
    step = step - 2;
    hunger--;
    thirst--;
    cout << endl;
    cout << "*��������Ҫ���������è���ӣ�" << endl;
    cout << "1.ɢ�� 2.��ë���� 3.è������ 4.���ɻ" << endl;
    cin >> a;
    switch (a)
    {
    case 1:
        cout << "*******************************" << endl;
        cout << "yeah!" << endl;
        cout << "*******************************" << endl;
        mood++;
        break;
    case 2:
        cout << "*******************************" << endl;
        cout << "yeah!yeah!" << endl;
        cout << "*******************************" << endl;
        mood = mood + 2;
        break;
    case 3:
        cout << "*******************************" << endl;
        cout << "yeah!yeah!yeah!" << endl;
        cout << "*******************************" << endl;
        mood = mood + 3;
        break;
    case 4:
        cout << "*******************************" << endl;
        cout << "yeah!yeah!yeah!yeah!" << endl;
        cout << "*******************************" << endl;
        mood = mood + 4;
        break;
    }
    switch (w)
    {
    case 0:
        mood++;
        break;
    case 1:
        break;
    case 2:
        break;
    case 3:
        break;
    case 4:
        hunger--;
        thirst--;
        fitness--;
        break;
    }
}

void Cat::work(int w)
{
    int a;
    step = step - 3;
    mood--;
    hunger = hunger - 2;
    thirst = thirst - 2;
    cout << "*******************************" << endl;
    cout << "�����ޣ��ҿ���Ϊ��׬ȡ��ҡ�" << endl;
    cout << "*******************************" << endl;
    cout << " 1�������ͣ�+$20�� 2��ץ����+$30�� 3��ץ�㣨+$60)" << endl;
    cout << "��ѡ�����Ĵ����ͣ�";
    cin >> a;
    switch (a)
    {
    case 1:
        money = money + 20;
        cout << "�װ������ˣ��������������һ�����棬����ա�" << endl;
        cout << "------------��" << money << endl;
        break;
    case 2:
        money = money + 30;
        cout << "����Ҳ��Ŭ���򹤵�һ�졣" << endl;
        cout << "------------��" << money << endl;
        break;
    case 3:
        money = money + 60;
        cout << "�������Ŷ�����ˡ�" << endl;
        cout << "------------��" <<money << endl;
        break;
    }
    switch (w)
    {
    case 0:
        mood++;
        break;
    case 1:
        break;
    case 2:
        break;
    case 3:
        mood--;
        break;
    case 4:
        hunger--;
        thirst--;
        fitness--;
        break;
    }
}

void Cat::birth()
{
    int n, g;
    cout << "*�����Ƿ��۳�" << name << "�ĺ��" << endl;
    cout << "�ǣ�1��/��2����" << endl;
    cin >> n;
    if (n == 1)
    {
        cout << "*��Ҫ�۳�����С���ӣ�" << "��������ӵ��" << offspring << "����" << endl;
        cin >> g;
        if (g <= offspring && g >= 0)
        {
            money = g * 80;
            cout << "------------��" << money << endl;
        }
        else
            cout << "�����������۳�ʧ��" << endl;
    }
}

/*-------------------------------------���Ƿָ���--------------------------------------------------------------------------*/
//��ʼ����
int S_start()
{
    Owner me;
    Pet* petx=NULL;
    me.Id();//ע��
    ClearScreen();
    int sel=me.ready();//����
    ClearScreen();
    me.choose(sel);//�����̵�
    ClearScreen();
    int life, date, w, act;
    int t = 0;
    int step, age, emg;
    cout << endl;
    cout << "��ʼ��������" << endl;
    cout << "-------------------------------------------------------------------------------" << endl;
    cout << endl;
    switch (sel)
    {
    case 1:
        petx = new Dog;
        break;
    case 2:
        petx = new Cat;
        break;
    case 3:
        petx = new Parrot;
        break;
    }
    petx->m_name = me.m_name;//��ֵ
    petx->money = me.money;
    petx->name = me.name;
    petx->select_t = sel;
    life = petx->getl();           //��ȡ����
    for (date = 1; date <= life; date++)
    {
        cout << "�������������ĵ�" << date << "��" << endl;
        petx->date = date;//����date���Զ���
        w = remake_weather();                  //������������
        t = t % 3;                  //t�ǿ���ʱ������
        petx->change();            //״̬�ı亯��
        while (t < 3)
        {
            int amn=0;
            emg = rand() % 20;      //�����Ƿ�����
            cout << "������";
            remak_time(t);
            step = petx->get_step();  //��ȡ�ж���
            cout << endl;
            cout << "����ж��������У�" << step << endl;
            cout << "��ĳ���";
            petx->show();
            if ((emg - 19) == 1)
                cout << "����״��������" << endl;
            else
                cout << "����״��������" << endl;
            cout << "��ѡ�����������£�" << endl;
            cout << "1.ιʳ 2.ιˮ 3.���� 4.��ˣ 5.������� 6.���� 7.���۳����� 8.ɶҲ���� 9.ѡ��˵�" << endl;;
            cout << "��ѡ��";
            cin >> act;
            int ooop = 0;
            ooop=petx->action(act, w, emg);
            if (ooop== 3)
                return 2;
           amn= petx->emergency(emg);
           if (amn == 2)
               break;
            age = petx->get_age();
            if (age > life)
            {
                cout << "------------------------------------------------------" << endl;
                cout << "��Ǹ�������������ƣ����Ѿ����������ϰ���ˡ�" << endl;
                cout << "------------------------------------------------------" << endl;
                return 2;
            }
            if (step < 0)
            {
                cout << "------------------------------------------------------" << endl;
                cout << "����Ϊ����������۲��������������ϰ���ˡ�" << endl;
                cout << "------------------------------------------------------" << endl;
                return 2;
            }                      //��������������
            t++;
            cout << "------------------------------------------------------" << endl;
        }
        if (age > life || step < 0)     //����������������ѭ��
            return 2;
        ClearScreen();
    }
    if (date == life)
    {
        cout << "------------------------------------------------------" << endl;
        cout << "��ϲ����ĳ����Ѿ�����" << endl;
        cout << "��ý�ҽ���+150��" << endl;
        cout << "------------------------------------------------------" << endl;
        petx->money = petx->money + 150;
        petx->Save_game();
        return 1;
    }
}

//��ȡ����������ʼ
int R_start()
{
    int a[3];
    int b[12] = { 0 };
    /*for (int f = 0; f < 12; f++)
    {
        cout << keep[f] << endl;
    }*/
    for (int j = 1; j <= 2; j++)
    {
        const char* c = keep[j].c_str();
        a[j] = atoi(c);
        //cout << a[j] << endl;
    }
    for (int j = 4; j <= 11; j++)
    {
        const char* c = keep[j].c_str();
        b[j] = atoi(c);
       // cout << b[j] << endl;
    }
    int L_date = b[4];
    int life,date,w, act;
    date = L_date;
    int t = 0;
    int step, age, emg;
    int sel = a[2];
    //cout << b[4] << endl;
    cout << endl;
    cout << "������������" << endl;
    cout << "-------------------------------------------------------------------------------" << endl;
    Pet* petx=NULL;
    switch (sel)
    {
    case 1:
        petx = new Dog;
        break;
    case 2:
        petx = new Cat;
        break;
    case 3:
        petx = new Parrot;
        break;
    }
    petx->m_name = keep[0]; petx->money = a[1]; petx->select_t = a[2]; petx->name = keep[3];
    petx->date = b[4]; petx->step = b[5]; petx->age = b[6]; petx->hunger = b[7];
    petx->thirst = b[8]; petx->mood = b[9]; petx->fitness = b[10]; petx->offspring = b[11];
    life = petx->getl();           //��ȡ����
    cout << date << endl;
    for ( date; date <= life; date++)
    {
        cout << "�������������ĵ�" << date << "��" << endl;
        w = remake_weather();                  //������������
        t = t % 3;                  //t�ǿ���ʱ������
        petx->change();            //״̬�ı亯��
        while (t < 3)
        {
            emg = rand() % 20;      //�����Ƿ�����
            cout << "������";
            remak_time(t);
            step = petx->get_step();  //��ȡ�ж���
            cout << endl;
            cout << "����ж��������У�" << step << endl;
            cout << "��ĳ���";
            petx->show();
            if ((emg - 19) == 1)
                cout << "����״��������" << endl;
            else
                cout << "����״��������" << endl;
            cout << "��ѡ�����������£�" << endl;
            cout << "1.ιʳ 2.ιˮ 3.���� 4.��ˣ 5.������� 6.���� 7.���۳����� 8.ɶҲ���� 9.ѡ��˵�" << endl;;
            cout << "��ѡ��";
            cin >> act;
            int ooot = 0;
            ooot = petx->action(act, w, emg);
            if (ooot == 3)
                return 2;
            petx->emergency(emg);
            age = petx->get_age();
            if (age > life)
            {
                cout << "------------------------------------------------------" << endl;
                cout << "��Ǹ�������������ƣ����Ѿ����������ϰ���ˡ�" << endl;
                cout << "------------------------------------------------------" << endl;
                return 2;
            }
            if (step < 0)
            {
                cout << "------------------------------------------------------" << endl;
                cout << "����Ϊ����������۲��������������ϰ���ˡ�" << endl;
                cout << "------------------------------------------------------" << endl;
                return 2;
            }                      //��������������
            t++;
            cout << "------------------------------------------------------" << endl;
        }
        if (age > life || step < 0)     //����������������ѭ��
            return 2;
        ClearScreen();
    }
    if (date == life)
    {
        cout << "------------------------------------------------------" << endl;
        cout << "��ϲ����ĳ����Ѿ�����" << endl;
        cout << "��ý�ҽ���+150��" << endl;
        cout << "------------------------------------------------------" << endl;
        petx->money = petx->money + 150;
        return 1;
    }
}

//�˵��ж�ȡ
int M_r_start()
{
    int k = 0;
    cout << "****ѡ����Ҫ��ȡ�Ĵ浵****" << endl;
    cout << "1/2" << endl;
    cout << "*****************************" << endl;
    int ca;
    cin >> ca;
    string temp;
    ifstream file;
    int i = 0;
    switch (ca)
    {
    case 1:
        file.open("�浵1.txt");
        if (!file)
        {
            cout << "*�浵�ļ���������ϵ������" << endl;
            break;
        }
        while (getline(file, temp))
        {
            keep[i] = temp;
            i++;
        }
        file.close();
        R_start();
        break;
    case 2:
        file.open("�浵2.txt");
        if (!file)
        {
            cout << "*�浵�ļ���������ϵ������" << endl;
            break;
        }
        while (getline(file, temp))
        {
            keep[i] = temp;
            i++;
        }
        file.close();
        k=R_start();
        break;
    }
    return k;
}
/*-------------------------------------���Ƿָ���--------------------------------------------------------------------------*/
//��ѭ��
int main()
{
    SetSysCaption("���ӳ����̵ꡪ���ų���");
    SetScreenGrid();
    int d = 1;
    int m = 1;
    while (1)
    {
        ClearScreen();
        ShowRootMenu();//void ClearScreen()
        switch (GetSelect())
        {
        case 1:
            ClearScreen();
            m = 1;
            while (m == 1)
            {
                //m--;
                m= S_start();
            }
            break;
        case 2:
            ClearScreen();
            d = 1;
            while (d == 1)
            {
                //d--;
                d = M_r_start();
            }
            break;
        case 3:
            ClearScreen();
            instruction();
            system("pause");
            break;
        case 4:
            ClearScreen();
            quit();
            break;
        }
    }
}