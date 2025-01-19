/*
管理线程池，分配任务给线程
*/
#include "thread_pool.h"
#include <iostream>

ThreadPool::ThreadPool(size_t threads) : done_(false) {
    for (size_t i = 0; i < threads; ++i) {
        workers_.emplace_back([this] {
            while (true) {
                std::function<void()> task;

                {
                    std::unique_lock<std::mutex> lock(this->queue_mutex_);
                    this->condition_.wait(lock, [this] { return this->done_ || !this->tasks_.empty(); });

                    if (this->done_ && this->tasks_.empty()) {
                        return;
                    }

                    task = std::move(this->tasks_.front());
                    this->tasks_.pop();
                }

                task();
            }
        });
    }
}

ThreadPool::~ThreadPool() {
    stop();
}

void ThreadPool::start() {
    // 线程池已经在构造函数中启动
}

void ThreadPool::stop() {
    {
        std::unique_lock<std::mutex> lock(queue_mutex_);
        done_ = true;
    }
    condition_.notify_all();

    for (std::thread& worker : workers_) {
        worker.join();
    }
}
