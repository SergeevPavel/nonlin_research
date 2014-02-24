
INCLUDE_PATH=include/
SRC_PATH=src/
C_FLAGS=-O2


all: main.o RKSolver.o
	g++ main.o RKSolver.o -o Solver

main.o: $(SRC_PATH)main.cpp
	g++ -I$(INCLUDE_PATH) $(C_FLAGS) -c $(SRC_PATH)main.cpp

RKSolver.o: $(SRC_PATH)RKSolver.cpp
	g++ -I$(INCLUDE_PATH) $(C_FLAGS) -c $(SRC_PATH)RKSolver.cpp
	
clean:
	rm *.o