SRC = src
OBJ = obj

SOURCES = $(wildcard $(SRC)/*.cpp)
OBJECTS = $(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(SOURCES))

LIBS = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system
CC = g++

$(OBJ)/%.o: $(SRC)/%.cpp
	@mkdir -p obj
	$(CC) -c $< -o $@

main: $(OBJECTS)
	$(CC) $^ $(LIBS)

run: main
	./a.out

clean:
	rm -r $(OBJ)
