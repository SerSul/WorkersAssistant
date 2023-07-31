#include "manager.h"

void displayEmployeeInfo(const sql::ResultSet& resEmployees, sql::ResultSet& resTasks) {
    int id = resEmployees.getInt("id");
    std::string post = resEmployees.getString("post");
    std::string first_name = resEmployees.getString("first_name");
    std::string last_name = resEmployees.getString("last_name");
    double monthly_pay = resEmployees.getDouble("monthly_pay");
    std::string hire_date = resEmployees.getString("hire_date");
    bool in_staff = resEmployees.getString("in_staff") == "T";

    std::string task, deadline;
    if (resTasks.next()) {
        task = resTasks.getString("task");
        deadline = resTasks.getString("deadline");
    }

    std::cout << "--------------- Employee ID: " << id << " ---------------" << std::endl;
    std::cout << "ID: " << id << std::endl;
    std::cout << "Position: " << post << std::endl;
    std::cout << "First Name: " << first_name << std::endl;
    std::cout << "Last Name: " << last_name << std::endl;
    std::cout << "Monthly Pay: " << monthly_pay << std::endl;
    std::cout << "Hire Date: " << hire_date << std::endl;
    std::cout << "In Staff: " << (in_staff ? "Yes" : "No") << std::endl;
    std::cout << "Task: " << task << std::endl;
    std::cout << "Deadline: " << deadline << std::endl;
}

void Manager::showEmployeeList(sql::Connection* con) {
    system("cls");
    try {
        sql::Statement* stmt = con->createStatement();
        sql::ResultSet* resEmployees = stmt->executeQuery("SELECT * FROM employees");
        while (resEmployees->next()) {
            int id = resEmployees->getInt("id");
            sql::ResultSet* resTasks = stmt->executeQuery("SELECT * FROM task WHERE id = " + std::to_string(id));

            displayEmployeeInfo(*resEmployees, *resTasks);

            delete resTasks;
        }
        delete resEmployees;
    }
    catch (sql::SQLException& e) {
        std::cout << "Error displaying employee list: " << e.what() << std::endl;
    }
}

void addEmployeeToDatabase(sql::Connection* con, employee& employee) {
    try {
        sql::PreparedStatement* pstmt = con->prepareStatement(
            "INSERT INTO employees (id, post, first_name, last_name, monthly_pay, hire_date, in_staff) VALUES (?, ?, ?, ?, ?, ?, ?)"
        );

        pstmt->setInt(1, employee.getId());
        pstmt->setString(2, employee.getPost());
        pstmt->setString(3, employee.getFirstName());
        pstmt->setString(4, employee.getLastName());
        pstmt->setDouble(5, employee.getMonthlyPay());
        pstmt->setString(6, employee.getHireDate());
        pstmt->setString(7, employee.isInStaff() ? "T" : "F");

        pstmt->execute();
        delete pstmt;

        sql::PreparedStatement* pstmtTask = con->prepareStatement(
            "INSERT INTO task (id, task, deadline) VALUES (?, ?, ?)"
        );
        pstmtTask->setInt(1, employee.getId());
        pstmtTask->setString(2, employee.getTask());
        pstmtTask->setString(3, employee.getDeadline());

        pstmtTask->execute();
        delete pstmtTask;
    }
    catch (sql::SQLException& e) {
        std::cout << "Error adding employee to the database: " << e.what() << std::endl;
    }
}

void Manager::addEmployee(sql::Connection* con, employee& employee) {
    system("cls");
    addEmployeeToDatabase(con, employee);
}

void Manager::editEmployeeInfo(sql::Connection* con, int employeeId, std::string ch) {
    std::system("cls");
    try {
        sql::Statement* stmt = con->createStatement();
        sql::ResultSet* res = stmt->executeQuery("SELECT * FROM employees WHERE id = " + std::to_string(employeeId));

        if (res->next()) {
            std::cout << "Текущая информация о сотруднике:" << std::endl;
            std::cout << "ID: " << employeeId << std::endl;
            std::cout << "Post: " << res->getString("post") << std::endl;
            std::cout << "First Name: " << res->getString("first_name") << std::endl;
            std::cout << "Last Name: " << res->getString("last_name") << std::endl;
            std::cout << "Monthly Pay: " << res->getDouble("monthly_pay") << std::endl;
            std::cout << "Hire Date: " << res->getString("hire_date") << std::endl;
            std::cout << "In Staff: " << res->getString("in_staff") << std::endl;
        }
        else {
            std::cout << "Сотрудник с ID " << employeeId << " не найден." << std::endl;
        }

        res = stmt->executeQuery("SELECT * FROM task WHERE id = " + std::to_string(employeeId));

        if (res->next()) {
            std::cout << "Task: " << res->getString("task") << std::endl;
            std::cout << "DeadLine: " << res->getString("deadline") << std::endl;
        }
        delete res;

        if (ch == "post" || ch == "first_name" || ch == "last_name" || ch == "hire_date" || ch == "monthly_pay" || ch == "in_staff") {
            std::string newValue;
            std::cout << "Введите новое значение: ";
            std::cin.ignore(); // Clear the buffer before std::getline()
            std::getline(std::cin, newValue);
            sql::PreparedStatement* pstmt = con->prepareStatement(
                "UPDATE employees SET " + ch + " = ? WHERE id = ?"
            );
            pstmt->setString(1, newValue);

            if (ch == "monthly_pay") {
                double newMonthlyPay;
                std::cout << "Введите новое значение: ";
                while (!(std::cin >> newMonthlyPay)) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Некорректный ввод. Пожалуйста, введите число: ";
                }
                pstmt->setDouble(1, newMonthlyPay);
            }
            else if (ch == "in_staff") {
                bool inStaff;
                std::cout << "В сотрудничаете сотрудником? (1 - Да, 0 - Нет): ";
                while (!(std::cin >> inStaff)) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Некорректный ввод. Пожалуйста, введите 1 или 0: ";
                }
                pstmt->setString(1, inStaff ? "T" : "F");
            }
            pstmt->setInt(2, employeeId);
            pstmt->execute();
            delete pstmt;
            std::cout << "Информация о сотруднике с ID " << employeeId << " успешно обновлена." << std::endl;
        }
        else if (ch == "task" || ch == "deadline") {
            std::string newValue;
            std::cout << "Введите новое значение: ";
            std::cin.ignore(); // Clear the buffer before std::getline()
            std::getline(std::cin, newValue);
            sql::PreparedStatement* pstmtTask = con->prepareStatement(
                "UPDATE task SET " + ch + " = ? WHERE id = ?"
            );
            pstmtTask->setString(1, newValue);
            pstmtTask->setInt(2, employeeId);
            pstmtTask->execute();
            delete pstmtTask;
            std::cout << "Информация о задаче сотрудника с ID " << employeeId << " успешно обновлена." << std::endl;
        }
        else {
            std::cout << "Некорректный выбор поля для редактирования." << std::endl;
        }

        delete stmt;
    }
    catch (sql::SQLException& e) {
        std::cout << "Ошибка при редактировании информации о сотруднике: " << e.what() << std::endl;
    }
}



void Manager::deleteEmployee(sql::Connection* con, int employeeId) {
    system("cls");
    try {
        sql::PreparedStatement* pstmt = con->prepareStatement(
            "DELETE FROM employees WHERE id = ?"
        );
        pstmt->setInt(1, employeeId);
        pstmt->execute();
        delete pstmt;

        sql::PreparedStatement* pstmtTask = con->prepareStatement(
            "DELETE FROM task WHERE id = ?"
        );
        pstmtTask->setInt(1, employeeId);
        pstmtTask->execute();
        delete pstmtTask;

        std::cout << "Employee with ID " << employeeId << " successfully deleted." << std::endl;
    }
    catch (sql::SQLException& e) {
        std::cout << "Error deleting employee with ID " << employeeId << ": " << e.what() << std::endl;
    }
}

void Manager::findEmployeeById(sql::Connection* con, int employeeId) {
    system("cls");
    try {
        sql::PreparedStatement* pstmt = con->prepareStatement("SELECT * FROM employees WHERE id = ?");
        pstmt->setInt(1, employeeId);
        sql::ResultSet* resEmployees = pstmt->executeQuery();

        if (resEmployees->next()) {
            int id = resEmployees->getInt("id");
            sql::ResultSet* resTasks = con->createStatement()->executeQuery("SELECT * FROM task WHERE id = " + std::to_string(id));

            displayEmployeeInfo(*resEmployees, *resTasks);

            delete resTasks;
        }
        else {
            std::cout << "Employee with ID " << employeeId << " not found." << std::endl;
        }

        delete pstmt;
    }
    catch (sql::SQLException& e) {
        std::cout << "Error finding employee with ID " << employeeId << ": " << e.what() << std::endl;
    }
}
