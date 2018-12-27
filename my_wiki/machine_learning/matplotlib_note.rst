***************
Matplotlib Note
***************

.. code-block:: py
   :caption: Bakery pie demo

   #!/usr/bin/env python

   import numpy as np
   import matplotlib.pyplot as plt
   
   recipe = ["375 g flour", "75 g sugar", "250 g butter", "300 g berries"]
   data = [float(x.split()[0]) for x in recipe]
   ingredients = [x.split()[-1] for x in recipe]
   
   def func(pct, allvals):
       absolute = int(pct/100.*np.sum(allvals))
       return "{:.1f}%\n({:d} g)".format(pct, absolute)
   
   # pct stands for percentage
   fig, ax = plt.subplots(figsize=(6, 3), subplot_kw=dict(aspect="equal"))
   wedges, texts, autotexts = ax.pie(data, autopct=lambda pct: func(pct, data), textprops=dict(color="w"))
   ax.legend(wedges, ingredients, title="Ingredients", loc="center left", bbox_to_anchor=(1, 0, 0.5, 1))
   plt.setp(autotexts, size=8, weight="bold")
   ax.set_title("Matplotlib bakery: A pie")
   plt.show()

.. code-block:: py
   :caption: Donut pie demo

   #!/usr/bin/env python
   
   import matplotlib.pyplot as plt
   import numpy as np
   
   size = 0.3
   vals = np.array([[60., 32.], [37., 40.], [29., 10.]])
   
   fig, ax = plt.subplots()
   cmap = plt.get_cmap("tab20c")
   outer_colors = cmap(np.arange(3)*4)
   inner_colors = cmap(np.array([1, 2, 5, 6, 9, 10]))
   ax.pie(vals.sum(axis=1), radius=1, colors=outer_colors, wedgeprops=dict(width=size, edgecolor='w'))
   ax.pie(vals.flatten(), radius=1-size, colors=inner_colors, wedgeprops=dict(width=size, edgecolor='w'))
   ax.set(aspect="equal", title='Pie plot with `ax.pie`')
   plt.show()   