//***************************************************************
//                   HEADER FILE USED IN PROJECT
//****************************************************************

#include<fstream>
#include<conio.h>
#include<stdio.h>
#include<process.h>
#include<string.h>
#include<iomanip>
#include <iostream>
#include<graphics.h>
#include<windows.h>
#include <stdexcept>
#include <stdlib.h>

using namespace std;

void intro();

//Password
string getpassword( const string& prompt = "Enter password> " )
  {
  string result;

  // Set the console mode to no-echo, not-line-buffered input
  DWORD mode, count;
  HANDLE ih = GetStdHandle( STD_INPUT_HANDLE  );
  HANDLE oh = GetStdHandle( STD_OUTPUT_HANDLE );
  if (!GetConsoleMode( ih, &mode ))
    throw runtime_error(
      "getpassword: You must be connected to a console to use this program.\n"
      );
  SetConsoleMode( ih, mode & ~(ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT) );

  // Get the password string
  WriteConsoleA( oh, prompt.c_str(), prompt.length(), &count, NULL );
  char c;
  while (ReadConsoleA( ih, &c, 1, &count, NULL) && (c != '\r') && (c != '\n'))
    {
    if (c == '\b')
      {
      if (result.length())
        {
        WriteConsoleA( oh, "\b \b", 3, &count, NULL );
        result.erase( result.end() -1 );
        }
      }
    else
      {
      WriteConsoleA( oh, "*", 1, &count, NULL );
      result.push_back( c );
      }
    }

  // Restore the console mode
  SetConsoleMode( ih, mode );

  return result;
  }


  //Login function validation
int login()
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    string user;
    string password;
    bool loginSuccess = false;

    cout<<setw(40)<<"Login Page"<<endl;

    do{
    SetConsoleTextAttribute(h,14);
    cout<<setw(20)<<"Username: ";
    cin>>user;
    cout<<"\n          ";
    password = getpassword("Password");
    if(user=="admin" && password=="admin")
    {
        SetConsoleTextAttribute(h,13);
        cout<<"\nLogin Successfully!!!"<<endl;
        SetConsoleTextAttribute(h,11);
        loginSuccess = true;
        system("pause");
        system("cls");
        intro();
    }
    else{
         system("cls");
         SetConsoleTextAttribute(h,12);
         cout<<"\n\nIncorrect username or password!!          \n Try again"<<endl;
         system("pause");
         system("cls");
    }
    }while(!loginSuccess);
    cout<<"\n\n\n";
    system("pause");
    return 0;
}


//***************************************************************
//                   CLASS USED IN PROJECT
//****************************************************************




void gotoxy(int x, int y)
{
  static HANDLE h = NULL;
  if(!h)
    h = GetStdHandle(STD_OUTPUT_HANDLE);
  COORD c = { x, y };
  SetConsoleCursorPosition(h,c);
}

class book
{
	char BookNo[6];
	char BookName[50];
	char AuthorName[20];
	int token;
  public:
	void create_book()
	{
        cout<<"\nNEW BOOK ENTRY...\n";
        cout<<"\nEnter The book no.";
        cin>>BookNo;
        cin.ignore();
        cout<<"\n\nEnter The Name of The Book ";
        gets(BookName);
        cout<<"\n\nEnter The Author's Name ";
        gets(AuthorName);
        cout<<"\n\n\nBook Created..";
    }

    void show_book()
    {
        cout<<"\nBook no. : "<<BookNo;
        cout<<"\nBook Name : ";
        puts(BookName);
        cout<<"Author Name : ";
        puts(AuthorName);
    }

    void modify_book()
    {
        cout<<"\nBook no. : "<<BookNo;
        cin.ignore();
        cout<<"\nModify Book Name : ";
        gets(BookName);
        cout<<"\nModify Author's Name of Book : ";
        gets(AuthorName);
    }

    char* retBookNo()
    {
        return BookNo;
    }

    void report()
    {cout<<BookNo<<setw(30)<<BookName<<setw(30)<<AuthorName<<endl;}

    /*int rettoken()
    {
        return token;
    }

    void addtoken()
    {token=1;}
*/



};         //class ends here




class student
{
    char admno[6];
    char name[20];
    char stBookNo[6];
    int token;
public:
    void create_student()
    {
        system("cls");
         cout<<"\nNEW STUDENT ENTRY...\n";
        cout<<"\nEnter The admission no. ";
        cin>>admno;
        cin.ignore();
        cout<<"\n\nEnter The Name of The Student ";

        gets(name);
        token=0;
        stBookNo[0]='/0';
        cout<<"\n\nStudent Record Created..";
    }

    void show_student()
    {
        cout<<"\nAdmission no. : "<<admno;
        cout<<"\nStudent Name : ";
        puts(name);
        cout<<"\nNo of Book issued : "<<token;
        if(token==1)
            cout<<"\nBook No "<<stBookNo;
    }

    void modify_student()
    {
        cout<<"\nAdmission no. : "<<admno;
        cin.ignore();
        cout<<"\nModify Student Name : ";
        gets(name);
    }

    char* retadmno()
    {
        return admno;
    }

    char* retstBookNo()
    {
        return stBookNo;
    }

    int rettoken()
    {
        return token;
    }

    void addtoken()
    {token=1;}

    void resettoken()
    {token=0;}

    void getstBookNo(char t[])
    {
        strcpy(stBookNo,t);
    }

    void report()
    {cout<<"\t"<<admno<<setw(20)<<name<<setw(10)<<token<<endl;}

};         //class ends here




//***************************************************************
//        global declaration for stream object, object
//****************************************************************

fstream fp,fp1;
book bk;
student st;


//***************************************************************
//        function to write in file
//****************************************************************


/*
void check_id()
{
	char bn[6];
	int found=0;
	system("cls");
	cout<<"Enter book id: "<<endl;
	cin>>bn;

	fp.open("book.dat",ios::in|ios::out);

	while(fp.read((char*)&bk,sizeof(book)) && found ==0)
	{
		if(strcmp(bk.retBookNo(),bn)==0)
			{
				found=1;
				cout<<"Can not be duplicated the Book ID...."<<endl;
				bk.addtoken();

			}

	}

}
*/


void write_book()
{
    char ch;
    fp.open("book.dat",ios::out|ios::app);
    do
    {
        system("cls");
        //check_id();
        //if(bk.rettoken()==0)
        //{

                bk.create_book();
                fp.write((char*)&bk,sizeof(book));
                cout<<"\n\nDo you want to add more record..(y/n?)";
                cin>>ch;

        //}
        //else{
           // cout<<"Duplicated Book Id"<<endl;
        //}


    }while(ch=='y'||ch=='Y');
    fp.close();
}

void write_student()
{
    char ch;
    fp.open("student.dat",ios::out|ios::app);
    do
    {
        st.create_student();
        fp.write((char*)&st,sizeof(student));
        cout<<"\n\ndo you want to add more record..(y/n?)";
        cin>>ch;
    }while(ch=='y'||ch=='Y');
    fp.close();
}


//***************************************************************
//        function to read specific record from file
//****************************************************************


void display_spb(char n[])
{
    cout<<"\nBOOK DETAILS\n";
    int flag=0;
    fp.open("book.dat",ios::in);
    while(fp.read((char*)&bk,sizeof(book)))
    {
        if(strcmp(bk.retBookNo(),n)==0)
        {
            bk.show_book();
             flag=1;
        }
    }

    fp.close();
    if(flag==0)
        cout<<"\n\nBook does not exist";
    _getch();
}

void display_sps(char n[])
{
    cout<<"\nSTUDENT DETAILS\n";
    int flag=0;
    fp.open("student.dat",ios::in);
    while(fp.read((char*)&st,sizeof(student)))
    {
        if((strcmp(st.retadmno(),n)==0))
        {
            st.show_student();
            flag=1;
        }
    }

    fp.close();
    if(flag==0)
            cout<<"\n\nStudent does not exist";
     _getch();
}


//***************************************************************
//        function to modify record of file
//****************************************************************


void modify_book()
{
    char n[6];
    int found=0;
    system("cls");
    cout<<"\n\n\tMODIFY BOOK REOCORD.... ";
    cout<<"\n\n\tEnter The book no. of The book";
    cin>>n;
    fp.open("book.dat",ios::in|ios::out);
    while(fp.read((char*)&bk,sizeof(book)) && found==0)
    {
        if(strcmp(bk.retBookNo(),n)==0)
        {
            bk.show_book();
            cout<<"\nEnter The New Details of book"<<endl;
            bk.modify_book();
            int pos=-1*sizeof(bk);
                fp.seekp(pos,ios::cur);
                fp.write((char*)&bk,sizeof(book));
                cout<<"\n\n\t Record Updated";
                found=1;
        }
    }

        fp.close();
        if(found==0)
            cout<<"\n\n Record Not Found ";
        _getch();
}


void modify_student()
{
    char n[6];
    int found=0;
    system("cls");
    cout<<"\n\n\tMODIFY STUDENT RECORD... ";
    cout<<"\n\n\tEnter The admission no. of The student";
    cin>>n;
    fp.open("student.dat",ios::in|ios::out);
    while(fp.read((char*)&st,sizeof(student)) && found==0)
    {
        if(strcmp(st.retadmno(),n)==0)
        {
            st.show_student();
            cout<<"\nEnter The New Details of student"<<endl;
            st.modify_student();
            int pos=-1*sizeof(st);
            fp.seekp(pos,ios::cur);
            fp.write((char*)&st,sizeof(student));
            cout<<"\n\n\t Record Updated";
            found=1;
        }
    }

    fp.close();
    if(found==0)
        cout<<"\n\n Record Not Found ";
    _getch();
}

//***************************************************************
//        function to delete record of file
//****************************************************************


void delete_student()
{
    char n[6];
    int flag=0;
    system("cls");
        cout<<"\n\n\n\tDELETE STUDENT...";
        cout<<"\n\nEnter The admission no. of the Student You Want To Delete : ";
        cin>>n;
        fp.open("student.dat",ios::in|ios::out);
        fstream fp2;
        fp2.open("Temp.dat",ios::out);
        fp.seekg(0,ios::beg);
        while(fp.read((char*)&st,sizeof(student)))
    {
        if(strcmp(st.retadmno(),n)!=0)
                 fp2.write((char*)&st,sizeof(student));
        else
               flag=1;
    }

    fp2.close();
        fp.close();
        remove("student.dat");
        rename("Temp.dat","student.dat");
        if(flag==1)
             cout<<"\n\n\tRecord Deleted ..";
        else
             cout<<"\n\nRecord not found";
        _getch();
}


void delete_book()
{
    char n[6];
    system("cls");
    cout<<"\n\n\n\tDELETE BOOK ...";
    cout<<"\n\nEnter The Book no. of the Book You Want To Delete : ";
    cin>>n;
    fp.open("book.dat",ios::in|ios::out);
    fstream fp2;
    fp2.open("Temp.dat",ios::out);
    fp.seekg(0,ios::beg);
    while(fp.read((char*)&bk,sizeof(book)))
    {
        if(strcmp(bk.retBookNo(),n)!=0)
        {
            fp2.write((char*)&bk,sizeof(book));
        }
    }

    fp2.close();
        fp.close();
        remove("book.dat");
        rename("Temp.dat","book.dat");
        cout<<"\n\n\tRecord Deleted ..";
        _getch();
}



//***************************************************************
//        function to display all students list
//****************************************************************

void display_alls()
{
    system("cls");
         fp.open("student.dat",ios::in);
         if(!fp)
         {
               cout<<"ERROR!!! FILE COULD NOT BE OPEN ";
               _getch();
               return;
         }

    cout<<"\n\n\t\tSTUDENT LIST\n\n";
    cout<<"==================================================================\n";
    cout<<"\tAdmission No."<<setw(10)<<"Name"<<setw(20)<<"Book Issued\n";
    cout<<"==================================================================\n";

    while(fp.read((char*)&st,sizeof(student)))
    {
        st.report();
    }

    fp.close();
    _getch();
}


//***************************************************************
//        function to display Books list
//****************************************************************

void display_allb()
{
    system("cls");
    fp.open("book.dat",ios::in);
    if(!fp)
    {
        cout<<"ERROR!!! FILE COULD NOT BE OPEN ";
               _getch();
               return;
         }

    cout<<"\n\n\t\tBook LIST\n\n";
    cout<<"=========================================================================\n";
    cout<<"Book Number"<<setw(20)<<"Book Name"<<setw(25)<<"Author\n";
    cout<<"=========================================================================\n";

    while(fp.read((char*)&bk,sizeof(book)))
    {
        bk.report();
    }
         fp.close();
         _getch();
}



//***************************************************************
//        function to issue book
//****************************************************************

void book_issue()
{
    char sn[6],bn[6];
    int found=0,flag=0;
    system("cls");
    cout<<"\n\nBOOK ISSUE ...";
    cout<<"\n\n\tEnter The student's admission no.";
    cin>>sn;
    fp.open("student.dat",ios::in|ios::out);
        fp1.open("book.dat",ios::in|ios::out);
        while(fp.read((char*)&st,sizeof(student)) && found==0)
           {
        if(strcmp(st.retadmno(),sn)==0)
        {
            found=1;
            if(st.rettoken()==0)
            {
                      cout<<"\n\n\tEnter the book no. ";
                cin>>bn;
                while(fp1.read((char*)&bk,sizeof(book))&& flag==0)
                {
                       if(strcmp(bk.retBookNo(),bn)==0)
                    {
                        bk.show_book();
                        flag=1;
                        st.addtoken();
                        st.getstBookNo(bk.retBookNo());
                               int pos=-1*sizeof(st);
                        fp.seekp(pos,ios::cur);
                        fp.write((char*)&st,sizeof(student));
                        cout<<"\n\n\t Book issued successfully\n\nPlease Note: Write current date in backside of book and submit within 15 days fine Rs. 1 for each day after 15 days period";
                    }
                    }
                  if(flag==0)
                        cout<<"Book no does not exist";
            }
                else
                  cout<<"You have not returned the last book ";

        }
    }
          if(found==0)
        cout<<"Student record not exist...";
    _getch();
      fp.close();
      fp1.close();
}

//***************************************************************
//        function to deposit book
//****************************************************************

void book_deposit()
{
    char sn[6],bn[6];
    int found=0,flag=0,day,fine;
    system("cls");
    cout<<"\n\nBOOK DEPOSIT ...";
    cout<<"\n\n\tEnter The student admission no.";
    cin>>sn;
    fp.open("student.dat",ios::in|ios::out);
    fp1.open("book.dat",ios::in|ios::out);
    while(fp.read((char*)&st,sizeof(student)) && found==0)
       {
        if(strcmp(st.retadmno(),sn)==0)
        {
            found=1;
            if(st.rettoken()==1)
            {
            while(fp1.read((char*)&bk,sizeof(book))&& flag==0)
            {
               if(strcmp(bk.retBookNo(),st.retstBookNo())==0)
            {
                bk.show_book();
                flag=1;
                cout<<"\n\nBook deposited in no. of days";
                cin>>day;
                if(day>15)
                {
                   fine=(day-15)*1;
                   cout<<"\n\nFine has to deposited Rs. "<<fine;
                }
                    st.resettoken();
                    int pos=-1*sizeof(st);
                    fp.seekp(pos,ios::cur);
                    fp.write((char*)&st,sizeof(student));
                    cout<<"\n\n\t Book deposited successfully";
            }
            }
          if(flag==0)
            cout<<"Book no does not exist";
              }
         else
            cout<<"No book is issued..please check!!";
        }
       }
      if(found==0)
    cout<<"Student record not exist...";
    _getch();
  fp.close();
  fp1.close();
  }




//***************************************************************
//        INTRODUCTION FUNCTION
//****************************************************************

void intro()
{

    system("cls");
    system("COLOR 2F");
    int i;
 for(i=1; i<=120; i++)
    {

        cout<<"*";
    }
    gotoxy(50,10);
    cout<<"LIBRARY MANAGEMENT SYSTEM\n\n\n\n";
    for(i=1; i<=120; i++)
    {

        cout<<"*";
    }
    _getch();
}



//***************************************************************
//        ADMINISTRATOR MENU FUNCTION
//****************************************************************

void admin_menu()
{
    system("cls");
    system("COLOR 3F");
    int ch2;
    gotoxy(35,11);
    cout<<"ADMIN MENU";
    cout<<"\n\n\t1.ADD STUDENT RECORD";
    cout<<"\n\n\t2.DISPLAY ALL STUDENTS RECORD";
    cout<<"\n\n\t3.SEARCH SPECIFIC STUDENT RECORD ";
    cout<<"\n\n\t4.UPDATE STUDENT RECORD";
    cout<<"\n\n\t5.DELETE STUDENT RECORD";
    cout<<"\n\n\t6.ADD BOOK ";
    cout<<"\n\n\t7.DISPLAY ALL BOOKS ";
    cout<<"\n\n\t8.SEARCH SPECIFIC BOOK ";
    cout<<"\n\n\t9.UPDATE BOOK ";
    cout<<"\n\n\t10.DELETE BOOK ";
    cout<<"\n\n\t11.BACK TO MAIN MENU";
    cout<<"\n\n\tPlease Enter Your Choice (1-11) ";
    cin>>ch2;
    switch(ch2)
    {
            case 1: system("cls");
                write_student();break;
            case 2: display_alls();break;
            case 3:
                   char num[6];
                   system("cls");
                   cout<<"\n\n\tPlease Enter The Admission No. ";
                   cin>>num;
                   display_sps(num);
                   break;
              case 4: modify_student();break;
              case 5: delete_student();break;
        case 6: system("cls");
            write_book();break;
        case 7: display_allb();break;
        case 8: {
                   char num[6];
                   system("cls");
                   cout<<"\n\n\tPlease Enter The book No. ";
                   cin>>num;
                   display_spb(num);
                   break;
            }
              case 9: modify_book();break;
              case 10: delete_book();break;
             case 11: return;
              default:cout<<"\a";
       }
       admin_menu();
}


//***************************************************************
//        THE MAIN FUNCTION OF PROGRAM
//****************************************************************


void ext()
{
    system("cls");
    int i;
    system("color 0c");
    gotoxy(35,11);
    cout<<"\n\n\t\t Thank you for using C++ Library Management System Project\n\n";
    cout<<"by: "<<"\n Rukesh Duwal \n";
    system("pause");
    system("cls");
    cout<<"\n\n\t\t\t Exiting\n\n";
    for(i=1; i<=120; i++)
    {
        Sleep(20);
        cout<<"*";
    }
    exit(0);
}

int main()
{
    char ch;
    login();
    do
    {
        system("cls");
        system("COLOR 9");
        cout<<"\n\n\n\tMAIN MENU";
        cout<<"\n\n\t01. ADMINISTRATOR MENU";
        cout<<"\n\n\t02. BOOK ISSUE";
          cout<<"\n\n\t03. BOOK DEPOSIT";
          cout<<"\n\n\t04. EXIT";
          cout<<"\n\n\tPlease Select Your Option (1-4) ";
          ch=getche();
          switch(ch)
          {
            case '1':system("cls");
                    admin_menu();
                    break;
              case '2':book_issue();
                     break;
              case '3':book_deposit();
                 break;
              case '4':ext();
              default :cout<<"\a";
        }
        }while(ch!='4');
}

//***************************************************************
//                END OF PROJECT
//**
