#include "triangulation.h"

triangulateio triangulateXYZ(void){

	// Loading data into a dynamic array
	vector<float> xPosition(NBPNTS),yPosition(NBPNTS),zPosition(NBPNTS);
	readPointsFromTxt("data/x.txt", xPosition);
	readPointsFromTxt("data/y.txt", yPosition);
	readPointsFromTxt("data/z.txt", zPosition);

	// Variables for the triangulation
	struct triangulateio in, mid, out, vorout;

	//Input data
	in.numberofpoints = 2*NBPNTS;
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

	float maxX=xPosition[0], minX=xPosition[0],
		maxY=yPosition[0], minY=yPosition[0],
		maxZ=zPosition[0], minZ=zPosition[0];

	for(int i=0; i<NBPNTS; i++){

		in.pointlist[2*i] = xPosition[i];
		in.pointlist[2*i+1] =  yPosition[i];

		out.pointattributelist[i]=zPosition[i];

		if(minX> xPosition[i])
			minX= xPosition[i];
		else if(maxX< xPosition[i])
			maxX= xPosition[i];

		else if(minY> yPosition[i])
			minY= yPosition[i];
		else if(maxY< yPosition[i])
			maxY= yPosition[i];

		else if(minZ> zPosition[i])
			minZ= zPosition[i];
		else if(maxZ< zPosition[i])
			maxZ= zPosition[i];
	}

	out.pointattributelist[NBPNTS]=minX;
	out.pointattributelist[NBPNTS+1]=maxX;

	out.pointattributelist[NBPNTS+2]=minY;
	out.pointattributelist[NBPNTS+3]=maxY;

	out.pointattributelist[NBPNTS+4]=minZ;
	out.pointattributelist[NBPNTS+5]=maxZ;

	mid.pointlist = (REAL *) NULL; /* Not needed if -N switch used. */
	/* Not needed if -N switch used or number of point attributes is zero: */
	mid.pointattributelist = (REAL *) NULL;
	mid.pointmarkerlist = (int *) NULL; /* Not needed if -N or -B switch used. */
	mid.trianglelist = (int *) NULL; /* Not needed if -E switch used. */
	/* Not needed if -E switch used or number of triangle attributes is zero: */
	mid.triangleattributelist = (REAL *) NULL;
	mid.neighborlist = (int *) NULL; /* Needed only if -n switch used. */
	/* Needed only if segments are output (-p or -c) and -P not used: */
	mid.segmentlist = (int *) NULL;
	/* Needed only if segments are output (-p or -c) and -P and -B not used: */
	mid.segmentmarkerlist = (int *) NULL;
	mid.edgelist = (int *) NULL; /* Needed only if -e switch used. */
	mid.edgemarkerlist = (int *) NULL; /* Needed if -e used and -B not used. */

	vorout.pointlist = (REAL *) NULL; /* Needed only if -v switch used. */
	/* Needed only if -v switch used and number of attributes is not zero: */
	vorout.pointattributelist = (REAL *) NULL;
	vorout.edgelist = (int *) NULL; /* Needed only if -v switch used. */
	vorout.normlist = (REAL *) NULL; /* Needed only if -v switch used. */

	triangulate("pczAevnQ", &in, &mid, &vorout); //pczAevn

	/* Attach area constraints to the triangles in preparation for */
	/* refining the triangulation. */

	/* Needed only if -r and -a switches used: */
	mid.trianglearealist = (REAL *) malloc(mid.numberoftriangles * sizeof(REAL));

	/* Make necessary initializations so that Triangle can return a */
	/* triangulation in `out'. */

	out.pointlist = (REAL *) NULL; /* Not needed if -N switch used. */
	/* Not needed if -N switch used or number of attributes is zero: */
	//out.pointattributelist = (REAL *) NULL;
	out.trianglelist = (int *) NULL; /* Not needed if -E switch used. */
	/* Not needed if -E switch used or number of triangle attributes is zero: */
	out.triangleattributelist = (REAL *) NULL;

	triangulate("prazBPQ", &mid, &out, (struct triangulateio *) NULL); //prazBP

	free(in.pointlist);
	free(in.pointattributelist);
	free(in.pointmarkerlist);
	free(in.regionlist);
	free(mid.pointlist);
	free(mid.pointattributelist);
	free(mid.pointmarkerlist);
	free(mid.trianglelist);
	free(mid.triangleattributelist);
	free(mid.trianglearealist);
	free(mid.neighborlist);
	free(mid.segmentlist);
	free(mid.segmentmarkerlist);
	free(mid.edgelist);
	free(mid.edgemarkerlist);
	free(vorout.pointlist);
	free(vorout.pointattributelist);
	free(vorout.edgelist);
	free(vorout.normlist);

	return out;
}
void readPointsFromTxt(char* filename,vector<float> &data ){

	float x=0;
	int pnts_counter=0;
	ifstream myfile(filename);
	string line;

	if (myfile.is_open())
	{	
		while (myfile.good() && pnts_counter<NBPNTS )
		{	
			getline(myfile,line);
			istringstream(line) >> data[pnts_counter++];
		}
		myfile.close();
	}
	else {cout << "Unable to open file"; exit(1);}

}