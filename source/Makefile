CXX = g++
CPU = Z80.cpp
MMU = MMU.cpp
OPS = ops.cpp
CPU_H = Z80.h
MMU_H = MMU.h

default:
	$(CXX) -c $(CPU) -o Z80.o
	$(CXX) -c $(MMU) -o MMU.o

test: $(CPU) $(MMU) $(CPU_H) $(MMU_H)
	$(CXX) $(CPU) $(MMU) -o test.out
