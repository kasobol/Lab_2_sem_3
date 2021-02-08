#pragma once

#include <string>

using namespace std;

//bool operator < (Person p1, Person p2)
//{
//    bool k = p1.GetAge(2020) < p2.GetAge(2020);
//    return k;
//}
//bool operator > (Person p1, Person p2)
//{
//    bool k = p1.GetAge(2020) > p2.GetAge(2020);
//    return k;
//}

class Person
{
private:
    string FirstName;
    string MiddleName;
    string LastName;
    int BirthYear;
public:
    Person(){}
    Person(string firstname, string middlename, string lastname, int birthyear)
    {
        FirstName = firstname;
        MiddleName = middlename;
        LastName = lastname;
        BirthYear = birthyear;
    }
    string GetFirstName()
    {
        return FirstName;
    }
    string GetMiddleName()
    {
        return MiddleName;
    }
    string GetLastName()
    {
        return LastName;
    }
    string GetFullName()
    {
        return FirstName + " " + MiddleName + " " + LastName;
    }
    string GetFIO()
    {
        return FirstName + " " + MiddleName[0] + "." + LastName[0] + ".";
    }
    int GetBirthYear()
    {
        return BirthYear;
    }
    int GetAge(int year)
    {
        return year - BirthYear;
    }
};