#include <iostream>
#include <fstream>
#include <iomanip>
#include <windows.h>
#include <limits> // Required for numeric_limits

using namespace std;

void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
class student
{
    int rollno;
    char name[50];
    int p_marks, c_marks, m_marks, e_marks, cs_marks;
    float per;
    char grade;
    int std;
    void calculate()
    {
        per = static_cast<float>(p_marks + c_marks + m_marks + e_marks + cs_marks) / 5.0;
        if (per >= 60)
            grade = 'A';
        else if (per >= 50 && per < 60)
            grade = 'B';
        else if (per >= 40 && per < 50)
            grade = 'C';
        else
            grade = 'F';
    }

public:
    void getdata()
    {
        cout << "\nEnter the roll no of student: ";
        cin >> rollno;
        cin.ignore(1000, '\n');
        cin.clear();
        cout << "\n\nEnter the name of the student : ";
        cin.getline(name, sizeof(name));
        cout << "\nEnter the marks in Physics out of 100 : ";
        cin >> p_marks;
        cout << "\nEnter the marks in Chemistry out of 100 :";
        cin >> c_marks;
        cout << "\nEnter the marks in Mathematics out of 100 :";
        cin >> m_marks;
        cout << "\nEnter the marks in Englishout of 100 :";
        cin >> e_marks;
        cout << "\nEnter the marks in Computer Science out of 100 :";
        cin >> cs_marks;
        calculate();
    }

    void showdata()
    {
        cout << "\nRoll no of student : " << rollno;
        cout << "\nName of student : " << name;
        cout << "\nMarks in Physics : " << p_marks;
        cout << "\nMarks in Chemistry  : " << c_marks;
        cout << "\nMarks in  Mathematics: " << m_marks;
        cout << "\nMarks in English : " << e_marks;
        cout << "\nMarks in Computer Science : " << cs_marks;
        cout << "\nPercentage of student : " << setprecision(2) << per;
        cout << "\nThe grade of the student is : " << grade;
        cin.ignore(1000,'\n');
    }

    void show_tabular()
    {
        cout << rollno << setw(12) << name << setw(10) << p_marks << setw(3) << c_marks << setw(3)
             << m_marks << setw(3) << e_marks << setw(3) << cs_marks << setw(6) << setprecision(3) << per << " " << grade ;
         cout<<"\n\nCLICK ENTER TO CONTINUE..................";
    cin.ignore(1000,'\n');    
    }


    int retrollno()
    {
        return rollno;
    }

}; // class ends here

// global declaration for stream object

fstream fp;
student st;

// function to write in file

void write_student()
{
    fp.open("student.dat", ios::out | ios::app);
    st.getdata();
    fp.write((char *)&st, sizeof(student));
    fp.close();
    cout << "\n\n student record has been created ";
}

// function to read all records from file

void display_all()
{
    system("cls");
    cout << "\n\n\n\tDISPLAY ALL RECORD !!! \n\n";
    fp.open("student.dat", ios::in);
    while (fp.read((char *)&st, sizeof(student)))
    {
        st.showdata();
        cout << "\n\n=====================\n";
    }
    fp.close();
}

// function to read specific record from file

void display_sp(int n)
{
    int flag = 0;
    fp.open("student.dat", ios::in);
    while (fp.read((char *)&st, sizeof(student)) )
    {
        if (st.retrollno() == n)
        {
            system("cls");
            st.showdata();
            flag = 1;
        }
    }
    fp.close();
    if (flag == 0)
    {
        cout << "\n\nRecord not exist";
    }
}

// function to modify record of file

void modify_student()
{
    int no, found = 0;
    system("cls");
    cout << "\n\n\t To Modify  ";
    cout << "\n\n\t Please Enter The roll number of student ";
    cin >> no;
    fp.open("student.dat", ios::in | ios::out);
    while (fp.read((char *)&st, sizeof(student)) && found == 0)
    {
        if (st.retrollno() == no)
        {
            st.showdata();
            cout << "\nPlease Enter The New Details of student " << endl;
            st.getdata();
            int pos = -1 * static_cast<int>(sizeof(st));
            fp.seekp(pos, ios::cur);
            fp.write((char *)&st, sizeof(student));
            cout << "\n\n\t Record Updated";
            found = 1;
        }
    }
    fp.close();
    if (found == 0)
    {
        cout << "\n\n\tRecord Not Found ";
    }
}

// function to delete record of file

void delete_student()
{
    int no;
    system("cls");
    cout << "\n\n\n\tDelete Record ";
    cout << "\n\n\tPlease Enter the roll no of student to you want to delete : ";
    cin >> no;
    fp.open("student.dat", ios::in | ios::out);
    fstream fp2;
    fp2.open("Temp.dat", ios::out);
    fp.seekg(0, ios::beg);

    while (fp.read((char *)&st, sizeof(student)))
    {
        if (st.retrollno() != no)
        {
            fp2.write((char *)&st, sizeof(student));
        }
    }

    fp2.close();
    fp.close();
    remove("student.dat");
    rename("Temp.dat", "student.dat");
    cout << "\n\n\tRecord Deleted";
}

// function to display all student grade report

void class_result()
{
    system("cls");
    fp.open("student.dat", ios::in);

    if (!fp)
    {
        cout << "Error!!! FILE COULD NOT BE OPEN\n\n\n Go to entry menu to create file";
        cout << "\n\n\n Program is closing .... ";
        exit(0);
    }

    cout << "\n\n\t\tALL STUDENTS RESULT \n\n";
    cout << "=====================================================\n";
    cout << "Roll No. Name            P   C   M   E   CS  %age GRADE \n";
    cout << "======================================================\n";

    while (fp.read((char *)&st, sizeof(student)))
    {
        st.show_tabular();
    }
    fp.close();
}

// Function to display result menu

void result()
{
    int ans, rno;
    char ch;
    system("cls");
    cout << "\n\n\nRESULT  MENU";
    cout << "\n\n\n1. Class Result \n\n2. Student Report Card\n\n3. Back to Main Menu";
    cout << "\n\n\nEnter Choice (1/2)?";
    cin >> ans;

    switch (ans)
    {
    case 1:
        class_result();
        break;
    case 2:
        char ans2;
        do
        {
            system("cls");
            cout << "\n\nEnter Roll no of student : ";
            cin >> rno;
            display_sp(rno);
            cout << "\n\nDo you want to see more result (y/n)?";
            cin >> ans2;
        } while (ans2 == 'y' || ans2 == 'Y');
        break;
    case 3:
        break;
    default:
        cout << "\a";
    }
}

// INTRODUCTION FUNCTION

void intro()
{
    system("cls");
    cout << "STUDENT      REPORT CARD     PROJECT" << endl;
    cout << "\n\nMADE BY : CODE WITH SADIP";
    cout << "\n\nCONTACT : tamangsadip08@gmail.com";
    cout<<"\n\nCLICK ENTER TO CONTINUE..................";
    cin.ignore(1000,'\n');
}

// ENTRY / EDIT MENU FUNCTION

void entry_menu()
{
    system("cls");
    int ch2;
    cout << "\n\n\n\tENTRY MENU";
    cout << "\n\n\t1.CREATE STUDENT RECORD";
    cout << "\n\n\t2.DISPLAY ALL STUDENT RECORDS";
    cout << "\n\n\t3. SEARCH STUDENT RECORD";
    cout << "\n\n\t4.MODIFY STUDENT RECORD";
    cout << "\n\n\t5.DELETE STUDENT RECORDS";
    cout << "\n\n\t6.BACK T0 MAIN MENU";
    cout << "\n\n\tPlease Enter Your Choice (1-6) ";
    cin>>ch2;
    switch(ch2)
    {
    case 1 :
        system("cls");
        write_student();
        break;
    case 2 : 
        display_all();
        break;
    case 3 :
        int num;
        system("cls");
        cout << "\n\n\tEnter The Roll Number ";
        cin >> num;
        display_sp(num);
        break;
    case 4 :
        modify_student();
        break;
    case 5 :
        delete_student();
        break;
    case 6 :
        break;
    default :
        cout << "\a";
        entry_menu();
    }
}

// THE MAIN FUNCTION OF PROGRAM

int main()
{
    char ch;
    intro();
    do
    {
        system("cls");
        cout << "\n\n\tMAIN MENU";
        cout << "\n\n\t01. RESULT MENU";
        cout << "\n\n\t02. ENTRY/EDIT MENU";
        cout << "\n\n\t03. EXIT";
        cout << "\n\n\t04. Please Select Your Option (1-3)";
        ch = getchar();
        switch (ch)
        {
        case '1':
            system("cls");
            result();
            break;
        case '2':
            entry_menu();
            break;
        case '3':
            exit(0);
        default:
            cout << "\a";
        }
    } while (ch != '3');
    return (1);
}

// END OF PROJECT