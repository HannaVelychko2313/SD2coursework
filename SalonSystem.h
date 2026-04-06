#ifndef SALONSYSTEM_H
#define SALONSYSTEM_H

#include <vector>
#include <string>
#include <iostream>
#include "Customer.h"
#include "Service.h"
#include "Product.h"
#include "Appointment.h"

//define SalonSystem class
class SalonSystem {
private:
    // storing customer, service, product, appointment data using vectors
    std::vector<Customer*> _customers;
    std::vector<Service*> _services;
    std::vector<Product*> _products;
    std::vector<Appointment*> _appointments;

    //headers
    const std::string _businessName = "";
    const std::string _businessID = ""; 
    //helper functions
    void loadCustomers(); // Reads from customers.txt file
    void loadServices(); // Reads from services.txt file
    void loadProducts(); // Reads from products.txt file
    void loadAppointments(); // Reads from appointments.txt file
    void saveCustomers();//Writes to customers.txt file
    void saveServices();//Writes to services.txt file
    void saveProducts();//Writes to products.txt file
    void saveAppointments(); // Writes to appointments.txt file 


public:
    // constructor and destructor
    SalonSystem();
    ~SalonSystem();
    //user roles menu
    void displayMainMenu();
    void displayAdminMenu();
    void displayStaffMenu();

    // adding customer, service, product
    void addCustomer(std::string name, std::string phone);
    void addService(std::string name, double price, double duration);
    void addProduct(std::string name, double price, int stock, std::string expiryDate);
    
    // scheduing, modifying, cancelling, viewing appointments and 
    // checking if staff is busy before creating and appointment or modifying it
    void scheduleAppointment(std::string custID, std::string servID, std::string date, std::string time);
    void updateAppointment(std::string apptID, std::string newDate, std::string newTime);
    void cancelAppointment(std::string apptID);
    void viewAllAppointments() const;

    // finding customer, service, product  by name and appointment by id
    Customer* findCustomer(std::string name);
    Service* findService(std::string name);
    Product* findProduct(std::string name);
    Appointment* findAppointment(std::string id);

    // loading data from the file and saving data to the file
    void loadData(); // call at startup
    void saveData(); // call at shutdown

    
    // helper fuction to add the file header
    void addHeader() const;
    
};

#endif