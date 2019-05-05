*******************
Mathematics Notes 3
*******************

#. quotient [商]

    In arithmetic, a quotient is the quantity produced by the division of two numbers. 
    The quotient has widespread use throughout mathematics, and is commonly referred 
    to as a fraction or a ratio. For example, when dividing twenty (the **dividend**) 
    by three (the **divisor**), the quotient is six and two thirds. In this sense, 
    a quotient is the ratio of a dividend to its divisor.

    .. image:: images/quotient.png
    .. image:: images/arithmetic_operations.png

    被除数 ÷ 除数 = 商，余数

#. Matrix Trace 

    In linear algebra, the trace of an :math:`n \times n` square matrix A is defined to 
    be **the sum of the elements on the main diagonal of A.** The trace of 
    a matrix is the sum of the eigenvalues [特征值], and it is invariant with 
    respect to a change of basis. This characterization can be used to 
    define the trace of a linear operator in general. **Note** that 
    the trace is only defined for a square matrix.

    .. math::

        \begin{vmatrix}
        \underline{a_{00}} & a_{01} & a_{02} \\
        a_{10} & \underline{a_{11}} & a_{12} \\
        a_{20} & a_{21} & \underline{a_{22}} \\
        \end{vmatrix}

#. Incidence matrix
   
    In mathematics, an incidence matrix is a matrix that shows the relationship 
    between two classes of objects. If the first class is X and the second is Y, 
    the matrix has one row for each element of X and one column for each element of Y. 
    The entry in row x and column y is 1 if x and y are related (called incident in this context) 
    and 0 if they are not. There are variants: 

    In graph theory an undirected graph has two kinds of incidence matrices: unoriented and oriented.

    The unoriented incidence matrix (or simply incidence matrix) of an undirected graph is a :math:`n \times m` matrix B, 
    where n and m are the numbers of vertices and edges respectively, such that `B[i,j] = 1` if the vertex :math:`v_i` 
    and edge :math:`e_j` are incident and 0 otherwise. For example the incidence matrix of the undirected graph is

    .. figure:: images/labeled_undirected_graph.svg 

        An undirected graph

    .. math::

        \begin{pmatrix}
        1 & 1 & & 1 & 0 \\
        1 & 0 & & 0 & 0 \\
        0 & 1 & & 0 & 1 \\
        0 & 0 & & 1 & 1 \\
        \end{pmatrix}

    If we look at the incidence matrix, we see that the sum of each column is equal to 2. 
    This is because each edge has a vertex connected to each end.

    The incidence matrix of a directed graph is a :math:`n \times m` matrix B, where n and m are the numbers 
    of vertices and edges respectively, such that `B[i,j] = -1` if the edge :math:`e_j` leaves vertex :math:`v_i`, 
    1 if enters vertex vertex :math:`v_i`, and 0 otherwise.

#. Matroid vs Greedoid
    
    In combinatorics, a branch of mathematics, a matroid is a structure that captures 
    and generalizes the notion of linear independence in vector spaces. There are many 
    equivalent ways to define a matroid, the most significant being in terms of independent 
    sets, bases, circuits, closed sets or flats, closure operators, and rank functions.

    In combinatorics, a greedoid is a type of set system. It arises from the notion of the matroid, 
    which was originally introduced by *Whitney* in 1935 to study *planar graphs* and was later used 
    by *Edmonds* to characterize a class of optimization problems that can be solved by ``greedy algorithms``.

#. Convex function
   
    In mathematics, a real-valued function defined on an n-dimensional interval is called convex 
    (or convex downward or concave upward) if the line segment between any two points on the graph 
    of the function lies above or on the graph. Equivalently, a function is convex if its epigraph 
    (the set of points on or above the graph of the function) is a convex set. For a twice differentiable
    function of a single variable, if the second derivative is always greater than or equal to zero for its 
    entire domain then the function is convex. Well-known examples of convex functions include the quadratic 
    function :math:`x^2` and the exponential function :math:`e^x`.

#. Softmax function
   
    In mathematics, the softmax function, also known as softargmax or normalized exponential function,
    is a function that takes as input a vector of K real numbers, and normalizes it into a probability
    distribution consisting of K probabilities. That is, prior to applying softmax, some vector components
    could be negative, or greater than one; and might not sum to 1; but after applying softmax, each component
    will be in the interval (0, 1), and the components will add up to 1, so that they can be interpreted as probabilities.

#. Sigmoid function
   
    A sigmoid function is a mathematical function having a characteristic "S"-shaped curve or sigmoid curve.

#. Codomain: a set that includes all the possible values of a given function.