#include "Manager.h"
class exec_app
{
public:
    Manager manager;
	void menu(sql::Connection* con)
	{
		while (true)
		{
            cout << "������� ����" << endl;
            cout << "1. �������� ������ �����������" << endl;
            cout << "2. �������� ������ ����������" << endl;
            cout << "3. ������������� ���������� � ����������" << endl;
            cout << "4. ������� ����������" << endl;
            cout << "5. �������� ������ ��� ����������" << endl;
            cout << "6. ����������� ������ ����������" << endl;
            cout << "7. �������� ���������� ������" << endl;
            cout << "8. �����" << endl;
            cout << "�������� �����: ";

            int choice;
            cin >> choice;
            if (choice == 1)
            {
                manager.employeelist(con);
            }
            if (choice == 2)
            {

                int id;
                double monthly_pay;
                string post, first_name, last_name, hire_date;
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

                // ����� ����� ���� �������������� ��������� ��� ����� �������� in_staff (��������, ��/��� ��� 1/0).
                // ��� �������� �����������, ��� ������������ ������ 1 ��� 0.
                std::cout << "� ������������� �����������? (1 - ��, 0 - ���): ";
                std::cin >> in_staff;

                // ������� ������ ���������� � �������� ��� � ������� addemployee
                employee newEmployee(id, post, first_name, last_name, monthly_pay, hire_date, in_staff);
                manager.addemployee(con, newEmployee);

            }
            if (choice == 3)
            {
                int id;
                string ch;
                std::cout << "������� ID ����������: ";
                std::cin >> id;
                manager.editinfo(con, id, ch);
                

            }
            if (choice == 4)
            {
                int id;
                string ch;
                std::cout << "������� ID ���������� ��� ��������: ";
                std::cin >> id;
                manager.deleteemployee(con, id);


            }
		}
	}
};

