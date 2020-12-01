#include <iostream>
#include <string>
using namespace std;

int main() {
    bool quit = true;

    // loop until exit menu
    while (quit) {
        
        string option = "0";
        // menu
        cout << "U.S. Senator Stock Market Data" << endl;
        cout << "1. Search for a Senator's records" << endl;
        cout << "2. Exit" << endl;
        
        // option selection
        cout << "Enter one of the options above: ";
        getline(cin, option);

        // function calls
        if (option == "1") {
            
            // input name
            string name;
            cout << "Enter a Senator's name: ";
            getline (cin, name);
            cout << "Searching for " << name << "..." << endl;

            // read in the csv


        }
        else if (option == "2") {
            
            // Exit the loop
            quit = false;
        }
        else {
            cout << "Not a valid option, try again." << endl;
        }
        cout << endl;
    }
    return 0;
}