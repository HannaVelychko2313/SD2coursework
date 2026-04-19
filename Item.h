#ifndef ITEM_H
#define ITEM_H

#include <string>
#include "Validator.h"

class Item {
protected:
    std::string _id;
    std::string _name;
    double _price;

public:
    Item(); // Default Constructor
    Item(std::string id, std::string name, double price); // Parameterized constructor
    virtual ~Item();//Destructor

    // setters
    void setID(std::string id);
    void setName(std::string name);
    bool setPrice(double price);

    // getters
    std::string getID() const;
    std::string getName() const;
    double getPrice() const;
    //pure virtual function - example of dynamic polymorphism
    virtual void showInfo() const = 0; 
};

#endif