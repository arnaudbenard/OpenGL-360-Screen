#include "data.h"


/////Readfile ////////////////////////////////////////////////////////////////////////////
triangulateio readfile(){


	// Variables for the triangulation
	struct triangulateio in, mid, out, vorout;

	//Input data
	in.numberofpoints = N_ECH/2;
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

  	//out parameters 
  	out.numberofpoints = N_ECH/2;
  	out.numberofpointattributes = 1;
	out.pointattributelist = (REAL *) malloc(out.numberofpoints *
                                          out.numberofpointattributes *
                                          sizeof(REAL));
	// Variables for reading the .txt files
	int i=0;
	string line;
	double x,max=0,min=0;
	mat M(N_ELEMENTS+2,3);
	const char* filename;

	for (int j = 0; j < 3; ++j)
	{
		if (j==0)
			filename="data/x.txt";
		else if (j==1)
			filename="data/y.txt";
		else if (j==2)
			filename="data/z.txt";

		ifstream myfile (filename);

		if (myfile.is_open())
		{	
			while ((myfile.good())&& (i<N_ELEMENTS))
			{	
				getline(myfile,line);
				istringstream(line) >> x;

				// Find maximum value
				if(M(max,j)<x)
				max=i;

				//Find minimum value
				else if(M(min,j)>x)
				min=i;

				//Save values in the col vector
				M(i,j)=x;
				i++;
			}

			M(N_ELEMENTS,j)=M(min,j);
			M(N_ELEMENTS+1,j)=M(max,j);
			i=0;
			myfile.close();
		}
		else {cout << "Unable to open file"; exit(1);}
	}

	//Assignment to a matrix
	double x_val,y_val,z_val;
	double x_min=M(N_ELEMENTS,0), x_max=M(N_ELEMENTS+1,0),
	y_min=M(N_ELEMENTS,1), y_max=M(N_ELEMENTS+1,1),
	z_min=M(N_ELEMENTS,2), z_max=M(N_ELEMENTS+1,2);

	mat BC=zeros(DIMENSION,DIMENSION);
	int count=0;

	for (int j = 0; j < N_ELEMENTS; ++j)
	{
		if(j%RATIO==0){

			x_val=M(j,0);
			x_val=floor((x_val-x_min)/(x_max-x_min)*(DIMENSION-1));
			y_val=M(j,1);
			y_val=floor((y_val-y_min)/(y_max-y_min)*(DIMENSION-1));

			//Triangulation input data
			if (count < N_ECH-1){

				//XY values
				in.pointlist[count] = M(j,0);
				in.pointlist[count+1] = M(j,1);
				cout <<  M(j,0) <<M(j,1) <<count << endl;
				count+=2;

				//Z values
				if ((y_val>=0) && (y_val<=(DIMENSION-1)) && (x_val>=0) && (x_val<=(DIMENSION-1))){
					z_val=M(j,2);
					z_val=(z_val-z_min)/(z_max-z_min);
					out.pointattributelist[count/2]=1-z_val;
				}

			}
		}	
	}

	/* Make necessary initializations so that Triangle can return a */
	/*   triangulation in `mid' and a voronoi diagram in `vorout'.  */

	mid.pointlist = (REAL *) NULL;            /* Not needed if -N switch used. */
	/* Not needed if -N switch used or number of point attributes is zero: */
	mid.pointattributelist = (REAL *) NULL;
	mid.pointmarkerlist = (int *) NULL; /* Not needed if -N or -B switch used. */
	mid.trianglelist = (int *) NULL;          /* Not needed if -E switch used. */
	/* Not needed if -E switch used or number of triangle attributes is zero: */
	mid.triangleattributelist = (REAL *) NULL;
	mid.neighborlist = (int *) NULL;         /* Needed only if -n switch used. */
	/* Needed only if segments are output (-p or -c) and -P not used: */
	mid.segmentlist = (int *) NULL;
	/* Needed only if segments are output (-p or -c) and -P and -B not used: */
	mid.segmentmarkerlist = (int *) NULL;
	mid.edgelist = (int *) NULL;             /* Needed only if -e switch used. */
	mid.edgemarkerlist = (int *) NULL;   /* Needed if -e used and -B not used. */

	vorout.pointlist = (REAL *) NULL;        /* Needed only if -v switch used. */
	/* Needed only if -v switch used and number of attributes is not zero: */
	vorout.pointattributelist = (REAL *) NULL;
	vorout.edgelist = (int *) NULL;          /* Needed only if -v switch used. */
	vorout.normlist = (REAL *) NULL;         /* Needed only if -v switch used. */

	triangulate("pczAevn", &in, &mid, &vorout);

  	/* Attach area constraints to the triangles in preparation for */
 	/*   refining the triangulation.                               */

  	/* Needed only if -r and -a switches used: */
	mid.trianglearealist = (REAL *) malloc(mid.numberoftriangles * sizeof(REAL));

  	/* Make necessary initializations so that Triangle can return a */
  	/*   triangulation in `out'.                                    */

  	out.pointlist = (REAL *) NULL;            /* Not needed if -N switch used. */
  	/* Not needed if -N switch used or number of attributes is zero: */
  	//out.pointattributelist = (REAL *) NULL;
  	out.trianglelist = (int *) NULL;          /* Not needed if -E switch used. */
  	/* Not needed if -E switch used or number of triangle attributes is zero: */
  	out.triangleattributelist = (REAL *) NULL;

   	triangulate("prazBP", &mid, &out, (struct triangulateio *) NULL);

/*
   for (int r = 0; r < N_ECH/2; ++r)
   {
		cout << "point" << out.pointattributelist[r]<< endl;
   }
*/
  	/* Free all allocated arrays, including those allocated by Triangle. */

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
  	/*free(vorout.pointlist);
  	free(vorout.pointattributelist);
  	free(vorout.edgelist);
  	free(vorout.normlist);
  	free(out.pointlist);
  	free(out.pointattributelist);
  	free(out.trianglelist);
  	free(out.triangleattributelist);*/

	return out;
}
