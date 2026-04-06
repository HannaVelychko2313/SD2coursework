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
    


// 2. Destructor: CLEANUP (Requirement a)
// This is critical because we used 'new' for our objects
SalonSystem::~SalonSystem() {
    saveData();
    for (auto c : _customers) delete c;
    for (auto s : _services) delete s;
    for (auto p : _products) delete p;
    for (auto a : _appointments) delete a;
    cout << "Memory cleared. System shutting down..." << endl;
}


void SalonSystem::displayMainMenu() {
    cout << "\nWelcome to the Business Management System" << endl;
    //try and catch for user roles
    try{
        cout << "Enter a for admin or s for staff" <<endl;
        char role;
        cin >> role;
        cout << "Please enter your password" << endl;
        string password;
        cin >> password;
        //clears the buffer
        cin.ignore(1000, '\n');
        if (role == 'a' && password == "admin890")
        {
            displayAdminMenu();
        }
        else if (role == 's' && password == "st45")
        {
            displayStaffMenu();
        }
        else
            throw invalid_argument ("Wrong creadentials");
    }
catch(invalid_argument e){
    cerr << "Error: " << e.what() << endl;
}
}
void SalonSystem::displayAdminMenu(){

    cout << "Press 1 to manage customers" << endl;
    cout << "Press 2 to manage services" << endl;
    cout << "Press 3 to manage products" << endl;
    cout << "Press 4 to make an order";
    cout << "Press 5 to manage appointments" << endl;
    cout << "Press 6 to generate an invoice" << endl;
    cout << "Press 7 to save and exit" << endl;
    cout << "Please make your choice: ";
}
void SalonSystem::displayStaffMenu(){
    cout << "Press 1 to manage customers" << endl;
    cout << "Press 2 to manage services" << endl;
    cout << "Press 3 to manage products" << endl;
    cout << "Press 4 to make an order";
    cout << "Press 5 to manage appointments" << endl;
    cout << "Press 6 to generate an invoice" << endl;
    cout << "Press 7 to save and exit" << endl;
    cout << "Please make your choice: ";

   
}

/* adding a customer
void SalonSystem::addCustomer(string name, string phone) {
    // generating customer ID
    string id = "C" + std::to_string(_customers.size() + 1);
    // creating a new object of the class Customer on the heap and storing the address in the pointer
    Customer* newCustPtr= new Customer(id, name, phone);
    //pushing the address of the new Customer object to the _customers vector
    _customers.push_back(newCustPtr);
    saveCustomers();
}*/
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

//adding a service
void SalonSystem::addService(string name, double price, double duration) {
    try{
    //generating service ID
    string id = "S" + to_string(_services.size() + 1);
    //creating a new object of Service class on the heap    
    Service* newServicePtr = new Service(id, name, price, duration);
    //adding the pointer to the new service pbject to the vector of pointers
    _services.push_back(newServicePtr);
    saveServices();
    }
    catch (const invalid_argument e){
        cerr << "Error: " << e.what() << endl;
    }
}

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
    catch(invalid_argument e) {
        cerr << "Error: "<<e.what() << endl;
    }
}
//finding a service by name
Service* SalonSystem::findService(string name) {
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
Product* SalonSystem::findProduct(string name) {
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
Appointment* SalonSystem::findAppointment(string id) {
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
Customer* SalonSystem::findCustomer(string name) {
    for (auto customer : _customers) {
        if (customer->getName() == name){
        return customer;
    }
}
    return nullptr;
}

//scheduling appointments
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
    //push the pointer to the newappintment to the vector of appointment pointers
    _appointments.push_back(apptPtr);
    //let the user know that the new appointment has been scheduled
    cout << "Appointment " << apptID << " scheduled successfully!" << endl;
    saveAppointments();
}

//updating existing appointment
//nedd to check for overlap later!
void SalonSystem::updateAppointment(string apptID, string newDate, string newTime){
    //find appointment by id calling function findAppointment()
    //later-try to find by customer/date
    Appointment* appt = findAppointment(apptID);
    // check if the appointment exists-the pointer is not nullptr
    if (appt != nullptr) {
        // use pointer to call reschedule() method of Appointment class
        appt->reschedule(newDate, newTime);
        } else {
        // if findAppointment returnes nullptr, the ID is not found
        cout << "Error: appointment ID " << apptID << " not found." << endl;
    }
    saveAppointments();
}
//saving all data
void SalonSystem::saveData() {
    // We call all the individual savers to refresh every file
    saveCustomers();
    saveServices();
    saveProducts();
    saveAppointments();
    
    cout << "All system data backed up to files." << endl;
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
    
    // Call the helpers in the correct order
    loadCustomers();
    loadServices();
    loadProducts();
    loadAppointments(); 
    
    cout << "Load complete!" << endl;
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
        string id, date, time, cName, sName, pName;

        getline(ss, id, '|');
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
//cancel appointment
void SalonSystem::cancelAppointment(string apptID){
    findAppointment(apptID);
};
//view appointments
void SalonSystem::viewAllAppointments() const{
    for (auto appt: _appointments){
        appt->displayAppointment(); 
    
    }
};