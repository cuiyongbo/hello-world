***************
Getting Started
***************

.. code-block:: py
   :caption: Example 1

   import scipy as sp
   import matplotlib.pyplot as plt
   data = sp.genfromtxt("web_traffic.tsv", delimiter="\t")
   x = data[:,0]
   y = data[:, 1]
   x = x[~sp.isnan(y)]
   y = y[~sp.isnan(y)]
   plt.scatter(x,y)
   plt.title("Web trafic over the last month")
   plt.xlabel("Time")
   plt.ylabel("Hits/hour")
   plt.xticks([w*7*24 for w in range(10)],
   ["week %i" %w for w in range(10)])
   plt.autoscale(tight=True)
   plt.grid()
   plt.show()

.. code-block:: py
   :caption: Example 2

   # code from example 1 comes here

   def error(f, x, y):
       return sp.sum((f(x)-y)**2)
   
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
   