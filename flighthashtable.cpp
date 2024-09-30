#include "flighthashtable.h"
#include<time.h>
#include<fstream>
#include<math.h>

//comstructor
FlightHASHTABLE::FlightHASHTABLE()
{
    //nearest prime number to 125000 (25% more than 100000)
    this->capacity = 125003;
    this->size = 0;
    this->collisions = 0;
    buckets = new MyList<HashNode>[capacity];      //Array of a list/chain
}

FlightHASHTABLE::~FlightHASHTABLE()
{
    delete[] buckets;
}

int FlightHASHTABLE::count_collisions()
{
    collisions = 0;
    
     for(int hcode = 0; hcode < capacity ; hcode++)
     {
         //number of collisions in each list
         int listCollisions = 0;
         
         //if the list is not empty and if there are more than 1 elements
         if(!buckets[hcode].empty() && buckets[hcode].size()!= 1)
          for( MyList<HashNode>::Iterator i (buckets[hcode].begin()) ; i != buckets[hcode].end() ; ++i )
          {
              HashNode t1;
              t1  = *i;
              
              //to see if a duplicate key exists in the list
              int check = 0;
             
              //iterating through the list,                                it runs till the iterator in the first loop is not reached
              for( MyList<HashNode>::Iterator j (buckets[hcode].begin()) ; j != i  ; ++j )
              {
                  HashNode t2;
                  t2  = *j;
                  string key = t2.getKey();
                  
                  // if a duplicate key is found before the iterator i
                  if( t1.checkKey( key )   ==   true  )
                  {
                      check = 1;
                  }
                  
              }
              
              //collisions increase if there's no duplicate key
              if(check == 0)
              {
                  listCollisions++;
              }
              
              
        }
         
         if(listCollisions == 0)
             collisions += listCollisions;
         
         else // the collisions in a list ( number of distinct original keys - 1 )
             collisions += listCollisions - 1;
    }
    
    
    return collisions;
}

//polynomial hash code
long FlightHASHTABLE::hashCode(string key)
{
    long hcode = 0;
    
    for(int i = 0 ; i < key.length() ; i++)
    {
        hcode = hcode * 31 + (long) (key[i]) ;
    }
    
    if (hcode < 0)
        hcode = hcode * -1;
    
    //makes sure it's not more than the capacity
    hcode %= capacity;
    
    return hcode;
    
}


/*
 //cycle shift hash code
long FlightHASHTABLE::hashCode(string key)
{
    long hcode = 0;
 
    for (int i = 0; i < key.length(); i++)
   {
     hcode = (hcode << 5) | (hcode >> 27); // 5-bit cyclic shift of the running sum
     hcode += (long) key[i]; // add in next character
   }
    
    if(hcode < 0)
        hcode = hcode * -1;
    
    //makes sure it's not more than the capacity
    hcode %= capacity;
    
   return hcode;
}
*/

/*
 //summation hash code
long FlightHASHTABLE::hashCode(string key)
{
    long hcode = 0;
    
    for(int i = 0 ; i < key.length() ; i++)
    {
        //long temp =  (long) (key[i]);
        hcode = hcode + (long) (key[i]) ;
    }
    
    if (hcode < 0)
        hcode = hcode * -1;
    
    //makes sure it's not more than the capacity
    hcode %= capacity;
    
    return hcode;
    
}*/

int FlightHASHTABLE::add(Flight_Ticket* data)
{
    string key = data->getKey();
    
    //temporary node to be added
    HashNode tempNode = HashNode( key, *data );
    
    //hash code
    long hcode = hashCode(key);
    
    //to check if the same flight ticket is in the record
    if ( buckets[hcode].checkDuplicate(data) == true)
    {
        cout<<"\nRecord already exists!";
        return 0;
    }
    
    else
    {
         //inserting in the list
        buckets[hcode].insertBack(tempNode);
        
        //increasing the size
        size++;
        
        //since the record is added
        return 1;
    }
}
void FlightHASHTABLE::removeRecord (string companyName, int flightNumber)
{
    string key = companyName + to_string(flightNumber);
    
    long hcode = hashCode(key);
    
    int check = 0;
    
    //to print the records in the order
    int count = 1;
    
    //iterating through the list
    for( MyList<HashNode>::Iterator i (buckets[hcode].begin()) ; i != buckets[hcode].end() ; ++i )
    {
        HashNode t;
        t  = *i;
        
        // to find the same keys in the list
        if (t.checkKey(key) == true)
        {
            check = 1;
            
            cout<<endl;
            cout<<count<<".";
            //derefrencing the iterator
            HashNode t = *i;
            //displaying the data of a node
            t.displayNodeData();
           
            count++;
        }
    }
    
    string choice;
    
    cout<<"\nPlease select the record you want to delete: ";
    getline(cin,choice);
    
    count = 1;
    
    //iterating throgh the list
    for( MyList<HashNode>::Iterator i (buckets[hcode].begin()) ; i != buckets[hcode].end() ; ++i )
    {
        HashNode t;
        t  = *i;
        
        //if the count(the record we want to delete) matches and the key matches
        if (t.checkKey(key) == true && stoi(choice) == count)
        {
            //erasing the record from the list
            buckets[hcode].erase(i);
            cout<<"\nRecord deleted successfully!";
        }
        
        
        if (t.checkKey(key) == true)
        {
            count++;
        }
        
    }
    
    if (check == 0)
    {
        cout<<"\nRecord does not exist!";
    }

}

void FlightHASHTABLE::find(string companyName, int flightNumber)
{
    //to measure the time taken by the function
    clock_t start, end;
      
        /* Recording the starting clock tick.*/
        start = clock();
    
    
    string key = companyName + to_string(flightNumber);
    
    //getting the hashcode
    long hcode = hashCode(key);
    
    //to see if the record exists
    int check =  0;
    int count = 1;
    
    //iterating through the list
    for( MyList<HashNode>::Iterator i (buckets[hcode].begin()) ; i != buckets[hcode].end() ; ++i )
    {
        HashNode t;
        //derefrencing the iterator
        t  = *i;
        
        if (t.checkKey(key) == true)
        {
            check = 1;

            cout<<endl;
            cout<<count<<".";
            HashNode t = *i;
            //displaying the ndoe
            t.displayNode();
            count++;
        }
    }

    if (check == 0)
    {
        cout<<"\nRecord does not exist!";
    }
    
    
    // Recording the end clock tick.
        end = clock();
      
        // Calculating total time taken by the program.
        double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
        cout << "\nTime taken by program is : " << fixed
             << time_taken << setprecision(5);
        cout << " sec " << endl;
    
}

void FlightHASHTABLE::allinday(string date)
{
    int check =  0;
    int count = 1;
    
    //iterating through the table
    for(int hcode = 0; hcode < capacity ; hcode++)
    {
        //if the list is not empty, we iterate through the list
        if(!buckets[hcode].empty())
        for( MyList<HashNode>::Iterator i (buckets[hcode].begin()) ; i != buckets[hcode].end() ; ++i )
        {
            HashNode t;
            t  = *i;
            
            //if the date matches the date of the node
            if (t.checkNodeDate(date))
            {
                check = 1;

                cout<<endl;
                cout<<count<<".";
                HashNode t = *i;
                t.displayNodeData();
                count++;
            }
        }
        
    }
    if (check == 0)
    {
        cout<<"\nRecord does not exist!";
    }
    
}

void FlightHASHTABLE::printASC(string companyName, int flightNumber)
{
    string key = companyName + to_string(flightNumber);
    
    long hcode = hashCode(key);
    
    int check =  0;
    int count = 0;
    
    //iterating through the list
    for( MyList<HashNode>::Iterator i (buckets[hcode].begin()) ; i != buckets[hcode].end() ; ++i )
    {
        HashNode t;
        t  = *i;
        
        //if the key matches
        if (t.checkKey(key) == true)
        {
            check = 1;
            //counting the number of keys that match
            count++;
        }
    }
    
    
    if (check == 0)
    {
        cout<<"\nRecord does not exist!";
        return;
    }
    
    Flight_Ticket * array = new Flight_Ticket[count];
    
    int n  = 0;
      
    //iterating through the list
    for( MyList<HashNode>::Iterator i (buckets[hcode].begin()) ; i != buckets[hcode].end() ; ++i )
    {
        HashNode t;
        t  = *i;
        
        //if the key matches
        if (t.checkKey(key) == true)
        {
            //we put the value of the nodes in the array
            array[n] = t.getValue();
            //increase the size of the array
            n++;
        }
    }
    
    //loop runs till the number of keys that match and perform bubble sort based on the destination
    for (int i = 0 ; i < count - 1 ; i ++)
        for (int j = 0 ; j < count - i  - 1; j++)
        {
            //comparing the destinantions
            if( array[j].getDestination() > array[j+1].getDestination())
                swap(array[j],array[j+1]);
        }
    
    n = 1 ;
    
    //displaying the nodes in descending order
    for(int i = 0; i < count ; i++)
    {
        cout<<endl;
        cout<<n<<".";
        array[i].displayTicketData();
        n++;
    }
        
            
}

int FlightHASHTABLE::importCSV(string path)
{
    ifstream f1;
    string x;
    //maintaining the contacts imported
    int count = 0;
    
    //opening the file
    f1.open(path, ios::in);

    //while the file does not end
    while( getline(f1,x) )
    {
        
        string companyName = "";
        string flightNumber = "";
        string country_of_origin = "";
        string country_of_destination = "";
        string stopOver = "";
        string price = "";
        string time_of_departure = "";
        string time_of_arrival = "";
        string date = "";
        
        int check = 0;
        int checkQuote = 0;
        
        // x.length() is the length of the line
        for ( int i = 0 ; i< x.length() ; i++)
            
        {
            if ( check == 0 && x[i] != ',' )
            {
                companyName += x[i];
            }
            
            else if ( check == 1 && x[i] != ',' )
            {
                flightNumber += x[i];
            }
            
            else if ( ( check == 2 && x[i] != ','  )  || (check == 2 && checkQuote == 1) )
            {
                if (x[i] == '"' && checkQuote == 0)
                    checkQuote = 1;
                
                //checking the quotes in the country names
                else if (x[i] == '"' && checkQuote == 1)
                    checkQuote = 0;
                
                country_of_origin += x[i];
            }
            
            else if ( ( check == 3 && x[i] != ',' ) || ( check == 3 && checkQuote == 1 ) )
            {
                if (x[i] == '"' && checkQuote == 0)
                    checkQuote = 1;
                
                //checking the quotes in the country destination names
                else if (x[i] == '"' && checkQuote == 1)
                    checkQuote = 0;
                
                country_of_destination += x[i];
            }
            
            else if ( check == 4 && x[i] != ',' )
            {
                stopOver += x[i];
            }
            
            else if ( check == 5 && x[i] != ',' )
            {
                price += x[i];
            }
            
            else if ( check == 6 && x[i] != ',' )
            {
                time_of_departure += x[i];
            }
            
            else if ( check == 7 && x[i] != ',' )
            {
                time_of_arrival += x[i];
            }
            
            else if ( check == 8 && x[i] != ',' )
            {
                date += x[i];
                
                if( i == x.length() - 2)
                    check = 9;
            }
            
            
            if ( check == 9 && x[i] != ',')
            {
                //adding the data after every line
                if(count != 0)
                {
                    Flight_Ticket * data = new Flight_Ticket( companyName, stoi(flightNumber), country_of_origin , country_of_destination, stopOver, price, time_of_departure, time_of_arrival, date);
                
                    add(data);
                    
                }
                
                //check is made 0 for reading the next line
                check = 0;
                
                //increases the count since a contact has been added
                count++;
            }
            
            //check increases everytime a comma comes across
            if (x[i] == ',' && checkQuote == 0 )
                check++;
                
        }
        
    }
    
    //closes the file
    f1.close();
    
    if (count - 1 == 0)
        return -1;
    
    //count is returned
    else
        return count - 1;
    
    return -1;
}

int FlightHASHTABLE::exportCSV(string path)
{
    ofstream f1;
    
    //appending in the file
    f1.open(path, ios::app);
    
    int count = 0;
    
    //iterating through the hash table
    for(int hcode = 0; hcode < capacity ; hcode++)
    {
        //iterating through the list
        if( ! buckets[hcode].empty() )
        for( MyList<HashNode>::Iterator i (buckets[hcode].begin()) ; i != buckets[hcode].end() ; ++i )
        {
            count++;
            
            HashNode t;
            t  = *i;
            f1<<t.getValue().getcompanyName()<<","<<t.getValue().getflightNumber()<<","<<t.getValue().getcountry_of_origin()<<","<<t.getValue().getcountry_of_destination()<<","<<t.getValue().getstopOver()<<","<<t.getValue().getprice()<<","<<t.getValue().gettime_of_departure()<<","<<t.getValue().gettime_of_arrival()<<","<<t.getValue().getdate()<<endl;
        }
        
    }
    
    f1.close();
    
    if ( count != 0 )
        return count;
    else
        return -1;
}



//=============================================================================
