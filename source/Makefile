#CC = x86_64-w64-mingw32-g++
#OUT = test.exe
CC = g++
OUT = test.out
CPU = Z80.cpp
MMU = MMU.cpp
GPU = GPU.cpp
OPS = ops_impl.cpp
MAIN = main.cpp
OP_GEN = ../scripts/Z80CoverageConverter.py
FUNCS = ../scripts/functions.cpp
OBJS = Z80.o MMU.o ops_impl.o GPU.o

$(OUT): ops obj
	$(CC) $(OBJS) $(MAIN) -o $@

obj: $(CPU) $(MMU) $(GPU) $(OPS)
	$(CC) -c $^

ops: $(OP_GEN) $(FUNCS)
	python3 $(OP_GEN)

noops: obj
	$(CC) $(OBJS) $(MAIN) -o $(OUT)

#CXX = g++
#CC = x86_64-w64-mingw32-g++
##OUT = test.out
#OUT = test.exe
#CPU = Z80.cpp
#MMU = MMU.cpp
#GPU = GPU.cpp
#OPS = ops_impl.cpp
#MAIN = main.cpp
#OP_GEN = ../scripts/Z80CoverageConverter.py
#FUNCS = ../scripts/functions.cpp
#OBJS = Z80.o MMU.o ops_impl.o GPU.o
#
#$(OUT): ops obj
#	$(CXX) $(OBJS) $(MAIN) -o $@
#
#obj: $(CPU) $(MMU) $(GPU) $(OPS)
#	$(CXX) -c $^
#
#ops: $(OP_GEN) $(FUNCS)
#	python3 $(OP_GEN)
#
#noops: obj
#	$(CXX) $(OBJS) $(MAIN) -o $(OUT)
#
#
#
#
#
#
#INC = -I
#ODIR = obj
#SDIR = source
#
#_OBJS = Z80.o MMU.o ops_impl.o
#
#OBJS = $(patsubst %,$(ODIR)/%,$(_OBJS))
#
#$(ODIR)/%.o: $(SDIR)/%.cpp
#	$(CXX) -c -o $@ $<
#
#$(OUT): $(OBJS)
#	ar rvs $(OUT) $^
#.PHONY: clean
#
#clean:
#	rm -f $(ODIR)/*.o 
