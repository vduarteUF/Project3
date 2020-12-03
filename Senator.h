#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
using namespace std;

class Senator
{
    public:
        struct Trade
        {
            string ticker; //Name of stock being traded
            string date; //Library to make date/time object?
            string owner; //Self, Spouse, Child, Joint
            string type; //Sale(Full), Sale(Partial), Purchase

            Trade();
            Trade(string _ticker, string _owner, string _type, string _date);
        };
    private:
        string name;
        
        void UpdateTrades();
    public:
        vector<Trade> trades;

        Senator();
        Senator(string _name);
        ~Senator();
};

// Trade nested class definitions
Senator::Trade::Trade()
{
    ticker = "N/A";
    date = "N/A";
    owner = "N/A";
    type = "N/A";
}

Senator::Trade::Trade(string _ticker, string _owner, string _type, string _date)
{
    this->ticker = _ticker;
    this->date = _date;
    this->owner = _owner;
    this->type = _type;
}

//Senator class definitions
Senator::Senator()
{
    name = "N/A";
    trades = {};
}

Senator::Senator(string _name)
{
    this->name = _name;
    UpdateTrades();
}

Senator::~Senator()
{
    //Need stuff here to prevent shallow deletion?
}

void Senator::UpdateTrades()
{
    ifstream file;
    file.open("SenatorTradingV2.csv");
    string line;
    string senator, ticker, owner, type, date;
    int count;
    while (!file.eof()) 
    {
        getline(file, line);
        stringstream str_stream(line);
        getline (str_stream, senator, ',');
        getline (str_stream, ticker, ',');
        getline (str_stream, owner, ',');
        getline (str_stream, type, ',');
        getline (str_stream, date, ',');

        if (name == senator)
        {
            Trade newTrade(ticker, owner, type, date);
            trades.push_back(newTrade);
        }
    }
}

