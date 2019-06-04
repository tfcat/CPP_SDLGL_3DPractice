CC = g++
CFLAGS = -IM:/DEV/dev/include -I./src/headers -I./src -LM:/DEV/dev/lib -fpermissive
LDFLAGS =
LIBS = -lSDL2 -lglew32 -lOpenGL32
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