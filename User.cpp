#include "User.h"
//default constructor
//if there is no data for User, cleans garbage value from memory
//member initializer list
User::User() : _id(""), _name(""), _role(""),_password(""){}
//parameterized constructor
User::User(std::string id, std::string name, std::string role, std::string password):_id(id),_name(name), _role(role), _password(password){}