#include "Admin.h"
#include <iostream>

using namespace std;

//constructor for Admin object
Admin::Admin(string id, string name, string password) : User(id, name, "Admin", password) {};

void Admin::printRole() const{
    cout << "User: " << _name << endl;
    cout << "Role: Administrator" << endl;
}