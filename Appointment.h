#ifndef APPOINTMENT_H
#define APPOINTMENT_H

#include <string>
#include "Customer.h"
#include "Service.h"
#include "Product.h"
//a list of pre-defined values
enum class ApptStatus { SCHEDULED, COMPLETED, CANCELLED };

class Appointment {
private:
    std::string _apptID;
    std::string _date;     // DD-MM-YYYY
    std::string _time;     // HH:MM
    Customer* _customer;   // Pointer to the Customer
    Service* _service;     // Pointer to the Service
    Product* _product;     // Pointer to the Product used (if any)
    ApptStatus _status;    //a vatiable that holds ApptStatus instance

public:
//constructor declaration
    Appointment(std::string id, std::string date, std::string time, 
                Customer* c, Service* s, Product* p);

    // settter for status
    void setStatus(ApptStatus status) { _status = status; }

    // getters for id, date, time
    std::string getID() const;
    std::string getDate() const;
    std::string getTime() const;
    // getters for the pointers
    Customer* getCustomer() const;
    Service* getService() const;
    Product* getProduct() const;
    // convert enum to string for printing/saving
    std::string getStatusString() const;

    // reschedule appointment
    void rescheduleAppt(std::string newDate, std::string newTime);
    //display appointment 
    void displayAppt() const;
    //complete appointment
    void completeAppt();
    // cancel appointment
    void cancelAppt();
    //generate invoice
    void saveInvoiceToFile(std::string businessName, std::string businessID) const;
};

#endif