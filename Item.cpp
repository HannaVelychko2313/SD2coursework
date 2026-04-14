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
    if (id.empty()) throw std::invalid_argument("ID cannot be empty");
    _id = id;
}

#include <regex>

void Item::setName(std::string name) {
    // regex pattern that allows letters, numbers, spaces, hyphens, and apostrophes, excludes the pipe '|'
    std::regex pattern("^[A-Za-z0-9]+(?:[ '-][A-Za-z0-9]+)*$");

    if (name.empty()) {
        throw invalid_argument("Name cannot be empty");
    }
    
    if (!std::regex_match(name, pattern)) {
        throw invalid_argument("Invalid name: Use only alphanumeric characters, spaces, or hyphens.");
    }

    _name = name;
}
//set price
bool Item::setPrice(double price) {
    if (price < 0) {
        throw std::invalid_argument("Price cannot be negative");
    }else{
         _price = price;
    
        return true;
    }
}

string Item::getID() const { return _id; }
string Item::getName() const { return _name; }
double Item::getPrice() const { return _price; }