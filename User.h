#ifndef USER_H
#define USER_H


#include <string>

class User{
    // we use protected access specifier for classes that have children
    //this way the children can have access to these variables
    protected:
    //naming convention _name
    // difference between a member variable (the data that belongs to the class) _name
    //and a local variable (temporary data inside a function) name
    //these are member variables with underscore
        std::string _id;
        std::string _name;
        std::string _role;
        std::string _password;

    public:
        //constructor is public
        //default constructor
        User();
        //parametarized constructor
        User(std::string id, std::string name, std::string role, std::string password);
        //Virtual destructor is used for cleanup when using pointers
        virtual ~User() {}

        //pure virtual function enables polymorphism
        //the fucnction is written for children Admin and Staff, not for generic User
        //= 0 is the "Pure" specifier. It tells the compiler: "There is no code for this function in this file."

        virtual void printRole() const = 0;
};

#endif