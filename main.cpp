#include <iostream>
#include "SalonSystem.h"

using namespace std;



int main() {
    SalonSystem mySalon;
   // mySalon.loadData();
   // User newUser;

    int choice = -1;

    while (choice != 0) {
        
        mySalon.displayMainMenu();        
        cin >> choice;

        // Clear the input buffer to prevent "skipping" later getlines
        cin.ignore(1000, '\n'); 

        switch (choice) {
            case 1:
                // Call a sub-menu or function for Customers
                {
                string name, phone;
                cout << "Enter Customer Name: "; 
                getline(cin, name);
                cout << "Enter Phone Number: ";
                getline(cin, phone);
                mySalon.addCustomer(name, phone); 
            }
                break;
            case 2:
                // Logic for Services
                {
                    string name;
                    double price;
                    double duration;
                    cout << "Enter service name: " << endl;
                    getline(cin, name);
                    cout << "Enter a sevice price: " << endl;
                    cin>>price;
                    cout << "Enter duration: " << endl;
                    cin>> duration;
                    mySalon.addService(name, price, duration); 
            }
                break;
            case 5:
            {
            string date, time, custName, servName;
                
            cout << "--- Schedule New Appointment ---" << endl;
            cout << "Enter Date (DD-MM-YYYY): ";
            getline(cin, date);
                
            cout << "Enter Time (HH:MM): ";
            getline(cin, time);
                
            cout << "Enter Customer Name: ";
            getline(cin, custName);
                
            cout << "Enter Service Name: ";
            getline(cin, servName);

            // This calls the logic in SalonSystem.cpp
            mySalon.scheduleAppointment(date, time, custName, servName);
            // View appointments to verify they were added
            cout << "\n--- Current Appointments ---" << endl;
            mySalon.viewAllAppointments();
            }
                break;
            case 7:
                cout << "Saving data... Goodbye!" << endl;
                mySalon.saveData();
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}