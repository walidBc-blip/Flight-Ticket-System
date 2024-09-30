output:  main.o flighthashtable.o flightticket.o 
	g++  flightticket.o flighthashtable.o  main.o -o output

flightticket.o: flightticket.cpp flightticket.h 
	g++ -c flightticket.cpp

flighthashtable.o:  flighthashtable.cpp flighthashtable.h
	g++ -c flighthashtable.cpp

main.o:  main.cpp flightticket.h flighthashtable.h
	g++ -c main.cpp



clean:
	rm *.o output