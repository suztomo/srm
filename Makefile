
.PHONY: test all
all:
	g++ -Wall string.cpp -o string
	g++ -Wall sort.cpp -o sort

test:
	./sort
	./string
