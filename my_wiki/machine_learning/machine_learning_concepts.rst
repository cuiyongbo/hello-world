*************************
Machine learning concepts
*************************

#. Machine learning vs Deep learning

    The widely-quoted definition of **Machine learning** by **Tom Mitchell** best explains
    machine learning in a nutshell. Here’s what it says:

    **A computer program is said to learn from experience E with respect
    to some class of tasks T and performance measure P if its performance
    at tasks in T, as measured by P, improves with experience E.**

    The concept of deep learning is not new. It has been around for a couple of years.
    But nowadays with all the hype, deep learning is getting more attention. a formal definition
    of **Deep Learning** comes as:

    **Deep learning is a particular kind of machine learning that achieves great power
    and flexibility by learning to represent the world as nested hierarchy of concepts,
    with each concept defined in relation to simpler concepts, and more abstract representations
    computed in terms of less abstract ones.**

#. Machine learning types

    - Supervised learning
    - Unsupervised learning
    - Semi-supervised learning

#. Neural Network, Reinforcement Learning and Genetic Algorithms

    Neural Networks model a brain learning by **example**―given a set of right answers,
    it learns the general patterns(**Supervised Learning**).
    Reinforcement Learning models a brain learning by **experience**―given some set of
    actions and an eventual reward or punishment, it learns which actions are good or
    bad(**Unsupervised Learning**).
    Genetic Algorithms models evolution by **natural selection**―given some set of agents,
    let the better ones live and the worse ones die(also **Unsupervised Learning**).

    Typically, genetic algorithms do not allow agents to learn during their lifetimes,
    while neural networks allow agents to learn only during their lifetimes.
    Reinforcement learning allows agents to learn during their lifetimes
    and share knowledge with other agents.

#. Cross-entropy: a metric of similarity between two probability distributions
#. Entropy, cross entropy, and KL-divergence `Introduction to cross entropy`_ .

#. Building Blocks of a ML algorithm

    - a loss function
    - an optimization criterion based on the loss function
    - an optimization routine that leverages training data to find a solution to the optimization criterion

.. rubric:: Footnotes

.. [#] `Introduction to cross entropy <https://rdipietro.github.io/friendly-intro-to-cross-entropy-loss/>`_
