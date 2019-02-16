********************
Latex Symbol Note 02
********************

#. Radical signs
   
    Radical signs use sqrt, which adjusts to the size of its argument: 
    \sqrt{x^3} --> :math:`\sqrt{x^3};`
    \sqrt[3]{\frac xy} --> :math:`\sqrt[3]{\frac xy}.`
    For complicated expressions, consider using ``{...}^{1/2}`` instead.

#. Sum and integrals
   
    ``\sum`` and ``\int``; the subscript is the lower limit and the superscript is the upper limit, 
    so for example :math:`\sum_1^n`. Don't forget ``{}`` if the limits are more than a single symbol. 
    For example, :math:`\sum_{i=0}^\infty i^2`. Similarly, ``\prod`` :math:`\prod`, ``\int`` :math:`\int`,
    ``\bigcup`` math:`\bigcup`, ``\bigcap`` :math:`\bigcap`, ``\iint`` :math:`\iint`, ``\iiint`` :math:`\iiint`,
    ``idotsint`` :math:`\idotsint`.

#. Limit
   
    Some special functions such as "lim", "sin", "max", "ln", and so on are normally 
    set in roman font instead of italic font. Use ``\lim, \sin,`` etc. to make these: 
    \sin x  --> :math:`\sin x.` Use subscripts to attach a notation to \lim: 
    \lim_{x \to 0} --> :math:`\lim \limits_{x \to 0}`

#. Degree and radian
   
    An acute angle is less than :math:`90^\circ`.
    An right angle is exactly :math:`90^\circ`.
    An obtuse angle is between :math:`90^\circ` and :math:`180^\circ`.

#. Dot sign
   
    ``\cdot`` is a centered dot: :math:`x \cdot y` while ``\dot``, ``\ddot`` is used 
    in deriatives: :math:`\dot x \ddot x`. 

    ``\ldots`` is the dots in :math:`a_1,a_2, \ldots ,a_n`. 
    ``\cdots`` is the dots in :math:`a_1+a_2+ \cdots +a_n`. 

#. Arbitrary operators

    If an operator is not available as a built-in command, use ``\operatorname{…}.`` 
    So for things like :math:`\operatorname{arsinh}(x)` write ``\operatorname{arsinh}(x).`` 
   
    For operators which need limits above and below the operator, use ``\operatorname*{…},`` as in 

    .. math::

        \operatorname*{Res}_{z=1}^{n} \left(\frac {1}{z^2-1}\right) = 1

#. Underline and overline
   
    | ``\overline``: :math:`\overline{A}`
    | ``\underline``: :math:`\underline{B}`
    | ``\overbrace``: :math:`\overbrace{(n-2) + \overbrace{(n-1) + n + (n+1)} + (n+2)}`
    | ``\underbrace``: :math:`\underbrace{(n-2) + \underbrace{(n-1) + n + (n+1)} + (n+2)}`
    | ``\underleftarrow``: :math:`\underleftarrow{E}` variant: ``\xleftarrow`` :math:`\xleftarrow{abc}`
    | ``\underrightarrow``: :math:`\underrightarrow{E}` variant: ``\xrightarrow`` :math:`\xrightarrow{abc}`
    | ``\underleftrightarrow``: :math:`\underleftrightarrow{AA}`

    To annotate the brace, e.g. :math:`\underbrace{a\cdot a\cdots a}_{b\text{ times}}`

    Single character accents:

        | ``\check``: :math:`\check{I}`
        | ``\acute``: :math:`\acute{J}`
        | ``\grave``: :math:`\grave{K}`
        | ``\vec``: :math:`\vec{AB}`
        | ``\bar``: :math:`\bar{z}`
        | ``\hat``: :math:`\hat{x}`
        | ``\tilde``: :math:`\tilde{x}`
        | ``\dot \ddot \dddot``: :math:`\dot{x} \ddot{x} \dddot{x}`
        | ``\mathring``: :math:`\mathring{A}` 

#. Bracket and parenthesis
   
   ``\left`` and ``\right`` apply to all the following sorts of parentheses: ``(), [], \{\}, \|`` :math:`\{x\}` :math:`|y|` , 
   ``\vert`` :math:`\vert x \vert`, ``\Vert`` :math:`\Vert x \Vert`, ``\langle`` and ``\rangle`` :math:`\langle x \rangle`, 
   \lceil and \rceil :math:`\lceil x \rceil`, and \lfloor and \rfloor :math:`\lfloor x \rfloor`.
   ``\middle`` can be used to add additional dividers. There are also invisible parentheses,
   denoted by ``.``: :math:`\left.\frac12\right\rbrace`.

   If manual size adjustments are required:
    ``\Biggl(\biggl(\Bigl(\bigl((x)\bigr)\Bigr)\biggr)\Biggr)`` 
    gives :math:`\Biggl(\biggl(\Bigl(\bigl((x)\bigr)\Bigr)\biggr)\Biggr)`

#. Matrix
   
    Use ``\begin{matrix}...\end{matrix}`` in between the ``\begin`` and ``\end``, 
    put the matrix elements, End each each matrix rou with ``\\``, and separate matrix 
    elements with ``&``. e.g.

    .. math::
    
        \begin{matrix}
        1 & x & x^2 \\
        1 & y & y^2 \\
        1 & z & z^2 \\
        \end{matrix}

    To add brackets, either use ``\left...\right``, or replace ``matrix`` with 
    ``pmatrix`` :math:`\begin{pmatrix} 1 & 2 \\ 3 & 4 \\ \end{pmatrix}`, 
    ``bmatrix`` :math:`\begin{bmatrix} 1 & 2 \\ 3 & 4 \\ \end{bmatrix}`, 
    ``Bmatrix`` :math:`\begin{Bmatrix} 1 & 2 \\ 3 & 4 \\ \end{Bmatrix}`, 
    ``vmatrix`` :math:`\begin{vmatrix} 1 & 2 \\ 3 & 4 \\ \end{vmatrix}`, 
    ``Vmatrix`` :math:`\begin{Vmatrix} 1 & 2 \\ 3 & 4 \\ \end{Vmatrix}`.

#. Fonts
   
    * Use ``\mathbb`` for "blackboard bold": :math:`\mathbb{RZ}`
    * Use ``\mathbf`` for boldface: :math:`\mathbf{abcdABCD}`
    * Use ``\mathit`` for italics: :math:`\mathit{abcdABCD}`
    * Use ``\pmb`` for boldfaced italics: :math:`\pmb{abcdABCD}`
    * Use ``\mathtt`` for typewriter font: :math:`\mathtt{abcdABCD}`
    * Use ``\mathrm`` for roman font: :math:`\mathrm{abcdABCD}`
    * Use ``\mathsf`` for sans-serif font: :math:`\mathsf{abcdABCD}`
    * Use ``\mathcal`` for "calligraphic" letters: :math:`\mathcal{abcdABCD}`
    * Use ``\mathscr`` for script letters: :math:`\mathcal{abcdABCD}`
    * Use ``\mathfrak`` for "Fraktur" (old German style) letters: :math:`\mathfrak{abcdABCD}`

#. Definition by cases
   
    Use ``\begin{cases}…\end{cases}``. End each case with a ``\\``, and use ``&`` 
    before parts that should be aligned. for example,

    .. math::

        f(n)=
        \begin{cases}
        n/2, & \text{if n is even} \\
        3n+1, & \text{if n is odd}
        \end{cases}

        f(n)=
        \begin{cases}
        \frac{n}{2}, & \text{if n is even} \\[2ex]
        3n+1, & \text{if n is odd}
        \end{cases}

        \left.
        \begin{array}{l}
        \text{if $n$ is even:}&n/2\\
        \text{if $n$ is odd:}&3n+1
        \end{array}
        \right\}
        =f(n)

    **Note**: An ‘ex’ is a length equal to the height of the letter x; 
    2ex here means the space should be two exes high.
