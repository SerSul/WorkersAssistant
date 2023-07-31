#include "exec_app.h"
using namespace std;


//const string server = "tcp://127.0.0.1:3306";
//const string username = "root";
//const string password = "";


string server = "";
string username = "";
string password = "";

int main()
{
    std::cout << "Введите хост";
    std::cin >> server;
    std::cout << "Введите пользователя";
    std::cin >> username;
    std::cout << "Введите пароль";
    std::cin >> password;
    setlocale(LC_ALL, "Russian");
    sql::Driver* driver;
    sql::Connection* con;
    sql::Statement* stmt;
    sql::PreparedStatement* pstmt;

    try
    {
        driver = get_driver_instance();
        con = driver->connect(server, username, password);
    }
    catch (sql::SQLException e)
    {
        cout << "Невозможно подключиться к серверу. Сообщение ошибки: " << e.what() << endl;
        system("pause");
        exit(1);
    }
    con->setSchema("workers");
    exec_app exec_app;
    exec_app.menu(con);

    system("pause");
    return 0;
}
