#include "Item.h"
#include <stdexcept>
#include <iostream>
using namespace std;

//Default constructor
Item::Item() : _id(""), _name(""), _price(0.0) {}
//Parametarized constructor
Item::Item(string id, string name, double price) {
    setID(id);
    setName(name);
    setPrice(price);
}
//Destructor
Item::~Item() {}

void Item::setID(string id) {
    if (!Validator::isNotEmpty(id)){
        throw std::invalid_argument("ID cannot be empty");
    }
    _id = id;
}

void Item::setName(std::string name) {
    
    //check if name is not empty
    if (!Validator::isNotEmpty(name)) {
        throw invalid_argument("Name cannot be empty");
    }
    //check if it is valid name
    if (!Validator::isValidItemName(name)) {
        throw invalid_argument("Invalid name: Use only alphanumeric characters, spaces, or hyphens.");
    }

    _name = name;
}
//set price
bool Item::setPrice(double price) {
    if (!Validator::isPositive(price)) {
        throw std::invalid_argument("Price cannot be negative or 0");
    }else{
         _price = price;
    
        return true;
    }
}

string Item::getID() const { return _id; }
string Item::getName() const { return _name; }
double Item::getPrice() const { return _price; }