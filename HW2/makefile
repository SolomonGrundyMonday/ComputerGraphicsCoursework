# Homework 2 executable name.
EXE=hw2

# Main target.
all: $(EXE)

# MSYS/MinGW compiler flags.
ifeq "$(OS)" "Windows_NT"
CFLG=-O3 -Wall -DUSEGLEW
LIBS=-lfreeglut -lglew32 -lglu32 -lopengl32 -lm
CLEAN=rm -f *.exe *.o *.a
else
# OSX compiler flags
ifeq "$(shell uname)" "Darwin"
CFLG=-O3 -Wall -Wno-deprecated-declarations -DRES=2
LIBS=-framework GLUT -framework OpenGL
else
# Linux/Unix/Solaris compiler flags.
CFLG=-O3 -Wall
LIBS=-lglut -lGLU -lGL -lm
endif
CLEAN=rm -f $(EXE) *.o *.a
endif

# Compiler rules.
.c.o:
	gcc -c $(CFLG) $<
.cpp.o:
	g++ -c $(CFLG) $<

# Linker.
hw2:lorenzattractor.o
	gcc $(CFLG) -o $@ $^  $(LIBS)

# Clean rule.
clean:
	$(CLEAN)