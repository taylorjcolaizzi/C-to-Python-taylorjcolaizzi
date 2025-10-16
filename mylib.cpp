#include "mylib.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

// here we check if the flag EXTERNC is set, if it is then
// we will tell the compiler to treat the code below a C code
// generating the library

#ifdef EXTERNC
extern "C" {
#endif

// estimate pi from the dart throwing method
double findPi(long nthrows=100*1000*1000){
  srand48((long)time(NULL));
  long count = 0;
  for (int i=0; i<nthrows; ++i){
    double x = drand48();
    double y = drand48();
    if (x*x+y*y < 1) ++count;
  }
  return 4.0*count/nthrows;
}

// estimate the volume of a d-dimensional hypersphere of radius r given N pseudorandom points.
double HSVolume(int d = 3, int N = 1000, double r = 1){
  srand48((long)time(NULL)); // Sets the seed to the current time. Keeps it random.
  long count = 0; // Counts points inside the hyper sphere.
  float point_store[d]; // make d-dimensional array to hold the random numbers for point
  float distance2 = 0; // distance squared of point from center
  float CUBE_VOLUME = 1;
  for (int i = 0; i < d; ++i){
    CUBE_VOLUME *= 2; // each cube length will be 2. So volume is 2 * 2 * 2 * 2 * ... d times.
  }
  float SPHERE_VOLUME = 0; // Saving for later on.
  for (int i = 0; i < N; ++i){ // for each point
    for (int j = 0; j < d; ++j){ // for each dimension
      point_store[j] = drand48() * 2. - 1.; // drand48() is only from [0.0, 1.0), so we need to stretch it by 2 and subtract it by 1
      distance2 += point_store[j] * point_store[j]; // maybe shorten this later on. adds the square of the dimension.
    }
    if (distance2 < r * r) ++ count; // if magnitude squared is less than r squared, add to the count
    distance2 = 0;
  }
  SPHERE_VOLUME = count * CUBE_VOLUME / N;
  return SPHERE_VOLUME;
}
 

// return the magnitude of a complex number
double magnitude(double re, double im){
  return sqrt(re*re+im*im);
}


int mandel_test(double c_re, double c_im, int NTRIALS){  
  // If a point is in the set, its magnitude will remain bounded by
  // 2.0 over iterations of z -> z^2 + C.  Stop the loop after a 
  // maximum of NTRIALS and consider this point to be in the set

  double z_re = c_re;
  double z_im = c_im;
  int counts = 1;
  while (magnitude(z_re,z_im)<=2.0  && counts<NTRIALS) {
    counts++;
    double re=z_re;  // careful! keep old values for calculation
    double im=z_im;
    // z -> z^2
    z_re = re*re-im*im;
    z_im = 2*re*im;
    // add c to z^2
    z_re = z_re + c_re;
    z_im = z_im + c_im;
  }
  return counts;
}


// explore the Mandelbrot set
// we pass the image buffer as a 1D array, and access the pixels
// using pointer arithmatic
// eg for an array a[n][m], n=nrow, m=mcolumns
// a[0] = a[0][0]
// a[m] = a[1][0]
// a[m+1] = a[1][1]
// ...
void mandel(double *img, double re1, double re2, double im1, double im2,
	    int nr, int ni, int NTRIALS){
  double dx=(re2-re1)/nr;
  double dy=(im2-im1)/ni;
  // loop over grid starting in lower left corner
  for (int j=0; j<ni; ++j){
    double im=im1+j*dy;
    for (int i=0; i<nr; ++i){
      double re=re1+i*dx;
      img[j*ni+i]=mandel_test(re,im,NTRIALS);
    }
  }
}

  

#ifdef EXTERNC
}
#endif




/*
int main(){
  findPi();
  return 0;
} 
*/
