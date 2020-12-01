#pragma once
#include <string>
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
            Trade(string _ticker, string _date, string _owner, string _type);
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

Senator::Trade::Trade(string _ticker, string _date, string _owner, string _type)
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
    //TODO: Read CSV and fill in trades vector
}

