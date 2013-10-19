# Author Jun Yu

EXE1 := prog1
EXE2 := prog2

DEBUG_MODE := y

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
CFLAGS := $(DEBUG) -Wall  
CXXFLAGS := $(CFLAGS) 
LDFLAGS := $(DEBUG)

OBJ := matrix.o

all: common
	$(CC) $(LDFLAGS) $(OBJ) $(OBJ1) -o $(EXE1)
	$(CC) $(LDFLAGS) $(OBJ) $(OBJ2) -o $(EXE2)

common:
	$(CC) -c $(CXXFLAGS) $(MACRO) *.cc

clean:
	rm -f *.o
	rm $(EXE1)
	rm $(EXE2)