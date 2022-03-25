CFLAGS=-ggdb3 -Wall -Werror -pedantic -std=gnu99

test: cards.o my-test-main.c
	gcc $(CFLAGS) cards.o my-test-main.c -o test.app
	./test.app
cards.o: cards.c
	gcc $(CFLAGS) -c cards.c
clean:
	rm test
