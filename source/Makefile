CXX = g++
CPU = Z80.cpp
MMU = MMU.cpp

default:
	$(CXX) -c $(CPU) -o Z80.o
	$(CXX) -c $(MMU) -o MMU.o

test: $(CPU) $(MMU)
	$(CXX) $^ -o test
