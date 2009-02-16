FLAGS= -Wall -ggdb
.PHONY: test all check-syntax
all: string.cpp sort.cpp number.cpp
	g++ $(FLAGS) string.cpp -o string
	g++ $(FLAGS) sort.cpp -o sort
	g++ $(FLAGS) number.cpp -o number

test: all
	./sort
	./string
	./number	


check-syntax:
	$(CC) -o /dev/null $(CFLAGS) $(INCLUDEDIR) -S ${CHK_SOURCES}
