FLAGS= -Wall -ggdb
.PHONY: test all
all: string.cpp sort.cpp
	g++ $(FLAGS) string.cpp -o string
	g++ $(FLAGS) sort.cpp -o sort

test: all
	./sort
	./string
