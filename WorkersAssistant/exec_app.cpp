#include "exec_app.h"
#include <iostream>
#include <string>

void exec_app::menu(sql::Connection* con) {
    setlocale(LC_ALL, "Russian");
    while (true) {
        std::cout << "������� ����" << std::endl;
        std::cout << "1. �������� ������ �����������" << std::endl;
        std::cout << "2. �������� ������ ����������" << std::endl;
        std::cout << "3. ������������� ���������� � ����������" << std::endl;
        std::cout << "4. ������� ����������" << std::endl;
        std::cout << "5. ����� ���������� �� ID" << std::endl;
        std::cout << "6. �����" << std::endl;
        std::cout << "�������� �����: ";


        int choice;
        std::cin >> choice;

        if (choice == 1) {
            manager.employeelist(con);
        }
        else if (choice == 2) {
            int id;
            double monthly_pay;
            std::string post, first_name, last_name, hire_date, task, deadline;
            bool in_staff;

            std::cout << "������� ID ����������: ";
            std::cin >> id;

            std::cout << "������� ��������� ����������: ";
            std::cin >> post;

            std::cout << "������� ��� ����������: ";
            std::cin >> first_name;

            std::cout << "������� ������� ����������: ";
            std::cin >> last_name;

            std::cout << "������� �������� �������� ����������: ";
            std::cin >> monthly_pay;

            std::cout << "������� ���� ������ �� ������ (����-��-��): ";
            std::cin >> hire_date;

            std::cout << "� ������������� �����������? (1 - ��, 0 - ���): ";
            std::cin >> in_staff;
            std::cout << "������� ������";
            std::cin >> task;
            std::cout << "������� �������";
            std::cin >> deadline;
            // ������� ������ ���������� � �������� ��� � ������� addemployee
            employee newEmployee(id, post, first_name, last_name, monthly_pay, hire_date, in_staff, task, deadline);
            manager.addemployee(con, newEmployee);
        }
        else if (choice == 3) {
            int id;
            std::string ch;
            std::cout << "������� ID ����������: ";
            std::cin >> id;
            std::cout << "�������� ���� ��� �������������� (post, first_name, last_name, monthly_pay, hire_date, in_staff, description_, deadline_): ";
            std::cin >> ch;


            manager.editinfo(con, id, ch);
        }
        else if (choice == 4) {
            int id;
            std::cout << "������� ID ���������� ��� ��������: ";
            std::cin >> id;
            manager.deleteemployee(con, id);
        }

        else if (choice == 5) {
            int id;
            std::cout << "������� ID ����������: ";
            std::cin >> id;
            manager.findEmployeeById(con, id);
        }
        else if (choice == 6) {
            break;
        }
        else {
            std::cout << "������������ ����� �����." << std::endl;
        }
    }
}
