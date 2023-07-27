#include "Manager.h"
class exec_app
{
public:
    Manager manager;
	void menu(sql::Connection* con)
	{
		while (true)
		{
            cout << "Главное меню" << endl;
            cout << "1. Просмотр списка сотрудников" << endl;
            cout << "2. Добавить нового сотрудника" << endl;
            cout << "3. Редактировать информацию о сотруднике" << endl;
            cout << "4. Удалить сотрудника" << endl;
            cout << "5. Добавить задачу для сотрудника" << endl;
            cout << "6. Просмотреть задачи сотрудника" << endl;
            cout << "7. Отметить выполнение задачи" << endl;
            cout << "8. Выход" << endl;
            cout << "Выберите опцию: ";

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

                // Здесь может быть дополнительная обработка для ввода значения in_staff (например, да/нет или 1/0).
                // Для простоты предположим, что пользователь вводит 1 или 0.
                std::cout << "В сотрудничаете сотрудником? (1 - Да, 0 - Нет): ";
                std::cin >> in_staff;

                // Создаем объект сотрудника и передаем его в функцию addemployee
                employee newEmployee(id, post, first_name, last_name, monthly_pay, hire_date, in_staff);
                manager.addemployee(con, newEmployee);

            }
            if (choice == 3)
            {
                int id;
                string ch;
                std::cout << "Введите ID сотрудника: ";
                std::cin >> id;
                manager.editinfo(con, id, ch);
                

            }
            if (choice == 4)
            {
                int id;
                string ch;
                std::cout << "Введите ID сотрудника для удаления: ";
                std::cin >> id;
                manager.deleteemployee(con, id);


            }
		}
	}
};

