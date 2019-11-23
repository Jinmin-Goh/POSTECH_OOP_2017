run : main.o Object.o Torpedo.o Boat.o BoatA.o BoatB.o BoatC.o
	g++ -o run main.o Object.o Torpedo.o Boat.o BoatA.o BoatB.o BoatC.o

main.o : main.cpp Object.h Torpedo.h Boat.h BoatA.h BoatB.h BoatC.h
	g++ -c -o main.o main.cpp

Object.o : Object.cpp Object.h
	g++ -c -o Object.o Object.cpp

Torpedo.o : Torpedo.cpp Torpedo.h
	g++ -c -o Torpedo.o Torpedo.cpp

Boat.o : Boat.cpp Boat.h
	g++ -c -o Boat.o Boat.cpp

BoatA.o : BoatA.cpp BoatA.h
	g++ -c -o BoatA.o BoatA.cpp

BoatB.o : BoatB.cpp BoatB.h
	g++ -c -o BoatB.o BoatB.cpp

BoatC.o : BoatC.cpp BoatC.h
	g++ -c -o BoatC.o BoatC.cpp

clean : 
	rm *.o run
