# socket-server
socket服务端开发模板，基于系统调用、muduo等。

## 需求

1. 基于系统调用实现经典socket服务端
2. 基于muduo实现经典socket服务端

## 协议

1. UDP
2. TCP

## 经典服务端架构

1. 单线程
    - Simple Server 简单模型
    - Iterative Server 循环模型
2. 多线程
    - Pre-fork/Pre-threaded Server 多进程/多线程模型
    - Reactor Server 事件驱动模型
    - Proactor Server 异步I/O模型
    - Thread Pool Server 多线程池模型
    - 混合架构（如muduo的多Reactor多线程）
- 网络I/O模型
    - one loop per thread
