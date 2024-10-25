#ifndef OWN_SERVER_THREAD_POOL_H
#define OWN_SERVER_THREAD_POOL_H

#include <vector>
#include <queue>
#include <thread>
#include <future>
#include <functional>
#include <atomic>
#include <mutex>
#include <condition_variable>

class ThreadPool{
public:
    ThreadPool(size_t threads);
    ~ThreadPool();

    template<class F, class... Args>
    auto enqueue(F&& f, Args&&... args) -> std::future< typename std::result_of<F(Args...)>::type >;

    void start();
    void stop();
private:
    bool done_;
    std::vector<std::thread> workers_;
    std::queue<std::function<void()>> tasks_;

    std::mutex queue_mutex_;
    std::condition_variable condition_;
}

#endif // OWN_SERVER_THREAD_POOL_H