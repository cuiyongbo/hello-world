**********************
Binominal Distribution
**********************

Introduction
============

=================================================  =================================================
Probability mass function                          Cumulative distribution function                 
=================================================  =================================================
.. image:: images/Binomial_distribution_pmf.svg    .. image:: images/Binomial_distribution_cdf.svg  
=================================================  =================================================

============  ===============================================================================================================
Property      Mathematic Notation                                                                                            
============  ===============================================================================================================
Notation      :math:`B(n, p)`                                                                                                
Parameters    :math:`n \in N_0` — number of trial, :math:`p \in [0,1]` — success probability in each trial                   
PMF           :math:`{\displaystyle \textstyle {n \choose k}\,p^{k}(1-p)^{n-k}} \textstyle {n \choose k}\,p^{k}(1-p)^{n-k}`  
CDF           :math:`{\displaystyle \textstyle I_{1-p}(n-k,1+k)} \textstyle I_{1-p}(n-k,1+k)`                                
Mean          :math:`{\displaystyle np}`                                                                                     
Variance      :math:`{\displaystyle np(1-p)}`                                                                                
============  ===============================================================================================================

In probability theory and statistics, the binomial distribution with parameters *n* and *p* 
is the discrete probability distribution of the number of successes in a sequence of *n* 
independent experiments, each asking a yes–no question, and each with its own boolean-valued 
outcome: a random variable containing a single bit of information: success/yes/true/one (with 
probability *p*) or failure/no/false/zero (with probability *q = 1 − p*). A single success/failure 
experiment is also called a **Bernoulli trial** or **Bernoulli experiment** and a sequence of outcomes 
is called a **Bernoulli process**; for a single trial, i.e., *n = 1*, the binomial distribution is a 
**Bernoulli distribution**. The binomial distribution is the basis for the popular binomial test of 
statistical significance.

The binomial distribution is frequently used to model the number of successes in a sample of size *n* 
drawn with replacement from a population of size *N*. If the sampling is carried out without replacement, 
the draws are not independent and so the resulting distribution is a **hypergeometric distribution**, not 
a binomial one. However, for *N* much larger than *n*, the binomial distribution remains a good approximation, 
and is widely used.


Specification
=============

Probability mass function
-------------------------

In general, if the random variable *X* follows the binomial distribution with parameters :math:`n \in N` 
and :math:`p \in [0,1]`, we write :math:`X \sim \mathrm {B}(n, p).` The probability of getting exactly *k* successes 
in *n* trials is given by the probability mass function:

.. math::

   {\displaystyle Pr(k;n,p)=\Pr(X=k)={n \choose k}p^{k}(1-p)^{n-k}} 

for :math:`k = 0, 1, 2, ..., n`, where

.. math::

   {\displaystyle {\binom {n}{k}}={\frac {n!}{k!(n-k)!}}} 


is the *binomial coefficient*, hence the name of the distribution. The formula can be understood as follows. 
*k* successes occur with probability *pk* and *n − k* failures occur with probability *(1 − p)n − k*. However, 
the *k* successes can occur anywhere among the *n* trials, and there are :math:`{\displaystyle {n \choose k}}` 
different ways of distributing *k* successes in a sequence of *n* trials.

In creating reference tables for binomial distribution probability, usually the table is filled in up to *n/2* 
values. This is because for :math:`k > n/2`, the probability can be calculated by its complement as

.. math::

   {\displaystyle f(k,n,p)=f(n-k,n,1-p).}

Looking at the expression *ƒ(k, n, p)* as a function of *k*, there is a *k* value that maximizes it. This *k* 
value can be found by calculating

.. math::

   {\displaystyle {\frac {f(k+1,n,p)}{f(k,n,p)}}={\frac {(n-k)p}{(k+1)(1-p)}}}

and comparing it to 1. There is always an integer *M* that satisfies

.. math::

   {\displaystyle (n+1)p-1 \leq M < (n+1)p.}

*ƒ(k, n, p)* is monotone increasing for :math:`k < M` and monotone decreasing for :math:`k > M`, with the exception 
of the case where *(n + 1)p* is an integer. In this case, there are two values for which *ƒ* is maximal: *(n + 1)p* 
and *(n + 1)p − 1*. *M* is the most probable (most likely) outcome of the Bernoulli trials and is called the **mode**. 
Note that the probability of it occurring can be fairly small.

Cumulative distribution function
--------------------------------

The cumulative distribution function can be expressed as:

.. math::

   F(k;n,p) = \Pr(X\leq k) = \sum_{i=0}^{\lfloor k\rfloor } {n \choose i} p^{i}(1-p)^{n-i}

where :math:`{\displaystyle \scriptstyle \lfloor k\rfloor \,}` is the "floor" under k, i.e. the greatest 
integer less than or equal to k.

It can also be represented in terms of the regularized incomplete beta function, as follows:

.. math::

   \begin{aligned}
      F(k;n,p) &= \Pr(X\leq k) \\
      &= I_{1-p} (n-k,k+1) \\
      &= (n-k){n \choose k} \int_{0}^{1-p} t^{n-k-1} (1-t)^{k}\, dt.
   \end{aligned}

Some closed-form bounds for the cumulative distribution function are given below.


Example
=======

Suppose a biased coin comes up heads with probability 0.3 when tossed. 
What is the probability of achieving 0, 1,..., 6 heads after six tosses?

.. math::

   \Pr(0{\text{ heads}}) = f(0) = \Pr(X=0) = {6 \choose 0}0.3^{0}(1-0.3)^{6-0} = 0.117649 \\
   \Pr(1{\text{ heads}}) = f(1) = \Pr(X=1) = {6 \choose 1}0.3^{1}(1-0.3)^{6-1} = 0.302526 \\ 
   \Pr(2{\text{ heads}}) = f(2) = \Pr(X=2) = {6 \choose 2}0.3^{2}(1-0.3)^{6-2} = 0.324135 \\ 
   \Pr(3{\text{ heads}}) = f(3) = \Pr(X=3) = {6 \choose 3}0.3^{3}(1-0.3)^{6-3} = 0.185220 \\ 
   \Pr(4{\text{ heads}}) = f(4) = \Pr(X=4) = {6 \choose 4}0.3^{4}(1-0.3)^{6-4} = 0.059535 \\ 
   \Pr(5{\text{ heads}}) = f(5) = \Pr(X=5) = {6 \choose 5}0.3^{5}(1-0.3)^{6-5} = 0.010206 \\ 
   \Pr(6{\text{ heads}}) = f(6) = \Pr(X=6) = {6 \choose 6}0.3^{6}(1-0.3)^{6-6} = 0.000729 \\ 


Mean
====

If :math:`X \sim \mathrm {B}(n, p)`, that is, *X* is a binomially distributed random variable, 
*n* being the total number of experiments and *p* the probability of each experiment 
yielding a successful result, then the expected value of *X* is:

.. math::

   {\displaystyle \operatorname {E}[X]=np.}

For example, if n = 100, and p = 1/4, then the average number of successful results will be 25.

**Proof**: We calculate the mean, :math:`\mu`, directly calculated from its definition

.. math::

   {\displaystyle \mu =\sum_{i=0}^{n}x_{i}p_{i},}

and the **binomial theorem**:

.. math::

   {\begin{aligned}
      \mu &= \sum_{k=0}^{n} k{\binom {n}{k}} p^{k}(1-p)^{n-k} \\
          &= np \sum_{k=0}^{n} k{\frac {(n-1)!}{(n-k)!k!}} p^{k-1}(1-p)^{(n-1)-(k-1)} \\
          &= np \sum_{k=1}^{n} {\frac {(n-1)!}{((n-1)-(k-1))!(k-1)!}} p^{k-1}(1-p)^{(n-1)-(k-1)} \\
          &= np \sum_{k=1}^{n} {\binom {n-1}{k-1}} p^{k-1}(1-p)^{(n-1)-(k-1)} \\
          &= np \sum_{\ell =0}^{n-1} {\binom {n-1}{\ell}} p^{\ell}(1-p)^{(n-1)-\ell} && {\text{with }} \ell :=k-1 \\
          &= np \sum_{\ell =0}^{m} {\binom {m}{\ell}} p^{\ell}(1-p)^{m-\ell} && {\text{with }} m:=n-1 \\
          &= np (p+(1-p))^{m} \\
          &= np
   \end{aligned}}

It is also possible to deduce the mean from the equation :math:`X = X_{1} + \cdots +X_{n}` 
whereby all :math:`X_{i}` are Bernoulli distributed random variables with :math:`E[X_{i}]=p` 
( :math:`X_{i}=1` if the i experiment succeed and :math:`X_{i}=0` otherwise ). We get: 

.. math::

   E[X] = E[X_{1} + \cdots + X_{n}] = E[X_{1}] + \cdots + E[X_{n}] = \underbrace{p + \cdots + p}_{n{\text{ times}}} = np


A more deductive proof using calculus is shown below. This relies on 
defining a new function which only replaces one *p=q*, and then plugging 
*p* back in at the end to recover the binomial distribution.

.. math::

   {\begin{aligned}
      E[X=i] = A(q) = \sum_{i=0}^{n} i{\binom {n}{i}}(1-p)^{n-i}q^{i} \\ 
      {\frac{A(q)}{q}} = \sum_{i=0}^{n} i{\binom {n}{i}}(1-p)^{n-i}q^{i-1} \\
      \int{\frac{A(q)}{q}}dq = C + \sum_{i=0}^{n} {\binom {n}{i}}(1-p)^{n-i}q^{i} \\ 
      = (q+(1-p))^{n} + C \\ 
      {\frac{d}{dq}} \int{\frac{A(q)}{q}}dq = {\frac{d}{dq}}((q+(1-p))^{n}+C) \\ 
      {\frac{A(q)}{q}} = n(q+(1-p))^{n-1} \\ 
      q=p \\ 
      {\frac{A(p)}{p}}=n \\ 
      E[X=i] = A(p) =np
   \end{aligned}}


Variance
========

The variance is:

.. math::

   {\displaystyle \operatorname {Var}(X)=np(1-p).}

**Proof:** Let :math:`{\displaystyle X=X_1 + \cdots + X_n}` where all 
:math:`X_i` are independently Bernoulli distributed random variables. Since 
:math:`{\displaystyle \operatorname {Var}(X_i) = p(1-p)}`, we get:

.. math::

   {\displaystyle 
      \operatorname {Var}(X) = \operatorname {Var}(X_{1} + \cdots +X_{n}) 
      = \operatorname {Var}(X_{1})+ \cdots + \operatorname {Var}(X_{n}) 
      = n\operatorname {Var}(X_{1})
      = np(1-p).
   }

Another proof, in the same vein as the section on the Mean, can be done using calculus. 
Keep in mind that all the functions integrated below are zero at zero, but the binomial 
distribution is: :math:`{\displaystyle B(q=0)=0}` as defined below.

.. math::

   {\begin{aligned}
      \operatorname {Var}(X) = E[X^2]-(E[X])^2 =E[X^2]-(np)^2 \\ 
      E[X^2=i^2] = B(q) =\sum_{i=0}^{n}i^{2}{\binom {n}{i}}(1-p)^{n-i}q^{i} \\
      {\frac{B(q)}{q}} = \sum_{i=0}^{n}i^{2}{\binom {n}{i}}(1-p)^{n-i}q^{i-1} \\
      A(q) = \int_{0}^{q}{\frac{B(q)}{q}}dq = \sum_{i=0}^{n}i{\binom {n}{i}}(1-p)^{n-i}q^{i} \\
      {\frac{A(q)}{q}} = \sum_{i=0}^{n}i{\binom {n}{i}}(1-p)^{n-i}q^{i-1} \\
      \int_{0}^{q}{\frac{A(q)}{q}}dq = \sum_{i=0}^{n}{\binom {n}{i}}(1-p)^{n-i}q^{i} \\
      \int_{0}^{q}{\frac{A(q)}{q}}dq = (q+(1-p))^{n} \\
   \end{aligned}}

Now let's backtrack to :math:`{\displaystyle B(q)}`. We have to solve the following for 

.. math::

   {\begin{aligned}
      \int_{0}^{q}{\frac{1}{q}}(\int_{0}^{q}{\frac{B(q)}{q}}dq)dq = (q+(1-p))^{n} \\
   \end{aligned}}

We can just use the operation: :math:`q{\frac{d}{dq}}q{\frac{d}{dq}}`. This will undo 
all of the steps we have done.

.. math::

   {\begin{aligned}
      B(q) &= q{\frac{d}{dq}}q{\frac{d}{dq}}((q+(1-p))^{n}) \\ 
           &= q{\frac {d}{dq}}(qn(q+(1-p))^{n-1}) \\
           &= q(n(q+(1-p))^{n-1}+qn(n-1)(q+(1-p))^{n-2}) \\
           &= qn(q+(1-p))^{n-1}+q^{2}n(n-1)(q+(1-p))^{n-2} \\
           &= pn+p^{2}n(n-1) \\
   \end{aligned}}

   \operatorname {Var}(X) = B(p)-(np)^{2} = pn+p^{2}n^{2}-np^{2}-(np)^{2} = pn-np^{2} \\
   \operatorname {Var}(X) = np(1-p) \\


Covariance between two binomials
================================

If two binomially distributed random variables *X* and *Y* are observed together, 
estimating their covariance can be useful. The covariance is

.. math::

   {\displaystyle \operatorname{Cov}(X,Y) = \operatorname {E}(XY) - \mu_{X}\mu_{Y}.}

In the case *n = 1* (the case of Bernoulli trials) *XY* is non-zero only when both *X* 
and *Y* are one, and :math:`\mu_X` and :math:`\mu_Y` are equal to the two probabilities.
Defining :math:`p_B` as the probability of both happening at the same time, this gives
:math:`{\displaystyle \operatorname {Cov}(X,Y) = p_{B}-p_{X}p_{Y},}` and for *n* independent 
pairwise trials. If *X* and *Y* are the same variable, this reduces to the variance formula 
given above.


Related distributions
=====================

Poisson approximation
---------------------

The binomial distribution converges towards the Poisson distribution as the number of trials 
goes to infinity while the product *np* remains fixed or at least *p* tends to zero. Therefore, 
the Poisson distribution with parameter *λ = np* can be used as an approximation to **B(n, p)** 
of the binomial distribution if *n* is sufficiently large and *p* is sufficiently small. 
According to two rules of thumb, this approximation is good if :math:`n \ge 20` and :math:`p \le 0.05`, 
or if :math:`n \ge 100` and :math:`np \le 10`.


History
=======

This distribution was derived by **James Bernoulli**. He considered the case where *p = r/(r+s)* 
where *p* is the probability of success and *r* and *s* are positive integers. **Blaise Pascal** 
had earlier considered the case where **p = 1/2**.
