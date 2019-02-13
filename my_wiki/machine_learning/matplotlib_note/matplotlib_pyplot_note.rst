**********************
Matplotlib Pyplot Note
**********************

.. note::

    Please note that "axes" here and in most places in the documentation 
    refers to the axes part of a figure and not the strict mathematical 
    term for more than one axis.

.. code-block:: py

    import matplotlib.pyplot as plt

    # plt.gca() returns the current axes (a matplotlib.axes.Axes instance)
    # plt.gcf() returns the current figure (a matplotlib.figure.Figure instance)
    # plt.clf() clears the current figure
    # plt.cla() clears the current axes
    # plt.title(title)
    # plt.legend()
    # plt.xlabel(label)
    # plt.ylabel(label)
    # plt.grid(bool)

.. function:: matplotlib.pyplot.plot(*args, scalex=True, scaley=True, data=None, **kwargs)

    Plot y versus x as lines and/or markers. Call signatures::

        plot([x], y, [fmt], data=None, **kwargs)
        plot([x], y, [fmt], [x2], y2, [fmt2], ..., **kwargs)

        # fmt = '[color][marker][line]'

    The optional parameter fmt is a convenient way for defining 
    basic formatting like color, marker and linestyle with a 
    format: ``[color][marker][line]``.

    Colors:

    ===========  =========
    character    color    
    ===========  =========
    'b'          blue     
    'g'          green    
    'r'          red      
    'c'          cyan     
    'm'          magenta  
    'y'          yellow   
    'k'          black    
    'w'          white    
    ===========  =========

    Markers:

    ===========  =======================
    character    description            
    ===========  =======================
    '.'          point marker           
    ','          pixel marker           
    'o'          circle marker          
    'v'          triangle_down marker   
    '^'          triangle_up marker     
    '<'          triangle_left marker   
    '>'          triangle_right marker  
    '1'          tri_down marker        
    '2'          tri_up marker          
    '3'          tri_left marker        
    '4'          tri_right marker       
    's'          square marker          
    'p'          pentagon marker        
    '*'          star marker            
    'h'          hexagon1 marker        
    'H'          hexagon2 marker        
    '+'          plus marker            
    'x'          x marker               
    'D'          diamond marker         
    'd'          thin_diamond marker    
    '|'          vline marker           
    '_'          hline marker           
    ===========  =======================

    Line Styles:

    ===========  =====================
    character    description          
    ===========  =====================
    '-'          solid line style     
    '--'         dashed line style    
    '-.'         dash-dot line style  
    ':'          dotted line style    
    ===========  =====================

.. function:: matplotlib.pyplot.subplot(*args, **kwargs)

    Add a subplot to the current figure. Call signatures::

        subplot(nrows, ncols, index, **kwargs)
        subplot(pos, **kwargs)
        subplot(ax)

.. function:: matplotlib.pyplot.figure(num=None, figsize=None, dpi=None, 
        facecolor=None, edgecolor=None, frameon=True, 
        FigureClass=<class 'matplotlib.figure.Figure'>, clear=False, **kwargs)

    Create a new figure. You can create multiple figures by using multiple 
    ``figure()`` calls with an increasing figure number. 

    .. note::

        If you are making lots of figures, you need to be aware of one more thing: 
        the memory required for a figure is not completely released until the figure 
        is explicitly closed with ``close()``. Deleting all references to the figure, 
        and/or using the window manager to kill the window in which the figure appears 
        on the screen, is not enough, because pyplot maintains internal references 
        until ``close()`` is called.

.. function:: matplotlib.pyplot.close(fig=None)

    Close a figure window. There are a number of ways 
    to specify the figure to close::

        None: the current figure
        Figure: the given Figure instance
        int: a figure number
        str: a figure name
        'all': all figures

.. function:: matplotlib.pyplot.axis(*v, **kwargs)

    Convenience method to get or set some axis properties.
    Call signatures::

        xmin, xmax, ymin, ymax = axis()
        xmin, xmax, ymin, ymax = axis(xmin, xmax, ymin, ymax)
        xmin, xmax, ymin, ymax = axis(option)
        xmin, xmax, ymin, ymax = axis(**kwargs)
