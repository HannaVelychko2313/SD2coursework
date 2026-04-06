#ifndef SERVICE_H
#define SERVICE_H

#include "Item.h" 
#include <string>


class Service : public Item {
private:
    double _duration;

public:
    // parameterized constructor for service object
    Service(std::string id, std::string name, double price, double duration);

    // setter and getter for duration
    void setDuration(double duration);
    double getDuration() const;

    // Overriding the parent's pure virtual function
    void showInfo() const override; 
};

#endif