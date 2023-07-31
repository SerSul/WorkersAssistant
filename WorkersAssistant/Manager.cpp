#include "Manager.h"

void Manager::employeelist(sql::Connection* con) {
    std::system("cls");
    try {
        sql::Statement* stmt = con->createStatement();
        sql::ResultSet* resEmployees = stmt->executeQuery("SELECT * FROM employees");

        while (resEmployees->next()) {
            int id = resEmployees->getInt("id");
            std::string post = resEmployees->getString("post");
            std::string first_name = resEmployees->getString("first_name");
            std::string last_name = resEmployees->getString("last_name");
            std::string monthly_pay = resEmployees->getString("monthly_pay");
            std::string hire_date = resEmployees->getString("hire_date");
            std::string in_staff = resEmployees->getString("in_staff");

            // Извлекаем данные из таблицы "task" для данного сотрудника
            sql::ResultSet* resTasks = stmt->executeQuery("SELECT * FROM task WHERE id = " + std::to_string(id));
            std::string task;
            std::string deadline;

            if (resTasks->next()) {
                task = resTasks->getString("task");
                deadline = resTasks->getString("deadline");
            }

            // Выводим информацию о сотруднике и его задаче (если есть)
            std::cout << "--------------- " << id << std::endl;
            std::cout << "ID: " << id << std::endl;
            std::cout << "Post: " << post << std::endl;
            std::cout << "First Name: " << first_name << std::endl;
            std::cout << "Last Name: " << last_name << std::endl;
            std::cout << "Monthly Pay: " << monthly_pay << std::endl;
            std::cout << "Hire Date: " << hire_date << std::endl;
            std::cout << "In Staff: " << in_staff << std::endl;
            std::cout << "Task: " << task << std::endl;
            std::cout << "Deadline: " << deadline << std::endl;

            delete resTasks; // Освобождаем память после использования результата запроса "task"
        }

        delete resEmployees; // Освобождаем память после использования результата запроса "employees"
    }
    catch (sql::SQLException& e) {
        std::cout << "Ошибка при выводе таблицы: " << e.what() << std::endl;
    }
}

void Manager::addemployee(sql::Connection* con, employee& employee) {
    std::system("cls");
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

        // Execute the insertion query for the "employees" table
        pstmt->execute();
        delete pstmt;

        // Assuming the employee object contains valid data for the "task" table
        sql::PreparedStatement* pstmtTask = con->prepareStatement(
            "INSERT INTO task (id, task, deadline) VALUES (?, ?, ?)"
        );
        pstmtTask->setInt(1, employee.getId());
        pstmtTask->setString(2, employee.getTask());       // Make sure employee.getTask() returns a valid value
        pstmtTask->setString(3, employee.getDeadline());   // Make sure employee.getDeadline() returns a valid value

        // Execute the insertion query for the "task" table
        pstmtTask->execute();
        delete pstmtTask;
    }
    catch (sql::SQLException& e) {
        std::cout << "Ошибка при добавлении работника в таблицу: " << e.what() << std::endl;
    }
}

void Manager::editinfo(sql::Connection* con, int employeeId, std::string ch) {
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

void Manager::deleteemployee(sql::Connection* con, int employeeId) {
    std::system("cls");
    try {
        sql::PreparedStatement* pstmt = con->prepareStatement(
            "DELETE FROM employees WHERE id = ?"
        );
        pstmt->setInt(1, employeeId); // Установка значения параметра в запросе
        pstmt->execute();
        delete pstmt;

        sql::PreparedStatement* pstmtTask = con->prepareStatement(
            "DELETE FROM task WHERE id = ?"
        );
        pstmtTask->setInt(1, employeeId); // Установка значения параметра в запросе
        pstmtTask->execute();
        delete pstmtTask;

        std::cout << "Сотрудник с ID " << employeeId << " успешно удален." << std::endl;
    }
    catch (sql::SQLException& e) {
        std::cout << "Ошибка при удалении сотрудника с ID " << employeeId << ": " << e.what() << std::endl;
    }
}


void Manager::findEmployeeById(sql::Connection* con, int employeeId) {
    try {
        sql::Statement* stmt = con->createStatement();
        sql::ResultSet* res = stmt->executeQuery("SELECT * FROM employees WHERE id = " + std::to_string(employeeId));

        if (res->next()) {
            std::cout << "Найден сотрудник с ID " << employeeId << ":" << std::endl;
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

        delete res;
        delete stmt;
    }
    catch (sql::SQLException& e) {
        std::cout << "Ошибка при поиске сотрудника с ID " << employeeId << ": " << e.what() << std::endl;
    }
}