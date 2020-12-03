#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include "Senator.h"
using namespace std;

//Function Declarations
void SingleSenator(unordered_map<string, Senator*>& senators); //Option 1
void DisplayNames(); //Option 4
void ReadSenator(string name, unordered_map<string, Senator*>& senators); //Helper

//Functions Definitions
void SingleSenator(unordered_map<string, Senator*>& senators)
{
    //Input name
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
void DisplayNames()
{
    ifstream file;
    file.open("SenatorTradingV2.csv");

    unordered_set<string> senatorNames;
    string senator;
    string garbage;

    getline(file, garbage);
    while (!file.eof())
    {
        getline(file, senator, ','); //There's a tiny bug in here where internal commas ("David A Perdue , Jr" for instance) are deleted
        if (senator[0] == '"')
        {
            senator = senator.substr(1);
            getline(file, garbage, '"'); //Recycling buh dum tis
            senator = senator + garbage;
        }
        if (senatorNames.count(senator) == 0)
        {
            senatorNames.emplace(senator);
            cout << senator << endl;
        }
        getline(file, garbage);
    }
    cout << "Total senators: " << senatorNames.size() << endl;
    file.close();
}
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
    file.close();
}

int main() {

    unordered_map<string, Senator*> senators;

    bool quit = true;

    //Loop until exit menu
    while (quit) {
        
        string option = "0";

        //Menu
        cout << "U.S. Senator Stock Market Data" << endl;
        cout << "1. Search for a Senator's records" << endl;
        // add more options below
        //cout << "2. " << endl;
        //cout << "3. " << endl;
        cout << "4. Display all availible senator names" << endl;
        cout << "5. Exit" << endl;

        //Option selection
        cout << "Enter one of the options above: ";
        getline(cin, option);

        //Function calls

        //Options 1: Searching a single senator
        if (option == "1") 
        {
            SingleSenator(senators);
        }
        //Option 4: Display all trading senator names
        else if (option == "4") 
        {
            DisplayNames();
        }
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
