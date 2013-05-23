# Compiler
CC 		= gcc
CXX		= g++ 	

# Libraries
CSWITCHES 	= -O  -I/sr/X11R6/include -L/usr/X11R6/lib -g
TRILIBDEFS 	= -DTRILIBRARY
CFLAGS     	=  -c -g -I/opt/local/include/libpng15
LDFLAGS    	=  -g -L/opt/local/lib -lpng15
OGLFLAGS 	= -lGLEW -framework OpenGL -framework GLUT

main: main.o triangulation.o triangle.o
	$(CXX) main.o triangulation.o triangle.o -o main $(LDFLAGS) $(OGLFLAGS)

triangle.o: triangle.c triangle.h
	$(CC) $(CSWITCHES) $(TRILIBDEFS) -c -o triangle.o \
		triangle.c

triangulation.o: triangulation.cpp triangulation.h triangle.h
	$(CXX) $(CFLAGS) triangulation.cpp 

main.o: main.cpp triangulation.h main.h
	$(CXX) $(CFLAGS) main.cpp

clean:
	rm *o main