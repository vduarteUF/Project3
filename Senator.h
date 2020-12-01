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
        vector<Trade> trades;
        void UpdateTrades();
    public:
        Senator();
        Senator(string _name);
};

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

void Senator::UpdateTrades()
{
    ifstream file;
    file.open("SenatorTradingV2.csv");
    string line;
    string date, owner, ticker, type, senator;
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
            trades.push_back(Trade(ticker, owner, type, date));
        }
    }
}

