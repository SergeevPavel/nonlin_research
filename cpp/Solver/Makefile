
INCLUDE_PATH=include/
SRC_PATH=src/
EXEM_PATH=exemple/
C_FLAGS=-g -O0 -std=c++11


all: main.o RKSolver.o
	g++ main.o RKSolver.o -o Test

main.o: $(EXEM_PATH)main.cpp
	g++ -I$(INCLUDE_PATH) $(C_FLAGS) -c $(EXEM_PATH)main.cpp

RKSolver.o: $(SRC_PATH)RKSolver.cpp $(INCLUDE_PATH)RKSolver.h
	g++ -I$(INCLUDE_PATH) $(C_FLAGS) -c $(SRC_PATH)RKSolver.cpp
	
clean:
	rm *.o
	rm Solver