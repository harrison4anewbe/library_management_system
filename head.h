struct reader
{
    int reader_number;
    char reader_code[20];
    char name[20];
    char class_num[20];
    char student_num[20];
    int borrowed_book[20][4];
    int stu_tea;
    int level;
    double libcard;
    char libcard_code[20];
    struct reader*next;
};
struct library_book
{
    int book_code;
    char book_name[20];
    char writer[20];
    char publisher[20];
    char publication_date[20];
    int price;
    char clss[20];
    int sum;
    int stock;
    struct library_book*next;
};


void show_single_book(struct library_book*p);
void menu();
void book_manage_menu();
void borrow_menu();
void reader_menu();
void show_book();
int check_name(char bookname[20]);
int  main();

void add_book();
void delete_book();
void search_book();
struct library_book* open(FILE *fp);
int save(struct library_book*head);
int search_book_by_name();
int search_book_by_code();
int delete_book_by_name();
int delete_book_by_code();
struct library_book* del(struct library_book*hh,struct library_book*head,struct library_book*p);
void change_book_information();
int change_book_by_name();
int change_book_by_code();
struct library_book* change(struct library_book*p);

void reader_registe();
struct reader* open_reader(FILE *fp);
int save_reader(struct reader*head);
int judge_same(char *name);

void reader_log_in();
int judge_code(char*this_name,char*code,int t);
void reader_log_in_menu(struct reader*p,struct reader*headhead);
void my_infor(struct reader*p,struct reader*headhead);
void show_borrowed_book(struct reader*p,struct reader*headhead);
void show_residue_days(struct reader*p,int i,int price);

void change_code(struct reader*p,struct reader*headhead);

void borrow_book(struct reader*p,struct reader*headhead);
void return_book(struct reader*p,struct reader*headhead);

void book_continue(struct reader*p,struct reader*headhead);

int find_book(char bookname[20]);
int stock_add(char bookname[20],int num);
int stock_minus(char bookname[20],int num);

void reader_delet();

void change_reader_information(struct reader*p,struct reader*headhead);

void search_borrowed_book();

void data_analyze_menu();
void rank_list();

void book_status();
void show_status(char nnnn[20],int a);

void stastic();
void charge_card(struct reader*p,struct reader*headhead);

void book_havenot_return();
