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

    }
    return 0;
}