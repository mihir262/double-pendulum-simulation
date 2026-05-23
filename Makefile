CC = clang
CFLAGS = -Wall -Wextra -std=c17 -I/opt/homebrew/include
LDFLAGS = -L/opt/homebrew/lib -lraylib \
		   -framework Cocoa \
		   -framework OpenGL \
		   -framework IOKit

SRC = main.c
OUT = main

all:
	$(CC) $(SRC) -o $(OUT) $(CFLAGS) $(LDFLAGS)

run: all
	./$(OUT)

clean:
	rm -f $(OUT)