#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>
#include "Senator.h"
using namespace std;

void Read() {

}
int main() {

    unordered_map<string, Senator> senators;

    bool quit = true;

    // loop until exit menu
    while (quit) {
        
        string option = "0";
        // menu
        cout << "U.S. Senator Stock Market Data" << endl;
        cout << "1. Search for a Senator's records" << endl;
        // add more options below
        //cout << "2. " << endl;
        //cout << "3. " << endl;
        //cout << "4. " << endl;
        cout << "5. Exit" << endl;

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
            ifstream file;
            file.open("SenatorTradingV2.csv");
            string line;
            string date, owner, ticker, type, senator;
            int count = 0;
            while (!file.eof()) {
                getline(file, line);
                stringstream str_stream(line);
                getline (str_stream, senator, ',');
                getline (str_stream, ticker, ',');
                getline (str_stream, owner, ',');
                getline (str_stream, type, ',');
                getline (str_stream, date, ',');

                if (name == senator) {
                    cout << senator << ",";
                    cout << ticker << ",";
                    cout << date;
                    cout << endl;
                    count++;
                }
            }
            if (count == 0) {
                cout << "Name not found." << endl;
            }
            else {
                cout << "Number of Records " << count << "." << endl;
            }
        }
        // saved for future commands
        /*else if () {

        }*/
        /*else if () {

        }*/
        /*else if () {

        }*/
        else if (option == "5") {
            
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
