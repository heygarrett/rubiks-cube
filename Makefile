CFLAGS=-O0 -std=c11 -march=native -ggdb -Wall -Wextra -Wshadow
 
main: main.o valid.o turns.o
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@
 
clean:
	rm -f *.o
	rm -f main
 
.PHONY: clean
