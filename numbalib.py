# a simple method to estimate pi using uniformly distributed random numbers

from random import random
from math import sqrt
import numba
from numba import jit

# estimate pi from the dart throwing method
@jit(nopython=True)
def findPi(nthrows=100*1000*1000):
    count=0
    for i in range (nthrows):
        x=random()
        y=random()
        if x*x+y*y < 1: count = count+1
    return 4.0*count/nthrows

    
# return the magnitude of a complex number
@jit(nopython=True)
def magnitude(re, im):
  return sqrt(re*re+im*im)

@jit(nopython=True)
def mandel_test(c_re, c_im, NTRIALS):
  # If a point is in the set, its magnitude will remain bounded by
  # 2.0 over iterations of z -> z^2 + C.  Stop the loop after a 
  # maximum of NTRIALS and consider this point to be in the set

    z_re = c_re
    z_im = c_im
    counts = 1
    while magnitude(z_re,z_im)<=2.0  and counts<NTRIALS:
        counts=counts+1
        re=z_re  # careful! keep old values for calculation
        im=z_im
        # z -> z^2
        z_re = re*re-im*im
        z_im = 2*re*im
        # add c to z^2
        z_re = z_re + c_re
        z_im = z_im + c_im
    return counts

# explore the Mandelbrot set
@jit(nopython=True)
def mandel(img, re1, re2, im1, im2, nr, ni, NTRIALS=255):
    dx=(re2-re1)/nr
    dy=(im2-im1)/ni
    # loop over grid starting in lower left corner
    for j in range(ni):
        im=im1+j*dy
        for i in range(nr):
            re=re1+i*dx
            img[j][i]=mandel_test(re,im,NTRIALS)

# doing the exercise project 1
@jit(nopython = True)
def jit_count3d(n):
    count=0
    for i in range (n):
        for j in range (i+1,n):
            for k in range (j+1,n):
                count = count +1
    return count

