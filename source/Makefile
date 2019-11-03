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
OP_GEN = ../scripts/Z80CoverageConverter.py
FUNCS = ../scripts/functions.cpp

default: ops obj
	$(CXX) $(OPS_OBJ) $(CPU_OBJ) $(MMU_OBJ) $(MAIN) -o test.out

obj: $(CPU) $(MMU) $(OPS)
	$(CXX) -c $^

ops: $(OP_GEN) $(FUNCS)
	python $(OP_GEN)

noops: obj
	$(CXX) $(OPS_OBJ) $(CPU_OBJ) $(MMU_OBJ) $(MAIN) -o test.out
