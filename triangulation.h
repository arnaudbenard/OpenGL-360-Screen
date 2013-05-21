#ifndef TRIANGULATION_H
#define TRIANGULATION_H

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

#define NBPNTS 200000

using namespace std;

extern "C"
{
	#ifdef SINGLE
	#define REAL float
	#else /* not SINGLE */
	#define REAL double
	#endif /* not SINGLE */

	#include "triangle.h"
}

triangulateio triangulateXYZ();
void readPointsFromTxt(char* filename,vector<double> &data );

#endif