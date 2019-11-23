ASSN1.exe : Dough.o DoughList.o Edge.o EdgeList.o Topping.o ToppingList.o main.o
	g++ -o ASSN1_exe main.o Dough.o DoughList.o Edge.o EdgeList.o Topping.o ToppingList.o

main.o : Dough.h DoughList.h Edge.h EdgeList.h Topping.h ToppingList.h main.cpp
	g++ -c -o main.o main.cpp

Dough.o : Dough.h Dough.cpp
	g++ -c -o Dough.o Dough.cpp

DoughList.o : DoughList.h DoughList.cpp
	g++ -c -o DoughList.o DoughList.cpp

Edge.o : Edge.h Edge.cpp
	g++ -c -o Edge.o Edge.cpp

EdgeList.o : EdgeList.h EdgeList.cpp
	g++ -c -o EdgeList.o EdgeList.cpp

Topping.o : Topping.h Topping.cpp
	g++ -c -o Topping.o Topping.cpp

ToppingList.o : ToppingList.h ToppingList.cpp
	g++ -c -o ToppingList.o ToppingList.cpp

clean : 
	rm *.o ASSN1_exe
