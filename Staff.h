#ifndef STAFF_H
#define STAFF_H

#include "User.h"

class Staff:public User{
    public:
        Staff(std::string id, std::string name, std::string password);

        void printRole() const override;
};

#endif