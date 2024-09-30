#ifndef FlightHASHTABLE_H
#define FlightHASHTABLE_H

#include<iostream>
#include "flightticket.h"
// include additional header files as needed

using namespace std;

//=====================================

//class for list adt

template<typename Elem>
class MyList
{
    private:
        
        // struct for the node of the list
        struct Node
        {
            Elem elem;
            Node* prev;
            Node* next;
          
            Node ()
            {
                
            }
            Node(Elem e)
            {
                this->elem = e;
            }
        };
    
    public:
    
        //Iterator class for the list
        class Iterator
        {
            public:
                Elem& operator*() { return v->elem; }
                bool operator==(const Iterator& p) const  { return v == p.v; }
                bool operator!=(const Iterator& p) const  { return v != p.v; }
                Iterator& operator++()
                {
                    v = v->next;
                    return *this;
                }
                Iterator& operator--()
                {
                   v = v->prev;
                   return *this;
                }
                friend class MyList;
            
            private:
                Node* v; // pointer to the node
                Iterator(Node* u) // constructor
                {
                   v = u;
                }
        };
    
    public:
    
        MyList()                               // default constructor
        {
            n = 0;
            header = new Node;
            trailer = new Node;
            header->next = trailer;
            trailer->prev = header;
        }
    
        int size() const        { return n; }                       // list size
        bool empty() const      { return (n == 0); }                // is the list empty?
        Iterator begin() const  { return Iterator(header->next); }      // beginning position
        Iterator end() const    { return Iterator(trailer); }           // (just beyond) last position
    
        void insertFront(const Elem& e);        // insert at front
    
        void insertBack(const Elem& e)          // insert at rear
        {
            Node* temp = new Node(e);
            Node* u = trailer->prev;
            u->next = temp;
            trailer->prev = temp;
            
            temp->prev = u;
            temp->next = trailer;
            
            n++;
            
        }
        void insert(const Iterator& p, const Elem& e) // insert e before p
        {
            Node* w = p.v; //w points to the node associated with p
            Node* u = w->prev;
            Node* v = new Node;
            v->elem = e;
            v->next = w; w->prev = v;
            v->prev = u; u->next = v;
            n++; //update the number of elements
            
        }
        void erase(const Iterator& p)          // remove p
        {
            Node* v = p.v;
            Node* w = v->next;
            Node* u = v->prev;
            u->next = w; w->prev = u;
            delete v;
            n--; //update the number of elements
        }
    
        void display() //displaying the nodes in a list
        {
            int count = 1;
            for( Iterator i(begin()); i != end() ; ++i )
            {
                cout<<endl;
                cout<<count<<".";
                Elem t;
                t  = *i;
                t.displayNode();
               
                count++;
            }
        }
    
        // checking for a duplicate record in the lsit
        bool checkDuplicate(Flight_Ticket* data)
        {
            if (!empty())
            for( Iterator i (begin()) ; i != end() ; ++i )
            {
                Elem t;
                t  = *i;
                
                //checkNode checks
                if ( t.checkNode( *data) == true )
                {
                    return true;
                }
                
            }
            return false;
        }
    
        // looking for a duplicate key through the list
        bool checkDuplicateKey(string key, Flight_Ticket f )
        {
            if (!empty())
            for( Iterator i (begin()) ; i != end() ; ++i )
            {
                Elem t;
                t  = *i;
                
                //check key checks if the key is the same and checkNode should be false as it should not be the same Node while iterating
                if ( t.checkKey(key) == true and t.checkNode(f) == false )
                {
                    return true;
                }
                
            }
            return false;
        }
    
    
    private:
    
        int n;                                  // number of items
        Node* header;                           // head-of-list sentinel
        Node* trailer;                          // tail-of-list sentinel
};


//=====================================
//=====================================
class HashNode
{
    private:
        string key; // key = companyName+flightNumber
        Flight_Ticket value;
    public:
    
        //constructor
        HashNode(string key, Flight_Ticket value)
        {
            this->key = key;
            this->value = value;
        }
        HashNode()
        {
            
        }
    
        //display functions
    
        void displayNode()
        {
            value.displayTicket();
        }
    
        void displayNodeData()
        {
            value.displayTicketData();
        }
    
        //checker functions
    
        //to see if the ticket is same
        bool checkNode( Flight_Ticket f)
        {
            return value.checkTicket( f );
        }
    
        //to see if the date is same
        bool checkNodeDate(string date)
        {
            return value.checkDate( date );
        }
    
        //to see if the key is the same
        bool checkKey( string key )
        {
            return this->key == key;
        }
    
        //getter funtions
    
        Flight_Ticket getValue()
        {
            return this->value;
        }
    
        string getKey()
        {
            return this->key;
        }

        friend class FlightHASHTABLE;
};

//=============================================================================
class FlightHASHTABLE
{
    private:
        MyList<HashNode> *buckets;                //List of Buckets, Please create your own List Class called MyList
        int size;                        //Current Size of HashTable
        int capacity;                    // Total Capacity of HashTable
        int collisions;
        // add more attributes as needed
    public:
        FlightHASHTABLE();                        //constructor
        ~FlightHASHTABLE();                       //destructor
        long hashCode(string key);                       //implement and test different hash functions
        int importCSV(string path);            //Load all the flight-tickets from the CSV file to the HashTable
        int exportCSV(string path);            //Export all the flight-tickets from the HashTable to a CSV file in an ascending order
        int count_collisions();                //return the number of collisions on the HashTable
        int add(Flight_Ticket* data);          //add new flight to the HashTable
        void removeRecord (string companyName, int flightNumber);    //Delete a record with key from the hashtable
        void find(string companyName, int flightNumber);        //Find and Display records with same key entered
        void allinday(string date);                      //Find and Display records with same day entered
        void printASC(string companyName, int flightNumber);          //display the collisions for the entered key in an ascending order

       
};



#endif
