*******************************
Clustering - Find related posts
*******************************

.. code-block:: py

    from sklearn.feature_extraction.text import CountVectorizer
    import scipy as sp
    import nltk.stem
    import sklearn.datasets

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

    vectorizer = StemmedTfidfVectorizer(min_df=1, stop_words="english", decode_error="ignore")


    all_data = sklearn.datasets.fetch_20newsgroups(subset="all")
    test_data = sklearn.datasets.fetch_20newsgroups(subset="test")
    train_data = sklearn.datasets.fetch_20newsgroups(subset="train")
    #dir(all_data)
    #['DESCR', 'data', 'filenames', 'target', 'target_names']

    groups = ['comp.graphics', 'comp.os.ms-windows.misc', 'comp.sys.ibm.pc.hardware', 'comp.sys.mac.hardware', 'comp.windows.x', 'sci.space']
    interested_data = sklearn.datasets.fetch_20newsgroups(subset='train', categories=groups)
    #interested_data.filenames.shape
    #(3529,)
    vectorized = vectorizer.fit_transform(interested_data.data)
    #vectorized.shape
    #(3529, 66108)
    num_samples, num_features = vectorized.shape
    num_clusters = 50
    from sklearn.cluster import KMeans
    km = KMeans(n_clusters=num_clusters, init='random', n_init=1, verbose=1)
    km.fit(vectorized)
    #km.labels_.shape
    #(3529,)
    #km.cluster_centers_.shape
    #(50, 66108)

    new_post = '''
    Disk drive problems. Hi, I have a problem with my hard disk.
    After 1 year it is working only sporadically now.
    I tried to format it, but now it doesn't boot any more
    Any ideas? Thanks.
    '''
    new_post_vec = vectorizer.transform([new_post])
    #new_post_vec.shape
    #(1, 66108)
    new_post_label = km.predict(new_post_vec)[0]
    similar_indices = (km.labels_ == new_post_label).nonzero()[0]
    #type(similar_indices)
    #<class 'numpy.ndarray'>

    similar = []
    for i in similar_indices:
        dist = sp.linalg.norm((new_post_vec - vectorized[i]).toarray())
        similar.append((dist, interested_data.data[i]))

    similar = sorted(similar)
    len(similar)

    post_group = zip(interested_data.data, interested_data.target)
    all = [(len(post[0]), post[0], interested_data.target_names[post[1]]) for post in post_group]
    graphics = sorted([post for post in all if post[2] == 'comp.graphics'])
    s1 = list(set(analyzer(graphics[6][1])).intersection(vectorizer.get_feature_names()))
    s2 = list(set(analyzer(graphics[5][1])).intersection(vectorizer.get_feature_names()))
    term_idfs=[(term, vectorizer._tfidf.idf_[vectorizer.vocabulary_[term]]) for term in s1+s2]
    pprint(sorted(term_idfs, key=lambda e: e[1], reverse=True))

Text preprocessing phrase:

    #. Tokenizing the text.
    #. Throwing away stop words.
    #. Trowing away words that occur so seldom.
    #. Counting the remaining words.
    #. Calculating TF-IDF values frorm the counts, considering the whole text corpus.
       

**KMeans** is the most widely used fat clustering algorithm. After it is initialized with
the desired number of clusters, *num_clusters*, it maintains that number of so-called
**cluster centroids**. Initially, it would pick any of the *num_clusters* posts and set the
centroids to their feature vector. Then it would go through all other posts and assign
them the nearest centroid as their current cluster. Then it will move each centroid
into the middle of all the vectors of that particular class. This changes, of course, the
cluster assignment. Some posts are now nearer to another cluster. So it will update
the assignments for those changed posts. This is done as long as the centroids move
a considerable amount. After some iterations, the movements will fall below a
threshold and we consider clustering to be converged.



