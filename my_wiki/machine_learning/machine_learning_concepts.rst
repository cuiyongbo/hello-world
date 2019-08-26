*************************
Machine learning concepts
*************************

#. Machine learning vs Deep learning
   
    The widely-quoted definition of **Machine learning** by **Tom Mitchell** best explains 
    machine learning in a nutshell. Here’s what it says:

    **A computer program is said to learn from experience E with respect 
    to some class of tasks T and performance measure P if its performance 
    at tasks in T, as measured by P, improves with experience E.**

    The concept of deep learning is not new. It has been around for a couple of years now. 
    But nowadays with all the hype, deep learning is getting more attention. a formal definition 
    of **Deep Learning** comes as:

    **Deep learning is a particular kind of machine learning that achieves great power 
    and flexibility by learning to represent the world as nested hierarchy of concepts, 
    with each concept defined in relation to simpler concepts, and more abstract representations 
    computed in terms of less abstract ones.**
    
#. Supervised learing vs Unsupervised learning
   
    **Unsupervised learning algorithms** experience a dataset containing many features, 
    then learn useful properties of the structure of this dataset. In the context of 
    deep learning, we usually want to learn the entire **probability distribution** that 
    generated a dataset, whether explicitly as in density estimation or implicitly 
    for tasks like synthesis or denoising. Some other unsupervised learning algorithms 
    perform other roles, like **clustering**, which consists of dividing the dataset into 
    clusters of similar examples.

    **Supervised learning algorithms** experience a dataset containing features, but each example 
    is also associated with a **label** or target. For example, the Iris dataset is annotated with 
    the species of each iris plant. A supervised learning algorithm can study the Iris dataset 
    and learn to classify iris plants into three different species based on their measurements.

    Roughly speaking, unsupervised learning involves observing several examples of a random vector x, 
    and attempting to implicitly or explicitly learn the probability distribution :math:`p(x)`, or some
    interesting properties of that distribution, while supervised learning involves observing several 
    examples of a random vector x and an associated value or vector y, and learning to predict y from x,
    usually by estimating :math:`p(y | x).` The term **supervised learning** originates from the view of the
    target y being provided by an instructor or teacher who shows the machine learning system what to do. 

    Unsupervised learning and supervised learning are not formally defined terms. 
    The lines between them are often blurred. Many machine learning technologies 
    can be used to perform both tasks. For example, the chain rule of probability states 
    that for a vector :math:`x \in \mathbb{R}^n`, the joint distribution can be decomposed as

    .. math::

        p(x) = \prod_{i=1}^n{p(x_i | x_1, \ldots, x_{i-1})}

    This decomposition means that we can solve the ostensibly unsupervised problem of
    modeling :math:`p(x)` by splitting it into n supervised learning problems.

    Alternatively, we can solve the supervised learning problem of learning :math:`p(y|x)` 
    by using traditional unsupervised learning technologies to learn the joint distribution 
    :math:`p(x,y)` and inferring

    .. math::

        p(y|x) = \frac{p(x,y)}{\sum_{y'}{p(x,y')}}

    Though unsupervised learning and supervised learning are not completely formal or distinct 
    concepts, they do help to roughly categorize some of the things we do with machine learning
    algorithms. Traditionally, people refer to **regression**, **classification** and 
    **structured output problems** as supervised learning. **Density estimation** in support 
    of other tasks is usually considered unsupervised learning.

#. Neural Network, Reinforcement Learning and Genetic Algorithms
   
    Neural Networks model a brain learning by **example**―given a set of right answers, 
    it learns the general patterns. (**Supervised Learning**) Reinforcement Learning models a brain learning by 
    **experience**―given some set of actions and an eventual reward or punishment, 
    it learns which actions are good or bad. (**Unsupervised Learning**) Genetic Algorithms model evolution by 
    **natural selection**―given some set of agents, let the better ones live and 
    the worse ones die. (alse **Unsupervised Learning**) Typically, genetic algorithms do not allow agents to learn 
    during their lifetimes, while neural networks allow agents to learn only during 
    their lifetimes. Reinforcement learning allows agents to learn during their lifetimes 
    and share knowledge with other agents.
   
#. Ground truth
   
    Ground truth is a term used in various fields to refer to information provided by direct observation
    as opposed to information provided by inference. In machine learning, the term "ground truth" refers 
    to the accuracy of the training set's classification for supervised learning techniques. 
    This is used in statistical models to prove or disprove research hypotheses.

#. Cross-entropy: a widely used metric of similarity between two probability distributions
   
    Entropy, cross entropy, and KL-divergence [#Introduction to cross entropy]_ .

.. rubric:: Footnotes

.. [#] `Introduction to cross entropy <https://rdipietro.github.io/friendly-intro-to-cross-entropy-loss/>`_
