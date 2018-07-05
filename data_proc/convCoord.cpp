#include<iostream>
#include<stdlib.h>
using namespace std;
float conv_coords(float in_coords)
 {
 //Initialize the location.
 float f = in_coords;
 // Get the first two digits by turning f into an integer, then doing an integer divide by 100;
 // firsttowdigits should be 77 at this point.
 int firsttwodigits = ((int)f)/100; //This assumes that f < 10000.
 float nexttwodigits = f - (float)(firsttwodigits*100);
 float theFinalAnswer = (float)(firsttwodigits + nexttwodigits/60.0);
 return theFinalAnswer;
 }

int main(int argc, char** argv){
  float c = atof(argv[1]);
  c = conv_coords(c);
  cout<<c<<endl;
  return 0;
}  
