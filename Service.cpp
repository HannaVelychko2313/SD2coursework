#include "Service.h"
#include <iostream>
#include <stdexcept>

using namespace std;

// Constructor
Service::Service(string id, string name, double price, double duration) 
    : Item(id, name, price) {
    setDuration(duration);
}
//setter for duration
void Service::setDuration(double duration) {
     if (!Validator::isPositive(duration)) {
        throw invalid_argument("Service duration must be greater than zero.");
    }
    if (!Validator::isValidDuration(duration)) {
        throw invalid_argument("Service duration cannot exceed 5 hours.");
    } 
    _duration = duration;
    }


double Service::getDuration() const {
    return _duration;
}

// Implementation of the pure virtual function showInfo
void Service::showInfo() const {
    cout << "Service ID: " <<_id << endl;
    cout << "Service name: " << _name << endl;
    cout << "Service price: £" << _price << endl;
    cout << "Service duration: " << _duration << endl;
    cout << "-----------------------" << endl;
}