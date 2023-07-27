#pragma once
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
using namespace std;

class employee
{
private:
    int id;
    string post;
    string firstName;
    string lastName;
    float monthlyPay;
    string hireDate;
    bool inStaff;
public:
    employee(int _id, const string& _post, const string& _firstName, const string& _lastName, float _monthlyPay, const string& _hireDate, bool _inStaff)
        : id(_id), post(_post), firstName(_firstName), lastName(_lastName), monthlyPay(_monthlyPay), hireDate(_hireDate), inStaff(_inStaff)
    {}
    int getId() const { return id; }
    string getFirstName() const { return firstName; }
    string getPost() const { return post; }
    string getLastName() const { return lastName; }
    float getMonthlyPay() const { return monthlyPay; }
    string getHireDate() const { return hireDate; }
    bool isInStaff() const { return inStaff; }

};

