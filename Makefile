.POSIX:

CFLAGS = -Wall -Wextra -O2 -Isrc `PKG_CONFIG_PATH=. pkg-config --cflags raylib`
LDLIBS = `PKG_CONFIG_PATH=. pkg-config --libs --static raylib`

OBJS = src/main.o src/graph.o src/game.o src/render.o

all: main

main: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LDLIBS)

clean:
	rm -f main $(OBJS)

.PHONY: all clean
