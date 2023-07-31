#ifndef MANAGER_H
#define MANAGER_H

#include <iostream>
#include <string>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/statement.h>
#include <cppconn/resultset.h>
#include <mysql_driver.h>
#include "employee.h"

class Manager {
public:
    // ���������� ������ �����������
    void showEmployeeList(sql::Connection* con);

    // �������� ���������� � ���� ������
    void addEmployee(sql::Connection* con, employee& employee);

    // ������������� ���������� � ����������
    void editEmployeeInfo(sql::Connection* con, int employeeId, std::string field);

    // ������� ���������� �� ���� ������ �� ��� ID
    void deleteEmployee(sql::Connection* con, int employeeId);
    void findEmployeeById(sql::Connection* con, int employeeId);
};

#endif // MANAGER_H
