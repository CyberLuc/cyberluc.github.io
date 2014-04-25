---
layout: post
title: "NYOJ-115-城市平乱"
date: 2014-04-22 11:19:13 +0800
keywords: 最短路径
comments: true
categories: [NYOJ]
tags: [NYOJ, 最短路径, Dijkstra]
published: true

---

### 城市平乱

南将军统领着N个部队，这N个部队分别驻扎在N个不同的城市。

他在用这N个部队维护着M个城市的治安，这M个城市分别编号从1到M。

现在，小工军师告诉南将军，第K号城市发生了暴乱，南将军从各个部队都派遣了一个分队沿最近路去往暴乱城市平乱。

现在已知在任意两个城市之间的路行军所需的时间，你作为南将军麾下最厉害的程序员，请你编写一个程序来告诉南将军第一个分队到达叛乱城市所需的时间。

[题目链接](http://acm.nyist.net/JudgeOnline/problem.php?pid=115)

<!-- more -->

### BFS

{% include_code BFS lang:c++ ACM/NYOJ/4.115.bfs.cpp %}

### Dijkstra

{% include_code Dijkstra的Vector邻接表实现 lang:c++ ACM/NYOJ/4.115.dijkstra.cpp %}

### Bellman-Ford

Bellman-Ford算法的介绍可以看[这里](http://wenku.baidu.com/link?url=zJJSMwhhM-Qof0hXwafd5jaQqKWIgVMbm1HQb5VRY6A8QBaHW0IPnIlBSoQYP4d1pe9vZEvMxjdj_eYzVcFi5VbEbn1eaTxRt0HHbPPmgUO)

{% include_code Bellman-Ford lang:c++ ACM/NYOJ/4.115.bellman-ford.cpp %}

### SPFA

SPFA(Shortest Path Faster Algorithm)在Bellman-Ford算法的基础上加上一个队列优化，减少了冗余的松弛操作，非常高效。

{% include_code SPFA队列实现 lang:c++ ACM/NYOJ/4.115.spfa.cpp %}

{% include_code SPFA栈实现 lang:c++ ACM/NYOJ/4.115.spfa-stack.cpp %}


#### POJ相关最短路径题目（差分约束）：

* [1364](http://poj.org/problem?id=1364)
* [1860](http://poj.org/problem?id=1860)
* [3159](http://poj.org/problem?id=3159)
* [1201](http://poj.org/problem?id=1201)

[解题代码](http://www.cppblog.com/guyuecanhui/articles/80873.html?opt=admin)
