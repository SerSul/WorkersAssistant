#ifndef EXEC_APP_H
#define EXEC_APP_H

#include "Manager.h"

class exec_app {
public:
    Manager manager;
    void menu(sql::Connection* con);
};

#endif // EXEC_APP_H
