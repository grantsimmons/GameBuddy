CXX = g++
CPU = Z80.cpp
MMU = MMU.cpp
OPS = ops_impl.cpp
CPU_OBJ = Z80.o
MMU_OBJ = MMU.o
OPS_OBJ = ops_impl.o
MAIN = main.cpp
CPU_H = Z80.h
MMU_H = MMU.h

default:
	$(CXX) -c $(CPU) -o Z80.o
	$(CXX) -c $(MMU) -o MMU.o

test: $(CPU) $(MMU) $(OPS) $(MAIN) $(CPU_H) $(MMU_H)
	$(CXX) -c $(OPS) $(CPU) $(MMU)
	$(CXX) $(OPS_OBJ) $(CPU_OBJ) $(MMU_OBJ) $(MAIN) -o test.out
