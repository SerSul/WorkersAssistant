#ifndef MANAGER_H
#define MANAGER_H

#include <iostream>
#include <string>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/statement.h>
#include <cppconn/resultset.h>
#include "employee.h"

class Manager {
public:
    void employeelist(sql::Connection* con);
    void addemployee(sql::Connection* con, employee& employee);
    void editinfo(sql::Connection* con, int employeeId, std::string ch);
    void deleteemployee(sql::Connection* con, int employeeId);
};

#endif // MANAGER_H
