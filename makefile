CC := g++

# Base flags
BASE_CFLAGS = $(shell sdl2-config --cflags) -Wall -Werror -lm -g
BASE_LDLIBS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_gfx

# Default build flags
CFLAGS = $(BASE_CFLAGS)
LDLIBS = $(BASE_LDLIBS)

# Memory debugging variants
DEBUG_CFLAGS = $(BASE_CFLAGS) -DDEBUG -O0 -g3
ASAN_CFLAGS = $(BASE_CFLAGS) -fsanitize=address -fsanitize=undefined -fno-omit-frame-pointer -O1
ASAN_LDLIBS = $(BASE_LDLIBS) -fsanitize=address -fsanitize=undefined
MSAN_CFLAGS = $(BASE_CFLAGS) -fsanitize=memory -fno-omit-frame-pointer -O1
MSAN_LDLIBS = $(BASE_LDLIBS) -fsanitize=memory

SOURCES = main.cpp parse.cpp display.cpp engine.cpp window.cpp menuItem.cpp test.cpp
OBJECTS = main.o parse.o display.o engine.o window.o menuItem.o test.o

# Default target
reader: $(OBJECTS)
	$(CC) $(CFLAGS) -o reader $(OBJECTS) $(LDLIBS)

# Debug build
debug: 
	$(MAKE) reader CFLAGS="$(DEBUG_CFLAGS)"

# AddressSanitizer build (recommended for SDL2 leak detection)
asan: reader-asan

reader-asan: $(SOURCES)
	$(CC) $(ASAN_CFLAGS) -c main.cpp -o main.o
	$(CC) $(ASAN_CFLAGS) -c parse.cpp -o parse.o
	$(CC) $(ASAN_CFLAGS) -c display.cpp -o display.o
	$(CC) $(ASAN_CFLAGS) -c engine.cpp -o engine.o
	$(CC) $(ASAN_CFLAGS) -c window.cpp -o window.o
	$(CC) $(ASAN_CFLAGS) -c menuItem.cpp -o menuItem.o
	$(CC) $(ASAN_CFLAGS) -c test.cpp -o test.o
	$(CC) $(ASAN_CFLAGS) -o reader-asan $(OBJECTS) $(ASAN_LDLIBS)

# MemorySanitizer build (more thorough but slower)
msan: reader-msan

reader-msan: $(SOURCES)
	$(CC) $(MSAN_CFLAGS) -c main.cpp -o main.o
	$(CC) $(MSAN_CFLAGS) -c parse.cpp -o parse.o
	$(CC) $(MSAN_CFLAGS) -c display.cpp -o display.o
	$(CC) $(MSAN_CFLAGS) -c engine.cpp -o engine.o
	$(CC) $(MSAN_CFLAGS) -c window.cpp -o window.o
	$(CC) $(MSAN_CFLAGS) -c menuItem.cpp -o menuItem.o
	$(CC) $(MSAN_CFLAGS) -c test.cpp -o test.o
	$(CC) $(MSAN_CFLAGS) -o reader-msan $(OBJECTS) $(MSAN_LDLIBS)

# Object file rules
main.o: main.cpp parse.h
	$(CC) $(CFLAGS) -c main.cpp

parse.o: parse.cpp parse.h
	$(CC) $(CFLAGS) -c parse.cpp

display.o: display.cpp display.h
	$(CC) $(CFLAGS) -c display.cpp

engine.o: engine.cpp engine.h
	$(CC) $(CFLAGS) -c engine.cpp

window.o: window.cpp window.h
	$(CC) $(CFLAGS) -c window.cpp

menuItem.o: menuItem.cpp menuItem.h
	$(CC) $(CFLAGS) -c menuItem.cpp

test.o: test.cpp test.h
	$(CC) $(CFLAGS) -c test.cpp

# Testing targets
test-leaks: asan
	@echo "Running AddressSanitizer leak detection..."
	@echo "Usage: make test-leaks INPUT=yourfile.txt"
	@if [ -z "$(INPUT)" ]; then \
		echo "Error: Please specify INPUT file: make test-leaks INPUT=yourfile.txt"; \
		exit 1; \
	fi
	ASAN_OPTIONS=detect_leaks=1:abort_on_error=1 ./reader-asan $(INPUT)

test-leaks-sample: asan
	@echo "Running AddressSanitizer with sample input..."
	@echo "Creating sample input file..."
	@echo "sample content for testing" > test_input.txt
	ASAN_OPTIONS=detect_leaks=1:abort_on_error=1 ./reader-asan test_input.txt
	@rm -f test_input.txt

test-valgrind: reader
	@echo "Running Valgrind leak detection..."
	@echo "Usage: make test-valgrind INPUT=yourfile.txt"
	@if [ -z "$(INPUT)" ]; then \
		echo "Error: Please specify INPUT file: make test-valgrind INPUT=yourfile.txt"; \
		exit 1; \
	fi
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=valgrind.log ./reader $(INPUT)

# Memory profiling (if you have massif)
profile-memory: reader
	valgrind --tool=massif --time-unit=B ./reader
	ms_print massif.out.* > memory_profile.txt

# Clean targets
clean:
	rm -f reader reader-asan reader-msan *.o

clean-debug: 
	rm -f reader reader-asan reader-msan *.o

clean-all: clean
	rm -f valgrind.log massif.out.* memory_profile.txt

# Help target
help:
	@echo "Available targets:"
	@echo "  reader       - Default build with debug symbols"
	@echo "  debug        - Debug build with extra symbols"
	@echo "  asan         - AddressSanitizer build (recommended for leak detection)"
	@echo "  msan         - MemorySanitizer build (thorough but slow)"
	@echo "  test-leaks INPUT=file.txt - Build with ASAN and run with leak detection"
	@echo "  test-leaks-sample - Run leak test with auto-generated sample file"
	@echo "  test-valgrind INPUT=file.txt - Run with Valgrind leak detection"
	@echo "  profile-memory - Profile memory usage with Valgrind/Massif"
	@echo "  clean        - Remove executables and object files"
	@echo "  clean-all    - Remove all generated files including logs"

.PHONY: debug asan msan test-leaks test-valgrind profile-memory clean clean-all help