EXE=hw2

all: $(EXE)

ifeq "$(OS)" "Windows_NT"
CFLG=-O3 -Wall -DUSEGLEW
LIBS=-lfreeglut -lglew32 -lglu32 -lopengl32 -lm
CLEAN=rm -f *.exe *.o *.a
else
ifeq "$(shell uname)" "Darwin"
CFLG=-O3 -Wall -Wno-deprecated-declarations -DRES=2
LIBS=-framework GLUT -framework OpenGL
else
CFLG=-O3 -Wall
LIBS=-lglut -lGLU -lGL -lm
endif
CLEAN=rm -f $(EXE) *.o *.a
endif

.c.o:
	gcc -c $(CFLG) $<
.cpp.o:
	g++ -c $(CFLG) $<

hw2:lorenzattractor.o
	gcc $(CFLG) -o $@ $^  $(LIBS)

clean:
	$(CLEAN)