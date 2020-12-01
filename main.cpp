#include <iostream>
#include <string>
using namespace std;

int main() {
    int option;
    // menu
    cout << "1. Search for a Senator's name" << endl;
    cout << "2. Exit" << endl;
    // option selection
    cout << "Enter one of the options above: ";
    cin >> option;
    
    // loop until exit menu
    while (option =! 2) {
        
        // function calls
        if (option == 1) {
            // Search the csv for Senator records

        }
        /*else if () {

        }*/
        else {
            cout << "Not a valid option, try again."
        }
    }
    return 0;
}