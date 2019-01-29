***************************
K Nearest Neighbours Method
***************************

.. function:: sklearn.neighbors.classification.KNeighborsClassifier.fit(X, y) 

    Fit the model using X as training data and y as target values.

.. function:: sklearn.neighbors.classification.KNeighborsClassifier.predict(X)

    Predict the class labels for the provided data.

.. function:: sklearn.neighbors.classification.KNeighborsClassifier.predict_proba(X)

    Return probability estimates for the test data X.

.. code-block:: py

    >>> from sklearn import neighbors
    >>> knn = neighbors.KNeighborsClassifier(n_neighbors=2)
    >>> print(knn)
    KNeighborsClassifier(algorithm='auto', leaf_size=30, metric='minkowski',
               metric_params=None, n_jobs=None, n_neighbors=2, p=2,
               weights='uniform')
    >>> knn.fit([[1], [2], [3], [4], [5], [6]], [0,0,0,1,1,1])
    KNeighborsClassifier(algorithm='auto', leaf_size=30, metric='minkowski',
               metric_params=None, n_jobs=None, n_neighbors=2, p=2,
               weights='uniform')
    >>> knn.predict([[1.5]])
    array([0])
    >>> knn.predict([[37]])
    array([1])
    >>> knn.predict([[3]])
    array([0])
    >>> knn.predict_proba([[1.5]])
    array([[1., 0.]])
    >>> knn.predict_proba([[37]])
    array([[0., 1.]])
    >>> knn.predict_proba([[3.5]])
    array([[0.5, 0.5]])

    code_match = re.compile('<pre>(.*?)</pre>', re.MULTILINE|re.DOTALL)
    link_match = re.compile('<a href="http://.*?".*?>(.*?)</a>', re.MULTILINE|re.DOTALL)
    
    def extract_features_from_body(s):
        link_count_in_code = 0
        for match_str in code_match.findall(s):
            link_count_in_code += len(link_match.findall(match_str))
        return len(link_match.findall(s)) - link_count_in_code