CC := g++

CFLAGS = $(shell sdl2-config --cflags) -Wall -Werror -lm
LDLIBS += -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_gfx

reader: main.o parse.o display.o engine.o controls.o window.o
	        $(CC) $(CFLAGS) -o reader main.o parse.o display.o engine.o controls.o window.o $(LDLIBS)

main.o: main.cpp parse.h
	        $(CC) $(CFLAGS) -c -g main.cpp

parse.o: parse.cpp parse.h
	        $(CC) $(CFLAGS) -c -g parse.cpp

display.o: display.cpp display.h
	        $(CC) $(CFLAGS) -c -g display.cpp

engine.o: engine.cpp engine.h
	        $(CC) $(CFLAGS) -c -g engine.cpp

controls.o: controls.cpp controls.h
			$(CC) $(CFLAGS) -c -g controls.cpp

window.o: window.cpp window.h
			$(CC) $(CFLAGS) -c -g window.cpp



clean:
	        rm -f reader *.o