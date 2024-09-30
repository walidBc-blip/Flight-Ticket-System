
//=================================================================================
// Name         : DS Assignment#4 
// Author       : 
// Version      : 1.0
// Date Created : Apr-17-2022
// Date Modified: 
// Description  : Starter Code for Flight-Ticket Management System using HASH TABLE in C++
//=================================================================================
#include<iostream>
#include<cstdlib>
#include<sstream>
#include<math.h>
#include<fstream>


#include "flightticket.h"
#include "flighthashtable.h"

//==========================================================
void listCommands()
{
	cout<<"\n----------------------------------"<<endl;
	cout<<"import <path>      	:Import flight-tickets from a CSV file"<<endl
		<<"export <path>      	:Export flight-tickets to a CSV file"<<endl
		<<"count_collisions   	:Print number of collisions"<<endl
		<<"add                	:Add a new flight-ticket"<<endl
		<<"delete <key>       	:Delete a flight-ticket"<<endl
		<<"find <key>         	:Find a flight-ticket's details"<<endl
		<<"allinday <date>    	:Display all flight-tickets in a day"<<endl
		<<"printASC <key>     	:Print flight-tickets in ascending order"<<endl
		<<"exit               	:Exit the program"<<endl;
}
//==========================================================

// to be completed with all the necessary method definitions

//==========================================================
int main(void)
{
    FlightHASHTABLE myFlightHASHTABLE;
    string user_input;
    string command;
    string key;

   
    while(true)
    {
        listCommands();
        cout<<">";
            
        getline(cin,user_input);

        // parse userinput into command and parameter(s)
        stringstream sstr(user_input);
        getline(sstr,command,' ');
        getline(sstr,key);
            
        if (command == "import")
        {
            int count = myFlightHASHTABLE.importCSV(key);
            cout<<endl<<endl<<count<<" flight-tickets imported!";
        }
        else if (command == "export")
        {
            ofstream f1;
            //to overwrite the old data in the file
            f1.open(key, ios::out);

            //number of flight tickets exported are displayed
            int count = myFlightHASHTABLE.exportCSV( key );
            cout<<endl<<endl<<count<<" flight-tickets exported!";

        }
        
        else if (command == "add")
        {
            string companyName;
            string flightNumber;
            string country_of_origin;
            string country_of_destination;
            string stopOver;
            string price;
            string time_of_departure;
            string time_of_arrival;
            string date;
            
            //making the user input details

            cout<<"\nEnter details : ";
            cout<<"\nComapny Name : ";
            getline(cin,companyName);
            cout<<"\nFlight Number : ";
            getline(cin,flightNumber);
            cout<<"\nCountry of Origin : ";
            getline(cin,country_of_origin);
            cout<<"\nCountry of destination : ";
            getline(cin,country_of_destination);
            cout<<"\nStop Over : ";
            getline(cin,stopOver);
            cout<<"\nPrice : ";
            getline(cin,price);
            cout<<"\nTime of departure : ";
            getline(cin,time_of_departure);
            cout<<"\nTime of arrival : ";
            getline(cin,time_of_arrival);
            cout<<"\nDate : ";
            getline(cin,date);
            
            //new ticket
            Flight_Ticket * data = new Flight_Ticket( companyName, stoi(flightNumber), country_of_origin , country_of_destination, stopOver, price, time_of_departure, time_of_arrival, date);
            
            //adding the ticket
            if ( myFlightHASHTABLE.add(data) == 1)
                cout<<"\nRecord added successfully!";

        }
        
        else if (command == "delete")
        {
            int check = 0;
            
            //getting the company name and flight number from the input
            
            string companyName = "" , flightNumber = "";
            int fNumber = 0;
            
            //seperating and inserting the values in the 2 variables
            for(int i = 0 ; i < key.length() ; i++)
            {
                if (check == 0 && key[i]!= ',')
                {
                    companyName += key[i];
                }
                
                if (key[i]==',')
                {
                    check = 1;
                }
                
                if(key[i] != ',' && check ==1)
                    flightNumber += key[i];
                
            }
            
            //converting flight number to int
            for (int i = 0; i< flightNumber.length(); i++)
            {
                fNumber += ( (int)flightNumber[i] -48 ) * pow( 10 , flightNumber.length() -1 - i);
            }
            
            //removing the record
            myFlightHASHTABLE.removeRecord( companyName, fNumber);
            
        }
        
        else if (command == "find")
        {
            int check = 0;
            
            //getting the company name and flight number from the input
            
            string companyName = "" , flightNumber = "";
            int fNumber = 0;
            
            //seperating and inserting the values in the 2 variables
            for(int i = 0 ; i < key.length() ; i++)
            {
                if (check == 0 && key[i]!= ',')
                {
                    companyName += key[i];
                }
                
                if (key[i]==',')
                {
                    check = 1;
                }
                
                if(key[i] != ',' && check ==1)
                    flightNumber += key[i];
                
            }
            
            //converting flight number to int
            for (int i = 0; i< flightNumber.length(); i++)
            {
                fNumber += ( (int)flightNumber[i] -48 ) * pow( 10 , flightNumber.length() -1 - i);
            }
            
            //funtion to find
            myFlightHASHTABLE.find( companyName, fNumber);
            
        }
        
        else if (command == "allinday")
        {
            myFlightHASHTABLE.allinday ( key );
        }
        
        else if (command == "printASC")
        {
            int check = 0;
            
            //getting the company name and flight number from the input
            
            string companyName = "" , flightNumber = "";
            int fNumber = 0;
            
            //seperating and inserting the values in the 2 variables
            for(int i = 0 ; i < key.length() ; i++)
            {
                if (check == 0 && key[i]!= ',')
                {
                    companyName += key[i];
                }
                
                if (key[i]==',')
                {
                    check = 1;
                }
                
                if(key[i] != ',' && check ==1)
                    flightNumber += key[i];
                
            }
            
            //converting flight number to int
            for (int i = 0; i< flightNumber.length(); i++)
            {
                fNumber += ( (int)flightNumber[i] -48 ) * pow( 10 , flightNumber.length() -1 - i);
            }
            
            //funtion to print in ascending
            myFlightHASHTABLE.printASC( companyName, fNumber);
            
        }
        
        else if (command == "count_collisions")
        {
            cout<<"\nTotal number of collisions is "<<myFlightHASHTABLE.count_collisions();
        }
        
        else if( user_input == "exit" )
            exit(0);
        
        else
            cout<<"\nInvalid Command!";
            
            

    }

    return 0;
}
