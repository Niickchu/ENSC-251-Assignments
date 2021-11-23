#compile and link the application
all: main

#run the application
run: main
	./main

#link main.o and bst.o to executable main
main: main.o stack.o
	g++ -g -o main main.o stack.o

#compile the main.cpp to main.o
main.o: main.cpp
	g++ -g -c main.cpp

#compile the bst.cpp to bst.o
stack.o: stack.cpp
	g++ -g -c stack.cpp

#remove built files
clean:
	rm -rf main main.o stack.o *~
