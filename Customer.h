#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include <vector>

class Customer {
private:
    std::string _customerID;
    std::string _name;
    std::string _phone;
    // We can store a history of their appointments here later

public:
    Customer(std::string id, std::string name, std::string phone);
    //setters
    //void setID(std::string id);
    bool setName(std::string name);
    bool setPhone(std::string phone);
    // getters
    std::string getID() const;
    std::string getName() const;
    std::string getPhone() const;

   //display customer info   
    void displayCustomerInfo() const;
};

#endif