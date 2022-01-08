PKGS=sdl2
CFLAGS=-Wall -Wextra -pedantic -std=c99 `pkg-config --cflags $(PKGS)`
CRFLAGS=-Wall -Wextra -pedantic -O2 -std=c99  `pkg-config --cflags --static $(PKGS)`
LIBS=`pkg-config --libs $(PKGS)`

snake: main.c
	$(CC) $(CFLAGS) -o snake main.c $(LIBS)
snake_release: main.c
	$(CC) $(CRFLAGS) -o snake_release main.c $(LIBS)
