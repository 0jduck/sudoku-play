CC = gcc
CFLAGS = -Wall -Wextra -O2

bin/exe: obj/main.o
	$(CC) $(CFLAGS) $^ -o bin/exe

obj/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf bin/* obj/*
