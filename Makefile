.POSIX:

CFLAGS = -Wall -Wextra -O2 -I/usr/local/include -Isrc
LDFLAGS = -L/usr/local/lib
LDLIBS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

OBJS = src/main.o src/graph.o src/game.o src/render.o

all: main

main: $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(OBJS) $(LDLIBS)

clean:
	rm -f main $(OBJS)

.PHONY: all clean
