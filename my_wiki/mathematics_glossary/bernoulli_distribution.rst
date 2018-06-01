**********************
Bernoulli Distribution
**********************

In probability theory and statistics, the Bernoulli distribution, 
named after Swiss mathematician **Jacob Bernoulli**, is the probability 
distribution of a random variable which takes the value 1 with probability 
*p* and the value 0 with probability *q = 1-p*, that is, the probability 
distribution of any single experiment that asks a yes–no question; the question 
results in a boolean-valued outcome, a single bit of information whose value is 
success/yes/true/one with probability *p* and failure/no/false/zero with probability *q*. 
It can be used to represent a coin toss where 1 and 0 would represent "head" and "tail" 
(or vice versa), respectively. In particular, unfair coins would have :math:`p\neq 0.5.`

The Bernoulli distribution is a special case of the **binomial distribution** where 
a single experiment/trial is conducted (*n = 1*). It is also a special case of the 
two-point distribution, for which the outcome need not be a bit, i.e., the two possible 
outcomes need not be 0 and 1.


Properties of the Bernoulli distribution
========================================

If X is a random variable with this distribution, we have:

.. math::

   Pr(X=1) = p = 1 - Pr(X=0) = 1-q

The probability mass function *f* of this distribution, over 
possible outcomes *k*, is

.. math::

   f(k; p) = {\begin{cases} p&{\text{if } k=1,}\\1-p&{\text{if }}k=0. \end{cases}}

This can also be expressed as

.. math::

   f(k; p) = p^k (1-p)^{1-k} {\text{ for }} k \in \{0,1\}

The Bernoulli distribution is a special case of the binomial distribution with *n=1*.
The **kurtosis** goes to infinity for high and low values of *p*, but for *p=1/2* the 
two-point distributions including the Bernoulli distribution have a lower excess kurtosis 
than any other probability distribution, namely −2.

The Bernoulli distributions for  :math:`0 \leq p \leq 1` form an exponential family.
The maximum likelihood estimator of *p* based on a random sample is the sample mean.


Mean
====

The expected value of a Bernoulli random variable X is

.. math::

   {\operatorname {E}[X] = p}

Deduction as Following:

.. math::

   {\Pr(X=1)=p} \\
   {\Pr(X=0)=q} \\
   {\operatorname {E}[X] = \Pr(X=1) \cdot 1 + \Pr(X=0) \cdot 0 = p \cdot 1+ q \cdot 0 = p} 


Variance
========

The variance of a Bernoulli distributed X is

.. math::

   {\operatorname {Var}[X] = pq = p(1-p)}

Deduction as Following:

.. math::

   \operatorname {E}[X^{2}] = \Pr(X=1) \cdot 1^{2} + \Pr(X=0) \cdot 0^{2} 
                                       = p \cdot 1^{2} + q \cdot 0^{2} = p \\

   \operatorname {Var}[X]= \operatorname {E}[X^{2}]- \operatorname {E}[X]^{2}
                         = p - p^{2} = p(1-p) = pq



Related distributions
=====================

If :math:{ X_1, \dots ,X_n} are independent, identically distributed (i.i.d.) random variables, 
all Bernoulli distributed with success probability *p*, then

.. math::

   { Y=\sum_{k=1}^{n} X_{k} \sim \mathrm {B}(n,p)} {\text{ (binomial distribution)}}.

The Bernoulli distribution is simply :math:`\mathrm {B}(1,p)`.