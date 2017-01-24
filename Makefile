safeRead: safeRead.c
	gcc -std=c99 -ggdb -Wall -o safeRead safeRead.c
clean:
	rm safeRead
