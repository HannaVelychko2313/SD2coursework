#include "Appointment.h"
#include <iostream>
#include <regex>

using namespace std;
//constructor defintion 
//using member initialization list
Appointment::Appointment(string id, string date, string time, Customer* c, Service* s, Product* p)
    : _apptID(id), _date(date), _time(time), _customer(c), _service(s), _product(p), _status(ApptStatus::SCHEDULED) {}
//getters
string Appointment::getID() const { return _apptID; }
string Appointment::getDate() const { return _date; }
string Appointment::getTime() const { return _time; }
Customer* Appointment::getCustomer() const { return _customer; }
Service* Appointment::getService() const { return _service; }
Product* Appointment::getProduct() const { return _product; }

//method to reschedule appointment
void Appointment::reschedule(string newDate, string newTime) {
    // Pattern for DD-MM-YYYY
    regex datePattern(R"(\d{2}-\d{2}-\d{4})");
    
    // Pattern for HH:MM (24-hour format)
    regex timePattern(R"(\d{2}:\d{2})");

    if (regex_match(newDate, datePattern) && std::regex_match(newTime, timePattern)) {
        _date = newDate;
        _time = newTime;
        cout << "Appointment " << _apptID << " is successfullt rescheduled to " << _date << " at " << _time << endl;
    } else {
        cout << "Error: Invalid format. Use DD-MM-YYYY and HH:MM." << endl;
    }
}
   
//method to get the status and convert it to string 
string Appointment::getStatusString() const {
    switch (_status) {
        case ApptStatus::SCHEDULED: return "Scheduled";
        case ApptStatus::COMPLETED: return "Completed";
        case ApptStatus::CANCELLED: return "Cancelled";
        default: return "Unknown";
    }
}
//method to display appointment
void Appointment::displayAppointment() const {
    //cout << "=== APPOINTMENT RECORD ===" << endl;
    cout << "ID: " << _apptID << endl;
    cout<< "Status: "<< getStatusString() << endl;
    cout << "Date: " << _date << endl;
    cout << "Time: " << _time << endl;
    cout << "Customer: " << _customer->getName() << endl;
    cout << "Service: " << _service->getName() << " (£" << _service->getPrice() << ")" << endl;
    if (_product) {
        cout << "Product: " << _product->getName() << " (£" << _product->getPrice() << ")" << endl;
    }
    cout << "--------------------------" << endl;
}