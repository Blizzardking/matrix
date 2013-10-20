# Author Jun Yu

EXE1 := prog1
EXE2 := prog2

DEBUG_MODE := n

ifeq ($(DEBUG_MODE), y)
	DEBUG := -g
	MACRO := -D__DEBUG__
else
	DEBUG :=
	MACRO :=
endif

LIBS := 

OBJ1 := $(EXE1).o
OBJ2 := $(EXE2).o

CC := g++
LD := ld
LIB := -L/usr/lib/x86_64-linux-gnu/ -L/usr/lib/i386-linux-gnu/ -lpthread
CFLAGS := $(DEBUG) -Wall  
CXXFLAGS := $(CFLAGS)
LDFLAGS := $(DEBUG) $(LIB)

OBJ := matrix.o

all: common
	$(CC) $(OBJ) $(OBJ1) $(LDFLAGS) -o $(EXE1)
	$(CC) $(OBJ) $(OBJ2) $(LDFLAGS) -o $(EXE2)

common:
	$(CC) -c $(CXXFLAGS) $(MACRO) *.cc

clean:
	rm -f *.o
	rm $(EXE1)
	rm $(EXE2)
