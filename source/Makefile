#CC = x86_64-w64-mingw32-g++
#CC = i686-w64-mingw32-g++
OUT = test.exe
RUN = run.exe
CC = g++.exe
#CC = mingw32-g++.exe

#OUT = test.out
CPU = Z80.cpp
MMU = MMU.cpp
GPU = GPU.cpp
OPS = ops_impl.cpp
BLIT = blit.cpp

OBJS = Z80.o MMU.o ops_impl.o GPU.o blit.o
SDL_OBJS = $(OBJS) blit.o

MAIN = main.cpp
SDL_MAIN = SDL_main.cpp

OP_GEN = ../scripts/Z80CoverageConverter.py
FUNCS = ../scripts/functions.cpp

WIN_CFLAGS = -Wall -Wextra -w -static-libgcc -static-libstdc++ -m32
WIN_LFLAGS = -LD:\MinGW\lib -lmingw32 -lSDL2main -lSDL2 -mwindows -ID:\MinGW\include -Dmain=SDL_main

all: ops obj
	$(CC) $(OBJS) $(SDL_MAIN) $(WIN_CFLAGS) $(WIN_LFLAGS) -o $(RUN)

#$(OUT): ops obj
#$(CC) $(OBJS) $(MAIN) -o $@

#obj: $(CPU) $(MMU) $(GPU) $(OPS)
obj: $(CPU) $(MMU) $(GPU) $(OPS) $(BLIT)
	$(CC) -c $(WIN_CFLAGS) $(WIN_LFLAGS) $^

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
