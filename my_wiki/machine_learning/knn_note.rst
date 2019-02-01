***************************
K Nearest Neighbours Method
***************************

.. function:: sklearn.neighbors.classification.KNeighborsClassifier.fit(X, y) 

    Fit the model using X as training data and y as target values.

.. function:: sklearn.neighbors.classification.KNeighborsClassifier.predict(X)

    Predict the class labels for the provided data.

.. function:: sklearn.neighbors.classification.KNeighborsClassifier.predict_proba(X)

    Return probability estimates for the test data X.

.. function:: sklearn.neighbors.classification.KNeighborsClassifier.score(X, y, sample_weight=None) 

    Returns the mean accuracy on the given test data and labels.

    Parameters::

        X : array-like, shape = (n_samples, n_features)
            Test samples.

        y : array-like, shape = (n_samples) or (n_samples, n_outputs)
            True labels for X.

        sample_weight : array-like, shape = [n_samples], optional
            Sample weights.

    Returns::

        score : float
            Mean accuracy of self.predict(X) wrt. y.

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

    code_match = re.compile(r'<pre>(.*?)</pre>', re.MULTILINE|re.DOTALL)
    link_match = re.compile(r'<a href="http://.*?".*?>(.*?)</a>', re.M|re.S)
    tag_match = re.compile(r'<[^>]*>', re.M|re.S)
    img_match = re.compile(r'<img(.*?)/>', re.M|re.S)
    
    def extract_features_from_body(s):
        link_count_in_code = 0
        for match_str in code_match.findall(s):
            link_count_in_code += len(link_match.findall(match_str))
        return len(link_match.findall(s)) - link_count_in_code

    from sklearn.cross_validation import KFold
    scores = []
    cv = KFold(n=len(X), k=10, indices=True)
    for train, test in cv:
        x_train, y_train = X[train], Y[train]
        x_test, y_test = X[test], Y[test]
        clf = neighbors.KNeighborsClassifier()
        clf.fit(x_train, y_train)
        scores.append(clf.score(x_test, y_test))
    
    print('Mean(scores)=%.5f\tStddev(scores)=%.5f'%(np.means(scores), np.std(scores)))

    def extract_features_from_body(s):
        num_code_lines = 0
        link_count_in_code = 0
        num_imgs = len(img_match.findall(s))
        code_free_s = s
        for match_str in code_match.findall(s):
            num_code_lines += match_str.count('\n')
            code_free_s = code_match.sub('', code_free_s)
            link_count_in_code += len(link_match.findall(match_str))
        links = link_match.findall(s)
        link_count = len(links) - link_count_in_code
        link_free_s = re.sub(' +', ' ', tag_match.sub('', code_free_s)).replace('\n', '')
        for link in links:
            if link.lower().startswith('http://'):
                link_free_s = link_free_s.replace(link, '')
        num_text_tokens = link_free_s.count(' ')
        return num_text_tokens, num_code_lines, link_count, num_imgs
