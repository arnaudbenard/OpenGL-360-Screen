#include "triangulation.h"

triangulateio triangulateXYZ(void){

	// Variables for the triangulation
	struct triangulateio in, mid, out, vorout;

	//Input data
	in.numberofpoints = NBPNTS;
	in.numberofpointattributes = 0;
	in.numberofsegments = 0;
	in.numberofholes = 0;
	in.numberofregions = 0;
	in.pointlist = (REAL *) malloc(in.numberofpoints * 2 * sizeof(REAL));
	in.pointmarkerlist = (int *) malloc(in.numberofpoints * sizeof(int));
	in.regionlist = (REAL *) malloc(in.numberofregions * 4 * sizeof(REAL));
	in.pointattributelist = (REAL *) malloc(in.numberofpoints *
		in.numberofpointattributes *
		sizeof(REAL));

	//Result of the triangulation
	out.numberofpoints = NBPNTS+6;
	out.numberofpointattributes = 1;
	out.pointattributelist = (REAL *) malloc(out.numberofpoints *
		out.numberofpointattributes *
		sizeof(REAL));

	// Variables for reading the .txt files
	int i=0;
	string line;
	const char* filename;

	double maxX=0, minX=0,
		maxY=0, minY=0,
		maxZ=0, minZ=0;

	vector<double> xPosition(NBPNTS);
	//xPosition = readPointsFromTxt("data/x.txt");

	return out;
}
void readPointsFromTxt(char* filename,vector<double> &data ){

	double x=0;
	ifstream myfile (filename);
	string line;

	if (myfile.is_open())
	{	
		while (myfile.good())
		{	
			getline(myfile,line);
			istringstream(line) >> x;
			data.push_back(x);
		}
		myfile.close();
	}
	else {cout << "Unable to open file"; exit(1);}
}