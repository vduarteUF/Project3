#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>
#include "Senator.h"
using namespace std;

void ReadSenator(string name, unordered_map<string, Senator*>& senators);

void ReadSenator(string name, unordered_map<string, Senator*>& senators)
{
    ifstream file;
    file.open("SenatorTradingV2.csv");
    string senator;
    string garbage; //better way to do this?
    bool found;
    while (!file.eof()) 
    {
        getline(file, senator, ',');
        if (name == senator)
        {
            //Create senator object and break
            Senator* newSenator = new Senator(name);
            senators.emplace(name, newSenator);
            found = true;
            break;
        }
        getline(file, garbage);
    }
    if (!found)
        cout << "Name not found." << endl;
}

int main() {

    unordered_map<string, Senator*> senators;

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

            //Search name
            cout << "Searching for " << name << "..." << endl;
            ReadSenator(name, senators);

            //Display trades
            if (senators.count(name) != 0)
            {
                cout << "Showing all trades for: " << name << endl;
                int numTrades = senators[name]->trades.size();
                for (int i = 0; i < numTrades; i++)
                {
                    string _ticker = senators[name]->trades[i].ticker;
                    string _owner = senators[name]->trades[i].owner;
                    string _type = senators[name]->trades[i].type;
                    string _date = senators[name]->trades[i].date;
                    cout << _ticker << ", " << _owner << ", " << _type << ", " << _date << endl; 
                }
                cout << "Total trades: " << numTrades << endl;
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
