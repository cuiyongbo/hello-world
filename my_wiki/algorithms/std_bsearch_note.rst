******************
Maximum likelihood
******************

**Maximum likelihood**: Given observed training data producing :math:`\alpha_1`
total "heads," and :math:`\alpha_0` total "tails," output the estimate

.. math::

    \hat{\theta} = \frac{\alpha_1}{\alpha_1 + \alpha_0}

**Maximum a posteriori probability**: Given observed training data producing :math:`\alpha_1`
total "heads," and :math:`\alpha_0` total "tails," plus prior information expressed by
introducing :math:`\gamma_1` imaginary "heads" and :math:`\gamma_0` imaginary "tails," output the estimate

.. math::

    \hat{\theta} = \frac{\gamma_1 + \alpha_1}{(\gamma_1 + \alpha_1) + (\gamma_0 + \alpha_0)}

:abbr:`MLE (Maximum Likelihood Estimation)`

.. math::

    \hat{\theta}^{MLE} = arg \underline{max}{\theta} P(D|\theta)

:abbr:`MAP (Maximum a Posteriori Probability Estimation)`

.. math::

    \hat{\theta}^{MAP} = arg \underline{max}{\theta} P(\theta|D)