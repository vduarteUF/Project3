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
void AllSenators(unordered_map<string, Senator*>& senators); //Option 2
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
void AllSenators(unordered_map<string, Senator*>& senators)
{
    cout << "Searching all senator's records..." << endl;
    
    ifstream file;
    file.open("SenatorTradingV2.csv");

    string name;
    string garbage;

    getline(file, garbage);
    while (!file.eof())
    {
        //Ensure the name is correct
        getline(file, name, ',');
        if (name == "") //I have tried endless to fix the blank senator bug, this is my best solution
                continue;
        if (name[0] == '"')
        {
            name = name + ',';
            getline(file, garbage, ',');
            name = name + garbage;
        }
        if (senators.count(name) == 0)
        {
            Senator* newSenator = new Senator(name);
            senators.emplace(name, newSenator);
        }
        getline(file, garbage);
    }

    int totalTrades = 0;
    for (auto i = senators.begin(); i != senators.end(); i++)
    {
        string name = i->first;
        cout << name << ":" << endl;
        cout << "Number of trades: " << i->second->trades.size() << endl;
        cout << endl;
        totalTrades += i->second->trades.size();
    }

    cout << "Total senators with trading records: " << senators.size() << endl;
    cout << "Total trades recorded: " << totalTrades << endl;

    file.close();
}
void DisplayNames()
{
    ifstream file;
    file.open("SenatorTradingV2.csv");

    unordered_set<string> senatorNames;
    string name;
    string garbage;

    getline(file, garbage);
    while (!file.eof())
    {
        //Ensure the name is correct
        getline(file, name, ',');
        if (name == "") //I have tried endless to fix the blank senator bug, this is my best solution
                continue;
        if (name[0] == '"')
        {
            name = name + ',';
            getline(file, garbage, ',');
            name = name + garbage;
        }
        if (senatorNames.count(name) == 0)
        { 
            senatorNames.emplace(name);
            cout << name << endl;
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
    string garbage;
    bool found;
    while (!file.eof()) 
    {
        //Ensure the name is correct
        getline(file, senator, ',');
        if (name == "") //I have tried endless to fix the blank senator bug, this is my best solution
                continue;
        if (senator[0] == '"')
        {
            senator = senator + ',';
            getline(file, garbage, ',');
            senator = senator + garbage;
        }
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
        cout << "1. Search for a Senator's public trading records" << endl;
        // add more options below
        cout << "2. Search all Senator's public trading records" << endl;
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
        //Option 2: Search all senators
        else if (option == "2")
        {
            AllSenators(senators);
        }
        //Option 4: Display all trading senator names
        else if (option == "4") 
        {
            DisplayNames();
        }
        //Option 5: Close program
        else if (option == "5") {
            
            // Exit the loop
            quit = false;
        }
        //Default case
        else {
            cout << "Not a valid option, try again." << endl;
        }
        cout << endl;
    }
    return 0;
}
