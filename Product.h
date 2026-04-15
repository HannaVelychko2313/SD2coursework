#ifndef PRODUCT_H
#define PRODUCT_H

#include "Item.h" 
#include <string>
#include "Validator.h"

class Product : public Item {
private:
    std::string _expiryDate;
    int _stock;

public:
    // parameterized Constructor
    Product(std::string id, std::string name, double price, int stock, std::string expiryDate);

    // setter and getter for expiry date and stock
    bool setStock(int stock);
    int getStock() const;
    void setExpiryDate(std::string expiryDate);
    std::string getExpiryDate() const;

    // Overriding the parent's pure virtual function
    void showInfo() const override; 
};

#endif