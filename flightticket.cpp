#include "flightticket.h"

Flight_Ticket::Flight_Ticket(string companyName, int flightNumber, string country_of_origin, string country_of_destination, string stopOver, string price, string time_of_departure, string time_of_arrival, string date)
{
    this->companyName = companyName ;
    this->flightNumber = flightNumber;
    this->country_of_origin = country_of_origin;
    this->country_of_destination = country_of_destination;
    this->stopOver = stopOver;
    this->price = price;
    this->time_of_departure = time_of_departure;
    this->time_of_arrival = time_of_arrival;
    this->date = date;

}

void  Flight_Ticket::displayTicket()
{
    cout<<"companyName : "<<companyName;
    cout<<"\n  flightNumber : "<<flightNumber;
    cout<<"\n  country_of_origin : "<<country_of_origin<<"\n  country_of_destination : "<<country_of_destination;
    cout<<"\n  stopOver : "<<stopOver<<"\n  price : "<<price;
    cout<<"\n  time_of_departure : "<<time_of_departure;
    cout<<"\n  time_of_arrival : "<<time_of_arrival<<"\n  date : "<<date;
    
}

void Flight_Ticket::displayTicketData()
{
    cout<<companyName<<","<<flightNumber<<","<<country_of_origin<<","<<country_of_destination<<","<<stopOver<<","<<price<<","<<time_of_departure<<","<<time_of_arrival<<","<<date<<endl;
}

bool Flight_Ticket::checkTicket( Flight_Ticket f)
{
    return
    this->companyName == f.companyName &&
    this->flightNumber == f.flightNumber &&
    this->country_of_origin == f.country_of_origin &&
    this->country_of_destination == f.country_of_destination &&
    this->stopOver == f.stopOver &&
    this->price == f.price &&
    this->time_of_departure == f.time_of_departure &&
    this->time_of_arrival == f.time_of_arrival &&
    this->date == f.date;
    
}
//=============================================================================
