#include <iostream>
#include <fstream>
#include <string>

#include "Patron.h"

using namespace std;

const int MAX_PATRONS = 100;

void showMenu()
{
    cout << "Please select:" << endl;
    cout << "1 - Login" << endl;
    cout << "2 - Register" << endl;
    cout << "3 - Record a loan" << endl;
    cout << "4 - Exit" << endl;
    cout << "Option: ";
}

void splitLoans(const string &loansPart, string loans[3])
{
    int index = 0;
    int start = 0;
    int length = (int)loansPart.length();

    for (int i = 0; i < 3; i++)
    {
        loans[i] = "";
    }

    for (int i = 0; i < length && index < 3; i++)
    {
        if (loansPart[i] == ',')
        {
            loans[index] = loansPart.substr(start, i - start);
            index++;
            start = i + 1;
        }
    }

    if (index < 3)
    {
        loans[index] = loansPart.substr(start);
        index++;
    }

    while (index < 3)
    {
        loans[index] = "";
        index++;
    }
}

bool parsePatronLine(const string &line, string &id, string &pin, string &name, int &year, string loans[3])
{
    size_t p1 = line.find('|');
    size_t p2 = string::npos;
    size_t p3 = string::npos;
    size_t p4 = string::npos;

    if (p1 != string::npos)
    {
        p2 = line.find('|', p1 + 1);
    }
    if (p2 != string::npos)
    {
        p3 = line.find('|', p2 + 1);
    }
    if (p3 != string::npos)
    {
        p4 = line.find('|', p3 + 1);
    }

    if (p1 == string::npos || p2 == string::npos || p3 == string::npos || p4 == string::npos)
    {
        return false;
    }

    id = line.substr(0, p1);
    pin = line.substr(p1 + 1, p2 - p1 - 1);
    name = line.substr(p2 + 1, p3 - p2 - 1);
    string yearText = line.substr(p3 + 1, p4 - p3 - 1);

    year = 0;
    for (size_t i = 0; i < yearText.length(); i++)
    {
        char c = yearText[i];
        if (c >= '0' && c <= '9')
        {
            year = year * 10 + (c - '0');
        }
    }

    string loansPart = "";
    if (p4 + 1 < line.length())
    {
        loansPart = line.substr(p4 + 1);
    }

    splitLoans(loansPart, loans);
    return true;
}

void writePatronLine(ofstream &out, const Patron &patron)
{
    string loans[3];
    patron.getLoans(loans);

    out << patron.getPatronID() << "|";
    out << patron.getPin() << "|";
    out << patron.getFullName() << "|";
    out << patron.getYearOfStudy() << "|";
    out << loans[0] << "," << loans[1] << "," << loans[2] << endl;
}

void handleRegister()
{
    string fullName;
    int year;
    string patronID;
    string pin;
    int loanCount;
    string loans[3];

    cout << "Enter full name: ";
    getline(cin, fullName);

    cout << "Enter year of study: ";
    cin >> year;
    cin.ignore(1000, '\n');

    cout << "Enter patron ID: ";
    getline(cin, patronID);

    cout << "Enter pin (4 digits): ";
    getline(cin, pin);

    for (int i = 0; i < 3; i++)
    {
        loans[i] = "";
    }

    cout << "How many items currently on loan (0-3): ";
    cin >> loanCount;
    cin.ignore(1000, '\n');

    if (loanCount < 0)
    {
        loanCount = 0;
    }
    if (loanCount > 3)
    {
        loanCount = 3;
    }

    for (int i = 0; i < loanCount; i++)
    {
        cout << "Enter item " << (i + 1) << ": ";
        getline(cin, loans[i]);
    }

    ofstream out("patrons.txt", ios::app);
    if (!out)
    {
        cout << "Could not open patrons.txt for writing" << endl;
        return;
    }

    out << patronID << "|" << pin << "|" << fullName << "|" << year << "|";
    out << loans[0] << "," << loans[1] << "," << loans[2] << endl;

    out.close();

    cout << "Patron registered" << endl;
}

bool handleLogin(Patron &currentPatron, bool &loggedIn)
{
    string idInput;
    string pinInput;

    cout << "Enter patron ID: ";
    getline(cin, idInput);
    cout << "Enter pin: ";
    getline(cin, pinInput);

    ifstream in("patrons.txt");
    if (!in)
    {
        cout << "Could not open patrons.txt for reading" << endl;
        return false;
    }

    string line;
    bool found = false;

    while (getline(in, line))
    {
        string id;
        string pin;
        string name;
        int year;
        string loans[3];

        if (!parsePatronLine(line, id, pin, name, year, loans))
        {
            continue;
        }

        if (id == idInput && pin == pinInput)
        {
            Patron p(name, year, id, pin);
            p.setLoans(loans);
            currentPatron = p;
            loggedIn = true;
            found = true;
            break;
        }
    }

    in.close();

    if (!found)
    {
        cout << "Login failed" << endl;
        return false;
    }

    cout << currentPatron << endl;
    cout << "Recent loans:" << endl;

    string loansToPrint[3];
    currentPatron.getLoans(loansToPrint);

    for (int i = 0; i < 3; i++)
    {
        if (loansToPrint[i] != "")
        {
            cout << "- " << loansToPrint[i] << endl;
        }
    }

    return true;
}

void handleRecordLoan(Patron &currentPatron, bool loggedIn)
{
    if (!loggedIn)
    {
        cout << "No patron is logged in" << endl;
        return;
    }

    string item;
    cout << "Enter item name: ";
    getline(cin, item);

    currentPatron.addLoan(item);

    ifstream in("patrons.txt");
    if (!in)
    {
        cout << "Could not open patrons.txt for reading" << endl;
        return;
    }

    string lines[MAX_PATRONS];
    int count = 0;

    while (count < MAX_PATRONS && getline(in, lines[count]))
    {
        count++;
    }

    in.close();

    ofstream out("patrons.txt");
    if (!out)
    {
        cout << "Could not open patrons.txt for writing" << endl;
        return;
    }

    for (int i = 0; i < count; i++)
    {
        string line = lines[i];
        string id;
        string pin;
        string name;
        int year;
        string loans[3];

        if (!parsePatronLine(line, id, pin, name, year, loans))
        {
            out << line << endl;
        }
        else if (id == currentPatron.getPatronID())
        {
            writePatronLine(out, currentPatron);
        }
        else
        {
            out << line << endl;
        }
    }

    out.close();

    cout << "Loan recorded" << endl;
}

int main()
{
    Patron currentPatron;
    bool loggedIn = false;
    int choice = 0;

    while (true)
    {
        showMenu();

        if (!(cin >> choice))
        {
            return 0;
        }

        cin.ignore(1000, '\n');

        if (choice == 1)
        {
            handleLogin(currentPatron, loggedIn);
        }
        else if (choice == 2)
        {
            handleRegister();
        }
        else if (choice == 3)
        {
            handleRecordLoan(currentPatron, loggedIn);
        }
        else if (choice == 4)
        {
            break;
        }

        cout << endl;
    }

    return 0;
}
