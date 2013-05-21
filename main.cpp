#include "main.h"

int main(int argc,char* argv[])
{
  vector<double> xPosition;

  readPointsFromTxt("data/x.txt",xPosition);
  cout << xPosition.size() << endl;
  for (int i = 0; i < 309; i++){
    cout << xPosition[i+10000] << endl;
  }
  return 0;
}