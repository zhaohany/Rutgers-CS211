all: first

first: first.c
	gcc -Wall -Werror -fsanitize=address -o first first.c -lm
	
clean:
	rm -rf first
