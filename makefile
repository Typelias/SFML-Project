TARGET = game
SOURCES :=$(wildcard *.cpp)
LIBS=-lsfml-graphics -lsfml-window -lsfml-system

build: $(SOURCES)
		g++ -o $(TARGET) $(LIBS)
run: build
	./$(TARGET)