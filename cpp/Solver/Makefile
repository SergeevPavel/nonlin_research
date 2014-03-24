
INCLUDE_PATH=include/
SOURCES=$(INCLUDE_PATH)/point.h $(INCLUDE_PATH)solution.h $(INCLUDE_PATH)solver.h $(INCLUDE_PATH)utils.h
EXAMPLE_PATH=example/
BIN_PATH=bin/
C_FLAGS=-g -O0 -std=c++0x


all: $(BIN_PATH)main.o
	g++ $(BIN_PATH)main.o -o $(BIN_PATH)example

$(BIN_PATH)main.o: $(EXAMPLE_PATH)main.cpp $(EXAMPLE_PATH)example.h $(SOURCES)
	g++ -I$(INCLUDE_PATH) $(C_FLAGS) -c $(EXAMPLE_PATH)main.cpp -o $(BIN_PATH)main.o

.PHONY: clean
	
clean:
	rm -rf bin/*