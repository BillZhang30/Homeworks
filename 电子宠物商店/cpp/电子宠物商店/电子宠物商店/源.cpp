/*设计历程：
1.1（9月1日版本）：
实现： 基本功能
1.2（9月2日版本）：
添加：特殊状态显示；纯虚函数实现动作；饥饿度or饱食度；心情变化随机化；数值变化各个区间不同；
            产子售出；缺少循环游玩的方法；解锁新宠
调试：读档存档功能
1.3（9月3日版本）：
完善： 读档存档功能；继续饲养时无法读档问题;虚基类指针问题；日期不前进问题；年龄暴涨问题；
添加： 页面菜单等设计；更合理的玩法；*/
#include<iostream>
#include<string>
#include<time.h>
#include<Windows.h>
#include<stdlib.h>
#include<fstream>
#include <iomanip>

#define CMD_COLS 80//屏幕设置
#define CMD_LINES 25
using namespace std;
string keep[12];//保存存档信息
/*-------------------------------------我是分割线--------------------------------------------------------------------------*/
//饲养说明
void instruction()
{
    cout << "-------------------------------------------------------------------------------" << endl;
    cout << "游戏说明：" << endl;
    cout << endl;
    cout << "      游戏中你将扮演一名为宠物店无良老板打工的店员。" << endl;
    cout << "店员负责为宠物店赚钱，每次认领一只宠物。" << endl;
    cout << "这只宠物将作为“种子”在其成年期间为宠物店提供售出幼崽的收益，直到其死亡。" << endl;
    cout << "若因饲养不当导致宠物死亡，店员将被开除，游戏结束（可以选择使用读档方式重开）。" << endl;
    cout << endl;
    cout << "-------------------------------------------------------------------------------" << endl;
    cout << "饲养说明：" << endl;
    cout << endl;
    cout << "每个时间段作为主人的你新增5点行动点，未使用可以存到下一个时间段，初始有10点。" << endl;
    cout << endl;
    cout << "当行动点相当低时(操劳过度而病倒，被无良张老板辞退)，出现bad ending，饲养结束。" << endl;
    cout << endl;
    cout << "每天有三个时间段，你可以进行9项操作：" << endl;
    cout << endl;
    cout << "1.喂食 2.喂水 3.抚摸 4.玩耍 5.宠物外快 6.看病 7.出售宠物后代 8.啥也不干 9.选项菜单" << endl;
    cout << endl;
    cout << "行动点对应的消耗：喂食-5，喂水-3，抚摸-5，玩耍-5" << endl;
    cout << endl;
    cout << "当饥饿值、口渴值相当高，或者健康指数相当低的时候，会出现bad ending，宠物死亡。" << endl;
    cout << endl;
    cout << "当宠物年龄到达寿命极限时，出现happy ending，寿终正寝！" << endl;
    cout << endl;
    cout << "你可以通过宠物外快与宠物一起劳动或者出售宠物后代获取金钱" << endl;
    cout << endl;
    cout << "当一只宠物寿终正寝或死亡你可以选择退出或继续购买下一只" << endl;
    cout << endl;
    cout << "当你主动退出或者没有金钱购买下一只宠物时游戏结束" << endl;
    cout << endl;
    cout << "你可以通过选项菜单退出游戏或储存进度" << endl;
    cout << endl;
    cout << "提醒：不同的天气对宠物的心情和健康值会有影响的哦！" << endl;
    cout << endl;
    cout << "在不同天气中进行抚摸会有特殊情况发生（如：晴天抚摸，心情值加双倍哦）。" << endl;
    cout << endl;
    cout << "-------------------------------------------------------------------------------" << endl;
}
//清除屏幕
void ClearScreen()
{
    system("cls");
}

//设置窗体名称
void SetSysCaption(const char* pText)
{
    char sysSetBuf[80];
    sprintf(sysSetBuf, "title %s", pText);
    system(sysSetBuf);
}

//设置屏幕显示
void SetScreenGrid()
{
    char sysSetBuf[80];
    sprintf(sysSetBuf, "mode con cols=%d lines=%d", CMD_COLS, CMD_LINES);
    system(sysSetBuf);
}

//显示主菜单
void ShowRootMenu()
{
    cout << setw(45);
    cout << "======电子宠物商店系统======" << endl;
    cout << setw(35);
    cout << "1.新的游戏" << endl;
    cout << setw(35);
    cout << "2.读取存档" << endl;
    cout << setw(35);
    cout << "3.游戏指南" << endl;
    cout << setw(35);
    cout << "4.退出系统" << endl;
    cout << setw(45);
    cout << "==课程==-by朝雾曦之-==设计==" << endl;
}

//用户选择
int GetSelect()
{
    char buf[256];
    gets_s(buf);
    return atoi(buf);
}

//退出系统
int quit()
{
    int t = 1;
    for (int i = 1; i < 100; i++)
    {
        cout << "\n\n\t\t\t\t感谢使用电子宠物系统，正在退出" << endl;
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

//重置并显示天气
int remake_weather()
{
    int w;
    srand((unsigned)time(0));
    w = rand() % 5;
    switch (w)
    {
    case 0:
        cout << "天气：晴" << endl;
        break;
    case 1:
        cout << "天气：阴" << endl;
        break;
    case 2:
        cout << "天气：多云" << endl;
        break;
    case 3:
        cout << "天气：小雨" << endl;
        break;
    case 4:
        cout << "天气：暴雨" << endl;
        break;
    }
    return w;
}

//充值并显示时间
void remak_time(int t)
{
    switch (t)
    {
    case 0:cout << "#早晨#" << endl;
        break;
    case 1:cout << "#中午#" << endl;
        break;
    case 2:cout << "#晚上#" << endl;
        break;
    }
}

//读取开始
int R_start();

//菜单中读取
int M_r_start();

//开始饲养
int S_start();
/*-------------------------------------我是分割线--------------------------------------------------------------------------*/
//用户类
class User
{
public:
    int money;//用户金币数
    string m_name;  //用户名字
public:
    void Id();//用户信息注册
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
    cout << "注册用户信息" << endl;
    cout << "Name:";
    cin >> m_name;
    cout << "注册完成！" << endl;
    cout << "你获得了300枚金币" << endl;
    set_money();
    cout << "-------------------------------------------------------------------------------" << endl;
    system("pause");
}

/*-------------------------------------我是分割线--------------------------------------------------------------------------*/
//饲养者类
class Owner:public User
{
public:
    int select_t=0; //选择的宠物编号
    string name;//名字   
public:
    void choose(int sel);//领养
    int ready();//选择领养的宠物
};
int Owner::ready()
{
    int a;
    cout << "本商店还有以下宠物可供选择：1、狗子($50)  2、猫主子($50)  3、鹦鹉($80)" << endl;
    cout << "请选择一个作为你的宠物吧：";
    cin >> select_t;
    //调用宠物商店的函数
    choose(select_t);
    cout << "给你的宠物起个名字吧：";
    cin >> name;
    cout << "你已经成功领养了一只叫做" << name << "的宠物" << endl;
    cout << "你是否要查看饲养说明呢？ 1、是 2、否" << endl;
    cout << "请选择：";
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
        cout << "恭喜，你已经领养了一只狗子" << endl;
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
        cout << "剩余金币：" << money << endl;
        break;
    case 2:
        cout << "恭喜，你已经领养了一只猫主子" << endl;
        cout << "-------------------------------------------------------------------------------" << endl;
        cout << "│＼＿＿╭╭╭╭╭＿＿／│" << endl;
        cout << "│　　　　　　　　　　　│" << endl;
        cout << "│　　　　　　　　　　　│" << endl;
        cout << "│　●　　　　　　　●　│" << endl;
        cout << "│≡　　╰┬┬┬╯　　≡│" << endl;
        cout << "│　　　　╰—╯　　　　│" << endl;
        cout << "╰——┬Ｏ———Ｏ┬——╯" << endl;
        cout << "-------------------------------------------------------------------------------" << endl;
        money = money - 50;
        cout << "剩余金币：" << money << endl;
        break;
    case 3:
        cout << "恭喜，你已经领养了一只鹦鹉" << endl;
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
        cout << "剩余金币：" << money << endl;
        break;
    }
}

/*-------------------------------------我是分割线--------------------------------------------------------------------------*/
//基本宠物类
class Pet:public Owner
{
public:
    int step;//精力
    int age;//年龄
    int hunger;//饱食度
    int thirst;//饮水度
    int mood;//心情度
    int fitness;//健康指数
    int offspring;//后代数
    int date;//饲养天数
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
    void change();           //饥、渴、心情随时间变化的函数
    void show();               //每个值的显示函数
    void feed();               //喂食
    void drink();               //喂水
    void touch(int w);             //抚摸
    virtual void play(int w)=0;      //玩耍（纯虚函数）
    virtual void work(int w)=0;    //宠物打工（纯虚函数）
    void doctor(int w);            //看医生
    virtual void birth()=0;                        //后代（纯虚函数）
    int emergency(int w);   //特殊状态函数
    virtual int getl()=0;              //提取生命值
    virtual int action(int act, int w, int emg)=0 {}; //主人的各种动作（纯虚函数）

    int menu();//选项菜单
    void Save_game();//保存
    void Load_game();//读取
};

void Pet::hname()
{
    cout << "为你的新宠取个名字吧：" << endl;
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
    cout << name<<"现在的状态：" << endl;
    cout << "余额：" << money << endl;
    cout << "年龄：" << age << endl;
    cout << "饱食度：" << hunger << endl;
    cout << "饮水度：" << thirst << endl;
    cout << "心情度：" << mood << endl;
    cout << "健康指数：" << fitness << endl;
    cout << "后代数量：" << offspring << endl;
    cout << "*******************************" << endl;
}

inline void Pet::feed()
{
    int n;
    step = step - 4;
    mood++;
    thirst--;
    cout << endl;
    cout << "你可以投喂的食物有：" << endl;
    cout << "1.(>^ω^<)喵牌通用食粮($5)   2.鸡腿($15)    3.营养套餐($20)    4.晨曦牌宝宝餐($30)" << endl;
    cout << "请选择：";
    cin >> n;
    switch (n)
    {
    case 1:
        money = money - 5;
        hunger =hunger+2;
        cout << "*******************************" << endl;
        cout << "太好吃啦！谢谢主人。" << endl;
        cout << "*******************************" << endl;
        cout << "———余额：" << money << endl;
        system("pause");
        break;
    case 2:
        money = money - 15;
        hunger = hunger + 4;
        cout << "*******************************" << endl;
        cout << "营养均衡偶滴最爱" << endl;
        cout << "*******************************" << endl;
        cout << "———余额：" << money << endl;
        system("pause");
        break;
    case 3:
        money = money - 20;
        hunger = hunger + 5;
        cout << "*******************************" << endl;
        cout << "哇，我最爱吃炸鸡了！" << endl;
        cout << "*******************************" << endl;
        cout << "———余额：" << money << endl;
        system("pause");
        break;
    case 4:
        money = money - 30;
        hunger = hunger + 10;
        cout << "*******************************" << endl;
        cout << "晨曦威武！！！" << endl;
        cout << "*******************************" << endl;
        cout << "———余额：" << money << endl;
        system("pause");
        break;
    }
}

inline void Pet::drink()
{
    step = step - 3;
    int n;
    cout << endl;
    cout << "你可以投喂的食物有：" << endl;
    cout << "1.凉白开($0)   2.矿泉水($2)    3.可乐($3)    4.至尊农夫三拳($10)" << endl;
    cout << "请选择：";
    cin >> n;
    switch (n)
    {
    case 1:
        thirst ++;
        cout << "*******************************" << endl;
        cout << "咕咚咕咚。" << endl;
        cout << "*******************************" << endl;
        cout << "———余额：" << money << endl;
        system("pause");
        break;
    case 2:
        money = money - 20;
        thirst = thirst + 2;
        cout << "*******************************" << endl;
        cout << "咕咚咕咚咕咚" << endl;
        cout << "*******************************" << endl;
        cout << "———余额：" << money << endl;
        system("pause");
        break;
    case 3:
        money = money - 35;
        thirst = thirst + 5;
        mood = mood + 5;
        fitness--;
        cout << "*******************************" << endl;
        cout << "吨吨吨吨吨吨吨(*^▽^*)" << endl;
        cout << "*******************************" << endl;
        cout << "———余额：" << money << endl;
        system("pause");
        break;
    case 4:
        money = money - 10;
        thirst = thirst + 10;
        mood++;
        cout << "*******************************" << endl;
        cout << "曾经我有一杯至尊水" << endl;
        cout << "*******************************" << endl;
        cout << "———余额：" << money << endl;
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
        cout << "(≥◇≤)最爱晴天啦" << endl; 
        cout << "*******************************" << endl;
        system("pause");
        break;
    case 1:
        mood++;
        cout << "*******************************" << endl;
        cout << "└(^o^)┘" << endl;
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
        cout << "潮湿(*>﹏<*)" << endl;
        cout << "*******************************" << endl;
        system("pause");
        break;
    case 4:
        mood--;
        hunger--;
        cout << "*******************************" << endl;
        cout << "阴霾的天气，阴郁的心情@_@" << endl;
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
    cout << "1、吃药（-$20）  2、打针（-$30）  3、打点滴（-$40）" << endl;
    cout << "请选择：";
    cin >> a;
    switch (a)
    {
    case 1:
        money = money - 20;
        mood--;
        fitness = fitness + 2;
        cout << "*******************************" << endl;
        cout << "好苦啊><。" << endl;
        cout << "*******************************" << endl;
        cout << "———余额：" << money << endl;
        system("pause");
        break;
    case 2:
        money = money - 30;
        mood=mood-2;
        fitness = fitness + 4;
        cout << "*******************************" << endl;
        cout << "打针≥﹏≤。" << endl;
        cout << "*******************************" << endl;
        cout << "———余额：" << money << endl;
        system("pause");
        break;
    case 3:
        money = money - 40;
        fitness = fitness + 8;
        hunger--;
        thirst--;
        cout << "*******************************" << endl;
        cout << "挂水好得快啊~.~。" << endl;
        cout << "*******************************" << endl;
        cout << "*余额：" << money << endl;
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
        cout << "!!!你的小宠物生病了" << endl;
        system("pause");
    }

    if (hunger <= 3 && hunger > 0)
    {
        mood--;
        cout << endl;
        cout << "!!!主人，我已经很饿了。" << endl;
        system("pause");
    }
    if (hunger >= 10 && hunger < 12)
    {
        mood--;
        cout << endl;
        cout << "!!!主人，我已经很饱了。" << endl;
        system("pause");
    }
    if (hunger <= 0 && hunger > -2)
    {
        mood = mood - 2;
        fitness--;
        cout << endl;
        cout << "!!!再不给我吃东西，我就饿死啦！" << endl;
        system("pause");
    }
    if (hunger >= 12)
    {
        mood = mood - 2;
        fitness--;
        cout << endl;
        cout << "!!!再给我吃东西，我就要撑死啦！" << endl;
        system("pause");
    }
    if (thirst > -1 && thirst < 0)
    {
        mood--;
        cout << endl;
        cout << "主人，我好渴。" << endl;
        system("pause");
    }
    if (thirst <= 10 && thirst > 12)
    {
        mood--;
        cout << endl;
        cout << "你再给我喝水，我就要吐啦！" << endl;
        system("pause");
    }
    if (thirst <= -1&&thirst>=-2 )
    {
        mood = mood - 2;
        fitness--;
        cout << endl;
        cout << "主人快给我喝生命的源泉吧，我快渴死啦！" << endl;
        system("pause");
    }
    if (thirst >= 12 && thirst < 14)
    {
        fitness--;
        cout << endl;
        cout << "我不要再喝水啦！" << endl;
        system("pause");
    }
    if (hunger >= 14 || thirst >= 14||hunger<=-4||thirst<=-3)
    {
        age = 100;
        cout << endl;
        cout << "*******************************" << endl;
        cout << "你这个可恶的主人！（咽气儿）" << endl;
        cout << "*******************************" << endl;
        cout << "由于工作不善，你已经被邪恶的张老板开除。（game over）" << endl;
        system("pause");
        cout << "假如人生不曾相遇，我还是那个我，偶尔做做梦，" << endl;
        cout << "然后，开始日复一日的奔波，淹没在这喧嚣的城市里。" << endl;
        cout << "我不会了解，这个世界还有这样的一个你，只有你能让人回味，也只有你会让我心醉。" << endl;
        cout << "假如人生不曾相遇，我不会相信，有一种人可以百看不厌，有一种人一认识就觉得温馨。" << endl;
        system("pause");
        return 2;
    }
    if (fitness < -6)
    {
        cout << endl;
        cout << "你可爱的宠物看了你最后一眼，缓缓地倒下了。" << endl;
        cout << "由于工作不善，你已经被邪恶的张老板开除。(game over)" << endl;
        system("pause");
        cout << "一直以为幸福在远方，在可以追逐的未来。" << endl;
        cout << "后来才发现，那些拥抱过的人，握过的手、唱过的歌、流过的泪、" << endl;
        cout << "爱过的人、所谓的曾经，就是幸福。在无数的夜里，说过的话、" << endl;
        cout << "打过的电话，思念过的人、流过的眼泪……看见的或看不见的感动，" << endl;
        cout << "我们都曾经过，然后在时间的穿梭中，一切成为了永恒！" << endl;
        system("pause");
        return 2;
    }
    return 0;
}

int  Pet::menu()
{
    cout << "****选项菜单****" << endl;
    cout << "1.玩法说明" << endl;
    cout << "2.储存" << endl;
    cout << "3.读取" << endl;
    cout << "4.退出到主菜单" << endl;
    cout << "5.退出到系统" << endl;
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
    return 0;//利用返回值控制退出循环
}

void Pet::Save_game()
{
    int ca;
    cout << "******菜单******" << endl;
    cout << "请选择存档位置" << endl;
    cout << "1          or           2" << endl;
    cout << "*****************" << endl;
    cin >> ca;
    ofstream file;
    switch (ca)
    {
    case 1:
        file.open("存档1.txt");
        if (!file)
        {
            cout << "*存档文件错误，请联系制作者" << endl;
            break;
        }
        //一行一个数据，方便读取
        file << m_name << '\n' << money << '\n' << select_t << '\n' <<name << '\n' << date << '\n' << step << '\n'
            << age << '\n' << hunger << '\n' << thirst << '\n' << mood << '\n' << fitness << '\n' << offspring << endl;
        file.close();
            break;
    case 2:
        file.open("存档2.txt");
        if (!file)
        {
            cout << "*存档文件错误，请联系制作者" << endl;
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
    cout << "******菜单******" << endl;
    cout << "请选择存档读取" << endl;
    cout << "1          or           2" << endl;
    cout << "*****************" << endl;
    cin >> ca;
    string temp;
    ifstream file;
    int i=0;
    switch (ca)
    {
    case 1:
        file.open("存档1.txt");
        if (!file)
        {
            cout << "*存档文件错误，请联系制作者" << endl;
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
        file.open("存档2.txt");
        if (!file)
        {
            cout << "*存档文件错误，请联系制作者" << endl;
            break;
        }
        while (getline(file, temp))//将数据读出存放至keep中
        {
            keep[i] = temp;
            i++;
        }
        file.close();
        R_start();
        break;
    }
}

/*-------------------------------------我是分割线--------------------------------------------------------------------------*/
//派生类的狗子
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
    void play(int w) ;      //玩耍
    void work(int w) ;    //宠物打工
    void birth() ;         //后代
    int action(int act, int w, int emg);  //主人的动作函数
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
    cout << "*请输入你要如何陪伴你的狗子：" << endl;
    cout << "1.散步 2.接飞盘 3.玩球 4.拆家" << endl;
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
    cout << "主人，我可以为你赚取金币哦。" << endl;
    cout << "*******************************" << endl;
    cout << " 1、捡瓶子（+$20） 2、看家护院（+$30） 3、导盲犬（+$60)" << endl;
    cout << "请选择宠物的打工类型：";
    cin >> a;
    switch (a)
    {
    case 1:
        money = money + 20;
        cout << "亲爱的主人，本汪给你带来了一笔收益，请查收。" << endl;
        cout << "------------余额：" << money << endl;
        break;
    case 2:
        money = money + 30;
        cout << "今天也是努力打工的一天。" << endl;
        cout << "------------余额：" << money << endl;
        break;
    case 3:
        money = money + 60;
        cout << "当导盲犬好累哦，主人。" << endl;
        cout << "------------余额：" << money << endl;
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
    cout << "*请问是否售出" << name << "的后代" << endl;
    cout << "是（1）/否（2）：" << endl;
    cin >> n;
    if (n == 1)
    {
        cout << "*需要售出几个小狗子？" << "（您现在拥有" << offspring << "个）" << endl;
        cin >> g;
        if (g <= offspring && g >= 0)
        {
            money = g * 80;
            cout << "------------余额：" << money << endl;
        }
        else
            cout << "数量不符，售出失败" << endl;
    }
}

//派生类鹦鹉
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
    void play(int w);      //玩耍
    void work(int w);    //宠物打工
    void birth();         //后代
    int action(int act, int w, int emg);  //主人的动作函数
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
    cout << "*请输入你要如何陪伴你的鹦鹉：" << endl;
    cout << "1.遛鸟 2.教说话 3.听歌 4.自由的飞翔" << endl;
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
    cout << "主人，我可以为你赚取金币哦。" << endl;
    cout << "*******************************" << endl;
    cout << " 1、供观赏（+$30） 2、表演学舌（+$40） 3、学碧昂丝唱歌（+$100)" << endl;
    cout << "请选择宠物的打工类型：";
    cin >> a;
    switch (a)
    {
    case 1:
        money = money + 20;
        cout << "亲爱的主人，本鹉给你带来了一笔收益，请查收。" << endl;
        cout << "------------余额：" << money << endl;
        break;
    case 2:
        money = money + 30;
        cout << "今天也是努力打工的一天。" << endl;
        cout << "------------余额：" << money << endl;
        break;
    case 3:
        money = money + 60;
        cout << "唱高音好累哦，主人。" << endl;
        cout << "------------余额：" << money << endl;
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
    cout << "*请问是否售出" << name << "的后代" << endl;
    cout << "是（1）/否（2）：" << endl;
    cin >> n;
    if (n == 1)
    {
        cout << "*需要售出几个小鹦鹉？" << "（您现在拥有" << offspring << "个）" << endl;
        cin >> g;
        if (g <= offspring && g >= 0)
        {
            money = g * 100;
            cout << "------------余额：" << money << endl;
        }
        else
            cout << "数量不符，售出失败" << endl;
    }
}

//派生类的猫主子
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
    void play(int w);      //玩耍
    void work(int w);    //宠物打工
    void birth();         //后代
    int action(int act, int w, int emg);  //主人的动作函数
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
    cout << "*请输入你要如何陪伴你的猫主子：" << endl;
    cout << "1.散步 2.玩毛线球 3.猫草挑逗 4.自由活动" << endl;
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
    cout << "两脚兽，我可以为你赚取金币。" << endl;
    cout << "*******************************" << endl;
    cout << " 1、供观赏（+$20） 2、抓老鼠（+$30） 3、抓鱼（+$60)" << endl;
    cout << "请选择宠物的打工类型：";
    cin >> a;
    switch (a)
    {
    case 1:
        money = money + 20;
        cout << "亲爱的主人，本喵给你带来了一笔收益，请查收。" << endl;
        cout << "------------余额：" << money << endl;
        break;
    case 2:
        money = money + 30;
        cout << "今天也是努力打工的一天。" << endl;
        cout << "------------余额：" << money << endl;
        break;
    case 3:
        money = money + 60;
        cout << "摸鱼好累哦，主人。" << endl;
        cout << "------------余额：" <<money << endl;
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
    cout << "*请问是否售出" << name << "的后代" << endl;
    cout << "是（1）/否（2）：" << endl;
    cin >> n;
    if (n == 1)
    {
        cout << "*需要售出几个小主子？" << "（您现在拥有" << offspring << "个）" << endl;
        cin >> g;
        if (g <= offspring && g >= 0)
        {
            money = g * 80;
            cout << "------------余额：" << money << endl;
        }
        else
            cout << "数量不符，售出失败" << endl;
    }
}

/*-------------------------------------我是分割线--------------------------------------------------------------------------*/
//开始饲养
int S_start()
{
    Owner me;
    Pet* petx=NULL;
    me.Id();//注册
    ClearScreen();
    int sel=me.ready();//领养
    ClearScreen();
    me.choose(sel);//宠物商店
    ClearScreen();
    int life, date, w, act;
    int t = 0;
    int step, age, emg;
    cout << endl;
    cout << "开始饲养啦！" << endl;
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
    petx->m_name = me.m_name;//赋值
    petx->money = me.money;
    petx->name = me.name;
    petx->select_t = sel;
    life = petx->getl();           //提取寿命
    for (date = 1; date <= life; date++)
    {
        cout << "今天是你领养的第" << date << "日" << endl;
        petx->date = date;//保存date用以读存
        w = remake_weather();                  //调用天气函数
        t = t % 3;                  //t是控制时间整型
        petx->change();            //状态改变函数
        while (t < 3)
        {
            int amn=0;
            emg = rand() % 20;      //控制是否生病
            cout << "现在是";
            remak_time(t);
            step = petx->get_step();  //提取行动点
            cout << endl;
            cout << "你的行动点数还有：" << step << endl;
            cout << "你的宠物";
            petx->show();
            if ((emg - 19) == 1)
                cout << "健康状况：生病" << endl;
            else
                cout << "健康状况：良好" << endl;
            cout << "请选择你想做的事：" << endl;
            cout << "1.喂食 2.喂水 3.抚摸 4.玩耍 5.宠物外快 6.看病 7.出售宠物后代 8.啥也不干 9.选项菜单" << endl;;
            cout << "请选择：";
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
                cout << "抱歉，由于饲养不善，你已经被吝啬张老板辞退。" << endl;
                cout << "------------------------------------------------------" << endl;
                return 2;
            }
            if (step < 0)
            {
                cout << "------------------------------------------------------" << endl;
                cout << "你因为饲养宠物过累病倒，被无良张老板辞退。" << endl;
                cout << "------------------------------------------------------" << endl;
                return 2;
            }                      //非正常结束饲养
            t++;
            cout << "------------------------------------------------------" << endl;
        }
        if (age > life || step < 0)     //非正常死亡，跳出循环
            return 2;
        ClearScreen();
    }
    if (date == life)
    {
        cout << "------------------------------------------------------" << endl;
        cout << "恭喜！你的宠物已经长大。" << endl;
        cout << "获得金币奖励+150。" << endl;
        cout << "------------------------------------------------------" << endl;
        petx->money = petx->money + 150;
        petx->Save_game();
        return 1;
    }
}

//读取类型饲养开始
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
    cout << "继续饲养啦！" << endl;
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
    life = petx->getl();           //提取寿命
    cout << date << endl;
    for ( date; date <= life; date++)
    {
        cout << "今天是你领养的第" << date << "日" << endl;
        w = remake_weather();                  //调用天气函数
        t = t % 3;                  //t是控制时间整型
        petx->change();            //状态改变函数
        while (t < 3)
        {
            emg = rand() % 20;      //控制是否生病
            cout << "现在是";
            remak_time(t);
            step = petx->get_step();  //提取行动点
            cout << endl;
            cout << "你的行动点数还有：" << step << endl;
            cout << "你的宠物";
            petx->show();
            if ((emg - 19) == 1)
                cout << "健康状况：生病" << endl;
            else
                cout << "健康状况：良好" << endl;
            cout << "请选择你想做的事：" << endl;
            cout << "1.喂食 2.喂水 3.抚摸 4.玩耍 5.宠物外快 6.看病 7.出售宠物后代 8.啥也不干 9.选项菜单" << endl;;
            cout << "请选择：";
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
                cout << "抱歉，由于饲养不善，你已经被吝啬张老板辞退。" << endl;
                cout << "------------------------------------------------------" << endl;
                return 2;
            }
            if (step < 0)
            {
                cout << "------------------------------------------------------" << endl;
                cout << "你因为饲养宠物过累病倒，被无良张老板辞退。" << endl;
                cout << "------------------------------------------------------" << endl;
                return 2;
            }                      //非正常结束饲养
            t++;
            cout << "------------------------------------------------------" << endl;
        }
        if (age > life || step < 0)     //非正常死亡，跳出循环
            return 2;
        ClearScreen();
    }
    if (date == life)
    {
        cout << "------------------------------------------------------" << endl;
        cout << "恭喜！你的宠物已经长大。" << endl;
        cout << "获得金币奖励+150。" << endl;
        cout << "------------------------------------------------------" << endl;
        petx->money = petx->money + 150;
        return 1;
    }
}

//菜单中读取
int M_r_start()
{
    int k = 0;
    cout << "****选择需要读取的存档****" << endl;
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
        file.open("存档1.txt");
        if (!file)
        {
            cout << "*存档文件错误，请联系制作者" << endl;
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
        file.open("存档2.txt");
        if (!file)
        {
            cout << "*存档文件错误，请联系制作者" << endl;
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
/*-------------------------------------我是分割线--------------------------------------------------------------------------*/
//主循环
int main()
{
    SetSysCaption("电子宠物商店——张晨曦");
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