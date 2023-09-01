HEADERS := $(wildcard src/*.hpp)

all : main


main: main.cpp $(HEADERS)
	g++ main.cpp -o main -lncurses