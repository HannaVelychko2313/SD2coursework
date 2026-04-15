#include "Appointment.h"
#include <iostream>
#include <regex>
#include <fstream> 


using namespace std;
//constructor defintion 
//using member initialization list
Appointment::Appointment(string id, string date, string time, Customer* c, Service* s, Product* p)
    : _apptID(id), _customer(c), _service(s), _product(p), _status(ApptStatus::SCHEDULED) {
    setDate(date);
    setTime(time);
}
//setters
void Appointment::setDate(string date){
    // Regex check for DD-MM-YYYY
    regex pattern("^\\d{2}-\\d{2}-\\d{4}$");
    if (!regex_match(date, pattern)) {
        throw invalid_argument("Invalid date. Please use DD-MM-YYYY");
    }
    // check that the date is not in the past
    if (!Validator::isFutureDate(date)) {
        throw invalid_argument("Date cannot be in the past.");
    }
    _date = date;
}
void Appointment::setTime(string time){
    // Regex check for HH:MM starting at 9:00 and finishing at 18:00
    regex pattern("^((0?9|1[0-7]):[0-5][0-9]|18:00)$");
    if (!regex_match(time, pattern)) {
        throw invalid_argument("Invalid time. Please use HH:MM");
    }
    _time = time;

}

//getters
string Appointment::getID() const { return _apptID; }
string Appointment::getDate() const { return _date; }
string Appointment::getTime() const { return _time; }
Customer* Appointment::getCustomer() const { return _customer; }
Service* Appointment::getService() const { return _service; }
Product* Appointment::getProduct() const { return _product; }



//method to get the status and convert it to string 
string Appointment::getStatusString() const {
    switch (_status) {
        case ApptStatus::SCHEDULED: return "Scheduled";
        case ApptStatus::COMPLETED: return "Completed";
        case ApptStatus::CANCELLED: return "Cancelled";
        default: return "Unknown";
    }
}
//method to display an appointment
void Appointment::displayAppt() const {
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
//method to complete an appointment
void Appointment::completeAppt() {
    _status = ApptStatus::COMPLETED;
}
//method to cancel an appointment
void Appointment::cancelAppt() {
    _status = ApptStatus::CANCELLED;
}
//save invoice to file
void Appointment::saveInvoiceToFile(string businessName, string businessID) const {
    // generate the dynamic filename
    string fileName = "invoice" + _apptID + ".txt";
    //output invoice to file
    ofstream outFile(fileName);
    if (!outFile) {
        cerr << "Error: Could not create invoice file " << fileName << endl;
        return;
    }
    // write the invoice data to the file
    outFile << "Business Name: " << businessName << endl;
    outFile << "Business ID: " << businessID << endl;   
    outFile << "BEAUTY SALON INVOICE" << endl;    
    outFile << "Invoice ID: " << _apptID << endl;
    outFile << "Customer:   " << _customer->getName() << endl;
    outFile << "Date:       " << _date << " at " << _time << endl;
   
    double total = _service->getPrice();
    outFile << "Service: " << _service->getName() << " ... £" << _service->getPrice() << endl;

    if (_product) {
        total += _product->getPrice();
        outFile << "Product: " << _product->getName() << " ... £" << _product->getPrice() << endl;
    }

    outFile << "--------------------------------" << endl;
    outFile << "TOTAL: £" << total << endl;
    
    outFile.close();
    cout << "System: Invoice saved to " << fileName << endl;
}
void Appointment::generateReceipt(string businessName, string businessID) const {
    // Dynamic filename for the receipt
    string fileName = "receipt_" + _apptID + ".txt";
    ofstream outFile(fileName);

    if (!outFile) {
        cerr << "Error: Could not create receipt file." << endl;
        return;
    }

   
    outFile << "CUSTOMER RECEIPT" << endl;
    outFile << "Business: " << businessName << endl;    
    outFile <<" Business ID: " << businessID << endl;
    outFile << "Receipt For Invoice: #" << _apptID << endl;
    outFile << "Customer: " << _customer->getName() << endl;
   

    double total = _service->getPrice();
    outFile << "Service: " << _service->getName() << " - £" << _service->getPrice() << endl;

    if (_product) {
        total += _product->getPrice();
        outFile << "Product: " << _product->getName() << " - £" << _product->getPrice() << endl;
    }

    outFile << "--------------------------------" << endl;
    outFile << "TOTAL PAID: £" << total << endl;
    outFile << "STATUS: PAID IN FULL" << endl;
    outFile << "--------------------------------" << endl;
    outFile << "Thank you for your business!" << endl;
    
    outFile.close();
    cout << "System: Receipt generated successfully: " << fileName << endl;
}