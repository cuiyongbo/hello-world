#!/usr/bin/env python

import numpy as np
import matplotlib.pyplot as plt

a = b = np.arange(0, 3, .02)
c = np.exp(a)
d = c[::-1]

fig, ax = plt.subplots()
ax.plot(a, c, 'k--', label="Model length")
ax.plot(a, d, "k:", label="Data length")
ax.plot(a, c+d, "k", label="Total message length")

legend = ax.legend(loc="upper center", shadow=True, fontsize="x-large")

# PUt a nicer backgroud color on the legend
legend.get_frame().set_facecolor("C0")
fig.savefig("./pictures/customized_legend.png")
plt.show()

#!/usr/bin/env python

import numpy as np
import matplotlib.pyplot as plt

x = np.linspace(0, 10, 500)
y = np.sin(x)

fig, ax = plt.subplots()

line1, = ax.plot(x, y, label="Using set_dashes()")
line1.set_dashes([2, 2, 10, 2]) # 2pt line, 2pt break, 10pt line, 2pt break
lie2, = ax.plot(x, y-0.2, dashes=[4, 2, 8, 2], label="Using the dashes parameter")
ax.legend(loc="upper center")
fig.savefig("./pictures/line_dash_control_sample.png")
plt.show()
#!/usr/bin/env python

import numpy as np
import matplotlib.pyplot as plt
from collections import OrderedDict
from matplotlib.transforms import blended_transform_factory

line_styles = OrderedDict(
    [('solid',               (0, ())),
	 ('loosely dotted',      (0, (1, 10))),
	 ('dotted',              (0, (1, 5))),
	 ('densely dotted',      (0, (1, 1))),
	 ('loosely dashed',      (0, (5, 10))),
	 ('dashed',              (0, (5, 5))),
	 ('densely dashed',      (0, (5, 1))),
	 ('loosely dashdotted',  (0, (3, 10, 1, 10))),
	 ('dashdotted',          (0, (3, 5, 1, 5))),
	 ('densely dashdotted',  (0, (3, 1, 1, 1))),
     ('loosely dashdotdotted', (0, (3, 10, 1, 10, 1, 10))),
     ('dashdotdotted',         (0, (3, 5, 1, 5, 1, 5))),
     ('densely dashdotdotted', (0, (3, 1, 1, 1, 1, 1)))
	])

plt.figure(figsize=(10, 6))
ax = plt.subplot(1,1,1)
X, Y = np.linspace(0, 100, 10), np.zeros(10)
for i, (name, line_style) in enumerate(line_styles.items()):
	ax.plot(X, Y+i, linestyle=line_style, linewidth=1.5, color='black')

ax.set_ylim(-0.5, len(line_styles)-0.5)
plt.yticks(np.arange(len(line_styles)), line_styles.keys())
plt.xticks([])

# For each line style, add a text annotation with a small offset from
# the reference point (0 in Axes coords, y tick value in Data coords).
reference_transform = blended_transform_factory(ax.transAxes, ax.transData)
for i, (name, line_style) in enumerate(line_styles.items()):
	ax.annotate(str(line_style), xy=(0.0, i), xycoords=reference_transform,
		xytext=(-6, -12), textcoords="offset points", color="blue", 
		fontsize=8, ha="right", family="monosapce")

plt.tight_layout()
plt.show()


"""
===================================
Shaded & power normalized rendering
===================================

The Mandelbrot set rendering can be improved by using a normalized recount
associated with a power normalized colormap (gamma=0.3). Rendering can be
further enhanced thanks to shading.

The `maxiter` gives the precision of the computation. `maxiter=200` should
take a few seconds on most modern laptops.
"""
import numpy as np


def mandelbrot_set(xmin, xmax, ymin, ymax, xn, yn, maxiter, horizon=2.0):
    X = np.linspace(xmin, xmax, xn).astype(np.float32)
    Y = np.linspace(ymin, ymax, yn).astype(np.float32)
    C = X + Y[:, None] * 1j
    N = np.zeros_like(C, dtype=int)
    Z = np.zeros_like(C)
    for n in range(maxiter):
        I = np.less(abs(Z), horizon)
        N[I] = n
        Z[I] = Z[I]**2 + C[I]
    N[N == maxiter-1] = 0
    return Z, N


if __name__ == '__main__':
    import time
    import matplotlib
    from matplotlib import colors
    import matplotlib.pyplot as plt

    xmin, xmax, xn = -2.25, +0.75, 4200/2
    ymin, ymax, yn = -1.25, +1.25, 3500/2
    maxiter = 200
    horizon = 2.0 ** 40
    log_horizon = np.log(np.log(horizon))/np.log(2)
    Z, N = mandelbrot_set(xmin, xmax, ymin, ymax, xn, yn, maxiter, horizon)

    # Normalized recount as explained in:
    # https://linas.org/art-gallery/escape/smooth.html
    # https://www.ibm.com/developerworks/community/blogs/jfp/entry/My_Christmas_Gift

    # This line will generate warnings for null values but it is faster to
    # process them afterwards using the nan_to_num
    with np.errstate(invalid='ignore'):
        M = np.nan_to_num(N + 1 -
                          np.log(np.log(abs(Z)))/np.log(2) +
                          log_horizon)

    dpi = 72
    width = 10
    height = 10*yn/xn
    fig = plt.figure(figsize=(width, height), dpi=dpi)
    ax = fig.add_axes([0.0, 0.0, 1.0, 1.0], frameon=False, aspect=1)

    # Shaded rendering
    light = colors.LightSource(azdeg=315, altdeg=10)
    M = light.shade(M, cmap=plt.cm.hot, vert_exag=1.5,
                    norm=colors.PowerNorm(0.3), blend_mode='hsv')
    plt.imshow(M, extent=[xmin, xmax, ymin, ymax], interpolation="bicubic")
    ax.set_xticks([])
    ax.set_yticks([])

    # Some advertisement for matplotlib
    year = time.strftime("%Y")
    text = ("The Mandelbrot fractal set\n"
            "Rendered with matplotlib %s, %s - http://matplotlib.org"
            % (matplotlib.__version__, year))
    ax.text(xmin+.025, ymin+.025, text, color="white", fontsize=12, alpha=0.5)

    plt.show()
#!/usr/bin/env python

import numpy as np
import matplotlib.pyplot as plt

t = np.arange(0.0, 1.0+0.01, 0.01)
s = np.cos(2 * 2 * np.pi * t)
t[41:60] = np.nan

plt.subplot(2,1,1)
plt.plot(t,s, '-', lw=2)

plt.xlabel('time (s)')
plt.ylabel('voltage (mV)')
plt.title("A sine wave with a gap of NaNs between 0.4 and 0.6")
plt.grid(True)

plt.subplot(2,1,2)
t[0] = np.nan
t[-1] = np.nan
plt.plot(t,s, '-', lw=1)
plt.title('Also with NaN in the first and last point')

plt.xlabel('time (s)')
plt.ylabel('more nans')
plt.grid(True)

plt.tight_layout()
plt.show()

#!/usr/bin/env python

import numpy as np
import matplotlib.pyplot as plt

def f(t):
	return np.exp(-t)*np.cos(2*np.pi*t)

t1 = np.arange(0.5, 5.0, 0.1)
t2 = np.arange(0.5, 5.0, 0.02)

plt.figure(1)
plt.subplot(2, 1, 1)
plt.plot(t1, f(t1), 'bo', t2, f(t2), 'k')

plt.subplot(2, 1, 2)
plt.plot(t2, np.cos(2*np.pi*t2), 'r--')
plt.show()

#!/usr/bin/env python

import numpy as np
import matplotlib.pyplot as plt

road_count = [24130441, 7340599]
road_labels = ["Bidirectional road", "Unidirectional road"]

def func(pct, allvals):
	absolute = int(pct/100.*np.sum(allvals))
	return "{:.1f}%\n({:d})".format(pct, absolute)

# pct stands for percentage
fig, ax = plt.subplots(figsize=(6, 3), subplot_kw=dict(aspect="equal"))
wedges, texts, autotexts = ax.pie(road_count, autopct=lambda pct: func(pct, road_count), textprops=dict(color="w"))
ax.legend(wedges, road_labels, title="Road directionality", loc="center left", bbox_to_anchor=(1, 0, 0.5, 1))
plt.setp(autotexts, size=8, weight="bold")
ax.set_title("Road directionality chart")
plt.show()
#!/usr/bin/env python

import numpy as np
import matplotlib.pyplot as plt

road_count = [438517,1450424,1722021,2355443,25504635]
func_class = [1,2,3,4,5]
road_labels = ["Function class {:d}".format(x) for x in func_class ]

# pct stands for percentage
fig, ax = plt.subplots(figsize=(6, 3), subplot_kw=dict(aspect="equal"))
#wedges, texts, autotexts = ax.pie(road_count, autopct=lambda pct: func(pct, road_count), textprops=dict(color="w"))
wedges,texts, autotexts = ax.pie(road_count, autopct=lambda pct: "%.2f%%" % pct, textprops=dict(color="w"))
ax.legend(wedges, road_labels, title="Road function class", loc="center left", bbox_to_anchor=(1, 0, 0.5, 1))
plt.setp(autotexts, size=8, weight="bold")
ax.set_title("Road function class  chart")
plt.show()
#!/usr/bin/env python

import matplotlib
import matplotlib.pyplot as plt
import numpy as np

t = np.arange(0.0, 2.0, 0.01)
s = 1+ np.sin(2 * np.pi * t)

fig, ax = plt.subplots()
ax.plot(t, s)

#ax.set(
#	xlabel="time (s)", 
#	ylabel="voltage (mV)",
#	title="About as simple as it gets, folks")
#ax.grid()

plt.xlabel("time (s)")
plt.ylabel("voltage (mV)")
plt.title("About as simple as it gets, folks")
plt.grid(True)

fig.savefig("./pictures/simple_plot.png")

plt.tight_layout()
plt.show()

#!/usr/bin/env python
import numpy as np
import matplotlib.pyplot as plt
import time

np.random.seed(int(time.time()))
data = np.random.randn(2, 100)

fig, axs = plt.subplots(2,2, figsize=(5,5))
axs[0, 0].hist(data[0])
axs[1, 0].scatter(data[0], data[1])
axs[0, 1].plot(data[0], data[1])
axs[1, 1].hist2d(data[0], data[1])

plt.show()
#First create some toy data:
x = np.linspace(0, 2*np.pi, 400)
y = np.sin(x**2)

#Creates just a figure and only one subplot
fig, ax = plt.subplots()
ax.plot(x, y)
ax.set_title('Simple plot')

#Creates two subplots and unpacks the output array immediately
f, (ax1, ax2) = plt.subplots(1, 2, sharey=True)
ax1.plot(x, y)
ax1.set_title('Sharing Y axis')
ax2.scatter(x, y)

#Creates four polar axes, and accesses them through the returned array
fig, axes = plt.subplots(2, 2, subplot_kw=dict(polar=True))
axes[0, 0].plot(x, y)
axes[1, 1].scatter(x, y)

#Share a X axis with each column of subplots
plt.subplots(2, 2, sharex='col')

#Share a Y axis with each row of subplots
plt.subplots(2, 2, sharey='row')

#Share both X and Y axes with all subplots
plt.subplots(2, 2, sharex='all', sharey='all')

#Note that this is the same as
plt.subplots(2, 2, sharex=True, sharey=True)

#Creates figure number 10 with a single subplot
#and clears it if it already exists.
fig, ax=plt.subplots(num=10, clear=True)

#!/usr/bin/env python

import numpy as np
import matplotlib.pyplot as plt

# fmt = '[color][marker][line]'
colors = ['b', 'g', 'r', 'c', 'm', 'k', 'w']
markers = ['.', ',', 'o', 'v', '^', '<', '>', '1', '2', '3', '4', 's', 'p', '*', 'h', 'H', '+', 'D', '|', '_']
line_styles = ['-', '--', '-.', ':']

color_len = len(colors)
marker_len = len(markers)
line_style_len = len(line_styles)

x, y = np.arange(0, 10, 1), np.zeros(10)

plt.figure(1, figsize=(10, 6), clear=True, frameon=True)
ax = plt.gca()

yticks = []
color_idx = 0
style_idx = 0
for i in range(marker_len):
	fmt = "{:s}{:s}{:s}".format(colors[color_idx], markers[i], line_styles[style_idx])
	color_idx = (color_idx+1)%color_len
	style_idx = (style_idx+1)%line_style_len
	ax.plot(x, y+i, fmt)
	yticks.append(fmt)
	#yticks.append("{:<4s}".format(fmt))
	#yticks.append("[{:4s}]".format(fmt))

ax.set_ylim(-0.5, marker_len - 0.5)
ax.set_ylabel("line format [color][marker][style]")
ax.set_yticks(np.arange(marker_len), yticks)
ax.set_xticks([])
ax.set_title("Line Format Sample")
#plt.yticks(np.arange(marker_len), yticks)
#plt.xticks([])
#plt.title("Line Format Sample")

plt.savefig("./pictures/line_fmt_sample.png")
plt.show()

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
   
    import numpy as np
    import matplotlib.pyplot as plt
   
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
