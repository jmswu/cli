CC := gcc
FLAGS := -Wall -std=c99

hello_main: main.o cli.o
	${CC} ${FLAGS} -o $@ $^

.PHONY: clean
clean:
	@rm *.o
	@echo done