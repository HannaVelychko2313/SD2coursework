#ifndef SALONSYSTEM_H
#define SALONSYSTEM_H

#include <vector>
#include <string>
#include <iostream>
#include <limits> // Required for numeric_limits
#include "Customer.h"
#include "Service.h"
#include "Product.h"
#include "Appointment.h"
#include "Admin.h"
#include "Staff.h"

//define SalonSystem class
class SalonSystem {
private:
    // storing customer, service, product, appointment, admin, staff data using vectors
    std::vector<Customer*> _customers;
    std::vector<Service*> _services;
    std::vector<Product*> _products;
    std::vector<Appointment*> _appointments;
    std::vector<Admin*> _admins;
    std::vector<Staff*> _staffMembers;
    //last id
    int _lastStaffId = 0;
    int _lastAdminId = 0;

    //business details
    std::string _businessName = "";
    std::string _businessID = ""; 
    std::string _businessPhone = ""; 
    std::string _businessAddress= ""; 

    //helper functions
    void loadUsers();     // Reads from users.txt
    void loadBusinessDetails(); // Reads from business_details.txt
    void loadCustomers(); // Reads from customers.txt file
    void loadServices(); // Reads from services.txt file
    void loadProducts(); // Reads from products.txt file
    void loadAppointments(); // Reads from appointments.txt file
    void saveUsers();//Writes to users.txt
    void saveBusinessDetails(); // writes to business_details.txt
    void saveCustomers(); // Writes to customers.txt file
    void saveServices();//Writes to services.txt file
    void saveProducts();//Writes to products.txt file
    void saveAppointments(); // Writes to appointments.txt file 
    bool isValidPhone(const std::string& phone);//checks the phone
    std::string getRequiredInput(std::string prompt);//checks the input
//helper function for limits
void clearBuffer() const {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

public:
    // constructor and destructor
    SalonSystem();
    ~SalonSystem();
    //add admin and staff objects
    void addAdmin();
    void addStaff();
    // main menu
    void displayMainMenu();
    //user roles menus
    void displayStaffMenu();
    void displayAdminMenu();
    //third level of menus for admin
    void displayAdminCustomerMenu();//1 
    void displayAdminServiceMenu();//2 done
    void displayAdminProductMenu();//3 done
       
    //owner management
    void manageBusinessDetails();
    
    //third level of menus for staff
    void displayStaffCustomerMenu();
    void displayStaffServiceMenu();
    void displayStaffProductMenu();
    void displayStaffAppointmentMenu();
    
    

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
    void deleteProduct(std::string name);//case5
    void updateStock(std::string name);

    // appointment management    
    void scheduleAppointment(std::string date, std::string time, std::string customerName, std::string serviceName);//case 1
    void rescheduleAppointment(std::string apptID, std::string newDate, std::string newTime);//case 2
    void completeAppointment(std::string apptID);
    void viewAppointment(std::string apptID)const;
    void viewUpcomingAppointments() const;
    void viewAllAppointments() const;
    void cancelAppointment(std::string apptID);
    void printReceipt(std::string);
    //financial docs
    void viewFinDocs();
    void displayDocs(std::string fileName);

    // finding customer, service, product  by name 
    Customer* findCustomer(std::string name) const;
    Service* findService(std::string name) const;
    Product* findProduct(std::string name)const;
    //finding appointment by ID
    Appointment* findAppointment(std::string id) const;

    // loading data from the file and saving data to the file
    void loadData(); // call at startup
    void saveData(); // call at shutdown

    //template function for numeric input
    template <typename T>
    T getNumericInput(std::string prompt) {
        T value;
        std::cout << prompt;
        
        while (!(std::cin >> value)) {
            std::cout << "Invalid input! Please enter a numeric value: ";
            std::cin.clear(); // Clear error flags
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard bad input
        }
        
        // Clean up the newline character left in the buffer so getline() works next
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        return value;
    }
    
    
};

#endif