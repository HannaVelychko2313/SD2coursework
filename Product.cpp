#include "Product.h"
#include <iostream>
#include <regex>

using namespace std;

// Constructor
Product::Product(string id, string name, double price, int stock, string expiryDate) 
    : Item(id, name, price) {
    setStock(stock);
    setExpiryDate(expiryDate);
}
//setter for stock
bool Product::setStock(int stock){
    if (stock<0){
        throw std::invalid_argument("Stock cannot be negative");
    }
    else
    {
        _stock = stock;
        return true;
    }
}
//setter for expiry date
void Product::setExpiryDate(string date) {
    // Regex check for DD-MM-YYYY
    regex pattern("^\\d{2}-\\d{2}-\\d{4}$");
    if (!regex_match(date, pattern)) {
        throw invalid_argument("Invalid date. Please use DD-MM-YYYY");
    }
    _expiryDate = date;
}
//getter for stock
int Product::getStock() const{
    return _stock;
}
//getter for expiry date
string Product::getExpiryDate() const {
    return _expiryDate;
}

// Implementation of the virtual function showInfo
void Product::showInfo() const {
    cout << "Product ID: " <<_id<<endl;
    cout << "Product name: " << _name << endl;
    cout << "Price: £" << _price << endl;
    cout << "Stock: " << _stock << endl;
    cout <<"Expiry date: " << _expiryDate << endl;
}