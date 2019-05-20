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
    printf("                      ����ͼ����Ĺ���ϵͳ  \n");
    printf("     *************************�˵�********************************\n");
    printf("     *  1 ͼ�����                       2 ͼ��黹              *\n");
    printf("     *  3 ͼ������                       4 ͼ���ѯ              *\n");
    printf("     *  5 ȫ��ͼ����Ϣ                   6 �ѽ�ͼ��              *\n");
    printf("     *  7 ��ֵ���鿨                     8 ������һ��            *\n");
    printf("     *  9 �˳�ϵͳ                                               *\n");
    printf("     *************************************************************\n");
    int a;
    cin>>a;
    while(a>9||a==0)
    {
        cout<<"�Ƿ����룬����������\n";
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
    printf("                      ����ͨ��  \n");
    printf("     *************************�˵�********************************\n");
    printf("     *  1 ����ע��                       2 ���ߵ�½              *\n");
    printf("     *  3 ���߹�ʧ                       4 �������˵�            *\n");
    printf("     *  5 �˳�ϵͳ                                               *\n");
    printf("     *************************************************************\n");
    int a;
    cin>>a;
    while(a>5||a==0)
    {
        cout<<"�Ƿ����룬����������\n";
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
	printf("********����ע��********\n\n");
	printf("��������\n");

	do {
		scanf("%s", p->name);
		num=judge_same(p->name);
	} while (num == -1);

	p->reader_number=num;
	char code[20];
	do
    {
        printf("��������\n");
        scanf("%s", p->reader_code);
        printf("�ٴ�����\n");
        cin>>code;
    }while(strcmp(p->reader_code,code)!=0);
	cout<<"����༶\n";
	cin>>p->class_num;
	cout<<"����ѧ��\n";
	cin>>p->student_num;

	cout<<"���ǽ�ʦ��ѧ��(t/s)?\n";
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
    cout<<"������鿨����\n";
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
	cout<<"ע��ɹ�";
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
		printf("û����Ϣ\n");
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
		printf("�޷���\n");
        return 0;
	}
	while (head)
	{
		fwrite(head, sizeof(struct reader), 1, fp);
		head = head->next;
	}
	fclose(fp);
	printf("����ɹ�\n");
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
                cout<<"�����Ѵ��ڣ���������\n";
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
    printf("********���ڵ�½********\n\n");
	printf("����������ѧ��\n");
	char new_name[20];
	scanf("%s", new_name);
	printf("��������\n");
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
			printf("��½�ɹ�\n");
			system("pause");
			reader_log_in_menu(p,head);
		}
		else if ((strcmp(p->name, this_name) == 0||strcmp(p->student_num,this_name)==0) && strcmp(p->reader_code, code) != 0 && t>0)
		{
			printf("����%d�λ���\n", t);
			system("pause");
			return 0;
		}
		p = p->next;
	}
	fclose(fp);
	if (t <= 0)
	{
		printf("�Ƿ���½\n");
		system("pause");
		reader_log_in();
	}
	printf("��������\n");
	system("pause");
    reader_log_in();
}

void reader_log_in_menu(struct reader*p,struct reader*headhead)
{
    system("cls");
    if(p->stu_tea==1)
        cout<<"                         ��ӭ��½  "<<p->name<<"��ʦ\n";
    else
        cout<<"                         ��ӭ��½  "<<p->name<<"ͬѧ\n";
    printf("     *************************************************************\n");
    printf("                            �ҵĿռ�\n");
    printf("     *************************�˵�********************************\n");
    printf("     *  1 �ҵ���Ϣ                       2 �޸�����              *\n");
    printf("     *  3 ����ͼ�����ϵͳ               4 �޸ĸ�����Ϣ          *\n");
    printf("     *  5 ������һ��                     6 �˳�ϵͳ              *\n");
    printf("     *************************************************************\n");
    int a;
    cin>>a;
    while(a>6||a==0)
    {
        cout<<"�Ƿ����룬����������\n";
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
        cout<<"��ӭ��½  "<<p->name<<"��ʦ\n";
    else
        cout<<"��ӭ��½  "<<p->name<<"ͬѧ\n";
    cout<<"���ߵȼ�:"<<p->level<<"\n";
    cout<<"���߱��:"<<p->reader_number<<"\n";
    cout<<"���߰༶"<<p->class_num<<"\n";
    cout<<"����ѧ��"<<p->student_num<<"\n";
    cout<<"ͼ�鿨���"<<p->libcard<<"\n";
    char a;
    cout<<"�Ƿ�鿴�ѽ�ͼ�飿(y/n)\n";
    cin>>a;
    if(a=='y')
    {
        cout<<"�ѽ�ͼ��\n";
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
    cout<<"�����"<<t<<"����\n";
    cout<<"***********************************************************\n";
    for(int i=0;i<20;i++)
    {
        FILE *fp;
        fp=fopen("book.dat","r+");
        struct library_book*head;
        head=open(fp);
        if(head==0)
            {cout<<"û������\n";system("pause");return;}
        while(head)
        {
            if(p->borrowed_book[i][0]==head->book_code)
            {
                show_single_book(head);
                cout<<"��������"<<p->borrowed_book[i][1]<<"��"<<p->borrowed_book[i][2]<<"��\n";
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
        cout<<"ͼ���ţ�"<<p->book_code<<"\n";
        cout<<"ͼ�����ƣ�"<<p->book_name<<"\n";
        cout<<"ͼ�����ߣ�"<<p->writer<<"\n";
        cout<<"ͼ�����"<<p->clss<<"\n";
        cout<<"ͼ������̣�"<<p->publisher<<"\n";
        cout<<"�������ڣ�"<<p->publication_date<<"\n";
        cout<<"ͼ��۸�"<<p->price<<"\n";
        cout<<"ͼ���ܴ棺"<<p->sum<<"\n";
        cout<<"ͼ���棺"<<p->stock<<"\n";
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
        cout<<"ʣ�໹������"<<t<<"\n";
    else
        cout<<"�ѳ�������ʱ�ޣ����컹��\n";
    if(t>0)
        fee=price*0.01*(10-t);
    else
        fee=price*0.1+price*0.05*abs(t);
    cout<<"Ӧ���ɽ����:"<<fee<<"Ԫ\n";
    return;
}

void change_code(struct reader*p,struct reader*headhead)
{
    FILE *fp;
	struct reader*q, *head;
	printf("����������\n");
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
    cout<<"�ѽ�"<<nt<<"����,";
    cout<<"���ɽ���"<<t<<"����\n";
    if(flag==-1)
    {
        char borrw;
        cout<<"������Ŀ�Ѵ����� �޷����� �Ƿ���(y/n)\n";
        cin>>borrw;
        if(borrw=='y')
            return_book(p,headhead);
        else
            return;
    }
    else
    {
        cout<<"�����������\n";
        char bookname[20];
        cin>>bookname;
        FILE *fp;
        fp=fopen("book.dat","r+");
        struct library_book*head;
        head=open(fp);
        if(head==0)
        {cout<<"û�и���\n";system("pause");return;}
        while(head)
        {
            if(head->stock<=0)
            {
                cout<<"����û�п��\n";
                cout<<"�Ƿ��������(y/n)\n";
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
                    cout<<"����ɹ�\n";
                    system("pause");
                    return;
                }
            head=head->next;
        }
        cout<<"û�и���\n";
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
    cout<<"�����"<<t<<"����\n";
    if(t==0)
    {
        cout<<"���軹��\n";
        system("pause");
        return;
    }
    cout<<"***********************************************************\n";
    cout<<"��������\n";
    for(int i=0;i<20;i++)
    {
        FILE *fp;
        fp=fopen("book.dat","r+");
        struct library_book*head;
        head=open(fp);
        if(head==0)
            {
                cout<<"�����ѱ�ɾ��\n";
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
                cout<<"������"<<head->book_name;
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
                cout<<"���ɽ�"<<fee;
                cout<<"\n***********************************************************\n\n";
            }
            head=head->next;
        }
    }

    cout<<"���뻹������\n";
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
                    cout<<"����\n";
                    cout<<"�Ƿ��ֵ(y/n)\n";
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
                cout<<"����ɹ�\n";
                cout<<"�������:"<<p->libcard<<"\n";
                system("pause");
                return;
            }
        cout<<"δ�����\n";
        system("pause");
        return;
}

void book_continue(struct reader*p,struct reader*headhead)
{
    char bookname[20];
    cout<<"������������\n";
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
            cout<<"����\n";
            cout<<"�Ƿ��ֵ(y/n)\n";
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
        cout<<"����ɹ�\n";
        cout<<"�������"<<p->libcard<<"\n";
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
        cout<<"û�и���\n";
        system("pause");
        return 0;
    }
    while(head)
    {
        if(strcmp(head->book_name,bookname)==0)
            return head->book_code;
        head=head->next;
    }
    cout<<"û�и������鱻ɾ��\n";
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
        cout<<"û�и���\n";
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
    cout<<"û�и������鱻ɾ��\n";
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
        cout<<"û�и���\n";
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
    cout<<"û�и������鱻ɾ��\n";
    return 0;
}

void reader_delet()
{
    cout<<"���ڹ�ʧ\n";
    cout<<"�����������\n";
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
            cout<<"������Ч\n";
            return;
        }
    while(ohead)
    {
        if(strcmp(readername,ohead->name)==0)
        {
            cout<<"���ڽ��������֤\n";
            cout<<"����ѧ��\n";
            char stunum[20];
            cin>>stunum;
            if(strcmp(ohead->student_num,stunum)==0)
            {
                headhead=ohead->next;
                save_reader(headhead);
                cout<<"ɾ���ɹ�\n";
                system("pause");
                return;
            }
            else
            {
                cout<<"ѧ�Ŵ��� ��Ȩ����\n";
                system("pause");
                return;
            }
        }
        if(strcmp(readername,p->name)==0)
        {
            cout<<"���ڽ��������֤\n";
            cout<<"����ѧ��\n";
            char stunum[20];
            cin>>stunum;
            if(strcmp(p->student_num,stunum)==0)
            {
                p=p->next;
                ohead->next=p;
                save_reader(headhead);
                cout<<"ɾ���ɹ�\n";
                system("pause");
                return;
            }
            else
            {
                cout<<"ѧ�Ŵ��� ��Ȩ����\n";
                system("pause");
                return;
            }
        }
            ohead=ohead->next;
            p=p->next;
    }
    cout<<"������Ч";
    return;
}

void charge_card(struct reader*p,struct reader*headhead)
{
    system("cls");
    cout<<"�����ֵ���\n";
    int a;
    cin>>a;
    char ccode[20];
    cout<<"������鿨����\n";
    cin>>ccode;
    int t=2;
    while(t>0&&strcmp(ccode,p->libcard_code)!=0)
    {
        cout<<"���������������\n";
        cin>>ccode;
        t--;
    }
    if(t<=0)
    {
        cout<<"�Ƿ���½\n";
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
    cout<<"1 �޸�����\n2 �޸�ѧ��\n3 �޸İ༶\n0 ȷ���޸�\n";
    int a;
    cin>>a;
    while(a!=0)
    {
        cout<<"����\n";
        if(a==1)
            {
                do{cin>>p->name;}
                while(judge_same(p->name)==-1);
            }
        else if(a==2)
            cin>>p->student_num;
        else if(a==3)
            cin>>p->class_num;
        cout<<"1 �޸�����\n2 �޸�ѧ��\n3 �޸İ༶\n0 ȷ���޸�\n";
        cin>>a;
    }
    save_reader(headhead);
    system("pause");
    return;
}
