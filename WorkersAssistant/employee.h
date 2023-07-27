#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>

class employee {
private:
    int id;
    std::string post;
    std::string firstName;
    std::string lastName;
    float monthlyPay;
    std::string hireDate;
    bool inStaff;

public:
    employee(int _id, const std::string& _post, const std::string& _firstName, const std::string& _lastName, float _monthlyPay, const std::string& _hireDate, bool _inStaff)
        : id(_id), post(_post), firstName(_firstName), lastName(_lastName), monthlyPay(_monthlyPay), hireDate(_hireDate), inStaff(_inStaff) {}

    int getId() const { return id; }
    std::string getFirstName() const { return firstName; }
    std::string getPost() const { return post; }
    std::string getLastName() const { return lastName; }
    float getMonthlyPay() const { return monthlyPay; }
    std::string getHireDate() const { return hireDate; }
    bool isInStaff() const { return inStaff; }
};

#endif // EMPLOYEE_H
