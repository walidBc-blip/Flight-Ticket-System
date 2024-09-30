#ifndef FLIGHT_TICKET_H
#define FLIGHT_TICKET_H

#include<iostream>
using namespace std;

class Flight_Ticket
{
    private:
        string companyName;
        int flightNumber;
        string country_of_origin;
        string country_of_destination;
        string stopOver;
        string price;
        string time_of_departure;
        string time_of_arrival;
        string date;

    public:
    Flight_Ticket(string companyName, int flightNumber, string country_of_origin, string country_of_destination, string stopOver, string price, string time_of_departure, string time_of_arrival, string date);
    
    Flight_Ticket()
    {
        
    }
    
    void displayTicket();
    
    void displayTicketData();
    
    bool checkTicket( Flight_Ticket f);
    
    bool checkDate(string date)
    {
        return this->date == date;
    }
    
    string getKey()
    {
        return companyName + to_string(flightNumber);
    }
    
    string getDestination()
    {
        return this->country_of_destination;
    }
    
    string getcompanyName()
    {
        return companyName;
    }
    int getflightNumber()
    {
        return flightNumber;
    }
    string getcountry_of_origin()
    {
        return country_of_origin;
    }
    string getcountry_of_destination()
    {
        return country_of_destination;
    }
    string getstopOver()
    {
        return stopOver;
    }
    string getprice()
    {
        return price;
    }
    string gettime_of_departure()
    {
        return time_of_departure;
    }
    string gettime_of_arrival()
    {
        return time_of_arrival;
    }
    string getdate()
    {
        return date;
    }

       
};

#endif
