#include <iostream>
#include <string>
#include <stdlib.h>
#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "head.h"
using namespace std;


void borrow_menu(struct reader*p,struct reader*headhead)
{
    system("cls");
    printf("                      读者图书借阅管理系统  \n");
    printf("     *************************菜单********************************\n");
    printf("     *  1 图书借阅                       2 图书归还              *\n");
    printf("     *  3 图书续借                       4 图书查询              *\n");
    printf("     *  5 全部图书信息                   6 已借图书              *\n");
    printf("     *  7 充值借书卡                     8 返回上一级            *\n");
    printf("     *  9 退出系统                                               *\n");
    printf("     *************************************************************\n");
    int a;
    cin>>a;
    while(a>9||a==0)
    {
        cout<<"非法输入，请重新输入\n";
        cin>>a;
    }
    if(a==1)
        borrow_book(p,headhead);
    else if(a==2)
        return_book(p,headhead);
    else if(a==3)
        book_continue(p,headhead);
    else if(a==4)
        search_book();
    else if(a==5)
        show_book();
    else if(a==6)
        show_borrowed_book(p,headhead);
    else if(a==7)
        charge_card(p,headhead);
    else if(a==8)
        reader_log_in_menu(p,headhead);
    else if(a==9)
        exit(0);
    borrow_menu(p,headhead);
}

void reader_menu()
{
    system("cls");
    printf("                      读者通道  \n");
    printf("     *************************菜单********************************\n");
    printf("     *  1 读者注册                       2 读者登陆              *\n");
    printf("     *  3 读者挂失                       4 返回主菜单            *\n");
    printf("     *  5 退出系统                                               *\n");
    printf("     *************************************************************\n");
    int a;
    cin>>a;
    while(a>5||a==0)
    {
        cout<<"非法输入，请重新输入\n";
        cin>>a;
    }
    if(a==1)
        reader_registe();
    else if(a==2)
        reader_log_in();
    else if(a==3)
        reader_delet();
    else if(a==4)
        menu();
    else if(a==5)
        exit(0);
    reader_menu();
}

void reader_registe()
{
    system("cls");
    int flag = 1,num;
	FILE *fp;
	fp = fopen("reader.dat", "a+");
	struct reader *p, *head,*rear;
	p = (struct reader*)malloc(sizeof(struct reader));
	printf("********正在注册********\n\n");
	printf("输入姓名\n");

	do {
		scanf("%s", p->name);
		num=judge_same(p->name);
	} while (num == -1);

	p->reader_number=num;
	char code[20];
	do
    {
        printf("输入密码\n");
        scanf("%s", p->reader_code);
        printf("再次输入\n");
        cin>>code;
    }while(strcmp(p->reader_code,code)!=0);
	cout<<"输入班级\n";
	cin>>p->class_num;
	cout<<"输入学号\n";
	cin>>p->student_num;

	cout<<"您是教师或学生(t/s)?\n";
	char tea;
	cin>>tea;
	if(tea=='t')
        p->stu_tea=1,p->level=1;
    else
        p->stu_tea=2,p->level=0;

	for(int i=0;i<20;i++)
	p->borrowed_book[i][0]=0;
    p->libcard=1;
    char ccode[20];
    cout<<"输入读书卡密码\n";
    cin>>ccode;
    strcpy(p->libcard_code,ccode);

	p->next = NULL;
	head=open_reader(fp);

	if (head == 0)
		save_reader(p);
	else
	{
		rear=head;
		while(rear->next)
            rear=rear->next;
        rear->next=p;
		save_reader(head);
	}
	cout<<"注册成功";
	system("pause");
	reader_menu();
}
struct reader* open_reader(FILE *fp)
{
    struct reader*op;
	struct reader*ohead = NULL, *orear;
	op = (struct reader*)malloc(sizeof(struct reader));
	ohead = op;
	fread(op, sizeof(struct reader), 1, fp);
	if (feof(fp) != 0)
	{
		printf("没有信息\n");
		fclose(fp);
		system("pause");
		return 0;
	}
	orear = op;
	ohead = orear;
	op = (struct reader*)malloc(sizeof(struct reader));
	while (fread(op, sizeof(struct reader), 1, fp) != NULL)
	{
		orear->next = op;
		orear = orear->next;
		op = (struct reader*)malloc(sizeof(struct reader));
	}
	orear->next = NULL;
	if (op == NULL)
		free(op);
	fclose(fp);
	return ohead;
};
int save_reader(struct reader*head)
{
    struct reader*p;
	p = head;
	FILE *fp;
	if ((fp = fopen("reader.dat", "w+")) == NULL)
	{
		printf("无法打开\n");
        return 0;
	}
	while (head)
	{
		fwrite(head, sizeof(struct reader), 1, fp);
		head = head->next;
	}
	fclose(fp);
	printf("保存成功\n");
}
int judge_same(char *name)
{
    FILE *fp;
    fp=fopen("reader.dat","a+");
    struct reader*ohead;
    ohead=open_reader(fp);
    if(ohead==0)
        return 1;
    int num;
    while(ohead)
    {
        if(strcmp(name,ohead->name)==0)
            {
                cout<<"名称已存在，重新输入\n";
                return -1;
            }
            num=ohead->reader_number;
            ohead=ohead->next;
    }
    return num;
}

void reader_log_in()
{
    system("cls");
    printf("********正在登陆********\n\n");
	printf("输入姓名或学号\n");
	char new_name[20];
	scanf("%s", new_name);
	printf("输入密码\n");
	char new_code[20];
	int t = 3;
	do
	{
	       int i;
		    for (i = 0; i<21; i++)
            {
                new_code[i] = getch();
                if (new_code[i] == '\r')
                    break;
                printf("*");
            }
            new_code[i] = '\0';
            cout<<"\n";
		t--;
	} while (judge_code(new_name, new_code, t) == 0);

}
int judge_code(char*this_name,char*code,int t)
{
    struct reader*p, *head;
	FILE *fp;
	fp = fopen("reader.dat", "r");
	p = open_reader(fp);
	if(p==0)
        return 0;
	head=p;
	while (p)
	{
		if ((strcmp(p->name, this_name) == 0||strcmp(p->student_num,this_name)==0) && strcmp(p->reader_code, code) == 0)
		{
			printf("登陆成功\n");
			system("pause");
			reader_log_in_menu(p,head);
		}
		else if ((strcmp(p->name, this_name) == 0||strcmp(p->student_num,this_name)==0) && strcmp(p->reader_code, code) != 0 && t>0)
		{
			printf("还有%d次机会\n", t);
			system("pause");
			return 0;
		}
		p = p->next;
	}
	fclose(fp);
	if (t <= 0)
	{
		printf("非法登陆\n");
		system("pause");
		reader_log_in();
	}
	printf("姓名错误\n");
	system("pause");
    reader_log_in();
}

void reader_log_in_menu(struct reader*p,struct reader*headhead)
{
    system("cls");
    if(p->stu_tea==1)
        cout<<"                         欢迎登陆  "<<p->name<<"教师\n";
    else
        cout<<"                         欢迎登陆  "<<p->name<<"同学\n";
    printf("     *************************************************************\n");
    printf("                            我的空间\n");
    printf("     *************************菜单********************************\n");
    printf("     *  1 我的信息                       2 修改密码              *\n");
    printf("     *  3 进入图书借阅系统               4 修改个人信息          *\n");
    printf("     *  5 返回上一级                     6 退出系统              *\n");
    printf("     *************************************************************\n");
    int a;
    cin>>a;
    while(a>6||a==0)
    {
        cout<<"非法输入，请重新输入\n";
        cin>>a;
    }
    if(a==1)
        my_infor(p,headhead);
    else if(a==2)
        change_code(p,headhead);
    else if(a==3)
        borrow_menu(p,headhead);
    else if(a==4)
        change_reader_information(p,headhead);
    else if(a==5)
        reader_menu();
    else if(a==6)
        exit(0);
    reader_log_in_menu(p,headhead);
}
void my_infor(struct reader*p,struct reader*headhead)
{
    system("cls");
    if(p->stu_tea==1)
        cout<<"欢迎登陆  "<<p->name<<"教师\n";
    else
        cout<<"欢迎登陆  "<<p->name<<"同学\n";
    cout<<"读者等级:"<<p->level<<"\n";
    cout<<"读者编号:"<<p->reader_number<<"\n";
    cout<<"读者班级"<<p->class_num<<"\n";
    cout<<"读者学号"<<p->student_num<<"\n";
    cout<<"图书卡余额"<<p->libcard<<"\n";
    char a;
    cout<<"是否查看已借图书？(y/n)\n";
    cin>>a;
    if(a=='y')
    {
        cout<<"已借图书\n";
        show_borrowed_book(p,headhead);
    }
    else
        {
            system("pause");
            return;
        }
}
void show_borrowed_book(struct reader*p,struct reader*headhead)
{
    int t=0;
    for(int i=0;i<20;i++)
    {
        if(p->borrowed_book[i][0]>0)
            t++;
    }
    cout<<"共租借"<<t<<"本书\n";
    cout<<"***********************************************************\n";
    for(int i=0;i<20;i++)
    {
        FILE *fp;
        fp=fopen("book.dat","r+");
        struct library_book*head;
        head=open(fp);
        if(head==0)
            {cout<<"没有数据\n";system("pause");return;}
        while(head)
        {
            if(p->borrowed_book[i][0]==head->book_code)
            {
                show_single_book(head);
                cout<<"借书日期"<<p->borrowed_book[i][1]<<"月"<<p->borrowed_book[i][2]<<"日\n";
                show_residue_days(p,i,head->price);

                cout<<"\n***********************************************************\n\n";
            }
            head=head->next;
        }
    }
    system("pause");
    return;
}
void show_single_book(struct library_book*p)
{
        cout<<"图书编号："<<p->book_code<<"\n";
        cout<<"图书名称："<<p->book_name<<"\n";
        cout<<"图书作者："<<p->writer<<"\n";
        cout<<"图书类别："<<p->clss<<"\n";
        cout<<"图书出版商："<<p->publisher<<"\n";
        cout<<"出版日期："<<p->publication_date<<"\n";
        cout<<"图书价格："<<p->price<<"\n";
        cout<<"图书总存："<<p->sum<<"\n";
        cout<<"图书库存："<<p->stock<<"\n";
}
void show_residue_days(struct reader*p,int i,int price)
{
    time_t timep;
    struct tm*tm;
    time(&timep);
    tm=gmtime(&timep);
    int t,fee;
    t=10-(tm->tm_mon+1-p->borrowed_book[i][1])*31+abs(p->borrowed_book[i][2]-tm->tm_mday);
    if(t>0)
        cout<<"剩余还书天数"<<t<<"\n";
    else
        cout<<"已超出还书时限，尽快还书\n";
    if(t>0)
        fee=price*0.01*(10-t);
    else
        fee=price*0.1+price*0.05*abs(t);
    cout<<"应缴纳借书费:"<<fee<<"元\n";
    return;
}

void change_code(struct reader*p,struct reader*headhead)
{
    FILE *fp;
	struct reader*q, *head;
	printf("输入新密码\n");
	fp = fopen("reader.dat", "r");
	q = open_reader(fp);
	head = q;
	while (q)
	{

		if (strcmp(p->name, q->name) == 0)
			{
			    scanf("%s", q->reader_code);
			    cout<<"\n";
			    save_reader(head);
			    system("pause");
			    return;
			}
		q =q->next;
	}
}

void borrow_book(struct reader*p,struct reader*headhead)
{
    int flag=-1;
    int i,nt=0,t;
    if(p->level==0)
        t=5;
    else if(p->level==1)
        t=10;
    else if(p->level==2)
        t=15;
    else
        t=20;
    for(i=0;i<t;i++)
        {
            if(p->borrowed_book[i][0]==0)
            flag=i;
            else
                nt++;
        }
    t-=nt;
    cout<<"已借"<<nt<<"本书,";
    cout<<"还可借阅"<<t<<"本书\n";
    if(flag==-1)
    {
        char borrw;
        cout<<"借书数目已达上限 无法借书 是否还书(y/n)\n";
        cin>>borrw;
        if(borrw=='y')
            return_book(p,headhead);
        else
            return;
    }
    else
    {
        cout<<"输入借书名称\n";
        char bookname[20];
        cin>>bookname;
        FILE *fp;
        fp=fopen("book.dat","r+");
        struct library_book*head;
        head=open(fp);
        if(head==0)
        {cout<<"没有该书\n";system("pause");return;}
        while(head)
        {
            if(head->stock<=0)
            {
                cout<<"该书没有库存\n";
                cout<<"是否继续借书(y/n)\n";
                char jie;
                cin>>jie;
                if(jie=='y')
                    {
                        borrow_book(p,headhead);
                        return;
                    }
                else
                    return;
            }
            if(strcmp(head->book_name,bookname)==0)
                {
                    p->borrowed_book[flag][0]=head->book_code;
                    p->borrowed_book[flag][3]=head->price;
                    time_t timep;
                    struct tm*tm;
                    time(&timep);
                    tm=gmtime(&timep);

                    p->borrowed_book[flag][1]=tm->tm_mon+1;
                    p->borrowed_book[flag][2]=tm->tm_mday;

                    stock_minus(bookname,1);
                    save_reader(headhead);
                    cout<<"保存成功\n";
                    system("pause");
                    return;
                }
            head=head->next;
        }
        cout<<"没有该书\n";
        system("pause");
        return;
    }
}
void return_book(struct reader*p,struct reader*headhead)
{
    int t=0;
    for(int i=0;i<20;i++)
    {
        if(p->borrowed_book[i]>0)
            t++;
    }
    cout<<"共租借"<<t<<"本书\n";
    if(t==0)
    {
        cout<<"无需还书\n";
        system("pause");
        return;
    }
    cout<<"***********************************************************\n";
    cout<<"书名如下\n";
    for(int i=0;i<20;i++)
    {
        FILE *fp;
        fp=fopen("book.dat","r+");
        struct library_book*head;
        head=open(fp);
        if(head==0)
            {
                cout<<"该书已被删除\n";
                for(int j=0;j<20;j++)
                    p->borrowed_book[i][0]=0;
                save_reader(headhead);
                system("pause");
                return;
                }
        while(head)
        {
            if(p->borrowed_book[i][0]==head->book_code)
            {
                cout<<"书名："<<head->book_name;
                time_t timep;
                    struct tm*tm;
                    time(&timep);
                    tm=gmtime(&timep);
                    int t;
                    double fee;
                    t=10-(tm->tm_mon-p->borrowed_book[i][1])*31+abs(p->borrowed_book[i][2]-tm->tm_mday);
                    if(t>0)
                        fee=head->price*0.01*(10-t);
                    else
                        fee=head->price*0.1+head->price*0.05*abs(t);
                cout<<"缴纳金额："<<fee;
                cout<<"\n***********************************************************\n\n";
            }
            head=head->next;
        }
    }

    cout<<"输入还书名称\n";
    char bookname[20];
    cin>>bookname;
    int booknum;
    booknum=find_book(bookname);
    if(booknum==0)
        return;
    for(int i=0;i<20;i++)
        if(booknum==p->borrowed_book[i][0])
            {
                time_t timep;
                struct tm*tm;
                time(&timep);
                tm=gmtime(&timep);
                int t;
                double fee;
                t=10-(tm->tm_mon+1-p->borrowed_book[i][1])*31+abs(p->borrowed_book[i][2]-tm->tm_mday);
                if(t>0)
                    fee=p->borrowed_book[i][3]*0.01*(10-t);
                else
                    fee=p->borrowed_book[i][3]*0.1+p->borrowed_book[i][3]*0.05*abs(t);
                if(fee>p->libcard)
                {
                    cout<<"余额不足\n";
                    cout<<"是否充值(y/n)\n";
                    char cha;
                    cin>>cha;
                    if(cha=='y')
                        charge_card(p,headhead);
                    else
                        return;
                }
                else
                    p->libcard-=fee;
                p->borrowed_book[i][0]=0;
                stock_add(bookname,1);
                save_reader(headhead);
                cout<<"还书成功\n";
                cout<<"卡内余额:"<<p->libcard<<"\n";
                system("pause");
                return;
            }
        cout<<"未借该书\n";
        system("pause");
        return;
}

void book_continue(struct reader*p,struct reader*headhead)
{
    char bookname[20];
    cout<<"输入续借书名\n";
    cin>>bookname;
    int num;
    num=find_book(bookname);
    if(num==0)
        return;
    for(int i=0;i<20;i++)
        if(num==p->borrowed_book[i][0])
    {
        time_t timep;
        struct tm*tm;
        time(&timep);
        tm=gmtime(&timep);
        int t;
        double fee;
        t=10-(tm->tm_mon-p->borrowed_book[i][1])*31+abs(p->borrowed_book[i][2]-tm->tm_mday);
        if(t>0)
            fee=p->borrowed_book[i][3]*0.01*(10-t);
        else
            fee=p->borrowed_book[i][3]*0.1+p->borrowed_book[i][3]*0.05*abs(t);
        if(fee>p->libcard)
        {
            cout<<"余额不足\n";
            cout<<"是否充值(y/n)\n";
            char cha;
            cin>>cha;
            if(cha=='y')
                charge_card(p,headhead);
            else
                return;
        }
        else
            p->libcard-=fee;
        p->borrowed_book[i][1]=tm->tm_mon+1;
        p->borrowed_book[i][2]=tm->tm_mday;
        cout<<"续借成功\n";
        cout<<"卡内余额"<<p->libcard<<"\n";
        save_reader(headhead);
        system("pause");
        return;
    }
}

int find_book(char bookname[20])
{
    FILE *fp;
    fp=fopen("book.dat","r+");
    struct library_book*head;
    head=open(fp);
    if(head==0)
    {
        cout<<"没有该书\n";
        system("pause");
        return 0;
    }
    while(head)
    {
        if(strcmp(head->book_name,bookname)==0)
            return head->book_code;
        head=head->next;
    }
    cout<<"没有该书或该书被删除\n";
    system("pause");
    return 0;
}
int stock_add(char bookname[20],int num)
{
    FILE *fp;
    fp=fopen("book.dat","r+");
    struct library_book*head,*headhead;
    head=open(fp);
    headhead=head;
    if(head==0)
    {
        cout<<"没有该书\n";
        system("pause");
        return 0;
    }
    while(head)
    {
        if(strcmp(head->book_name,bookname)==0)
            {
                head->stock+=num;
                save(headhead);
                return 0;
            }
        head=head->next;
    }
    cout<<"没有该书或该书被删除\n";
    return 0;
}
int stock_minus(char bookname[20],int num)
{
    FILE *fp;
    fp=fopen("book.dat","r+");
    struct library_book*head,*headhead;
    head=open(fp);
    headhead=head;
    if(head==0)
    {
        cout<<"没有该书\n";
        system("pause");
        return 0;
    }
    while(head)
    {
        if(strcmp(head->book_name,bookname)==0)
            {
                head->stock-=num;
                save(headhead);
                return 0;
            }
        head=head->next;
    }
    cout<<"没有该书或该书被删除\n";
    return 0;
}

void reader_delet()
{
    cout<<"正在挂失\n";
    cout<<"输入你的名字\n";
    char readername[20];
    cin>>readername;

    FILE *fp;
    fp=fopen("reader.dat","r");
    struct reader*ohead,*p,*headhead;
    ohead=open_reader(fp);
    headhead=ohead;
    p=ohead->next;
    if(ohead==0)
        {
            cout<<"姓名无效\n";
            return;
        }
    while(ohead)
    {
        if(strcmp(readername,ohead->name)==0)
        {
            cout<<"正在进行身份验证\n";
            cout<<"输入学号\n";
            char stunum[20];
            cin>>stunum;
            if(strcmp(ohead->student_num,stunum)==0)
            {
                headhead=ohead->next;
                save_reader(headhead);
                cout<<"删除成功\n";
                system("pause");
                return;
            }
            else
            {
                cout<<"学号错误 无权操作\n";
                system("pause");
                return;
            }
        }
        if(strcmp(readername,p->name)==0)
        {
            cout<<"正在进行身份验证\n";
            cout<<"输入学号\n";
            char stunum[20];
            cin>>stunum;
            if(strcmp(p->student_num,stunum)==0)
            {
                p=p->next;
                ohead->next=p;
                save_reader(headhead);
                cout<<"删除成功\n";
                system("pause");
                return;
            }
            else
            {
                cout<<"学号错误 无权操作\n";
                system("pause");
                return;
            }
        }
            ohead=ohead->next;
            p=p->next;
    }
    cout<<"姓名无效";
    return;
}

void charge_card(struct reader*p,struct reader*headhead)
{
    system("cls");
    cout<<"输入充值金额\n";
    int a;
    cin>>a;
    char ccode[20];
    cout<<"输入读书卡密码\n";
    cin>>ccode;
    int t=2;
    while(t>0&&strcmp(ccode,p->libcard_code)!=0)
    {
        cout<<"密码错误重新输入\n";
        cin>>ccode;
        t--;
    }
    if(t<=0)
    {
        cout<<"非法登陆\n";
        reader_menu();
    }
    p->libcard+=abs(a);
    save_reader(headhead);
    system("pause");
    return;
}

void change_reader_information(struct reader*p,struct reader*headhead)
{
    system("cls");
    cout<<"1 修改姓名\n2 修改学号\n3 修改班级\n0 确认修改\n";
    int a;
    cin>>a;
    while(a!=0)
    {
        cout<<"输入\n";
        if(a==1)
            {
                do{cin>>p->name;}
                while(judge_same(p->name)==-1);
            }
        else if(a==2)
            cin>>p->student_num;
        else if(a==3)
            cin>>p->class_num;
        cout<<"1 修改姓名\n2 修改学号\n3 修改班级\n0 确认修改\n";
        cin>>a;
    }
    save_reader(headhead);
    system("pause");
    return;
}
