#include "main.h"

/*  Globals */
double dim=2; /* dimension of orthogonal box */
float xMin=-1,yMin=-1,xMax=1,yMax=1;
static int windowSize = 500;
GLuint ID;
int size,el_size;

void initVBO(void){

  float z_val=0;
  int point=0;
  el_size=6*sizeof(float);

  //Loading data from the text files and applying the Delaunay algorithm
  triangulateio fullData=triangulateXYZ();
  vector<float> fullData_vector(fullData.numberoftriangles*3*6); //3 points with 6 coordinates (position and color)

  size=fullData_vector.size();

  cout << "Number of triangles generated " << fullData.numberoftriangles<< endl;

  // Min max values for GlOrtho and normalization
  xMin=fullData.pointattributelist[NBPNTS];
  xMax=fullData.pointattributelist[NBPNTS+1];
  yMin=fullData.pointattributelist[NBPNTS+2];
  yMax=fullData.pointattributelist[NBPNTS+3];

  double  zMin=fullData.pointattributelist[NBPNTS+4],
  zMax=fullData.pointattributelist[NBPNTS+5];
  for(int i_tri = 0; i_tri < fullData.numberoftriangles; i_tri++) {

    for (int i_point = 0; i_point < 3; i_point++) {

      z_val=fullData.pointattributelist[fullData.trianglelist[i_tri * 3 + i_point]];
      z_val=((z_val-zMin)/(zMax-zMin)); //normalize and invertion

      point=6*(i_tri *3 + i_point);

      fullData_vector[point+0]=fullData.pointlist[2*fullData.trianglelist[i_tri * 3 + i_point]];
      fullData_vector[point+1]=fullData.pointlist[2*fullData.trianglelist[i_tri * 3 + i_point]+1];
      fullData_vector[point+2]=z_val;
      fullData_vector[point+3]=z_val;
      fullData_vector[point+4]=z_val;
      fullData_vector[point+5]=z_val;
    }
  }
  
  GLenum err = glewInit();

  if (GLEW_OK != err)
    fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
  else
    cout << "glewInit" << endl;


  glEnable(GL_DEPTH_TEST);
  glDepthMask(GL_TRUE);
  glDepthFunc(GL_LEQUAL);
  glDepthRange(-2.0f, 2.0f);
  glClearColor(0.0f, 1.0f, 0.0f, 0.0f);
  glShadeModel(GL_SMOOTH);
  glEnableClientState(GL_VERTEX_ARRAY);
  cout << "Generate buffer" << endl;
  glGenBuffers(1,&ID);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,size*sizeof(float), &fullData_vector[0], GL_STATIC_DRAW);
  cout << "Initialisation done!" << endl;

}
/*
 *  Display the scene
 */
void display()
{
  cout << "Displaying on the screen" << endl;

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(xMin, xMax,yMin,yMax, -1.0f, 1.0f);
  glPushMatrix ();
  glBindBuffer(GL_ARRAY_BUFFER, ID);

  // Pointer for the position of the points
  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_FLOAT, el_size, 0);

  // Pointer for the color of the points
  glEnableClientState(GL_COLOR_ARRAY);
  glColorPointer(3,GL_FLOAT, el_size,(void*)(el_size/2));

  //Draw callback
  glDrawArrays(GL_TRIANGLES,0,size/6);

  glPopMatrix ();
  glFlush();
}

/*
 *  GLUT calls this routine when the window is resized
 */
void reshape(int width,int height)
{
  double w2h = (height>0) ? (double)width/height:1;
  glViewport(0,0,width,height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-dim*w2h,+dim*w2h,-dim,+dim,-dim,+dim);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

/*
 *  Start up GLUT and tell it what to do
 */
int main(int argc,char* argv[])
{
  
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_DEPTH | GLUT_RGB);
  glutInitWindowSize(windowSize,windowSize);
  glutCreateWindow("OpenGL");
  initVBO();
  glutDisplayFunc(display);
  //glutReshapeFunc(reshape);
  glutMainLoop();

  return 0;
}