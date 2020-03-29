#CC = x86_64-w64-mingw32-g++
#CC = i686-w64-mingw32-g++
#CC = mingw32-g++.exe
#CC = g++
OUT = test.exe
RUN = run.exe
VERIF_EXE = verif.exe
CC = g++.exe

CPU = Z80.cpp
CPU_H = Z80.h
MMU = MMU.cpp
MMU_H = MMU.h
GPU = GPU.cpp
GPU_H = GPU.h
OPS = ops_impl.cpp
BLIT = blit.cpp
BLIT_H = blit.h

OBJS = Z80.o MMU.o ops_impl.o GPU.o
SDL_OBJS = $(OBJS) blit.o

MAIN = main.cpp
SDL_MAIN = SDL_main.cpp

OP_GEN = ../scripts/Z80CoverageConverter.py
FUNCS = ../scripts/functions.cpp

WIN_CFLAGS = -Wall -Wextra -w -static-libgcc -static-libstdc++ -m32
WIN_LFLAGS = -LC:\MinGW\lib -lmingw32 -lSDL2main -lSDL2 -mwindows -IC:\MinGW\include -Dmain=SDL_main

.PHONY: run
run : WIN_VFLAGS =
run: $(RUN)

.PHONY: verif
verif : WIN_VFLAGS = -DVERIF
verif : $(VERIF_EXE)

.PHONY: all
all: verif run

$(RUN): $(SDL_OBJS) $(SDL_MAIN)
	$(CC) $^ $(WIN_CFLAGS) $(WIN_LFLAGS) -o $@

$(VERIF_EXE): $(OBJS) $(MAIN)
	$(CC) $^ $(WIN_CFLAGS) $(WIN_LFLAGS) -o $@

blit.o: $(BLIT) $(BLIT_H)
	$(CC) -c $(WIN_CFLAGS) $(WIN_LFLAGS) $<

.PHONY: Z80.o
Z80.o: $(CPU) $(CPU_H)
	$(CC) -c $(WIN_VFLAGS) $(WIN_CFLAGS) $<

ops_impl.o: $(OPS)
	$(CC) -c $(WIN_VFLAGS) $(WIN_CFLAGS) $<

MMU.o: $(MMU) $(MMU_H)
	$(CC) -c $(WIN_VFLAGS) $(WIN_CFLAGS) $<

.PHONY: GPU.o
GPU.o: $(GPU) $(GPU_H)
	$(CC) -c $(WIN_VFLAGS) $(WIN_CFLAGS) $<

$(OPS): $(OP_GEN) $(FUNCS)
	python3 $(OP_GEN)

.PHONY: clean
clean:
	rm *.o





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
