*************************
Machine Learning Keywords
*************************

浪费机会必定会遭到惩罚。

feature example object recognition face recognition speech recognition

medical diagnosis Google Street View Transcription Machine translation

frequentist estimator and Bayesian inference

supervised learning: regression, classification

unsupervised learning: transformations of datasets, clustering

K-means clustering, vector quantization

Agglomerative clustering, Hierarchical clustering

:abbr:`DBSCAN (Density- based spatial clustering of applications with noise)`

:abbr:`ARI (Adjusted rand index)`, :abbr:`NMI (Normalized Mutual Information)`

:abbr:`SGD (stochastic gradient descent)`

Linear model, tree-based model, naive Bayes

cross validation, k-fold cross-validation, stratified k-fold cross-validation, leave-one-out crosss-validation

Grid search

False positive, False negative, True positive, True negative

imbalanced datasets, confusion matrix

By definition a confusion matrix :math:`C` is such that :math:`C_{i, j}`
is equal to the number of observations known to be in group :math:`i` but
predicted to be in group :math:`j`.
    
Thus in binary classification, the count of true negatives is
:math:`C_{0,0}`, false negatives is :math:`C_{1,0}`, true positives is
:math:`C_{1,1}` and false positives is :math:`C_{0,1}`.

:abbr:`RNN (Recurrent Neural Networks)`

Regression: In this type of task, the computer program is asked to predict a
numerical value given some input. To solve this task, the learning algorithm
is asked to output a function :math:`f : \mathbb{R}^n \rightarrow \mathbb{R}`.

Linear Regression, Logistic Regression

:abbr:`RFE (Recursive Feature Elimination)`

:abbr:`MES (mean squared error)`

test set, validation set, and training set

accuracy and error rate

precision, recall, f-score

operating point, precision-recall curve

:abbr:`ROC (Receiver Operating Characteristics)`, :abbr:`AUC (Area Under Curve)`

:abbr:`NLP (Natural Language Processing)`, :abbr:`IR (Information Retrieval)`

corpus, document

Bag of words: Tokenization, Vocabulary building, Encoding 

scarlar

Vectors: A vector is an array of numbers. The numbers are arranged in
order. We can identify each individual number by its index in that ordering.
Typically we give vectors lower case names written in bold typeface, such
as :math:`\mathbf{x}`. 

Matries: A matrix is a 2-D array of numbers, so each element is identified
by two indices instead of just one. We usually give matrices upper-case
variable names with bold typeface, such as :math:`\mathbf{A}`.

The transpose of the matrix can be thought of as a mirror image across the main diagonal.

Tensors: In some cases we will need an array with more than two axes.
In the general case, an array of numbers arranged on a regular grid with a
variable number of axes is known as a tensor. We denote a tensor named “A”
with this typeface: :math:`\mathsf{A}`. 

broadcasting

distributive: :math:`A(B+C)=AB+AC`

associative: :math:`A(BC)=(AB)C`

commutative: :math:`ab=ba`

Identity matrix: `np.eye()`

matrix inverse: :math:`\mathbf{A^{-1}A = I_n}`

norm, Euclidean norm, :math:`L^2 norm`

:abbr:`SVM (Support Vector Machine)`

Linear regression, Ridge Regression, Logistic regression

convex optimization

:abbr:`RBF (Radial Basis Function)`

Kernel method, kernel trick

:abbr:`KNN (K-Nearest Neighbors)`

decision tree

diagonal matrix symmetric matrix orthogonal matrix

unit vector

othogonal othonormal

eigendecomposition eigenvector eigenvalue

:abbr:`SVD (Singular Value Decomposition)`

:abbr:`PCA (Principal Components Analysis)`

:abbr:`NMF (Non-negative Matrix Factorization)`

Frequentist Probability  Bayesian Probability 

Conditional Probability  Intervention query

The Chain rule of Conditional Probabilty Bayesian rule

Independence and Conditional Independence

:abbr:`i.i.d (Independent and identifically distributed)`

Expectation Variance Standard deviation Covariance Correlation

underfitting overfitting

model capacity VS mode complexity

represent capacity VS effective capacity

Bayes error

:abbr:`lerp (Linear intERPolation)`

posterior distribution VS prior distribution

:abbr:`Maximum a posteriori`

maximum likelihood VS log-likelihood 

negative conditional log-likelihood

Gaussian distribution = Normal distribution

Bayesian inference

:abbr:`SGD (stochastic gradient descent)`

minibatch

Generalization error

manifold

partial derivative VS directional derivative

learnig rate 

line search

hill climbing

Jacobian matrix VS Hessian matrix

Tayler Series VS Newton's method

sencond derivative test

condition number

objective function, criterion

cost function, loss function, error function

first-order optimization algorithms VS second-order optimization algorithms

:abbr:`KKT (Karush-Kuhn-Tucker)`

Generalized Largrangian

.. math::

    \begin{align*}
    &\hat{y} = w[0] x[0] + w[1] x[1] + \dotsc + w[p] x[p] + b &\text{ (1) linear regression} 
    \end{align*}

.. math:: 

    \begin{align*}
    &\hat{y} = w[0] x[0] + w[1] x[1] + \dotsc + w[p] x[p] + b > 0 &\text{ (2) linear binary classification}
    \end{align*}

.. math:: 

    \begin{align*}
    & w[0] x[0] + w[1] x[1] + \dotsc + w[p] x[p] + b & \text{ (3) classification confidence}
    \end{align*}

.. math:: 

    \begin{align*}
    &k_\text{rbf}(x_1, x_2) = \exp(\gamma||x_1 - x_2||^2) &\text{ (4) Gaussian kernel}  \end{align*}

Accuracy

.. math::

    \begin{equation}
    \text{Accuracy} = \frac{\text{TP} + \text{TN}}{\text{TP} + \text{TN} + \text{FP} + \text{FN}}
    \end{equation}

Precision, :abbr:`PPV (Positive Predicate Value)`

.. math::

    \begin{equation}
    \text{Precision} = \frac{\text{TP}}{\text{TP} + \text{FP}} 
    \end{equation}

Recall, :abbr:`TPR (True Positive Rate)`

.. math::

    \begin{equation}
    \text{Recall} = \frac{\text{TP}}{\text{TP} + \text{FN}} 
    \end{equation}

f-score

.. math::

    \begin{equation}
    \text{F} = 2 \cdot \frac{\text{precision} \cdot \text{recall}}{\text{precision} + \text{recall}}
    \end{equation}

:abbr:`TF-IDF (Term Frequency-Inverse Document Frequency)`

.. math::

    \begin{equation*}
    \text{tfidf}(w, d) = \text{tf} \log\big(\frac{N + 1}{N_w + 1}\big) + 1 
    \end{equation*}



The probability density for the **Gaussian distribution** is

.. math:: p(x) = \frac{1}{\sqrt{ 2 \pi \sigma^2 }}
                 e^{ - \frac{ (x - \mu)^2 } {2 \sigma^2} },

where :math:`\mu` is the mean and :math:`\sigma` the standard
deviation. The square of the standard deviation, :math:`\sigma^2`,
is called the variance.

The function has its peak at the mean, and its "spread" increases with
the standard deviation (the function reaches 0.607 times its maximum at
:math:`x + \sigma` and :math:`x - \sigma`).  This implies that
`numpy.random.normal` is more likely to return samples lying close to
the mean, rather than those far away.

https://github.com/chiphuyen/stanford-tensorflow-tutorials.git