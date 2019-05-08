***************************
Machine Learning algorithms
***************************

A computer program is said to learn from **experience** E with respect 
to some class of **tasks** T and **performance measure** P if its performance 
at tasks in T, as measured by P, improves with experience E.

-- Tom Mitchell

.. code-block:: none
    :caption: K fold cross-validation 

    KFoldXV(D, A, L, k):
        Require: D, the given dataset, with elements z_i
        Require: A, the learning algorithm, seen as a function that takes D as input and outputs a learned function
        Require: L, the loss function, seen as a function from f and z_i to a scalar R 
        Require: k, the number of folds

        Split D into k mutually exclusive subsets D_i. 
        for i = 1 to k
            f_i = A(D, i) 
            for z_j in D_i
                e_j =L(f_i, z_j)
            end for 
        end for
        return e

.. code-block:: none
    :caption: :abbr:`SGD (Stochastic Gradient Descent)` update at training iteration k

    Require: Learning rate k. 
    Require: Initial parameter theta
    while stopping criterion not met
        Sample a minibatch of m examples from the training set x_i with corresponding targets y_i 
        Compute gradient estimate: g = 1/m * LossFunc(derivative(f(x_i, theta)), y_i)
        Apply update: θ =  θ − k * g
    end while

.. code-block:: none
    :caption: :abbr:`SGD (Stochastic Gradient Descent)` with momentum

    Require: Learning rate k, momentum parameter alpha
    Require: Initial parameter theta, initial velocity v
    while stopping criterion not met
        Sample a minibatch of m examples from the training set x_i with corresponding targets y_i
        Compute gradient estimate: g = 1/m * LossFunc(derivative(f(x_i, theta)), y_i)
        Compute velocity update: v = alpha * v − k * g
        Apply update: θ =  θ + v
    end while

.. code-block:: none
    :caption: :abbr:`SGD (Stochastic Gradient Descent)` with Nesterov momentum

    Require: Learning rate k, momentum parameter alpha
    Require: Initial parameter theta, initial velocity v
    while stopping criterion not met
        Sample a minibatch of m examples from the training set x_i with corresponding targets y_i
        Apply interim update: θ = θ + alpha * v
        Compute gradient estimate: g = 1/m * LossFunc(derivative(f(x_i, theta)), y_i)
        Compute velocity update: v = alpha * v − k * g
        Apply update: θ =  θ + v
    end while


#. Algorithm 8.4 The AdaGrad algorithm P308
#. Algorithm 8.5 The RMSProp algorithm P309
#. Algorithm 8.6 RMSProp algorithm with Nesterov momentum P310
#. Algorithm 8.7 The Adam algorithm P311
   
.. code-block:: py
    :caption: Gradient Descent algorithm 

    def update_w_and_b(spendings, sales, w, b, alpha):
        dl_dw = 0.0
        dl_db = 0.0
        N = len(spending)
    
        for i in range(N):
            dl_dw += -2*spendings[i]*(sales[i] - (w*spendings[i] + b))
            dl_db += -2*(sales[i] - (w*spendings[i] + b))
    
        w = w - (1/float(N))*dl_dw*alpha
        b = b - (1/float(N))*dl_db*alpha
        return w, b
    
    def train(spendings, sales, w, b, alpha, epochs):
        for e in range(epochs):
            w, b = update_w_and_b(spendings, sales, w, b, alpha)
            if (e+1)%400 == 0:
                print('epoch: ', e, 'loss: ', avg_loss(spendings, sales, w, b))
        return w, b
    
    def avg_loss(spendings, sales, w, b):
        N = len(spendings)
        total_error = 0.0
        for i in range(N):
            total_error += (sales[i] = (w*spendings[i] + b))
        return total_error/float(N)

    def predict(x, w, b):
        return w*x + b

    w, b = train(x, y, 0.0, 0.0, 0.001, 150000)
    x_new = 23.0
    y_new = predict(x_new, w, b)
    print(y_new)