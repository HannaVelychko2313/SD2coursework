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

    //business details
    std::string _businessName = "";
    std::string _businessID = ""; 
    std::string _businessPhone = ""; 
    std::string _businessAddress= ""; 

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
    //main menu
    void displayMainMenu();
    //user roles menus
    void displayStaffMenu();
    void displayAdminMenu();
    //third level of menus for admin
    void displayAdminCustomerMenu();//1 
    void displayAdminServiceMenu();//2 done
    void displayAdminProductMenu();//3 done
    void displayAdminAppointmentMenu();//4 done
    void displayAdminGenerateMenu();//5
    void displayAdminOrderMenu();//6
    
    //owner management
    void manageBusinessDetails();
    
    //third level of menus for staff
    void displayStaffCustomerMenu();
    void displayStaffServiceMenu();
    void displayStaffProductMenu();
    void displayStaffAppointmentMenu();
    void displayStaffGenerateMenu();
    //const void displayAdminOrderMenu();
    

    // customer management methods
    void addCustomer(std::string name, std::string phone);//case1 tested
    void updateCustomerInfo(std::string name);//case 2 tested updates only phone for now
    void viewCustomer(std::string name);//case3 tested
    void viewAllCustomers() const;//case4 tested
    void deleteCustomer(std::string name);//case5 has a bug ID collision after deleting Fix later
    void viewCustomerAppts(std::string name);//case6 view all appointments
    
    //service management methods
    void addService(std::string name, double price, double duration);//case 1
    void updateService(std::string name);//case 2
    void viewService(std::string name);//case 3
    void viewAllServices() const;//case 4
    void deleteService(std::string name);//case 5
    
    //product management methods
    void addProduct(std::string name, double price, int stock, std::string expiryDate);//case 1
    void updateProduct(std::string name);//case 2 
    void viewProduct(std::string name);//case3 
    void viewAllProducts() const;//case4 
    void deleteProducts(std::string name);//case5 
    
    
    // appointment management    
    void scheduleAppointment(std::string custID, std::string servID, std::string date, std::string time);//case 1
    void updateAppointment(std::string apptID, std::string newDate, std::string newTime);//case 2
    void viewAppointment(std::string apptID);                                            // case 3
    void viewAllAppointments() const;//case 4
    void cancelAppointment(std::string apptID);//case 5
   

    // finding customer, service, product  by name 
    Customer* findCustomer(std::string name);
    Service* findService(std::string name);
    Product* findProduct(std::string name);
    //finding appointment by ID
    Appointment* findAppointment(std::string id);

    // loading data from the file and saving data to the file
    void loadData(); // call at startup
    void saveData(); // call at shutdown
    
    // helper fuction to add the file header
    void addHeader() const;
    
};

#endif