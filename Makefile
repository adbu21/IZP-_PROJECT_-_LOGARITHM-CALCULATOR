CFLAGS = -std=c99 -Wall -Wextra -Werror
main: proj2.c
	gcc proj2.c -lm -o proj2
clean:
	rm proj2