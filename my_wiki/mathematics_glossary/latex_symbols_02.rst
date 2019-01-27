********************
Latex Symbol Note 02
********************

#. Radical signs
   
    Radical signs Use sqrt, which adjusts to the size of its argument: 
    \sqrt{x^3} --> :math:`\sqrt{x^3};`
    \sqrt[3]{\frac xy} --> :math:`\sqrt[3]{\frac xy}.`
    For complicated expressions, consider using ``{...}^{1/2}`` instead.

#. limit
   
    Some special functions such as "lim", "sin", "max", "ln", and so on are normally 
    set in roman font instead of italic font. Use ``\lim, \sin,`` etc. to make these: 
    \sin x  --> :math:`\sin x.` Use subscripts to attach a notation to \lim: 
    \lim_{x \to 0} --> :math:`\lim \limits_{x \to 0}`

#. degree and radian
   
    An acute angle is less than :math:`90^\circ`.
    An right angle is exactly :math:`90^\circ`.
    An obtuse angle is between :math:`90^\circ` and :math:`180^\circ`.

#. dot sign
   
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

#. underline and overline
   
    | \overline: :math:`\overline{A}`
    | \underline: :math:`\underline{B}`
    | \overbrace: :math:`\overbrace{(n-2) + \overbrace{(n-1) + n + (n+1)} + (n+2)}`
    | \underbrace: :math:`\underbrace{(n-2) + \underbrace{(n-1) + n + (n+1)} + (n+2)}`

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

#. bracket and parenthesis

#. matrix
   
