#include "employee.h"

class Manager
{
public:
    void employeelist(sql::Connection* con)
    {
        std::system("cls");
        try {
            sql::Statement* stmt = con->createStatement();
            sql::ResultSet* res = stmt->executeQuery("SELECT * FROM employees");
            while (res->next()) {
                int id = res->getInt("id");
                std::string post = res->getString("post");
                std::string first_name = res->getString("first_name");
                std::string last_name = res->getString("last_name");
                std::string monthly_pay = res->getString("monthly_pay");
                std::string hire_date = res->getString("hire_date");
                std::string in_staff = res->getString("in_staff");

                std::cout << "--------------- " << id << std::endl;
                std::cout << "ID: " << id << std::endl;
                std::cout << "Post: " << post << std::endl;
                std::cout << "First Name: " << first_name << std::endl;
                std::cout << "Last Name: " << last_name << std::endl;
                std::cout << "Monthly Pay: " << monthly_pay << std::endl;
                std::cout << "Hire Date: " << hire_date << std::endl;
                std::cout << "In Staff: " << in_staff << std::endl;
            }
        }
        catch (sql::SQLException& e) {
            std::cout << "Ошибка при выводе таблицы: " << e.what() << std::endl;
        }
    }

    void addemployee(sql::Connection* con, employee& employee)
    {
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

            pstmt->execute();
            delete pstmt;
        }
        catch (sql::SQLException& e) {
            std::cout << "Ошибка при добавлении работника в таблицу: " << e.what() << std::endl;
        }
    }

    void editinfo(sql::Connection* con, int employeeId, std::string ch)
    {
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

                // Выбор поля для редактирования
                std::cout << "Выберите поле для редактирования (post, first_name, last_name, monthly_pay, hire_date, in_staff): ";
                std::cin >> ch;

                sql::PreparedStatement* pstmt = con->prepareStatement(
                    "UPDATE employees SET " + ch + " = ? WHERE id = ?"
                );

                if (ch == "post" || ch == "first_name" || ch == "last_name" || ch == "hire_date") {
                    std::string newValue;
                    std::cout << "Введите новое значение: ";
                    std::cin.ignore();
                    std::getline(std::cin, newValue);
                    pstmt->setString(1, newValue);
                }
                else if (ch == "monthly_pay") {
                    double newValue;
                    std::cout << "Введите новое значение: ";
                    std::cin >> newValue;
                    pstmt->setDouble(1, newValue);
                }
                else if (ch == "in_staff") {
                    bool newValue;
                    std::cout << "В сотрудничаете сотрудником? (1 - Да, 0 - Нет): ";
                    std::cin >> newValue;
                    pstmt->setString(1, newValue ? "T" : "F");
                }
                else {
                    std::cout << "Некорректный выбор поля для редактирования." << std::endl;
                    delete pstmt;
                    delete stmt;
                    return;
                }

                pstmt->setInt(2, employeeId);
                pstmt->execute();

                delete pstmt;

                std::cout << "Информация о сотруднике с ID " << employeeId << " успешно обновлена." << std::endl;
            }
            else {
                std::cout << "Сотрудник с ID " << employeeId << " не найден." << std::endl;
            }

            delete stmt;
        }
        catch (sql::SQLException& e) {
            std::cout << "Ошибка при редактировании информации о сотруднике: " << e.what() << std::endl;
        }
    }

    void deleteemployee(sql::Connection* con, int employeeId)
    {
        std::system("cls");
        try {
            sql::PreparedStatement* pstmt = con->prepareStatement(
                "DELETE FROM employees WHERE id = ?"
            );
            pstmt->setInt(1, employeeId); // Установка значения параметра в запросе
            pstmt->execute();
            delete pstmt;

            std::cout << "Сотрудник с ID " << employeeId << " успешно удален." << std::endl;
        }
        catch (sql::SQLException& e) {
            std::cout << "Ошибка при удалении сотрудника с ID " << employeeId << ": " << e.what() << std::endl;

        }
    }

};


//cout << "1. Просмотр списка сотрудников" << endl; +
//cout << "2. Добавить нового сотрудника" << endl;+
//cout << "3. Редактировать информацию о сотруднике" << endl;+
//cout << "4. Удалить сотрудника" << endl;
//cout << "8. Выход" << endl;
//cout << "Выберите опцию: ";