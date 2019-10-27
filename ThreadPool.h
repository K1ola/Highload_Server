//
// Created by kate on 30.09.2019.
//

#ifndef HIGHLOAD_DZ1_THREADPOOL_H
#define HIGHLOAD_DZ1_THREADPOOL_H
#include <boost/asio.hpp>
#include "Session.h"
#include <vector>
#include <queue>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <atomic>

template<class Task>
class ThreadPool
{
private:
    std::vector<std::thread> threads;
    std::queue<Task> tasks;
    std::condition_variable synchronizer;
    std::mutex writeMutex;
    std::mutex readMutex;
    std::atomic_bool terminate;

public:
    ThreadPool(int threadsCount = 0) : terminate(false)
    {
        if (threadsCount == 0)
        {
            threadsCount = std::thread::hardware_concurrency();
            if (threadsCount == 0) threadsCount = 1;
        }
        for (int i = 0; i < threadsCount; i++)
        {
            threads.push_back(std::thread(&ThreadPool::Executor, this));
        }
    }

    ~ThreadPool()
    {
        terminate = true;
        synchronizer.notify_all();
        for (auto &thread : threads)
        {
            if (thread.joinable()) thread.join();
        }
    }

    void AddTask(Task task)
    {
        writeMutex.lock();
        tasks.push(task);
        writeMutex.unlock();
        synchronizer.notify_one();
    }

protected:
    void Executor()
    {
        while (!terminate)
        {
            std::mutex localMutex;
            std::unique_lock<std::mutex> lock(localMutex);
            synchronizer.wait(lock, [&] {return !tasks.empty() || terminate;});
            readMutex.lock();
            if (!tasks.empty()) {
                Task task = tasks.front();
                tasks.pop();
                readMutex.unlock();
                RunTask(task);
            }
            else {
                readMutex.unlock();
            }
            //lock.unlock();
        }
    }

    virtual void RunTask(Task task) = 0;
};

#endif //HIGHLOAD_DZ1_THREADPOOL_H
