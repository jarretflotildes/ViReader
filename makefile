CC := g++

CFLAGS = $(shell sdl2-config --cflags) -Wall -Werror -lm
LDLIBS += -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_gfx

reader: main.o parse.o display.o
	        $(CC) $(CFLAGS) -o reader main.o parse.o display.o $(LDLIBS)

main.o: main.cpp parse.h
	        $(CC) $(CFLAGS) -c -g main.cpp

parse.o: parse.cpp parse.h
	        $(CC) $(CFLAGS) -c -g parse.cpp

display.o: display.cpp display.h
	        $(CC) $(CFLAGS) -c -g display.cpp

clean:
	        rm -f reader *.o