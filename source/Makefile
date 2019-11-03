CXX = g++
OUT = test.out
CPU = Z80.cpp
MMU = MMU.cpp
OPS = ops_impl.cpp
MAIN = main.cpp
OP_GEN = ../scripts/Z80CoverageConverter.py
FUNCS = ../scripts/functions.cpp
OBJS = Z80.o MMU.o ops_impl.o

$(OUT): ops obj
	$(CXX) $(OBJS) $(MAIN) -o $@

obj: $(CPU) $(MMU) $(OPS)
	$(CXX) -c $^

ops: $(OP_GEN) $(FUNCS)
	python $(OP_GEN)

noops: obj
	$(CXX) $(OBJS) $(MAIN) -o $(OUT)

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
