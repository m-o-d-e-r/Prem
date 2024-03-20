CXX := g++
SOURCE_PATH := src
BIN_PATH := bin
P_NAME := prem


all: assembly_objects

assembly_objects: $(P_NAME).o
	$(CXX) -o $(BIN_PATH)/$(P_NAME) $(BIN_PATH)/$(P_NAME).o

$(P_NAME).o: src/$(P_NAME).cpp
	$(CXX) -c $(SOURCE_PATH)/$(P_NAME).cpp -o $(BIN_PATH)/$(P_NAME).o


.PHONY: clean
clean:
	rm $(BIN_PATH)/*.o

cleanall:
	rm $(BIN_PATH)/*