#include <iostream>
#include <string>
using namespace std;

int main() {
    bool quit = true;

    // loop until exit menu
    while (quit) {
        
        int option;
        // menu
        cout << "U.S. Senator Stock Market Data" << endl;
        cout << "1. Search for a Senator's records" << endl;
        cout << "2. Exit" << endl;
        
        // option selection
        cout << "Enter one of the options above: ";
        cin >> option;

        // function calls
        if (option == 1) {
            
            // Search the csv for Senator records

        }
        else if (option == 2) {
            
            // Exit the loop
            quit = false;
        }
        else {
            cout << "Not a valid option, try again."
        }
    }
    return 0;
}