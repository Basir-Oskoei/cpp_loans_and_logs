#include "Patron.h"
#include <iostream>
#include <string>

using namespace std;

Patron::Patron()
{
    fullName = "";
    yearOfStudy = 0;
    patronID = "";
    pin = "";
    for (int i = 0; i < 3; i++)
    {
        recentLoans[i] = "";
    }
}

Patron::Patron(const string& name, int year, const string& id, const string& p)
{
    fullName = name;
    yearOfStudy = year;
    patronID = id;
    pin = p;

    for (int i = 0; i < 3; i++)
    {
        recentLoans[i] = "";
    }
}

string Patron::getFullName() const
{
    return fullName;
}

int Patron::getYearOfStudy() const
{
    return yearOfStudy;
}

string Patron::getPatronID() const
{
    return patronID;
}

string Patron::getPin() const
{
    return pin;
}

void Patron::getLoans(string arr[3]) const
{
    for (int i = 0; i < 3; i++)
    {
        arr[i] = recentLoans[i];
    }
}

void Patron::setLoans(const string arr[3])
{
    for (int i = 0; i < 3; i++)
    {
        recentLoans[i] = arr[i];
    }
}

void Patron::addLoan(const string& itemName)
{
    recentLoans[2] = recentLoans[1];
    recentLoans[1] = recentLoans[0];
    recentLoans[0] = itemName;
}

ostream& operator<<(ostream& out, const Patron& p)
{
    out << "Name: " << p.fullName << endl;
    out << "Year: " << p.yearOfStudy << endl;
    out << "Patron ID: " << p.patronID << endl;
    return out;
}
