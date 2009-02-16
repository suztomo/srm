FLAGS= -Wall -ggdb
.PHONY: test check-syntax
TARGETS=string sort number

test: $(TARGETS)
	./sort
	./string
	./number	

string: string.cpp
	g++ $(FLAGS) string.cpp -o string

sort: sort.cpp
	g++ $(FLAGS) sort.cpp -o sort

number: number.cpp
	g++ $(FLAGS) number.cpp -o number





check-syntax:
	$(CC) -o /dev/null $(CFLAGS) $(INCLUDEDIR) -S ${CHK_SOURCES}

clean:
	rm $(TARGETS)