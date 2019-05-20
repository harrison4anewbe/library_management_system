#include <iostream>
#include <string>
#include <stdlib.h>
#include <conio.h>
#include <stdio.h>
#include <string.h>
#include "head.h"

using namespace std;



void menu()
{
system("cls");
printf("                          ͼ�����ϵͳ  \n");
printf("     *************************���˵�********************************\n");
printf("     *  1 ͼ���������                    2 ���Ĳ�ѯ             *\n");//��ѯ˭�����Ȿ��
printf("     *  3 ���߹���                          4 ���ݷ���             *\n");
printf("     *  5 �˳�ϵͳ                                                 *\n");
printf("     ***************************************************************\n");
int a;
cin>>a;
while(a>5||a==0)
{
    cout<<"�Ƿ����룬����������\n";
    cin>>a;
}
if(a==1)
    book_manage_menu();
else if(a==2)
    search_borrowed_book();
else if(a==3)
    reader_menu();
else if (a==4)
   data_analyze_menu();
else if(a==5)
    exit(0);
menu();
}
void book_manage_menu()
{
system("cls");
printf("                      ͼ���������ϵͳ  \n");
printf("     *************************�˵�********************************\n");
printf("     *  1 ͼ�����                       2 ͼ��ɾ��              *\n");
printf("     *  3 ͼ����Ϣ�޸�                   4 ͼ���ѯ              *\n");
printf("     *  5 ȫ��ͼ����Ϣ                   6 �������˵�            *\n");
printf("     *  7 �˳�ϵͳ                                               *\n");
printf("     *************************************************************\n");
int a;
cin>>a;
while(a>7||a==0)
{
    cout<<"�Ƿ����룬����������\n";
    cin>>a;
}
if(a==1)
    add_book();
else if(a==2)
    delete_book();
else if(a==3)
    change_book_information();
else if(a==4)
    search_book();
else if(a==5)
    show_book();
else if(a==6)
    menu();
else if(a==7)
    exit(0);
book_manage_menu();
}

void add_book()
{
    system("cls");
    char bookname[20];
    int last_book_code;

    cout<<"��������";
    do{
            cin>>bookname;
            last_book_code=check_name(bookname);
    }while(last_book_code==-1);
    last_book_code+=1;


    FILE *fp;
    fp=fopen("book.dat","a+");
    struct library_book*head,*p,*rear;
    p = (struct library_book*)malloc(sizeof(struct library_book));

    cout<<"�������ߣ���Ӣ�ģ�\n";
    scanf("%s",p->writer);
    cout<<"���������\n";
    scanf("%s",p->publisher);
    cout<<"�����������\n";
    scanf("%s",p->publication_date);
    cout<<"����۸�ʹ�����֣�\n";
    scanf("%d",&p->price);
    cout<<"����ͼ������\n";
    scanf("%s",p->clss);
    cout<<"�����������ʹ�����֣�\n";
    scanf("%d",&p->sum);

    p->stock=p->sum;
    strcpy(p->book_name,bookname);
    p->book_code=last_book_code;
    p->next=NULL;
    head=open(fp);
    if(head==0)
        save(p);
    else
    {
        rear=head;
        while(rear->next)
            {
                rear=rear->next;
            }

        rear->next=p;
        save(head);
    }
    system("pause");
    book_manage_menu();
}
int save(struct library_book*head)
{
    struct library_book*p;
	p = head;
	FILE *fp;
	if ((fp = fopen("book.dat", "w+")) == NULL)
	{
		printf("�޷���\n");
        return 0;
	}
	while (head)
	{
		fwrite(head, sizeof(struct library_book), 1, fp);
		head = head->next;
	}
	fclose(fp);
	printf("����ɹ�\n");
}
int check_name(char bookname[20])
{
    FILE *fp;
    fp=fopen("book.dat","a+");
    struct library_book*ohead;
    ohead=open(fp);
    if(ohead==0)
        return 0;
    int num;
    while(ohead)
    {
        if(strcmp(bookname,ohead->book_name)==0)
            {
                cout<<"ͼ���Ѵ��ڣ���������\n";
                return -1;
            }
            num=ohead->book_code;
            ohead=ohead->next;
    }
    return num;
}
struct library_book* open(FILE *fp)
{
    struct library_book*op;
	struct library_book*ohead = NULL, *orear;
	op = (struct library_book*)malloc(sizeof(struct library_book));
	ohead = op;
	fread(op, sizeof(struct library_book), 1, fp);
	if (feof(fp) != 0)
	{
		printf("û����Ϣ\n");
		fclose(fp);
		system("pause");
		return 0;
	}
	orear = op;
	ohead = orear;
	op = (struct library_book*)malloc(sizeof(struct library_book));
	while (fread(op, sizeof(struct library_book), 1, fp) != NULL)
	{
		orear->next = op;
		orear = orear->next;
		op = (struct library_book*)malloc(sizeof(struct library_book));
	}
	orear->next = NULL;
	if (op == NULL)
		free(op);
	fclose(fp);
	return ohead;
};

void search_book()
{
    system("cls");
    cout<<"�����ַ�ʽ����\n1  ����������\n2  ����Ų���\n";
    int a;
    cin>>a;
    if(a==1)
        search_book_by_name();
    else if(a==2)
        search_book_by_code();
    return;
}
int search_book_by_name()
{
    cout<<"������������������";
    char bookname[20];
    cin>>bookname;
    FILE *fp;
    fp=fopen("book.dat","r+");
    struct library_book*head,*p;
    head=open(fp);
    if(head==0)
        {cout<<"û������\n";return 0;}
    while(head)
    {
        if(strcmp(head->book_name,bookname)==0)
        {
            show_single_book(head);
            system("pause");
            return 0;
        }
        head=head->next;
    }
    cout<<"δ�ҵ������Ϣ\n";
    system("pause");
    return 0;
}
int search_book_by_code()
{
    cout<<"�������������ı��";
    int code;
    cin>>code;
    FILE *fp;
    fp=fopen("book.dat","r+");
    struct library_book*head,*p;
    head=open(fp);
    if(head==0)
        {cout<<"û������\n";return 0;}
    while(head)
    {
        if(code==head->book_code)
        {
            show_single_book(head);
            system("pause");
            return 0;
        }
        head=head->next;
    }
    cout<<"δ�ҵ������Ϣ\n";
    system("pause");
    return 0;
}


void delete_book()
{
    system("cls");
    cout<<"�����ַ�ʽɾ��\n1  ������ɾ��\n2  �����ɾ��\n";
    int a;
    cin>>a;
    if(a==1)
        delete_book_by_name();
    else if(a==2)
        delete_book_by_code();
}
int delete_book_by_name()
{
    cout<<"��������ɾ��������";
    char bookname[20];
    cin>>bookname;
    FILE *fp;
    fp=fopen("book.dat","r+");
    struct library_book*head,*p,*headhead;
    head=open(fp);
    headhead=head;
    if(head==0)
        {cout<<"û������\n";book_manage_menu();}
    p=head->next;

    int flag=0;

    while(head)
    {
        if(strcmp(head->book_name,bookname)==0)
        {
            headhead=head->next;
            flag=1;

            //save(head->next);
            cout<<"ɾ���ɹ�\n";
            //system("pause");
            //book_manage_menu();
        }
        head->book_code-=1;
        if(p==NULL)
            break;
        if(strcmp(p->book_name,bookname)==0)
        {
            flag=1;
            del(headhead,head,p);
        }
        if(flag==1)
        head=head->next;
        p=p->next;
    }
    if(flag==1)
    {
        save(headhead);
        system("pause");
        book_manage_menu();
    }
    else
        cout<<"δ�ҵ������Ϣ\n";
        system("pause");
        book_manage_menu();

    return 0;
}
int delete_book_by_code()
{
    cout<<"��������ɾ���ı��";
    int code;
    cin>>code;
    FILE *fp;
    fp=fopen("book.dat","r+");
    struct library_book*headhead,*head,*p;
    head=open(fp);
    headhead=head;
    if(head==0)
        {cout<<"û������\n";book_manage_menu();}
    p=head->next;

    int flag=0;

    while(head)
    {
        if(code==head->book_code)
        {
            //save(head->next);
            cout<<"ɾ���ɹ�\n";
            //system("pause");
            //book_manage_menu();
            headhead=head->next;
            flag=1;
        }
        if(p==NULL)
            break;
        head->book_code-=1;
        if(code==p->book_code)
        {
            del(headhead,head,p);
            flag=1;
        }
        if(flag==1)
            p->book_code-=1;
        head=head->next;
        p=p->next;
    }
if(flag==1)
{
    save(headhead);
    system("pause");
    book_manage_menu();
}
else
        cout<<"δ�ҵ������Ϣ\n";
        system("pause");
    book_manage_menu();
}
struct library_book* del(struct library_book*hh,struct library_book*head,struct library_book*p)
{
    p=p->next;
    head->next=p;
    //save(hh);
    cout<<"ɾ���ɹ�\n";
    //system("pause");
    //book_manage_menu();
};

void show_book()
{
    system("cls");
    FILE *fp;
    fp=fopen("book.dat","r");
    struct library_book*ohead;
    ohead=open(fp);
    if(ohead==0)
        book_manage_menu();
    int num;
    while(ohead)
    {
        cout<<"*********************************************************\n";
        show_single_book(ohead);
        cout<<"*********************************************************\n\n";
        num=ohead->book_code;
        ohead=ohead->next;
    }
    system("pause");
}

void change_book_information()
{
    system("cls");
    cout<<"�����ַ�ʽ�޸�\n1  �������޸�\n2  ������޸�\n";
    int a;
    cin>>a;
    while(a!=1&&a!=2)
    {
        cout<<"�Ƿ����� ��������\n";
        cin>>a;
    }
    if(a==1)
        change_book_by_name();
    else if(a==2)
        change_book_by_code();
}
int change_book_by_name()
{
    cout<<"���������޸ĵ�����\n";
    char bookname[20];
    cin>>bookname;

    FILE *fp;
    fp=fopen("book.dat","r+");
    struct library_book*p,*head;
    p=open(fp);
    head=p;
    while(p)
    {
        if(strcmp(bookname,p->book_name)==0)
            change(p);
        p=p->next;
    }
    save(head);
    system("pause");
    book_manage_menu();
}
int change_book_by_code()
{
    cout<<"���������޸ĵ���ı��\n";
    int code;
    cin>>code;

    FILE *fp;
    fp=fopen("book.dat","r+");
    struct library_book*p,*head;
    p=open(fp);
    head=p;
    while(p)
    {
        if(code==p->book_code)
            change(p);
        p=p->next;
    }
    save(head);
    system("pause");
    book_manage_menu();
}
struct library_book* change(struct library_book*p)
{
    cout<<"1 �޸�����\n2 �޸�����\n3 �޸ĳ�����\n4 �޸ĳ�������\n5 �޸ļ۸�\n6 �޸����\n7 �޸��ܴ�\n8 �޸Ŀ��\n0 ȷ���޸�\n";
    int a;
    cin>>a;
    while(a!=0)
    {
        cout<<"����\n";
        if(a==1)
            cin>>p->book_name;
        else if(a==2)
            cin>>p->writer;
        else if(a==3)
            cin>>p->publisher;
        else if(a==4)
            cin>>p->publication_date;
        else if(a==5)
            cin>>p->price;
        else if(a==6)
            cin>>p->clss;
        else if(a==7)
            cin>>p->sum;
        else if(a==8)
            cin>>p->stock;
        cout<<"1 �޸�����\n2 �޸�����\n3 �޸ĳ�����\n4 �޸ĳ�������\n5 �޸ļ۸�\n6 �޸����\n7 �޸��ܴ�\n8 �޸Ŀ��\n0 ȷ���޸�\n";
        cin>>a;
    }
};


void search_borrowed_book()
{
    system("cls");
    cout<<"�������ѯ��ͼ������\n";
    char bookname[20];
    cin>>bookname;
    int bookcode,flag=0;
    bookcode=find_book(bookname);
    if(bookcode==0)
        return;
    cout<<"�����û��������\n";

    FILE *fp;
    fp=fopen("reader.dat","r");
    struct reader*head;
    head=open_reader(fp);
    if(head==0)
    {
        cout<<"�����û�\n";
        system("pause");
        return;
    }
    while(head)
    {
        for(int i=0;i<20;i++)
        {
            if(head->borrowed_book[i][0]==bookcode)
            {
                cout<<"*********************************************************\n";
                cout<<"�û���"<<head->name<<"\n";
                flag=1;
                cout<<"*********************************************************\n\n";
            }
        }
        head=head->next;
    }
    if(flag==0)
        cout<<"���û����\n";
    system("pause");
    return;
}
int main()
{
    menu();
    return 0;
}
