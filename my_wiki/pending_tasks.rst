*************
Pending tasks
*************

eta-server 开发设计：

3. server frame: multi-process, iterative concurrent server，使用 json 编码，http 协议传输，撰写设计文档
4. 功能开发：迁移现有 eta 计算逻辑, 设计测试案例，对比现有服务，评估开发效果，完成功能测试
5. 撰写部署文档，内网部署，选取常规测试案例和远距离路线案例按照一定比例混合压力测试，得出服务 RPS 在 650 左右
6. 分析服务日志，利用统计学方法，结合 matplotlib 进行可视化，确定性能瓶颈
7. 确定优化方案：引入缓存，采用 libtbb 作并行计算，预分配减少内存分配次数。
8. 回归测试，优化后服务 RPS 在 8000 左右。
9. 满足预先设计目标，整理开发文档，代码通过 review 合并到 master。 通过 Kubernetes 部署到线上。

**Now or Never**

**自救或者去死**

#. C++ smart pointer: ``shared_ptr, uniq_ptr``
#. Computer graphics algorithms [#geomatric_alg]_
#. Unix Network Programming [#unix_network_programming]_
#. Apple Open Soure [#apple_opensource]_
#. https://github.com/janishar/mit-deep-learning-book-pdf.git
#. matplotlib to draw the cover of murphy's machine learning
#. Explore boston_housing, diabetes datasets for regression, the digits dataset for multi-class classification.
#. The architecture of open source applications [#open_source_app_architecture]_

#. Search system for the WIKI docs

    - Search keyword, and return relevant results.
    - preprocessing: docs to feature vectors
    - how to compute similarity: clustering or classification
    - Make some ranking

2019 Targets
============

    #. Deep Learning (Part I and Part II)
    #. Introduction machine learning with python (Fininshed, 2019-03-26 -- 2019-04-20)
    #. The Hundred-Page Machine Learning Book (2019-05-03 -- 2019-05-10)
    #. Building machine learning system using python
    #. Hacker and Painters [Finished, 2019-04-13]
    #. A* algorithm [#a_star_algorithm]_ (Finished, 2019-03-10)
    #. Review *Inside C++ Object Model* [finished, 2019-02-17 -- 2019-02-25]
    #. 2019年底存款不低于 40 万 [**Failed**]
    #. 英语电影摆脱字幕 [**Failed**]
    #. 日语漫画不需要字典可以看懂旁白 [**Failed**]


.. rubric:: Footnotes

.. [#a_star_algorithm] http://theory.stanford.edu/~amitp/GameProgramming/AStarComparison.html
.. [#unix_network_programming] http://www.unpbook.com
.. [#geomatric_alg] http://geomalgorithms.com/
.. [#apple_opensource] https://opensource.apple.com
.. [#programing books] http://www.banshujiang.cn/
.. [#open_source_app_architecture] https://www.aosabook.org/en/index.html
