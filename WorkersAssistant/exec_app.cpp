#include "exec_app.h"
#include <iostream>
#include <string>

void exec_app::menu(sql::Connection* con) {
    setlocale(LC_ALL, "Russian");
    while (true) {
        std::cout << "Главное меню" << std::endl;
        std::cout << "1. Просмотр списка сотрудников" << std::endl;
        std::cout << "2. Добавить нового сотрудника" << std::endl;
        std::cout << "3. Редактировать информацию о сотруднике" << std::endl;
        std::cout << "4. Удалить сотрудника" << std::endl;
        std::cout << "5. Найти сотрудника по ID" << std::endl;
        std::cout << "6. Выход" << std::endl;
        std::cout << "Выберите опцию: ";


        int choice;
        std::cin >> choice;

        if (choice == 1) {
            manager.showEmployeeList(con);
        }
        else if (choice == 2) {
            int id;
            double monthly_pay;
            std::string post, first_name, last_name, hire_date, task, deadline;
            bool in_staff;

            std::cout << "Введите ID сотрудника: ";
            std::cin >> id;

            std::cout << "Введите должность сотрудника: ";
            std::cin >> post;

            std::cout << "Введите имя сотрудника: ";
            std::cin >> first_name;

            std::cout << "Введите фамилию сотрудника: ";
            std::cin >> last_name;

            std::cout << "Введите месячную зарплату сотрудника: ";
            std::cin >> monthly_pay;

            std::cout << "Введите дату приема на работу (ГГГГ-ММ-ДД): ";
            std::cin >> hire_date;

            std::cout << "В сотрудничаете сотрудником? (1 - Да, 0 - Нет): ";
            std::cin >> in_staff;
            std::cout << "Введите задачу";
            std::cin >> task;
            std::cout << "Введите дедлайн";
            std::cin >> deadline;
            // Создаем объект сотрудника и передаем его в функцию addemployee
            employee newEmployee(id, post, first_name, last_name, monthly_pay, hire_date, in_staff, task, deadline);
            manager.addEmployee(con, newEmployee);
        }
        else if (choice == 3) {
            int id;
            std::string ch;
            std::cout << "Введите ID сотрудника: ";
            std::cin >> id;
            std::cout << "Выберите поле для редактирования (post, first_name, last_name, monthly_pay, hire_date, in_staff, task, deadline): ";
            std::cin >> ch;


            manager.editEmployeeInfo(con, id, ch);
        }
        else if (choice == 4) {
            int id;
            std::cout << "Введите ID сотрудника для удаления: ";
            std::cin >> id;
            manager.deleteEmployee(con, id);
        }

        else if (choice == 5) {
            int id;
            std::cout << "Введите ID сотрудника: ";
            std::cin >> id;
            manager.findEmployeeById(con, id);
        }
        else if (choice == 6) {
            break;
        }
        else {
            std::cout << "Некорректный выбор опции." << std::endl;
        }
    }
}
