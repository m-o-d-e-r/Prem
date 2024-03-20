CXX := g++
SOURCE_PATH := src
BIN_PATH := bin


all: assembly_objects

assembly_objects: prem.o MainWindow.o PremCycle.o
	$(CXX) -o $(BIN_PATH)/prem $(BIN_PATH)/prem.o $(BIN_PATH)/MainWindow.o $(BIN_PATH)/PremCycle.o -lncurses

prem.o: src/prem.cpp
	$(CXX) -c $(SOURCE_PATH)/prem.cpp -o $(BIN_PATH)/prem.o

PremCycle.o: src/core/PremCycle.cpp
	$(CXX) -c $(SOURCE_PATH)/core/PremCycle.cpp -o $(BIN_PATH)/PremCycle.o

MainWindow.o: src/core/MainWindow.cpp
	$(CXX) -c $(SOURCE_PATH)/core/MainWindow.cpp -o $(BIN_PATH)/MainWindow.o


.PHONY: clean
clean:
	rm $(BIN_PATH)/*.o

cleanall:
	rm $(BIN_PATH)/*