#include "Product.h"
#include <iostream>
#include <regex>

using namespace std;

// constructor
Product::Product(string id, string name, double price, int stock, string expiryDate) 
    : Item(id, name, price) {
    setStock(stock);
    setExpiryDate(expiryDate);
}
//setter for stock-check if the stock is negative
bool Product::setStock(int stock){
    if (!Validator::isNonNegative(stock)){
        throw invalid_argument("Stock cannot be negative");
    }
    else
    {
        _stock = stock;
        return true;
    }
}
//setter for expiry date
void Product::setExpiryDate(string date) {
    //check the date format    
    if (!Validator::isValidDate(date)) {        
        throw invalid_argument("Invalid date. Please use DD-MM-YYYY");
    }
    // check that the date is not in the past
    if (!Validator::isFutureDate(date)) {
        throw invalid_argument("Date cannot be in the past.");
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