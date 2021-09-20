# SkipListKV

#### SkipList

skiplist也就是跳跃表，是[William Pugh](https://en.wikipedia.org/wiki/William_Pugh_(computer_scientist))在1990年[Skip Lists: A Probabilistic Alternative to Balanced Trees](https://15721.courses.cs.cmu.edu/spring2018/papers/08-oltpindexes1/pugh-skiplists-cacm1990.pdf)文中提出的一种数据结构，相比较平衡树和红黑树更加简单，性能也十分出色，是典型的用空间换时间的算法。skiplist的数据结构如下图：

![](https://github.com/fenglin-Zhou/fenglin-zhou.github.io/tree/master/img/skiplist.png)

单链表的结构是顺序存储，每一个节点有一个next指向下一个位置，skiplist其实也是单链表的扩展，在每一个节点加了一个层的概念，每个节点都有不同的层来指向下面的节点(可能是下一个，之后第n个)。这样我们查询或插入时就可以从最上面的层开始，可以跳跃过很多不必要的节点，大大缩短时间。

![](https://github.com/fenglin-Zhou/fenglin-zhou.github.io/tree/master/img/skiplist1.png)

以论文给出的例子来说，header是头节点（注意这里是不存数据的）。我们要插入17，那么从最高层开始，比较header->forward[level]->key 和要插入的17的值，采用forward比较保证了我们最后停留在<17的值的node，每一层向下，这样我们就拿到了每一层比17值小的node。要插入17，我们就可以对没一层进行类似单链表的操作，当然新加入的节点的层数，应该随机生成。也就是说不一定要最高层数。

William Pugh的论文中对于插入，删除都给出了伪代码。十分的容易实现，建议直接对着论文撸代码。我自己也实现了一下，[SkipListKV](https://github.com/fenglin-Zhou/SkipListKV)，因为我是在看kvdb，所以是存的key value，区别不大。还是比较简单的。


#### How to build
```
g++ test.c
./a.out
```
