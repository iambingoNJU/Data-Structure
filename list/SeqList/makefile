test:main.o SeqList.o
	g++ -o test main.o SeqList.o
main.o:main.cpp
	g++ -c main.cpp 
SeqList.o:SeqList.cpp
	g++ -c SeqList.cpp 

clean:
	rm main.o SeqList.o
	rm test
