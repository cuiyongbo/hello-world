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
