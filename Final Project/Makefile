#compile and link the application
all: main

#run the application
run: main
	./main

#link main.o, time.o, and date.o to executable main
main: main.o list.o student.o unit.o spellcheck.o
	g++ -g -o main main.o student.o list.o	unit.o spellcheck.o

#compile the main.cpp to main.o
main.o: main.cpp
	g++ -g -c main.cpp

#compile the time.cpp to time.o
list.o: list.cpp
	g++ -g -c list.cpp

#compile the date.cpp to date.o
student.o: student.cpp
	g++ -g -c student.cpp

spellcheck.o: spellcheck.cpp
	g++ -g -c spellcheck.cpp

unit.o: unit.cpp
	g++ -g -c unit.cpp

#remove built files
clean:
	rm -rf main main.o student.o list.o unit.o spellcheck.o *~