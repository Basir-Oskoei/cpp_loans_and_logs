#ifndef PATRON_H
#define PATRON_H

#include <string>
using namespace std;

class Patron
{
private:
    string fullName;
    int yearOfStudy;
    string patronID;
    string pin;
    string recentLoans[3];

public:
    Patron();
    Patron(const string &name, int year, const string &id, const string &pinCode);

    string getFullName() const;
    int getYearOfStudy() const;
    string getPatronID() const;
    string getPin() const;

    void setLoans(const string loans[3]);
    void getLoans(string loans[3]) const;

    void addLoan(const string &itemName);

    friend ostream &operator<<(ostream &out, const Patron &p);
};

#endif
