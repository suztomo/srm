FLAGS= -Wall -ggdb
.PHONY: test check-syntax
TARGETS=string sort number dp container

test: $(TARGETS)
	./sort
	./string
	./number
	./dp
	./container

string: string.cpp
	g++ $(FLAGS) string.cpp -o string

sort: sort.cpp
	g++ $(FLAGS) sort.cpp -o sort

number: number.cpp
	g++ $(FLAGS) number.cpp -o number

dp: dp.cpp
	g++ $(FLAGS) dp.cpp -o dp

container: container.cpp
	g++ $(FLAGS) container.cpp -o container

check-syntax:
	$(CC) -o /dev/null $(CFLAGS) $(INCLUDEDIR) -S ${CHK_SOURCES}



clean:
	rm $(TARGETS)