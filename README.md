# 基于 fuse 的多级调度文件系统

下面介绍一下该目录下的各种文件。

## 核心文件

main.c: 实现 fuse 提供的文件接口

util.h: 定义了存在 DRAM 的目录多叉树的数据结构
util.c: 实现上述结构的各种操作 

control.c, control.h: 实现调度算法，并发控制

目前已经完成了持久化到 pmem 的操作，同时也完成了 pmem 和 disk 的动态调度的过程。

- TODO: 
    - [x] 已完成：项目的存在数据竞争的问题，即从线程在进行 pmem 与 disk 的调度时，主线程文件系统的文件被访问时可能会起数据竞争。
    - [x] 已支持变长文件，后期将使用 content 链表进行改进。
    - [x] 已解决原子性操作问题。
    - [x] 已完成测试
    - [] 需要考虑并发删除问题，解决办法
        - 树形加锁：1. 从需要删除的目录出发，一直给其所有子结点加锁，若全部加锁成功，2. 则删除目录
        - 但是，需要考虑删除效率，这样做的话，其实删除所需时间会很长（外部进程调用删除，会导致长时间等待）
        - 优化方案一：在进行 2. 删除目录时，可以考虑把目录结点的父节点的下一级指针置为空，然后返回给外部进程信息，之后把子目录的删除交给一个删除线程完成。
            - 但是，这样并没有解决第 1 步的时间开销问题。
        - 优化方案二：从读/写文件的操作修改，实现读/写文件的操作时，考虑从根节点到写/读的文件上的路径加上不可删除锁（实际上可以每个结点设置一个不可删除计数），写/读完再释放。然后删除时，判断删除目录的不可删除计数是否为 0 ，若是则进行优化方案一的操作；否则，直接返回失败信息。需要修改 find 接口，以及如何返回的接口。

            

