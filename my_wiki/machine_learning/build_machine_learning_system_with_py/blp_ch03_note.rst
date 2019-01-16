*******************************
Clustering - Find related posts
*******************************

.. code-block:: py

    from sklearn.feature_extraction.text import CountVectorizer
    import scipy as sp
    import nltk.stem
    
    posts = [open(os.path.join(".", f)).read() for f in os.listdir(".")]

    posts = 
    [
        '''
This is a toy post about machine learning. Actually, 
it contains not much interesting stuff.
        ''',
        '''
Imaging databases can get huge.
        ''',
'''
Most imaging databases safe images permanently.
''',
'''
Imaging databases store images.
''',

'''
Imaging databases store images.
Imaging databases store images.
Imaging databases store images.
'''
    ]



    vectorizer = CountVectorizer(min_df=1, stop_words="english")
    
    # vectorizer.get_stop_words()
    
    x_train = vectorizer.fit_transform(posts)
    num_samples, num_features = x_train.shape
    
    # vectorizer.get_feature_names()
    
    new_post = "imaging databases"
    new_post_vec = vectorizer.transform([new_post])
    
    def euclidean_distance(v1, v2):
        return sp.linalg.norm((v1-v2).toarray())
    
    def normalized_euclidean_distance(v1, v2):
        v1_normalized = v1/sp.linalg.norm(v1.toarray())
        v2_normalized = v2/sp.linalg.norm(v2.toarray())
        return euclidean_distance(v1_normalized, v2_normalized)
    
    best_doc = None
    best_dist = sys.maxsize
    best_i = None
    for i in range(0, num_samples):
        post = posts[i]
        if post == new_post:
            continue
        post_vec = x_train.getrow(i)
        d = normalized_euclidean_distance(post_vec, new_post_vec)
        print("=== Post %i with distance=%.2f: %s" % (i, d, post))
        if d < best_dist:
            best_i = i
            best_doc = post
    
    
    english_stemmer = nltk.stem.SnowballStemmer("english")
    
    class StemmedCountVectorizer(CountVectorizer):
        def build_analyzer(self):
            analyzer = super(StemmedCountVectorizer, self).build_analyzer()
            return lambda doc: (english_stemmer.stem(w) for w in analyzer(doc))
    
    vectorizer = StemmedCountVectorizer(min_df=1, stop_words="english")

    def tfidf(term, doc, docset):
        tf = float(doc.count(term))/sum(doc.count(w) for w in set(doc))
        idf = sp.log(float(len(docset))/len([d for d in docset if term in d]))
        return tf * idf
    
    from sklearn.feature_extraction.text import TfidfVectorizer
    class StemmedTfidfVectorizer(TfidfVectorizer):
        def build_analyzer(self):
            analyzer = super(TfidfVectorizer, self).build_analyzer()
            return lambda doc: (english_stemmer.stem(w) for w in analyzer(doc))

    vectorizer = StemmedTfidfVectorizer(min_df=1, stop_words="english", charset_error="ignore")
