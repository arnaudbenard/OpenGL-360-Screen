# Compiler
CC 		= gcc
CXX		= g++ 	

# Libraries
CSWITCHES 	= -O -DLINUX -I/usr/X11R6/include -L/usr/X11R6/lib -g
TRILIBDEFS 	= -DTRILIBRARY
CFLAGS     	+=  -c -Wall -O2 -lGLEW -lGL -lglut -lGLU -g
LDFLAGS    	+= -lGLEW -lGL -lglut -lGLU -g


main: main.o triangulation.o triangle.o
	$(CXX) main.o triangulation.o triangle.o -o main $(LDFLAGS) 

triangle.o: triangle.c triangle.h
	$(CC) $(CSWITCHES) $(TRILIBDEFS) -c -o triangle.o \
		triangle.c

triangulation.o: triangulation.cpp triangulation.h triangle.h
	$(CXX) $(CFLAGS) triangulation.cpp 

main.o: main.cpp triangulation.h main.h
	$(CXX) $(CFLAGS) main.cpp

clean:
	rm *o main