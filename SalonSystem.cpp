#include "SalonSystem.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

// constructor
SalonSystem::SalonSystem() {
    //call load functions
    loadData();
    cout << "System ready. " << _customers.size() << " customers loaded." << std::endl;
}
    


// destructor:
SalonSystem::~SalonSystem() {
    saveData();
    for (auto c : _customers) delete c;
    for (auto s : _services) delete s;
    for (auto p : _products) delete p;
    for (auto a : _appointments) delete a;
    for (auto ad : _admins) delete ad;
    for (auto st : _staffMembers) delete st;
    cout << "Memory cleared. System shutting down..." << endl;
}

// create admin object

void SalonSystem::addAdmin() {
    _lastAdminId++;
    string id = "A" + to_string(_lastAdminId);
    string name, password;

    cout << "Enter Admin Name: ";
    getline(cin, name);
    cout << "Set Admin Password: ";
    getline(cin, password);

    // Create the object and store it
    _admins.push_back(new Admin(id, name, password));
    cout << "Admin account created successfully!" << endl;
}
//create staff object
void SalonSystem::addStaff() {
    _lastStaffId++;
    string id = "ST" + to_string(_lastStaffId);
    string name, password;

    cout << "Enter Staff Name: ";
    getline(cin, name);
    cout << "Set Staff Password: ";
    getline(cin, password);

    // Create the object and store it
    _staffMembers.push_back(new Staff(id, name, password));
    cout << "Staff account created successfully!" << endl;
}
//main menu
void SalonSystem::displayMainMenu() {
    cout << "\nWelcome to the Business Management System" << endl;
    
    try {
        cout << "Enter a for admin, s for staff: ";
        char roleInput;
        cin >> roleInput;
        cout << "Please enter your password: ";
        string enteredPassword;
        cin >> enteredPassword;
        cin.ignore(1000, '\n');

        bool authenticated = false;

        if (roleInput == 'a') {
            // Search through loaded Admin objects
            for (Admin* ad : _admins) {
                if (ad->getPassword() == enteredPassword) {
                    ad->printRole(); // Polymorphic call to Admin::printRole
                    authenticated = true;
                    displayAdminMenu();
                    break;
                }
            }
        } 
        else if (roleInput == 's') {
            // Search through loaded Staff objects
            for (Staff* st : _staffMembers) {
                if (st->getPassword() == enteredPassword) {
                    st->printRole(); // Polymorphic call to Staff::printRole
                    authenticated = true;
                    displayStaffMenu();
                    break;
                }
            }
        }
        else if (roleInput == 'b' && enteredPassword == "owner") {
            manageBusinessDetails();
            authenticated = true;
        }

        if (!authenticated) {
            throw invalid_argument("Invalid role or password.");
        }
    }
    catch(const invalid_argument& e) {
        cerr << "Error: " << e.what() << endl;
    }
}
//admin menu
void SalonSystem::displayAdminMenu(){
    int adminChoice = -1;
    while (adminChoice !=0){
    cout << "\n-----WELCOME TO THE ADMIN MENU-----" << endl;
    cout << "Press 1 to manage customers" << endl;
    cout << "Press 2 to manage services" << endl;
    cout << "Press 3 to manage products" << endl;
    cout << "Press 4 to add a new Admin account" << endl;
    cout << "Press 5 to add a new Staff account" << endl;
    cout << "Press 6 to manage business details" << endl;
    cout << "Press 7 to view financial documentation" << endl;
    cout << "Press 0 to save and exit" << endl;
    cout << "Please make your choice: ";
    cin >> adminChoice;
    cin.ignore(1000, '\n'); // Clear buffer
    //switch for cases
    switch (adminChoice) {
            case 1:
                // call third-level menu for customer management
                {
                    displayAdminCustomerMenu();
                }
                break;
            case 2:
                // call third-level menu for service management
                {
                    displayAdminServiceMenu();
                }
                break;
            case 3:
                //call third-level menu for product management
                {
                    displayAdminProductMenu();
                }
            break;
            case 4:
                addAdmin(); // Triggers Admin creation
                break;
            case 5:
                addStaff(); // Triggers Staff creation
                break;
            case 6:
                manageBusinessDetails();
                break;
            case 7:
                viewFinDocs();
                break;
            
            case 0:
                cout << "Saving data... Goodbye!" << endl;
                saveData();
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
}
//staff menu
void SalonSystem::displayStaffMenu(){
    int staffChoice = -1;
    while (staffChoice !=0){
    cout << "\n-----WELCOME TO THE STAFF MENU-----" << endl;
    cout << "Press 1 to manage customers" << endl;
    cout << "Press 2 to manage services" << endl;
    cout << "Press 3 to manage products" << endl;
    cout << "Press 4 to manage appointments" << endl;
    cout << "Press 0 to save and exit" << endl;
    cout << "Please make your choice: ";
    cin >> staffChoice;
    cin.ignore(1000, '\n'); // Clear buffer
     //switch for cases
    switch (staffChoice) {
            case 1:
                // call third-level menu for customer management
                {
                    displayStaffCustomerMenu();
                }
                break;
            case 2:
                // call third-level menu for service management
                {
                    displayStaffServiceMenu();
                }
                break;
            case 3:
                //call third-level menu for product management
                {
                    displayStaffProductMenu();
                }
            break;
            case 4:
                // call third-level menu for appointment management
                {
                    displayStaffAppointmentMenu();
                }
            break;
            case 0:
                cout << "Saving data... Goodbye!" << endl;
                saveData();
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
    }

//third level menus-customer/service/product/appointment

//third-level menu for admin customer management
void SalonSystem::displayAdminCustomerMenu (){
    int adminChoice = -1;
    while (adminChoice !=0){
        cout << "\n-----WELCOME TO THE ADMIN CUSTOMER MANAGEMENT-----" << endl;
        cout << "Press 1 to add a new customer" << endl;
        cout << "Press 2 to update customer info" << endl;
        cout << "Press 3 to view a customer" << endl;
        cout << "Press 4 to view all customers" << endl;
        cout << "Press 5 to delete a customer" << endl;
        cout << "Press 6 to view customer appointments" << endl;
        cout << "Press 0 to go back to admin menu" << endl;
        cout << "Please make your choice: " << endl;
        
        cin >> adminChoice;

        cin.ignore(1000, '\n'); // Clear buffer

        // switch for menu cases
        switch (adminChoice)
        {
        case 1:
        {
        string name, phone;
        cout << "Enter Customer Name: "; 
        getline(cin, name);
        cout << "Enter Phone Number: ";
        getline(cin, phone);
        addCustomer(name, phone);
        }
        break;
        case 2:
        {
            string name;
            cout << "Please enter customer name: ";
            getline(cin, name);
            updateCustomerInfo(name);
        }
        break;
        case 3:
        {
            string name;
            cout << "Please enter customer name: "<<endl; 
            getline(cin, name);
            cout << "\n--- BEAUTY SALON CUSTOMER ---" << endl;
            viewCustomer(name);
        }
        break;
        case 4:
        {
            viewAllCustomers();
        }
        break;
        //delete a customer
        case 5:
        {   string name;
            char answer;
            cout << "Please enter customer name: " << endl;
            getline(cin, name);
            cout << "Are you sure you want to delete customer " << name << " permanently? y/n" << endl;
            cin >> answer;
            if (answer == 'y')
            {
                deleteCustomer(name);
            }
            else
            {
                cout << "Customer records remain in the system" << endl;
            }
        }
        break;

        //case 6 see all customer's appointments
        case 6:
        {   string name;
            cout << "Please enter customer name: " << endl;
            getline(cin, name);
            viewCustomerAppts(name);
        }
    
        break;
        //case 0 to return to admin menu
        case 0:
            cout<<"Going back to the admin menu. "<<endl;
            return;
        //default case
        default: 
            cout << "Invalid input. " << endl;
        break;

        }//end of switch
    }//end of while
}//end of functiom


//third-level menu for staff customer management

void SalonSystem::displayStaffCustomerMenu (){
    int adminChoice = -1;
    while (adminChoice !=0){
        cout << "\n-----WELCOME TO THE STAFF CUSTOMER MANAGEMENT-----" << endl;
        cout << "Press 1 to add a new customer" << endl;
        cout << "Press 2 to update customer info" << endl;
        cout << "Press 3 to view a customer" << endl;
        cout << "Press 4 to view all customers" << endl;
        cout << "Press 5 to view customer appointments" << endl;
        cout << "Press 0 to go back to staff menu" << endl;
        cout << "Please make your choice: " << endl;
        
        cin >> adminChoice;

        cin.ignore(1000, '\n'); // Clear buffer

        // switch for menu cases
        switch (adminChoice)
        {
        case 1:
        {
        string name, phone;
        cout << "Enter Customer Name: "; 
        getline(cin, name);
        cout << "Enter Phone Number: ";
        getline(cin, phone);
        addCustomer(name, phone);
        }
        break;
        case 2:
        {
            string name;
            cout << "Please enter customer name: ";
            getline(cin, name);
            updateCustomerInfo(name);
        }
        break;
        case 3:
        {
            string name;
            cout << "Please enter customer name: "<<endl; 
            getline(cin, name);
            cout << "\n--- BEAUTY SALON CUSTOMER ---" << endl;
            viewCustomer(name);
        }
        break;
        case 4:
        {
            viewAllCustomers();
        }
        break;
        case 5:
        {   string name;
            cout << "Please enter customer name: " << endl;
            getline(cin, name);
            viewCustomerAppts(name);
        }    
        break;
        //case 0 to return to admin menu
        case 0:
            cout<<"Going back to the staffmenu. "<<endl;
            return;
        //default case
        default: 
            cout << "Invalid input. " << endl;
        break;

        }//end of switch
    }//end of while
}//end of functiom


//third-level menu for admin service management
void SalonSystem::displayAdminServiceMenu (){
    int adminChoice = -1;
    while (adminChoice !=0){
        cout << "\n-----WELCOME TO THE ADMIN SERVICE MANAGEMENT-----" << endl;
        cout << "Press 1 to add a new service" << endl;
        cout << "Press 2 to update service info" << endl;
        cout << "Press 3 to view a service" << endl;
        cout << "Press 4 to view all services" << endl;
        cout << "Press 5 to delete a service" << endl;
        cout << "Press 0 to go back to admin menu" << endl;
        cout << "Please make your choice: " << endl;
        
        cin >> adminChoice;

        cin.ignore(1000, '\n'); // Clear buffer

        // switch for menu cases
        switch (adminChoice)
        {
        //add a service
        case 1:
        {
        string name;
        double price, duration;
        cout << "Enter service name: ";
        getline(cin, name);
        cout << "Enter service price: ";
        cin >> price;
        cout << "Enter service duration: ";
        cin >> duration;
        addService(name, price, duration);
        }
        break;
        //update a service
        case 2:
        {
            string name;
            cout << "Please enter service name: ";
            getline(cin, name);
            updateService(name);
        }
        break;
        //view a service
        case 3:
        {
            string name;
            cout << "Please enter service name: "; 
            getline(cin, name);
            cout << "\n--- BEAUTY SALON SERVICE ---" << endl;
            viewService(name);
        }
        break;
        //view all services
        case 4:
        {
            viewAllServices();
        }
        break;
        //delete a service
        case 5:
        {   string name;
            char answer;
            cout << "Please enter service name: ";
            getline(cin, name);
            cout << "Are you sure you want to delete the service " << name << " permanently? y/n";
            cin >> answer;
            if (answer == 'y')
            {
                deleteService(name);
            }
            else
            {
                cout << "Service records remain in the system" << endl;
            }
        }
        break;
        //case 0 to return to admin menu
        case 0:
            cout<<"Going back to the admin menu. "<<endl;
            return;
        //default case
        default: 
            cout << "Invalid input. Please try again" << endl;
        break;

        }//end of switch
    }//end of while
}//end of functiom
//third-level menu for staff service management
void SalonSystem::displayStaffServiceMenu (){
    int staffChoice = -1;
    while (staffChoice !=0){
        cout << "\n-----WELCOME TO THE STAFF SERVICE MANAGEMENT-----" << endl;
        cout << "Press 1 to view a service" << endl;
        cout << "Press 2 to view all services" << endl;
        cout << "Press 0 to go back to staff menu" << endl;
        cout << "Please make your choice: " << endl;
        
        cin >> staffChoice;

        cin.ignore(1000, '\n'); // Clear buffer

        // switch for menu cases
        switch (staffChoice)
        {
       
        case 1:
        {
            string name;
            cout << "Please enter service name: "; 
            getline(cin, name);
            cout << "\n--- BEAUTY SALON SERVICE ---" << endl;
            viewService(name);
        }
        break;
        //view all services
        case 2:
        {
            viewAllServices();
        }
        break;
       
        //case 0 to return to staff menu
        case 0:
            cout<<"Going back to the staff menu. "<<endl;
            return;
        //default case
        default: 
            cout << "Invalid input. Please try again" << endl;
        break;

        }//end of switch
    }//end of while
}//end of functiom

//third-level menu for admin product management
void SalonSystem::displayAdminProductMenu (){
    int adminChoice = -1;
    while (adminChoice !=0){
        cout << "\n-----WELCOME TO THE ADMIN PRODUCT MANAGEMENT-----" << endl;
        cout << "Press 1 to add a new product" << endl;
        cout << "Press 2 to update product info" << endl;
        cout << "Press 3 to view a product" << endl;
        cout << "Press 4 to view all poducts" << endl;
        cout << "Press 5 to delete a product" << endl;
        cout << "Press 0 to go back to admin menu" << endl;
        cout << "Please make your choice: " << endl;
        
        cin >> adminChoice;

        cin.ignore(1000, '\n'); // Clear buffer

        // switch for menu cases
        switch (adminChoice)
        {
        //add a product
        case 1:
        {
        string name, expiryDate;
        int stock;
        double price;
        cout << "Enter the product name: "<<endl;
        getline(cin, name);
        cout << "Enter the product price: "<<endl;
        cin >> price;
        cin.ignore(1000, '\n');
        cout << "Enter the product stock: ";
        cin >> stock;
        cin.ignore(1000, '\n');
        cout << "Enter the product expiry date: ";
        getline(cin, expiryDate);
        addProduct(name, price, stock, expiryDate);
        }
        break;
        //update a product
        case 2:
        {
            string name;
            cout << "Please enter product name: ";
            getline(cin, name);
            updateProduct(name);
        }
        break;
        //view a product
        case 3:
        {
            string name;
            cout << "Please enter the product name: "<<endl; 
            getline(cin, name);
            cout << "\n--- BEAUTY SALON PRODUCT---" << endl;
            viewProduct(name);
        }
        break;
        //view all products
        case 4:
        {
            viewAllProducts();
        }
        break;
        //delete a product
        case 5:
        {   string name;
            char answer;
            cout << "Please enter the product name: " << endl;
            getline(cin, name);
            cout << "Are you sure you want to delete the product " << name << " permanently? y/n" << endl;
            cin >> answer;
            if (answer == 'y')
            {
                deleteProduct(name);
            }
            else
            {
                cout << "Product records remain in the system" << endl;
            }
        }
        break;
        //case 0 to return to admin menu
        case 0:
            cout<<"Going back to the admin menu. "<<endl;
            return;
        //default case
        default: 
            cout << "Invalid input. Please try again" << endl;
        break;

        }//end of switch
    }//end of while
}//end of functiom
//third-level menu for staff product management
void SalonSystem::displayStaffProductMenu (){
    int staffChoice = -1;
    while (staffChoice !=0){
        cout << "\n-----WELCOME TO THE STAFF PRODUCT MANAGEMENT-----" << endl;
        cout << "Press 1 to update product stock" << endl;
        cout << "Press 2 to view a product" << endl;
        cout << "Press 3 to view all poducts" << endl;        
        cout << "Press 0 to go back to staff menu" << endl;
        cout << "Please make your choice: " << endl;
        
        cin >> staffChoice;

        cin.ignore(1000, '\n'); // Clear buffer

        // switch for menu cases
        switch (staffChoice)
        {
       
        //update a product stock
        case 1:
        {
            string name;
            cout << "Please enter product name: ";
            getline(cin, name);
            updateStock(name);
        }
        break;
        //view a product
        case 2:
        {
            string name;
            cout << "Please enter the product name: "<<endl; 
            getline(cin, name);
            cout << "\n--- BEAUTY SALON PRODUCT---" << endl;
            viewProduct(name);
        }
        break;
        //view all products
        case 3:
        {
            viewAllProducts();
        }
        break;
        
        //case 0 to return to staff menu
        case 0:
            cout<<"Going back to staff menu. "<<endl;
            return;
        //default case
        default: 
            cout << "Invalid input. Please try again" << endl;
        break;

        }//end of switch
    }//end of while
}//end of functiom


//third-level menu for staff appointment management
void SalonSystem::displayStaffAppointmentMenu (){
    int adminChoice = -1;
    while (adminChoice !=0){
        cout << "\n-----WELCOME TO THE STAFF APPOINTMENT MANAGEMENT-----" << endl;
        cout << "Press 1 to schedule an appointment" << endl;
        cout << "Press 2 to reschedule appointment" << endl;
        cout << "Press 3 to complete an appointment" << endl;
        cout << "Press 4 to view an appointment" << endl;
        cout << "Press 5 to view upcoming appointments" << endl;
        cout << "Press 6 to view all appointments" << endl;
        cout << "Press 7 to cancel an appointment" << endl;
        cout << "Press 8 to print a receipt for an appointment" << endl;
        cout << "Press 0 to go back to staff menu" << endl;
        cout << "Please make your choice: " << endl;
        
        cin >> adminChoice;

        cin.ignore(1000, '\n'); // Clear buffer

        // switch for menu cases
        switch (adminChoice)
        {
        //schedule an appointment
        case 1:
        {
        string date, time, customerName, serviceName;
        cout << "Enter customer name: "<<endl;
        getline(cin, customerName);
        cout << "Enter service name: " << endl;
        getline(cin, serviceName);
        cout << "Enter date: " << endl;
        getline(cin, date);
        cout << "Enter time: " << endl;
        getline(cin, time);        
        scheduleAppointment(date, time, customerName, serviceName);
        }
        break;
        //reschedule an appointment
        case 2:
        {
            string id, newDate, newTime;
            cout << "Please enter appointment ID: ";
            getline(cin, id);
            cout << "The current appointment is: " << endl;
            viewAppointment(id);
            cout << "Please enter new date in DD-MM-YYYY format: ";
            getline(cin,newDate);
            cout <<"Please enter new time in format HH:MM.";
            getline(cin,newTime);
            rescheduleAppointment(id, newDate, newTime);
        }
        break;
        //complete  an appointment
        case 3:
        {
            string id;
            cout << "Please enter appointment ID: ";
            getline(cin, id);
            completeAppointment(id);
        }
        break;
        // view an appointment
        case 4:
        {
            string id;
            cout << "Please enter appointment id: "<<endl; 
            getline(cin, id);
            cout << "\n--- APPOINTMENT DETAILS ---" << endl;
            viewAppointment(id);
        }
        break;
        case 5:
        {
            viewUpcomingAppointments();
        }
        break;
        // view all appointments
        case 6:
        {
            viewAllAppointments();
        }
        break;
        //cancel appointment
        case 7:
        {   string id;
            cout << "Please enter appointment ID: " << endl;
            getline(cin, id);
            cancelAppointment(id);            
        }
        break;
        case 8:

        {   string id;
            cout << "Please enter appointment ID: " << endl;
            getline(cin, id);
            printReceipt(id);
        }
            // case 0 to return to admin menu
            case 0:
            cout<<"Going back to the admin menu. "<<endl;
            return;
        //default case
        default: 
            cout << "Invalid input. Please try again" << endl;
        break;

        }//end of switch
    }//end of while
}//end of functiom







//customer management functions
//case 1 - add a customer
void SalonSystem::addCustomer(string name, string phone) {
    // 1. Create a temp ID
    string id = "C" + to_string(_customers.size() + 1);
    
    // 2. Create the object
    Customer* newCust = new Customer(id, "Temp", "0000000000");

    // 3. Validate both fields
    if (!newCust->setName(name)) {
        //cout << "Error: Invalid Name. Use letters only." << endl;
        delete newCust;
        return;
    }

    if (!newCust->setPhone(phone)) {
        //cout << "Error: Invalid Phone. Enter 10-12 digits without spaces/dashes." << endl;
        delete newCust;
        return;
    }

    // 4. Success!
    _customers.push_back(newCust);
    saveCustomers();
    cout << "Customer " << name << " added successfully!" << endl;
}
//case 2 - update a customer
void SalonSystem::updateCustomerInfo(string name) {
    Customer* c = findCustomer(name);
    if (c) {
        string newPhone;
        cout << "Current Info: " << endl;
        c->displayCustomerInfo();
        cout << "Enter new phone number: ";
        getline(cin, newPhone);
        if (c->setPhone(newPhone)) {
            cout << "Update successful!" << endl;
            saveCustomers();
            cout << "Updated customer info: " << endl;
            viewCustomer(name);
        }
    } else {
        cout << "Customer not found." << endl;
    }
}
//case 3 - view a customer
void SalonSystem::viewCustomer(string name) {
    Customer* c = findCustomer(name);
    if (c) {
        c->displayCustomerInfo();
    } else {
        cout << "Customer not found." << endl;
    }
}
//case 4 - view all customers
void SalonSystem::viewAllCustomers() const {
    cout << "\n--- BEAUTY SALON CUSTOMERS ---" << endl;
    if (_customers.empty()) {
        cout << "No customers found in the system." << endl;
        return;
    }
    for (auto c : _customers)
            {
                c->displayCustomerInfo();
            }
}
//case 5 - delete a customer
void SalonSystem::deleteCustomer(string name) {
    //it is iterator-a smart pointer-a pointer to the pointer
    for (auto it = _customers.begin(); it != _customers.end(); ++it) {
        //when we dereference iterator, we get a pointer *Customer
        if ((*it)->getName() == name) {
            delete *it;            // Free the memory on the heap - delete the Customer object 
            _customers.erase(it);  // Remove the pointer from the vector
            saveCustomers();       // Update the .txt file
            cout << "Customer removed successfully." << endl;
            return;
        }
    }
    cout << "Customer not found." << endl;
}
//case 6 - view all customer appointments
void SalonSystem::viewCustomerAppts(string name) {
    cout << "\n--- APPOINTMENT HISTORY FOR " << name << " ---" << endl;
    bool found = false;
    for (auto appt : _appointments) {
        if (appt->getCustomer()->getName() == name) {
            appt->displayAppt();
            found = true;
        }
    }
    if (!found) cout << "No appointments found for this customer." << endl;
}






//service management functions
//case 1 - add a service
void SalonSystem::addService(string name, double price, double duration) {
    try{
    //generating service ID
    string id = "S" + to_string(_services.size() + 1);
    //creating a new object of Service class on the heap    
    Service* newServicePtr = new Service(id, name, price, duration);
    //adding the pointer to the new service object to the vector of pointers
    _services.push_back(newServicePtr);
    saveServices();
    }
    catch (const invalid_argument e){
        cerr << "Error: " << e.what() << endl;
    }
}
//case 2-update a service-set a new price
 void SalonSystem::updateService(string name){
     Service *s = findService(name);
     if (s) {
         //string newName;         
         double newPrice, newDuration;
         cout << "Current Service Details: " << endl;
         s->showInfo();
         cout << "Enter new price: "<<endl;
         cin>>newPrice;
         if (s->setPrice(newPrice))
         {
             cout << "Update successful!" << endl;
             saveServices();
             cout << "Updated service price. " << endl;
             //viewService(name);
         }
    } else {
        cout << "Service not found." << endl;
    }

 };
 //case 3-view a service
 void SalonSystem::viewService(string name) {
    Service* s = findService(name);
    if (s) {
        s->showInfo();
    } else {
        cout << "Service not found." << endl;
    }
}
//case 4 - view all services
void SalonSystem::viewAllServices() const {
    cout << "\n--- BEAUTY SALON SERVICES---" << endl;
    if (_services.empty()) {
        cout << "No services found in the system." << endl;
        return;
    }
    for (auto s : _services)
            {
                s->showInfo();
            }
}
//case 5 - delete a service
void SalonSystem::deleteService(string name) {
    for (auto it = _services.begin(); it != _services.end(); ++it) {
        if ((*it)->getName() == name) {
            delete *it;            // Free the memory on the heap
            _services.erase(it);  // Remove the pointer from the vector
            saveServices();       // Update the services.txt file
            cout << "Service removed successfully." << endl;
            return;
        }
    }
    cout << "Service not found." << endl;
}

// product management functions
// adding a product
void SalonSystem::addProduct(string name, double price, int stock, string expiryDate) {
    try{
    string id = "P" + to_string(_products.size() + 1);
    //creating a new object of Product class on the heap    
    Product* newProductPtr = new Product(id, name, price, stock, expiryDate);
    //pushing the pointer to the vector
    _products.push_back(newProductPtr);
    saveProducts();
    } 
    catch(invalid_argument& e) {
        cerr << "Error: "<<e.what() << endl;
    }
}

//case 2-update a product -price only
 void SalonSystem::updateProduct(string name){
     Product *p = findProduct(name);
     if (p) {             
         double newPrice;
         cout << "Current product details: " << endl;
         p->showInfo();
         cout << "Enter new price: "<<endl;
         cin>>newPrice;
         if (p->setPrice(newPrice))
         {
             cout << "Update successful!" << endl;
             saveProducts();
             cout << "Updated product price. " << endl;
           
         }
    } else {
        cout << "Product not found." << endl;
    }
 };
 //update stock
 void SalonSystem::updateStock(string name){
     Product *p = findProduct(name);
     if (p) {             
         int newStock;
         cout << "Current product details: " << endl;
         p->showInfo();
         cout << "Enter new stock: "<<endl;
         cin>>newStock;
         try{
             p->setStock(newStock);
             cout << "Update successful!" << endl;
            saveProducts();
            cout << "Updated product stock. " << endl;
             
    } catch (const invalid_argument& e){
            cerr << "Error: " << e.what() << endl;
        }
    }
        else {
        cout << "Product not found." << endl;
    }
 };
 //case 3 - view a product
 void SalonSystem::viewProduct(string name) {
    Product* p = findProduct(name);
    if (p) {
        p->showInfo();
    } else {
        cout << "Product not found." << endl;
    }
}
//case 4 - view all products
void SalonSystem::viewAllProducts() const {
    cout << "\n--- BEAUTY SALON PRODUCTS---" << endl;
    if (_products.empty()) {
        cout << "No products found in the system." << endl;
        return;
    }
    for (auto p : _products)
            {
                p->showInfo();
            }
}
//case 5 - delete a product
void SalonSystem::deleteProduct(string name) {
    for (auto it = _products.begin(); it != _products.end(); ++it) {
        if ((*it)->getName() == name) {
            delete *it;            // Free the memory on the heap
            _products.erase(it);  // Remove the pointer from the vector
            saveProducts();       // Update the services.txt file
            cout << "Product removed successfully." << endl;
            return;
        }
    }
    cout << "Product not found." << endl;
}

//appointment management functions
//case 1 - schedule an appointment
void SalonSystem::scheduleAppointment(string date, string time, string customerName, string serviceName) {
    //find customer by name
    Customer* customerPtr = findCustomer(customerName);
    //find service by name
    Service* servicePtr= findService(serviceName);
    //check that the customer name is valid
    if (customerPtr == nullptr) {
        cout << "Error: invalid customer name." << endl;
        return;
    }
    //check that the service exists
     if (servicePtr == nullptr) {
        cout << "Error: invalid service name." << endl;
        return;
    }

    // Logic: Check for collisions before creating later
    // We use the 'timeToMinutes' logic we discussed earlier here

    //create an id for a new appointment    
    string apptID = "A" + to_string(_appointments.size() + 1);
    
    // Create the new Appointment object on the heap
    Appointment* apptPtr = new Appointment(apptID, date, time, customerPtr, servicePtr, nullptr);
    //push the pointer to the new appointment to the vector of appointment pointers
    _appointments.push_back(apptPtr);
    //let the user know that the new appointment has been scheduled
    cout << "Appointment " << apptID << " scheduled successfully!" << endl;
    saveAppointments();
}

//case 2 - reschedule an appointment
//need to check for overlap later!
void SalonSystem::rescheduleAppointment(string apptID, string newDate, string newTime){
    //find appointment by id calling function findAppointment()
    //later-try to find by customer/date
    Appointment* appt = findAppointment(apptID);
    // check if the appointment exists-the pointer is not nullptr
    if (appt != nullptr) {
        // use pointer to call reschedule() method of Appointment class
        appt->rescheduleAppt(newDate, newTime);
        } else {
        // if findAppointment returnes nullptr, the ID is not found
        cout << "Error: appointment ID " << apptID << " not found." << endl;
    }
    saveAppointments();
}
//case 3 - complete an appointment;
void SalonSystem::completeAppointment(string apptID){
    Appointment* appt = findAppointment(apptID);
     if (appt){
        appt->completeAppt();
        saveAppointments();
        cout << "Appointment " << apptID << " has been marked as completed" << endl;
        appt->saveInvoiceToFile(_businessName, _businessID);
        
    }
    else
    {
        cout << "Error: Appointment ID " << apptID << " not found";
    }

};
//case 4 -view an appointmnet
void SalonSystem::viewAppointment(string apptID) const{
    Appointment* a = findAppointment(apptID);
    if (a) {
        a->displayAppt();
    } else {
        cout << " Appointment not found." << endl;
    }
}
//case 5 -view upcoming appointmets
void SalonSystem::viewUpcomingAppointments() const {
    cout << "\n--- UPCOMING SCHEDULED APPOINTMENTS ---" << endl;
    bool found = false;
    for (const auto& appt : _appointments) {
            if (appt->getStatusString() == "SCHEDULED") {
            appt->displayAppt(); 
            //cout << "-----------------------" << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "No upcoming appointments found." << endl;
    }
}
//case 6 - view all appointments
void SalonSystem::viewAllAppointments() const {
    cout << "\n--- BEAUTY SALON APPOINTMENTS---" << endl;
    if (_appointments.empty()) {
        cout << "No appointments found in the system." << endl;
        return;
    }
    for (auto a : _appointments)
            {
                a->displayAppt();
            }
}
//cancel an appointment
void SalonSystem::cancelAppointment(string apptID){
    //find appointment pointer
    Appointment* appt=findAppointment(apptID);
    //cancel appointment if id is found
    if (appt){
        appt->cancelAppt();
        saveAppointments();
        cout << "Appointment "<<apptID<<" has been cancelled" << endl;
            }
    else
    {
        cout << "Appointment ID " << apptID << " not found";
    }
};
//print a receipt
void SalonSystem::printReceipt(string apptID){
    Appointment* appt = findAppointment(apptID);
     if (appt){        
        cout << "printing receipt for an appointment " << apptID << endl;
        appt->generateReceipt(_businessName, _businessID);        
    }
    else
    {
        cout << "Error: Appointment ID " << apptID << " not found";
    }

}
//view financial docs
void SalonSystem::viewFinDocs(){    
    int choice;
    string id;
    cout << "\n--- ADMIN DOCUMENT VIEWER ---" << endl;
    cout << "1. View an Invoice" << endl;
    cout << "2. View a Receipt" << endl;
    cout << "3. Return to Main Menu" << endl;
    cout << "Selection: ";
    cin >> choice;

    if (choice == 3) return;

    cout << "Enter Appointment ID: ";
    cin >> id;

    if (choice == 1) {
        displayDocs("invoice" + id + ".txt");
    } else if (choice == 2) {
        displayDocs("receipt_" + id + ".txt");
    }
}
//display docs
void SalonSystem::displayDocs(string fileName) {
    ifstream file(fileName);
    string line;

    if (file.is_open()) {
        cout << "\n--- Displaying File: " << fileName << " ---" << endl;
        while (getline(file, line)) {
            cout << line << endl;
        }
        file.close();
       
    } else {
        cout << "\nError: File not found: " << fileName << endl;
        cout << "Ensure the ID is correct or the file has been generated." << endl;
    }
}

//finding a service by name
Service* SalonSystem::findService(string name) const{
    //looping through the vector of pointers that point to  to find the right name
    for (auto service: _services) {        
        if (service->getName() == name) {
            return service;
        }
    }
    //return nullptr if there is no such name
    return nullptr; 
}
//finding a product by name
Product* SalonSystem::findProduct(string name) const{
    //looping through the vector of pointers that point to products
    for (auto product : _products) {        
        if (product->getName() == name) {
            return product;
        }
    }
    //return nullptr if there is no such name
    return nullptr; 
}

//finding an appointment by id
Appointment* SalonSystem::findAppointment(string id) const {
    //looping through the vector of pointers that point to appointments to find the right id
    for (auto appt : _appointments) {        
        if (appt->getID() == id) {
            return appt;
        }
    }
    //return nullptr if there is no such id
    return nullptr; 
}
//finding a customer by name
Customer* SalonSystem::findCustomer(string name) const{
    for (auto customer : _customers) {
        if (customer->getName() == name){
        return customer;
    }
}
    return nullptr;
}


//save functions
//saving all data
void SalonSystem::saveData() {
    // call save functions    
    saveUsers();
    saveBusinessDetails();
    saveCustomers();
    saveServices();
    saveProducts();
    saveAppointments();
    
    cout << "All system data backed up to files." << endl;
}
//save users
void SalonSystem::saveUsers() {
    ofstream outFile("users.txt");
    if (!outFile) return;

    // Save Admins
    for (Admin* a : _admins) {
        outFile << "A|" << a->getID() << "|" << a->getName() << "|" << a->getPassword() << endl;
    }

    // Save Staff
    for (Staff* s : _staffMembers) {
        outFile << "S|" << s->getID() << "|" << s->getName() << "|" << s->getPassword() << endl;
    }
    outFile.close();
}
//save business details
void SalonSystem::saveBusinessDetails() {
    ofstream outFile("business_details.txt");
    if (outFile.is_open()) {
        outFile << _businessName << endl;
        outFile << _businessID << endl;
        outFile << _businessPhone << endl;
        outFile << _businessAddress << endl;
        outFile.close();
    } else {
        cerr << "Error: Could not save business details to file." << endl;
    }
}
//save customers to customers.txt
void SalonSystem::saveCustomers() {
    //open customers.txt
    ofstream outFile("customers.txt");
    //check for error
    if (!outFile) {
        cerr << "Error: Could not open customers.txt for writing." << endl;
        return;
    }
    //add header to the file customer.txt
    outFile << "Business name: " << _businessName << endl;
    outFile << "Business ID: " << _businessID << endl;
    //loop through _customers vector _customers and save the data to the file customers.txt
    for (auto c : _customers) {
        outFile << c->getID() << "|"
                << c->getName() << "|"
                << c->getPhone() <<endl;
    }
    outFile.close();
}
//save services to services.txt
void SalonSystem::saveServices(){
    //open services.txt
    ofstream outFile("services.txt");
    //check for error
    if(!outFile){
        cerr<<"Error: Could not open services.txt for writing." << endl;
        return;
    }
    //add header to the file services.txt
    outFile << "Business name: " << _businessName << endl;
    outFile << "Business ID: " << _businessID << endl;
    //loop through the vector _services and write to services.txt
    for (auto s :_services){
        outFile << s->getID() << "|"
                << s->getName() << "|"
                << s->getPrice() << "|"
                << s->getDuration() << endl;
        }
        outFile.close();
}
//save products to products.txt
void SalonSystem::saveProducts(){
    //open products.txt
    ofstream outFile("products.txt");
    //check for error
    if(!outFile){
        cerr<<"Error: Could not open products.txt for writing." << endl;
        return;
    }
    //add header to the file products.txt
    outFile << "Business name: " << _businessName << endl;
    outFile << "Business ID: " << _businessID << endl;
    //loop through the vector _products and write to products.txt
    for (auto p : _products){
        outFile << p->getID() << "|"
                << p->getName() << "|"
                << p->getPrice() << "|"
                << p->getStock() << "|" 
                << p->getExpiryDate() << endl;
        }
        outFile.close();
}

//save appointments to appointments.txt
void SalonSystem::saveAppointments() {
    //open appointmets.txt
    ofstream outFile("appointments.txt");
    //check for error
    if (!outFile) {
        cerr<<"Error: Could not open appointments.txt for writing." << endl;
        return;
    }
    //add header to appointments.txt
    outFile << "Business name: " << _businessName << endl;
    outFile << "Business ID: " << _businessID << endl;
    //loop through the vector _appointments and save appointments to the file appointments.txt
    for (auto appt : _appointments) {
        outFile << appt->getID() << "|"
                << appt->getStatusString() << "|"
                << appt->getDate() << "|"
                << appt->getTime() << "|"
                << appt->getCustomer()->getName() << "|"
                << appt->getService()->getName() << "|"; 
        
        //check if optional product is there and save it too
        if (appt->getProduct() != nullptr) {
            outFile << appt->getProduct()->getName();
        } else {
            outFile << "NONE";
        }
        outFile << endl;
    }
    outFile.close();
}

//load all data
void SalonSystem::loadData() {
    cout << "Loading system data..." << endl;
    
    // call load functions
    loadUsers();
    loadBusinessDetails();
    loadCustomers();
    loadServices();
    loadProducts();
    loadAppointments(); 
    
    cout << "Load complete!" << endl;
}
//load users
void SalonSystem::loadUsers() {
    ifstream inFile("users.txt");
    if (!inFile) {
        // if no file exists, default admin is created
        cout << "No user records found. Creating default administrator..." << endl;
        _admins.push_back(new Admin("A0", "Default Admin", "admin890"));
        return;
    }

    string line;
    while (getline(inFile, line)) {
        stringstream ss(line);
        string type, id, name, pass;

        getline(ss, type, '|');
        getline(ss, id, '|');
        getline(ss, name, '|');
        getline(ss, pass);

        if (type == "A") {
            _admins.push_back(new Admin(id, name, pass));
        } else if (type == "S") {
            _staffMembers.push_back(new Staff(id, name, pass));
        }
    }
    inFile.close();
}
//load business details
void SalonSystem::loadBusinessDetails() {
    ifstream inFile("business_details.txt");
    if (inFile.is_open()) {
        getline(inFile, _businessName);
        getline(inFile, _businessID);
        getline(inFile, _businessPhone);
        getline(inFile, _businessAddress);
        inFile.close();
    } else {
       cout << "No existing business record found. Starting fresh." << endl;
    }
}
//load customer data
void SalonSystem::loadCustomers() {
    ifstream inFile("customers.txt");
    if (!inFile) return; // Exit quietly if file doesn't exist yet
    string line, name, phone, id;
    if (!getline(inFile, line)) return; // Skip Name or exit if empty
    if (!getline(inFile, line)) return; // Skip ID or exit if empty

    while (getline(inFile, line)) {
        stringstream ss(line);
        getline(ss, id, '|');
        getline(ss, name, '|');
        getline(ss, phone);

        // creating the object and adding it to the list
        _customers.push_back(new Customer(id, name, phone));
    }
    inFile.close();
}
void SalonSystem::loadProducts() {
    ifstream inFile("products.txt");
    if (!inFile) return; // Exit quietly if file doesn't exist yet
    string line, id, name, price, stock, expiryDate;

    if (!getline(inFile, line)) return; // Skip Name or exit if empty
    if (!getline(inFile, line)) return; // Skip ID or exit if empty

    while (getline(inFile, line)) {
        stringstream ss(line);
        getline(ss, id, '|');
        getline(ss, name, '|');
        getline(ss, price, '|');
        getline(ss, stock, '|');
        getline(ss, expiryDate);

        // creating the object and adding it to the list
        _products.push_back(new Product(id, name, stod(price), stoi(stock), expiryDate));
    }
    inFile.close();
}

void SalonSystem::loadServices() {
    ifstream inFile("services.txt");
    if (!inFile) return; // Exit quietly if file doesn't exist yet
    string line, id, name, price, duration;

    if (!getline(inFile, line)) return; // Skip Name or exit if empty
    if (!getline(inFile, line)) return; // Skip ID or exit if empty

    while (getline(inFile, line)) {
        stringstream ss(line);
        getline(ss, id, '|');
        getline(ss, name, '|');
        getline(ss, price, '|');
        getline(ss, duration);

        // creating the object and adding it to the list
        _services.push_back(new Service(id, name, stod(price), stod(duration)));
    }
    inFile.close();
}
void SalonSystem::loadAppointments() {
    ifstream inFile("appointments.txt");
    if (!inFile) return; // Exit quietly if file doesn't exist yet
    string line;

    if (!getline(inFile, line)) return; // Skip Name or exit if empty
    if (!getline(inFile, line)) return; // Skip ID or exit if empty

    while (getline(inFile, line)) {
        stringstream ss(line);
        string id, statusStr, date, time, cName, sName, pName;

        getline(ss, id, '|');
        getline(ss, statusStr, '|');
        getline(ss, date, '|');
        getline(ss, time, '|');
        getline(ss, cName, '|');
        getline(ss, sName, '|');
        getline(ss, pName, '|');

        // Use your existing "find" functions to get the pointers
        Customer* c = findCustomer(cName);
        Service* s = findService(sName);
        Product* p = (pName == "NONE") ? nullptr : findProduct(pName);

        // Only add if we actually found the customer and service
        if (c != nullptr && s != nullptr) {
            _appointments.push_back(new Appointment(id, date, time, c, s, p));
        }
    }
    inFile.close();
}


//manage business details
void SalonSystem::manageBusinessDetails() {
    cout << "\n--- MANAGE BUSINESS DETAILS ---" << endl;
    cout << "Current Name: " << (_businessName.empty() ? "Not Set" : _businessName) << endl;
    cout << "Current ID:   " << (_businessID.empty() ? "Not Set" : _businessID) << endl;
    cout << "Current Phone: " << (_businessPhone.empty() ? "Not Set" : _businessPhone) << endl;
    cout << "Current Adddress:   " << (_businessAddress.empty() ? "Not Set" : _businessAddress) << endl;
    cout << "-------------------------------" << endl;
    cout << "Would you like to update business details? y/n " << endl;
    char answer;
    cin >> answer;
    cin.ignore(1000, '\n');

    if (answer=='y'){
        cout<< "Enter New Business Name: ";
        getline(cin, _businessName);
        cout << "Enter New Business ID: ";
        getline(cin, _businessID);
        cout<< "Enter New Business Phone: ";
        getline(cin, _businessPhone);
        cout << "Enter New Business Address: ";
        getline(cin, _businessAddress);
        saveBusinessDetails(); 
        cout << "\nBusiness details updated and synced to all records!" << endl;
    }
    return;
}