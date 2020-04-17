*************
Pending tasks
*************

eta 计算服务开发设计：

设计目的：设计独立的 eta 计算服务，使得算路服务不再直接依赖路况数据，减少算路服务部署时的内存和磁盘占用。

1. 选取服务器架构，提取服务输入输出，设计协议传输，撰写设计文档
2. 功能开发：迁移现有 eta 计算逻辑, 设计单元测试和功能测试，完成功能开发，并对比原有服务，评估开发效果
3. 撰写部署文档，内网部署，选取典型案例进行压力测试，得出服务 RPS 在 600 左右
4. 为提升服务器 RPS，提取压力测试得到服务器日志进行分析，并结合 matplotlib 进行可视化，确定性能瓶颈
5. 为进一步确定性能瓶颈，使用 gprof 工具分析确定热点函数
6. 确定优化方案：路况查询引入缓存；采用 libtbb 作并行计算；使用内存池减少内存分配次数
7. 回归测试，优化后服务 RPS 在 800 左右
8. 满足预先设计目标，整理开发文档，review 代码并合并到 master。 通过 Kubernetes 部署到线上

算路结果流量压缩

1. 目的：一次算路结果集中，路线彼此之间可以分成若干路线片，单独下发这些路线片段相比下发完整路线，
   算路结果的流量大小可以减小30%到70%。

2. 方案设计：

    将路线集还原成图，利用 DFS 遍历将图切分成路线片段，然后用这些片段拆分路线，
    记下每条路线的组成信息，客户端根据该信息还原路线。算法设计关键在于路线片段的切分
    和怎么根据路线片段还原路线。进一步抽象路线片段的切分问题发现它类似 CH 算法的节点收缩过程。

4. 确定实现方案：

    路线片段的切分借助并查集实现，设计路段的合并规则聚合路线片中的路段。
    路线片段组合和还原借助哈希表实现。

5. 使用 python 开发算法原型，验证算法可行性。
6. 服务器端开发：实现设计思想，设计单元测试和功能测试验证算法正确性。
7. 选取典型案例，比较压缩前后算路流量大小，验证设计目标，同时评估算法给算路性能带来的惩罚。
8. 整理文档，代码review合并，整合到算路服务并上线。

路况服务器性能优化

瓶颈所在：服务器对每个请求都重新编译网格数据，但是在下次路况更新前，
同一个网格编译后的数据是一样的，每次都重编相当浪费性能。

优化方案：增加缓存层，并且支持超时处理，由于路况数据的实时更新，没有作缓存持久化的需求，
综上考虑选择以 memcached 为基础的分布式缓存作为技术方案。




**Now or Never**

**自救或者去死**

**自助者天助之**

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
