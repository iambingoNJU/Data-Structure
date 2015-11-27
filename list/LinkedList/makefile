test: main.o LinkedList.o
	g++ -o test main.o LinkedList.o
main.o: main.cpp
	g++ -c main.cpp
LinkedList.o: LinkedList.cpp
	g++ -c LinkedList.cpp

clean:
	rm main.o LinkedList.o
	rm test
