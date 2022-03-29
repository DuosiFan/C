CFLAGS :=-ggdb3 -Wall -Werror -pedantic -std=c99
OBJS := main.o stack.o getop.o getch.o
HEADERS := calc.h

calculator.app: $(OBJS) $(HEADERS)
	gcc $(OBJS) -o $@

%.c.o: %.c
	gcc $(CFLAGS) -c $<

.PHONY: clean cleanall
clean:
	rm *.o
cleanall:
	rm *.o *.app
