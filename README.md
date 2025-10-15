# C-to-Python

Various examples and short exercises on bridging Python and compiled code.

C-to-Python.ipynb

I used numpy to calculate pi using 100M random points in the [0,1) unit square. The timing module says that it took a user CPU time of 851 ms, which is pretty fast. For the pythonic method, it was 5.28 s, and for the C method, it was 244 ms. So clearly, numpy isn't as fast as compiled C code. But that's fine! I don't need it to be super fast. Numpy is easy to work with if you think in matrices and vectors, and it is still much faster than raw python. For reference, the numba method was 719 ms, which is on par with numpy.