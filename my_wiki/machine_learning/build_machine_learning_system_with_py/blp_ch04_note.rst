**************
Topic Modeling
**************

:abbr:`LDA (Latent Dirichlet Allocation)`: a topic modeling method.

:abbr:`HDA (Hierarchical Dirichlet Allocation)`: a method automatically determines the number of topics.

**Sparsity** means that while you may have large matrices and vectors, 
in principle, most of the values are zero (or so small that we can round 
them to zero as a good approximation). Therefore, only a few things are 
relevant at any given time.

.. code-block:: py

    from gensim import corpora, models, matutils

    corpus = corpora.BleiCorpus('./datasets/ap/ap.dat', './datasets/ap/vocab.txt')
    model = models.ldamodel.LdaModel(corpus, num_topics=100, id2word=corpus.id2word)

    for ti in range(model.num_topics):
        words = model.show_topic(ti, 64)
        tf = sum(f for w, f in words)
        with open('topics.txt', 'w') as output:
                output.write('\n'.join('{}:{}'.format(w, int(1000.*f/tf)) for w, f in words))
                output.write('\n\n\n')

    topics = matutils.corpus2dense(model[corpus], num_terms=model.num_topics)
    weight = topics.sum(1)
    max_topic = weight.argmax()
    words = model.show_topic(max_topic, 64)
    create_cloud('cloud_blei_lda.png', words)

    num_topics_used = [len(model[c]) for c in corpus]
    fig, ax = plt.subplots()
    ax.hist(num_topics_used, np.arange(42))
    ax.set_ylabel("Num of documents")
    ax.set_xlabel("Num of topics")
    fig.tight_layout()
    plt.show()

    model1 = models.ldamodel.LdaModel(corpus, num_topics=100, id2word=corpus.id2word, alpha=1.0)
    num_topics_used1 = [len(model1[c]) for c in corpus]
    
    fig, ax = plt.subplots()
    ax.hist(num_topics_used1, np.arange(42))
    ax.set_ylabel("Num of documents")
    ax.set_xlabel("Num of topics")
    ax.text(9, 223, r'default alpha')
    ax.text(26, 156, 'alpha=1.0')
    fig.tight_layout()
    plt.show()