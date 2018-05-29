********************************
Probability and Statistics Terms
********************************

mean, median and mode
=====================

.. sidebar:: Mean, media and mode

   .. image:: images/Comparison_mean_median_mode.svg

   Comparison of the arithmetic mean, median and mode 
   of two skewed (log-normal) distributions.

   .. image:: images/Visualisation_mode_median_mean.svg

   Geometric visualisation of the mode, median and mean 
   of an arbitrary probability density function.

Comparison of the arithmetic mean, median and mode 
of two skewed (log-normal) distributions.

Geometric visualisation of the mode, median and mean 
of an arbitrary probability density function. In 
descriptive statistics, the mean may be confused with 
the median, mode or mid-range, as any of these may be 
called an "average" (more formally, a measure of central 
tendency). The mean of a set of observations is the arithmetic 
average of the values; however, for skewed distributions, the 
mean is not necessarily the same as the middle value (median), 
or the most likely value (mode). For example, mean income is 
typically skewed upwards by a small number of people with very 
large incomes, so that the majority have an income lower than the mean. 
By contrast, the median income is the level at which half the population 
is below and half is above. The mode income is the most likely income, 
and favors the larger number of people with lower incomes. While the median 
and mode are often more intuitive measures for such skewed data, many skewed 
distributions are in fact best described by their mean, including the exponential 
and Poisson distributions.


Mean of a probability distribution
==================================

The mean of a probability distribution is the long-run arithmetic average value 
of a random variable having that distribution. In this context, it is also known 
as the expected value. For a discrete probability distribution, the mean is given by 
:math:`{\displaystyle \textstyle \sum xP(x),}` where the sum is taken over all possible 
values of the random variable and *P(x)* is the **probability mass function**. For a 
continuous distribution,the mean is :math:`{\textstyle \int_{-\infty}^{\infty}xf(x)\,dx}`,  
where *f(x)* is the **probability density function**. In all cases, including those in 
which the distribution is neither discrete nor continuous, the mean is the Lebesgue integral 
of the random variable with respect to its probability measure. The mean need not exist or 
be finite; for some probability distributions the mean is infinite :math:`(+\infty\ or\ -\infty)`, 
while others have no mean.


Probability density function
============================

.. sidebar:: PDF Example

   .. image:: images/Boxplot_vs_PDF.svg
   
   Boxplot and probability density function of 
   a normal distribution :math:`N(0, {\sigma}^2)`.

In probability theory, a :abbr:`PDF (probability density function)`, or density 
of a continuous random variable, is a function, whose value at any given sample 
(or point) in the sample space (the set of possible values taken by the random 
variable) can be interpreted as providing a relative likelihood that the value 
of the random variable would equal that sample. In other words, while the absolute 
likelihood for a continuous random variable to take on any particular value is 0 
(since there are an infinite set of possible values to begin with), the value of 
the PDF at two different samples can be used to infer, in any particular draw 
of the random variable, how much more likely it is that the random variable would 
equal one sample compared to the other sample.

In a more precise sense, the PDF is used to specify the probability of the random 
variable falling within a particular range of values, as opposed to taking on any 
one value. This probability is given by the integral of this variable’s PDF over 
that range—that is, it is given by the area under the PDF but above the horizontal 
axis and between the lowest and greatest values of the range. The PDF is non-negative 
everywhere, and its integral over the entire space is equal to one.

The terms "probability distribution function" and "probability function" have also sometimes 
been used to denote the PDF. However, this use is not standard among probabilists and statisticians. 
In other sources, "probability distribution function" may be used when the probability distribution 
is defined as a function over general sets of values, or it may refer to the cumulative distribution 
function, or it may be a :abbr:`PMF (probability mass function)` rather than the density. 
"Density function" itself is also used for the probability mass function, leading to further confusion. 

In general though, the PMF is used in the context of discrete random variables (random variables that 
take values on a discrete set), while PDF is used in the context of continuous random variables.
