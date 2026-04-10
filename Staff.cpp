#include "Staff.h"
#include <iostream>

using namespace std;

//constructor for Staff object
Staff::Staff(string id, string name, string password) : User(id, name, "Staff", password) {};

void Staff::printRole() const{
    cout << "User: " << _name << endl;
    cout << "Role: Staff Member" << endl;
}