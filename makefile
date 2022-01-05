PKGS=sdl2
CFLAGS=-Wall -Wextra -pedantic -std=c99 `pkg-config --cflags $(PKGS)`
LIBS=`pkg-config --libs $(PKGS)`

snake: main.c
	$(CC) $(CFLAGS) -o snake main.c $(LIBS)
