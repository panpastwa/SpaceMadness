SRC = src
OBJ = obj
EXECUTABLE = SpaceMadness

SOURCES = $(wildcard $(SRC)/*.cpp)
OBJECTS = $(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(SOURCES))

LIBS = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system
CC = g++

$(OBJ)/%.o: $(SRC)/%.cpp
	@mkdir -p obj
	$(CC) -c $< -o $@

main: $(OBJECTS)
	$(CC) $^ $(LIBS) -o $(EXECUTABLE)

run: main
	./$(EXECUTABLE)

clean:
	rm -rf $(OBJ) $(EXECUTABLE)
