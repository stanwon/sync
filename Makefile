all: *.c
	@gcc main.c queue.c recv.c -o main
	@./main
