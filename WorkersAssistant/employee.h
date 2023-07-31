#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>
#include <vector>
#include <algorithm>

class employee {
private:
    int id;
    std::string post;
    std::string firstName;
    std::string lastName;
    float monthlyPay;
    std::string hireDate;
    bool inStaff;
    std::string task;
    std::string deadline;

public:
    employee(int _id,  std::string& _post,  std::string& _firstName,  std::string& _lastName, float _monthlyPay,  std::string& _hireDate, bool _inStaff, std::string _task, std::string _deadline)
        : id(_id), post(_post), firstName(_firstName), lastName(_lastName), monthlyPay(_monthlyPay), hireDate(_hireDate), inStaff(_inStaff), task(_task), deadline(_deadline) {}

    int getId()  { return id; }
    std::string getFirstName()  { return firstName; }
    std::string getPost()  { return post; }
    std::string getLastName()  { return lastName; }
    float getMonthlyPay()  { return monthlyPay; }
    std::string getHireDate()  { return hireDate; }
    bool isInStaff()  { return inStaff; }
    std::string getTask()  { return task; }
    std::string getDeadline()  { return deadline; }
};

#endif // EMPLOYEE_H
