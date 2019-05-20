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
printf("                          图书管理系统  \n");
printf("     *************************主菜单********************************\n");
printf("     *  1 图书出入库管理                    2 借阅查询             *\n");//查询谁借了这本书
printf("     *  3 读者管理                          4 数据分析             *\n");
printf("     *  5 退出系统                                                 *\n");
printf("     ***************************************************************\n");
int a;
cin>>a;
while(a>5||a==0)
{
    cout<<"非法输入，请重新输入\n";
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
printf("                      图书出入库管理系统  \n");
printf("     *************************菜单********************************\n");
printf("     *  1 图书添加                       2 图书删除              *\n");
printf("     *  3 图书信息修改                   4 图书查询              *\n");
printf("     *  5 全部图书信息                   6 返回主菜单            *\n");
printf("     *  7 退出系统                                               *\n");
printf("     *************************************************************\n");
int a;
cin>>a;
while(a>7||a==0)
{
    cout<<"非法输入，请重新输入\n";
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

    cout<<"输入书名";
    do{
            cin>>bookname;
            last_book_code=check_name(bookname);
    }while(last_book_code==-1);
    last_book_code+=1;


    FILE *fp;
    fp=fopen("book.dat","a+");
    struct library_book*head,*p,*rear;
    p = (struct library_book*)malloc(sizeof(struct library_book));

    cout<<"输入作者（用英文）\n";
    scanf("%s",p->writer);
    cout<<"输入出版商\n";
    scanf("%s",p->publisher);
    cout<<"输入出版日期\n";
    scanf("%s",p->publication_date);
    cout<<"输入价格（使用数字）\n";
    scanf("%d",&p->price);
    cout<<"输入图书种类\n";
    scanf("%s",p->clss);
    cout<<"输入入库数（使用数字）\n";
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
		printf("无法打开\n");
        return 0;
	}
	while (head)
	{
		fwrite(head, sizeof(struct library_book), 1, fp);
		head = head->next;
	}
	fclose(fp);
	printf("保存成功\n");
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
                cout<<"图书已存在，重新输入\n";
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
		printf("没有信息\n");
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
    cout<<"按哪种方式查找\n1  按书名查找\n2  按编号查找\n";
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
    cout<<"输入你想搜索的书名";
    char bookname[20];
    cin>>bookname;
    FILE *fp;
    fp=fopen("book.dat","r+");
    struct library_book*head,*p;
    head=open(fp);
    if(head==0)
        {cout<<"没有数据\n";return 0;}
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
    cout<<"未找到相关信息\n";
    system("pause");
    return 0;
}
int search_book_by_code()
{
    cout<<"输入你想搜索的编号";
    int code;
    cin>>code;
    FILE *fp;
    fp=fopen("book.dat","r+");
    struct library_book*head,*p;
    head=open(fp);
    if(head==0)
        {cout<<"没有数据\n";return 0;}
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
    cout<<"未找到相关信息\n";
    system("pause");
    return 0;
}


void delete_book()
{
    system("cls");
    cout<<"按哪种方式删除\n1  按书名删除\n2  按编号删除\n";
    int a;
    cin>>a;
    if(a==1)
        delete_book_by_name();
    else if(a==2)
        delete_book_by_code();
}
int delete_book_by_name()
{
    cout<<"输入你想删除的书名";
    char bookname[20];
    cin>>bookname;
    FILE *fp;
    fp=fopen("book.dat","r+");
    struct library_book*head,*p,*headhead;
    head=open(fp);
    headhead=head;
    if(head==0)
        {cout<<"没有数据\n";book_manage_menu();}
    p=head->next;

    int flag=0;

    while(head)
    {
        if(strcmp(head->book_name,bookname)==0)
        {
            headhead=head->next;
            flag=1;

            //save(head->next);
            cout<<"删除成功\n";
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
        cout<<"未找到相关信息\n";
        system("pause");
        book_manage_menu();

    return 0;
}
int delete_book_by_code()
{
    cout<<"输入你想删除的编号";
    int code;
    cin>>code;
    FILE *fp;
    fp=fopen("book.dat","r+");
    struct library_book*headhead,*head,*p;
    head=open(fp);
    headhead=head;
    if(head==0)
        {cout<<"没有数据\n";book_manage_menu();}
    p=head->next;

    int flag=0;

    while(head)
    {
        if(code==head->book_code)
        {
            //save(head->next);
            cout<<"删除成功\n";
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
        cout<<"未找到相关信息\n";
        system("pause");
    book_manage_menu();
}
struct library_book* del(struct library_book*hh,struct library_book*head,struct library_book*p)
{
    p=p->next;
    head->next=p;
    //save(hh);
    cout<<"删除成功\n";
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
    cout<<"按哪种方式修改\n1  按书名修改\n2  按编号修改\n";
    int a;
    cin>>a;
    while(a!=1&&a!=2)
    {
        cout<<"非法输入 重新输入\n";
        cin>>a;
    }
    if(a==1)
        change_book_by_name();
    else if(a==2)
        change_book_by_code();
}
int change_book_by_name()
{
    cout<<"输入你想修改的书名\n";
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
    cout<<"输入你想修改的书的编号\n";
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
    cout<<"1 修改书名\n2 修改作者\n3 修改出版社\n4 修改出版日期\n5 修改价格\n6 修改类别\n7 修改总存\n8 修改库存\n0 确认修改\n";
    int a;
    cin>>a;
    while(a!=0)
    {
        cout<<"输入\n";
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
        cout<<"1 修改书名\n2 修改作者\n3 修改出版社\n4 修改出版日期\n5 修改价格\n6 修改类别\n7 修改总存\n8 修改库存\n0 确认修改\n";
        cin>>a;
    }
};


void search_borrowed_book()
{
    system("cls");
    cout<<"输入想查询的图书名称\n";
    char bookname[20];
    cin>>bookname;
    int bookcode,flag=0;
    bookcode=find_book(bookname);
    if(bookcode==0)
        return;
    cout<<"以下用户借出此书\n";

    FILE *fp;
    fp=fopen("reader.dat","r");
    struct reader*head;
    head=open_reader(fp);
    if(head==0)
    {
        cout<<"暂无用户\n";
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
                cout<<"用户："<<head->name<<"\n";
                flag=1;
                cout<<"*********************************************************\n\n";
            }
        }
        head=head->next;
    }
    if(flag==0)
        cout<<"无用户借出\n";
    system("pause");
    return;
}
int main()
{
    menu();
    return 0;
}
