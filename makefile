CXX := g++
SOURCE_PATH := src
BIN_PATH := bin


all: assembly_objects

assembly_objects: main.o
	$(CXX) -o $(BIN_PATH)/main $(BIN_PATH)/main.o

main.o: src/main.cpp
	$(CXX) -c $(SOURCE_PATH)/main.cpp -o $(BIN_PATH)/main.o


.PHONY: clean
clean:
	rm $(BIN_PATH)/*.o

cleanall:
	rm $(BIN_PATH)/*
