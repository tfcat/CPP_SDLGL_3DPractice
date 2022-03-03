CC = g++
CFLAGS = -I/usr/include -I./src/headers -I./src -fpermissive
LDFLAGS =
LIBS = -lSDL2 -lGL -lGLEW
SRC = $(wildcard src/*.cpp)
OBJ = $(patsubst src/%.cpp, obj/%.o, $(SRC))

main: $(OBJ)
	$(CC) -g -Wall $(OBJ) $(CFLAGS) $(LDFLAGS) $(LIBS)  -o main 

obj/%.o: src/%.cpp
	$(CC) $(CFLAGS) $(LIBS) -c $< -o $@

run: main
	main.exe

clean:
	rm obj/*