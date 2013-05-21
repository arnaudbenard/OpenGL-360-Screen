#ifndef DATA_H
#define DATA_H



#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <time.h>

/*#include <cv.h>
#include <highgui.h>
#include <math.h>
#include <ctime>*/
#include <GL/gl.h> //include the gl header file
#include <GL/glut.h> //include the glut header file
#include "armadillo"
#include <unistd.h>



#define N_ELEMENTS 1283841
#define DIMENSION 512
#define GRAYSCALE 255
#define window_width  512
#define window_height 512
#define N_ECH 2000000
#define RATIO 1

//Namespace for OpenCV and std
using namespace std;
using namespace arma;

extern "C"
{
	#ifdef SINGLE
	#define REAL float
	#else /* not SINGLE */
	#define REAL double
	#endif /* not SINGLE */
	#include "triangle.h"
}


triangulateio readfile();


#endif