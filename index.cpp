#include <iostream>
#include <fstream>
#include <vector>
#include <conio.h>
using namespace std;

class record
{
    string date, time;
    string title;
    string note;
    string password;

    void load_pass()
    {
        ifstream in("password.txt");
        if (in.is_open())
        {
            getline(in, password);
            in.close();
            return;
        }
        else
        {
            password = "abc123";
        }
    }

    void save_pass(string &pass)
    {
        ofstream out("password.txt");
        out << pass;
        out.close();
    }

    bool match_pass()
    {
        string pass;
        char ch;
        cout << "********************" << endl;
        cout << "ENTER THE PASSWORD" << endl;
        cout << "********************" << endl;
        ch = getch();
        // while (ch != '\r')
        // {
        //     if (ch == '\b')
        //     {
        //         if (!pass.empty())
        //         {
        //             pass.pop_back();
        //             cout << "\b \b";
        //         }
        //     }
        //     pass.push_back(ch);
        // }

        cin >> pass;
        if (pass == password)
        {
            return true;
        }
        else
        {
            return false;
        }
    };

public:
    record()
    {
        load_pass();
    }
    void add_record();
    void view_record();
    void edit_password();
    void edit_record();
};

void clearScreen()
{
#if defined(_WIN32) || defined(_WIN64)
    system("cls"); // Windows-specific command
#else
    system("clear"); // Linux/Unix/MacOS command
#endif
}

void backTomenu()
{
    cout << "PRESS ANY KEY TO CONTINUE !" << endl;
    getch();
    return;
}

void record::add_record()
{
    string date, filename;
    fstream f;
    if (match_pass())
    {
        clearScreen();
        std::cout << "************************************************" << endl;
        std::cout << "TO ADD A NEW RECORD ENTER THE DATE [dd-mm-yyyy]!" << endl;
        std::cout << "************************************************" << endl
                  << endl;
        cin.ignore();
        getline(cin, date);
        filename = date + ".txt";
        f.open(filename, ios::out | ios::app);
        if (!f.is_open())
        {
            clearScreen();
            cout << "SYSTEM ERROR" << endl;
            cout << "PRESS ANY KEY TO CONTINUE !" << endl;
            getch();
            return;
        }
        else
        {
            clearScreen();
            cout << "************************" << endl;
            cout << "ENTER RECORD DETAILS !" << endl;
            cout << "************************" << endl
                 << endl;
            cout << endl
                 << "Time [hh:mm] : " << endl;
            getline(cin, time);
            cout << endl
                 << "Title : " << endl;
            getline(cin, title);
            cout << endl
                 << "Note : (type 'END-X' on a new line to end input)" << endl
                 << endl;
            // Multi-line input for the note
            note.clear(); // Clear previous note if any
            string line;
            while (getline(cin, line) && line != "END-X")
            {
                note += line + "\n"; // Append each line to the note string with a newline
            }

            f << time << endl
              << endl;
            f << title << endl
              << endl;
            f << note << endl;
            f.close();
            return;
        }
    }
    else
    {
        cout << "Incorrect Password !" << endl
             << endl;
        backTomenu();
    }
}

void record::view_record()
{
    string filename, date;
    fstream f;
    if (match_pass())
    {
        clearScreen();
        cout << "************************" << endl;
        cout << "ENTER DATE OF ENTRY !" << endl;
        cout << "*************************" << endl
             << endl;
        cin >> date;
        filename = date + ".txt";
        f.open(filename, ios::in);
        if (!f.is_open())
        {
            clearScreen();
            cout << "File does not exist" << endl;
            cout << "PRESS ANY KEY TO CONTINUE !" << endl;
            getch();
            return;
        }
        else
        {
            char ch;
            while (f.get(ch))
            {
                cout << ch;
            }
            f.close();
            return;
        }
    }
    else
    {
        cout << "Incorrect Password !" << endl
             << endl;
        backTomenu();
    }
}

void record::edit_record()
{
    if (match_pass())
    {
        clearScreen();
        string filename;
        fstream f;
        cout << "************************" << endl;
        cout << "ENTER DATE OF ENTRY !" << endl;
        cout << "*************************" << endl
             << endl;
        cin >> date;
        cin.ignore();
        filename = date + ".txt";
        f.open(filename, ios::in | ios::binary);
        if (!f.is_open())
        {
            clearScreen();
            cout << "File does not exist" << endl;
            cout << "PRESS ANY KEY TO CONTINUE !" << endl;
            getch();
            return;
        }
        else
        {
            vector<string> lines;
            string line;
            while (getline(f, line))
            {
                lines.push_back(line);
            }
            f.close();

            cout << "********************" << endl;
            cout << "EXISTING RECORDS -> " << endl;
            cout << "********************" << endl
                 << endl;

            for (int i = 0; i < lines.size(); i++)
            {
                cout << i + 1 << " " << lines[i] << endl;
            }

            cout << "*****************************" << endl;
            cout << "SELECT RECORD NUMBER TO EDIT" << endl;
            cout << "*****************************" << endl;
            int n;
            cin >> n;
            cin.ignore();
            if (n >= 0 && n < lines.size())
            {
                clearScreen();
                cout << "*****************" << endl;
                cout << "ENTER NEW LINE : " << endl;
                cout << "******************" << endl
                     << endl;
                string newline;
                getline(cin, newline);
                lines[n - 1] = newline;

                f.open(filename, ios::out | ios::trunc);
                for (const auto &it : lines)
                {
                    f << it << endl;
                }
                f.close();
                clearScreen();
                cout << "*****************************" << endl;
                cout << " RECORD SUCCESSFULLY EDITED !" << endl;
                cout << "*****************************" << endl;

                return;
            }
            else
            {
                cout << "Invalid record number " << endl;
            }
        }
    }
    else
    {
        cout << "Incorrect Password !" << endl
             << endl;
        backTomenu();
    }
}

void record::edit_password()
{
    if (match_pass())
    {
        string new_pass, confirm_pass;
        clearScreen();
        cout << "********************" << endl;
        cout << " ENTER NEW PASSWORD  " << endl;
        cout << "********************" << endl
             << endl;
        cin.ignore();
        getline(cin, new_pass);
        cout << endl
             << endl;
        cout << "******************" << endl;
        cout << " CONFIRM PASSWORD " << endl;
        cout << "******************" << endl
             << endl;
        getline(cin, confirm_pass);

        if (new_pass != confirm_pass)
        {
            cout << "**********************" << endl;
            cout << "PASSWORDS NOT MATCHING" << endl;
            cout << "**********************" << endl
                 << endl;
            return;
        }
        else
        {
            cout << "----exit program to save password----" << endl;
            cout << "****************" << endl;
            cout << "PASSWORD UPDATED" << endl;
            cout << "****************" << endl
                 << endl;
            save_pass(new_pass);
        }
    }
    else
    {
        cout << "Incorrect Password !" << endl
             << endl;
        backTomenu();
    }
}

int main()
{
    int option;
    record r; // Create an object of the record class
    do
    {
        clearScreen();
        cout << "*************************" << endl;
        cout << "WELCOME TO PERSONAL DIARY" << endl;
        cout << "*************************" << endl
             << endl;
        cout << "Select any of the following options : " << endl
             << endl;
        cout << "To view a record                 press 1" << endl;
        cout << "To add a new record              press 2" << endl;
        cout << "To edit an existing record       press 3" << endl;
        cout << "To edit password                 press 4" << endl;
        cout << "To exit                          press 5" << endl
             << endl;
        cin >> option;
        clearScreen();
        switch (option)
        {
        case 1:
            r.view_record();
            break;

        case 2:
            r.add_record();
            break;

        case 3:
            r.edit_record();
            break;

        case 4:
            r.edit_password();
            break;

        case 5:
            cout << "Exiting diary !" << endl;
            exit(0);
            break;

        default:
            cout << "Invalid option ";
            break;
        }
    } while (option != 5);
    return 0;
}