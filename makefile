CC=g++
DEPS = bowling_frame.h

all: bowling_frame.o main.o
	$(CC) -std=c++11 bowling_frame.o main.o

bowling_frame.o: bowling_frame.cpp $(DEPS)
	$(CC) -c -std=c++11 bowling_frame.cpp

main.o: main.cpp $(DEPS)
	$(CC) -c -std=c++11 main.cpp

clean:
	rm -f *.o *.out
