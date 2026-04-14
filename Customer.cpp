#include "Customer.h"
#include <regex>
#include <stdexcept>
#include <iostream>


using namespace std;

Customer::Customer(string id, string name, string phone) 
    : _customerID(id) {
    setName(name);
    setPhone(phone);

}
//setters with regex input validation
bool Customer::setName(string name) {
    //regex for name-characters, spaces, -, ' are allowed
    regex namePattern("^[A-Za-z]+(?:[ '-][A-Za-z]+)*$");
    if (regex_match(name, namePattern)) {
        _name = name;
        return true;
    }else {
        throw invalid_argument("Invalid Name. Use letters only.");
}
    }
    
bool Customer::setPhone(string phone) {
    // regex for 10 to 12 digits
    regex phonePattern("^[0-9]{10,12}$");

    if (regex_match(phone, phonePattern)) {
        _phone = phone;
        return true;
    }else{
         throw invalid_argument(" Invalid Phone. Enter 10-12 digits without spaces/dashes.");
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