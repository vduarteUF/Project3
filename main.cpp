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
void ReadSenator(string name, unordered_map<string, Senator*>& senators); //Helper for Single Senator
void InvestmentCalculator(Senator* senator); //Helper for calculating trade success
void TradeCalculator(int lineNum, Senator::Trade trade);
string ConvertDate(string date);

//Functions Definitions
void SingleSenator(unordered_map<string, Senator*>& senators)
{
    //Input name
    string name;
    cout << "Enter a Senator's name: ";
    getline (cin, name);

    //Search name
    cout << "Searching for " << name << "..." << endl << endl;
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
            cout << "Total trades: " << numTrades << endl << endl;
        }

    //Calculate from stocks database
    InvestmentCalculator(senators[name]);
}
void AllSenators(unordered_map<string, Senator*>& senators)
{
    cout << "Searching all senator's records..." << endl;
    
    //Open file
    ifstream file;
    file.open("SenatorTradingV2.csv");

    //Variables for data retrieval
    string name;
    string garbage;

    getline(file, garbage); //Clears first line
    while (!file.eof())
    {
        //Ensure the name is correct
        getline(file, name, ',');
        if (name == "") //I have tried endless to fix the blank senator bug, this is my best solution
                continue;
        if (name[0] == '"') //Fixes issues with quoted names such as "A. Mitchell McConnell, Jr."
        {
            name = name + ',';
            getline(file, garbage, ',');
            name = name + garbage;
        }
        if (senators.count(name) == 0) //If name not in senator map, adds them to map
        {
            Senator* newSenator = new Senator(name);
            senators.emplace(name, newSenator);
        }
        getline(file, garbage);
    }

    //Provide basic data about all senators (name, number of trades)
    int totalTrades = 0;
    for (auto i = senators.begin(); i != senators.end(); i++)
    {
        string name = i->first;
        cout << name << ":" << endl;
        cout << "Number of trades: " << i->second->trades.size() << endl;
        cout << endl;
        totalTrades += i->second->trades.size();
    }

    cout << "Total senators with public trading records: " << senators.size() << endl;
    cout << "Total public trades recorded: " << totalTrades << endl;

    file.close();
}
void DisplayNames()
{
    //Open file
    ifstream file;
    file.open("SenatorTradingV2.csv");

    //Variables for data retrieval / storage
    unordered_set<string> senatorNames;
    string name;
    string garbage;

    getline(file, garbage); //Clears first line
    while (!file.eof())
    {
        //Ensure the name is correct
        getline(file, name, ',');
        if (name == "") //I have tried endless to fix the blank senator bug, this is my best solution
                continue;
        if (name[0] == '"') //Fixes issues with quoted names such as "A. Mitchell McConnell, Jr."
        {
            name = name + ',';
            getline(file, garbage, ',');
            name = name + garbage;
        }
        if (senatorNames.count(name) == 0) //If name not in set, places it in and prints name
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
    //Variables for retrieving data / opening file
    ifstream file;
    file.open("SenatorTradingV2.csv");
    string senator;
    string garbage;
    bool found; //Detects whether the name was found or not

    while (!file.eof()) 
    {
        //Ensure the name is correct
        getline(file, senator, ',');
        if (name == "") //I have tried endless to fix the blank senator bug, this is my best solution
                continue;
        if (senator[0] == '"') //Fixes name issues with quoted name such as "A. Mitchell McConnell, Jr."
        {
            senator = senator + ',';
            getline(file, garbage, ',');
            senator = senator + garbage;
        }
        if (name == senator) //Match found
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
void InvestmentCalculator(Senator* senator)
{
    cout << "Analyzing investments..." << endl;

    //Variables for data retrieval
    ifstream file;
    string garbage;
    string line;
    int lineNum = 0;
    string stockDate;

    //Goes through each of the senator's trades
    for (int i = 0; i < senator->trades.size(); i++)
    {
        //Opens file
        file.open("StockMarketDataset/stocks/" + senator->trades[i].ticker + ".csv");
        if (!file.is_open())
        {
            cout << "Couldn't find data for ticker: " << senator->trades[i].ticker << endl;
            cout << "File needed: " << "StockMarketDataset/stocks/" + senator->trades[i].ticker + ".csv" << endl;
            continue;
        }
        
        //Searches for where a senator's trade date lines up with the trade date on the stock database
        while (!file.eof())
        {
            stringstream str_stream(line);
            getline(file, line);
            getline(str_stream, stockDate, ',');
            lineNum++;
            string senatorTradeDate = ConvertDate(senator->trades[i].date); //Converts date formats for comparison (trying to convert stockDate breaks apart time and space)

            //Upon match, analyzes the trade specifically
            if (stockDate == senatorTradeDate)
            {
                cout << senator->trades[i].ticker << " trade on: " << stockDate << endl; //TODO: SEE IF TRADE WAS GOOD OR NOT
                TradeCalculator(lineNum, senator->trades[i]);
            }
            getline(str_stream, garbage);
        }
        lineNum = 0;
        file.close();
    }

    cout << endl;
    cout << "NOTE: There may be less analyzed trades than recorded trades due to database not containing information on certain days.";
}
void TradeCalculator(int lineNum, Senator::Trade trade)
{
    //Constant values for calculations
    const int DAYS_OUT = 10;

    //Variables for data retrieval
    ifstream file;
    string garbage;
    string line;
    string stockDate, open, high, low, close, adjClose, volume;

    //Opens file
    file.open("StockMarketDataset/stocks/" + trade.ticker + ".csv");
    if (!file.is_open())
    {
        cout << "Couldn't find data for ticker: " << trade.ticker << endl;
        cout << "File needed: " << "StockMarketDataset/stocks/" + trade.ticker + ".csv" << endl;
        return;
    }
    
    //Skips to relevant lines
    for (int i = 0; i < lineNum - 2; i++)
    {
        getline(file, garbage, '\n');
    }

    //Loops through the next DAYS_OUT days
    for (int i = 0; i < DAYS_OUT; i++)
    {
        getline(file, line);
        stringstream str_stream(line);
        getline(str_stream, stockDate, ',');
        getline(str_stream, open, ',');
        getline(str_stream, high, ',');
        getline(str_stream, low, ',');
        getline(str_stream, close, ',');
        getline(str_stream, adjClose, ',');
        getline(str_stream, volume);

        cout << "Date: " << stockDate << endl;
        cout << "Open: " << open << endl;
        cout << "High: " << high << endl;
        cout << "Low: " << low << endl;
        cout << "Close: " << close << endl;
        cout << "AdjClose: " << adjClose << endl;
        cout << "Volume: " << volume << endl;
        cout << endl;
    }
    file.close();
}
string ConvertDate(string date)
{
    //String manipulations to get the dates in a comparable state
    int pos = date.find_first_of('/');
    string month = date.substr(0, pos);
    if (month.size() == 1)
        month = '0' + month;
    date = date.substr(pos+1);
    pos = date.find_first_of('/');
    string day = date.substr(0, pos);
    if (day.size() == 1)
        day = '0' + day;
    string year = date.substr(pos+1);
    return year + '-' + month + '-' + day;
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
