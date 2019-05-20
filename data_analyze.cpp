#include <iostream>
#include <string>
#include <stdlib.h>
#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "head.h"
using namespace std;

void data_analyze_menu()
{
    system("cls");
    printf("                          ���ݷ���ϵͳ  \n");
    printf("     *************************�˵�************************************\n");
    printf("     *  1 �������а�                      2 ����״̬                 *\n");
    printf("     *  3 ����ͳ��                        4 �������ڵ���δ������Ϣ   *\n");
    printf("     *  5 ������һ��                      6 �˳�ϵͳ                 *\n");
    printf("     *****************************************************************\n");
int a;
cin>>a;
while(a>6||a==0)
{
    cout<<"�Ƿ����룬����������\n";
    cin>>a;
}
if(a==1)
    rank_list();
else if(a==2)
    book_status();
else if(a==3)
    stastic();
else if (a==4)
    book_havenot_return();
else if(a==5)
    return;
else if(a==6)
    exit(0);
data_analyze_menu();
}
void rank_list()
{
    system("cls");
    cout<<"     *************************�������а�**********************************\n";

    FILE *fp;
    fp=fopen("book.dat","r+");
    struct library_book*head,*p;
    head=open(fp);
    p=head;
    if(head==0)
        {cout<<"û������\n";system("pause");return;}
    char top[11][20];
    int top_[11],t=0;
    top_[0]=9999;
    for(int i=1;i<11;i++)
    {
        int max_;
        max_=-1;
        p=head;
        t++;
        while(p)
        {
            t++;
            if(max_<=(p->sum-p->stock)&&(p->sum-p->stock)<=top_[i-1]&&strcmp(p->book_name,top[i-1])!=0)
            {
                max_=p->sum-p->stock;
                strcpy(top[i],p->book_name);
                top_[i]=max_;
            }
            p=p->next;
        }
    }
    for(int i=1;i<11&&i<t/10;i++)
    {
        cout<<"����   "<<top[i]<<"\n";
        cout<<"������ "<<top_[i]<<"\n";
    }
    system("pause");
    return;
}

void book_status()
{
    system("cls");
    cout<<"1 ������ͳ��\n2 ������ͳ��\n3 ��������ͳ��\n4 ����ͳ��\n";
    int a;
    cin>>a;
    while(a>4||a==0)
        cin>>a;
    cout<<"������Ϣ\n";
    char nnnn[20];
    cin>>nnnn;
    show_status(nnnn,a);
    return;
}
void show_status(char nnnn[20],int a)
{
    system("cls");
    FILE *fp;
    fp=fopen("book.dat","r");
    struct library_book*ohead;
    ohead=open(fp);
    if(ohead==0)
        return;
    int flag=0;
    while(ohead)
    {
        if(a==1){
            if(strcmp(ohead->book_name,nnnn)==0)
            {
                cout<<"*********************************************************\n";
                cout<<"������"<<nnnn<<"\n�������"<<(ohead->sum-ohead->stock)<<"\n";flag=1;system("pause");return;
                cout<<"*********************************************************\n\n";
                }
            }
        else if(a==2){
            if(strcmp(ohead->writer,nnnn)==0)
                {cout<<"*********************************************************\n";
                cout<<"������"<<ohead->book_name<<"\n�������"<<(ohead->sum-ohead->stock)<<"\n";
                flag=1;
                cout<<"*********************************************************\n\n";}
            }
        else if(a==3){
                if(strcmp(ohead->publisher,nnnn)==0)
                {cout<<"*********************************************************\n";
                cout<<"������"<<ohead->book_name<<"\n�������"<<(ohead->sum-ohead->stock)<<"\n";
                flag=1;
                cout<<"*********************************************************\n\n";}
            }
        else if(a==4){
                if(strcmp(ohead->clss,nnnn)==0)
                {cout<<"*********************************************************\n";
                cout<<"������"<<ohead->book_name<<"\n�������"<<(ohead->sum-ohead->stock)<<"\n";
                flag=1;
                cout<<"*********************************************************\n\n";}
            }
        ohead=ohead->next;
    }
    if(flag==0)
        cout<<"����Ϣ\n";
    system("pause");
    return;
}

void stastic()
{
    system("cls");
    FILE *fp;
    fp=fopen("book.dat","r");
    struct library_book*head;
    head=open(fp);
    char this_clss[50][20];
    int sum=0,Nreturn=0,class_sum[50]={0};
    if(head==0)
        return;
    int n=0,flag=0;
    while(head)
    {
        sum+=head->sum;
        Nreturn+=head->sum-head->stock;
        flag=0;
        for(int i=0;i<=n;i++)
        {
            if(strcmp(this_clss[i],head->clss)==0)
                flag=1;
        }
        if(flag==0)
        {
        strcpy(this_clss[n],head->clss);
        class_sum[n]+=(head->sum-head->stock);
        n++;
        }
        head=head->next;
    }
    cout<<"���ݲ��鹲"<<sum<<"��\n";
    cout<<"��"<<n<<"��\n";
    cout<<"�����"<<Nreturn<<"��\n";
    for(int i=0;i<n;i++)
    {
        cout<<this_clss[i]<<"�ࣺ"<<class_sum[i]<<"��\n";
        cout<<"***************************************\n";
    }
    system("pause");
    return;
}

void book_havenot_return()
{
    system("cls");
    FILE *fp;
    fp=fopen("reader.dat","r");
    struct reader*head;
    head=open_reader(fp);
    if(head==0)
        return;
    int flag=0,book_num=0,fflage=0;
    double fee_sum=0;
    while(head)
    {
        for(int i=0;i<20;i++)
        {
            if(head->borrowed_book[i][0]<=0)
                continue;
            time_t timep;
            struct tm*tm;
            time(&timep);
            tm=gmtime(&timep);
            int t;
            t=10-(tm->tm_mon-head->borrowed_book[i][1])*31+abs(head->borrowed_book[i][2]-tm->tm_mday);
            double fee;
            if(t<0)
            {
                if(flag==0)
                cout<<"�û�:"<<head->name<<"δ�黹:\n";
                fee=head->borrowed_book[i][3]*0.1+head->borrowed_book[i][3]*0.05*abs(t);
                flag=1,book_num++,fee_sum+=fee,fflage=1;
                cout<<"             "<<head->borrowed_book[i][0]<<"�����:"<<fee<<"Ԫ\n";
            }
        }
        if(flag==1)
        cout<<"����"<<book_num<<"��    "<<fee_sum<<"Ԫ\n";
        flag=0,book_num=0,fee_sum=0;
        head=head->next;
    }
    if(fflage==0)
        cout<<"������δ�黹ͼ��\n";
    system("pause");
    return;
}
