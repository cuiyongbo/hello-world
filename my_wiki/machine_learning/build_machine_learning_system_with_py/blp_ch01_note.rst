***************
Getting Started
***************

.. code-block:: py
   :caption: Performance Comparison

   import timeit
   
   normal_py_sec = timeit.timeit("sum(x*x for x in xrange(1000))", 
      number = 10000)
   
   naive_np_sec = timeit.timeit("sum(na*na)", 
      setup="import numpy as np; na=np.arange(1000)",
      number = 10000)
   
   effect_np_sec = timeit.timeit("na.dot(na)", 
      setup="import numpy as np; na=np.arange(1000)",
      number = 10000)
   
   print("Normal Python: %f seconds" % normal_py_sec)
   print("Naive NumPy: %f seconds" % naive_np_sec)
   print("Effect NumPy: %f seconds" % effect_np_sec)
   # Output:
   # Normal Python: 0.551879 seconds
   # Naive NumPy: 0.718675 seconds
   # Effect NumPy: 0.011509 seconds

.. code-block:: py
   :caption: utils.py

   import sys
   sys.dont_write_bytecode = True
   
   import scipy as sp
   import matplotlib.pyplot as plt
   
   sp.random.seed(3)  # to reproduce the data later on
   
   def error(f, x, y):
       return sp.sum((f(x) - y)**2)
   
   def print_traffic_map(x, y):
       plt.figure(num=None, figsize=(8, 6))
       plt.scatter(x, y, s = 10)
       plt.title("Web trafic over the last month")
       plt.xlabel("Time")
       plt.ylabel("Hits/hour")
       plt.xticks([w*7*24 for w in range(10)],
       ["week %i" %w for w in range(10)])
       plt.autoscale(tight=True)
       plt.ylim(ymin=0)
       plt.grid(True, linestyle='-', color='0.75')
   
.. code-block:: py
   :caption: Example 1

   from utils import *

   data = sp.genfromtxt("web_traffic.tsv", delimiter="\t")
   x = data[:,0]
   y = data[:, 1]
   x = x[~sp.isnan(y)]
   y = y[~sp.isnan(y)]

   print_traffic_map(x, y)

.. code-block:: py
   :caption: Example 2

   # code from example 1 comes here
   
   fp1, res, rank, sv, rcond = sp.polyfit(x, y, 1, full=True)
   f1 = sp.poly1d(fp1)
   # res means residual, which should equal to error(f1, x, y)
   fx = sp.linspace(0, x[-1], 1000)
   plt.plot(fx, f1(fx), linewidth=4)
   plt.legend(["d=%i" % f1.order], loc="upper left")
   plt.show()

.. code-block:: py
   :caption: Example 3

   # code from example 1 comes here

   fx = sp.linspace(0, x[-1], 1000)

   orders = [1,2,3,10,100]
   line_styles = ["-", "--", "-.", "-", ":"]
   colors = ["green", "black", "blue", "cyan", "magenta"]
   
   for i in range(len(orders)):
      fp = sp.polyfit(x, y, orders[i])
      f = sp.poly1d(fp)
      plt.plot(fx, f(fx), color=colors[i], linestyle=line_styles[i], linewidth=1.75)
   
   plt.legend(["d=%i" % i for i in orders], loc="upper left")
   plt.show()

.. code-block:: py
   :caption: Example 4

   # code from example 1 comes here

   inflection = int(3.5 * 7 * 24)
   xa = x[:inflection]
   ya = y[:inflection]
   xb = x[inflection:]
   yb = y[inflection:]
   
   fa = sp.poly1d(sp.polyfit(xa, ya, 1))
   fb = sp.poly1d(sp.polyfit(xb, yb, 1))
   
   fa_error = error(fa, xa, ya)
   fb_error = error(fb, xb, yb)
   print("Error inflection: %f" % (fa_error + fb_error))
   
   fx = sp.linspace(0, x[-1], 1000)
   plt.plot(fx, fa(fx), color="g", linestyle = "-", linewidth=2)
   plt.plot(fx, fb(fx), color="black", linestyle = "--", linewidth=2)
   plt.legend(["d=%d" % o for o in [fa.order, fb.order]], loc="upper left")
   plt.show()
