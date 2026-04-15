#include "Customer.h"
#include <stdexcept>
#include <iostream>


using namespace std;

Customer::Customer(string id, string name, string phone) 
    : _customerID(id) {
    setName(name);
    setPhone(phone);

}
//setters with input validation
bool Customer::setName(string name) {
    //check if name is valid
    if (Validator::isValidName(name)) {
        _name = name;
        return true;
    }else {
        throw invalid_argument("Invalid Name. Use letters only.");
    }
    }
    
bool Customer::setPhone(string phone) {
    //check if the phone is valid
    if (Validator::isValidPhone(phone)) {
        _phone = phone;
        return true;
    }else{
         throw invalid_argument("Invalid Phone. Enter 10-12 digits without spaces/dashes.");
}
    }
   

//getters
string Customer::getID() const { return _customerID; }
string Customer::getName() const { return _name; }
string Customer::getPhone() const { return _phone; }

void Customer::displayCustomerInfo() const {
    cout << "Customer ID: " << _customerID << endl;
    cout << "Name:  " << _name << endl;
    cout << "Phone: " << _phone << endl;
    cout << "-----------------------" << endl;
}