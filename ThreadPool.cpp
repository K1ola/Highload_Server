////
//// Created by kate on 30.09.2019.
////
//
#include "ThreadPool.h"
//
//void Worker::operator()()
//{
//    std::function<void()> task;
//    while(true)
//    {
//        {   // acquire lock
//            std::unique_lock<std::mutex>
//                    lock(pool.queue_mutex);
//
//            // look for a work item
//            while(!pool.stop && pool.tasks.empty())
//            { // if there are none wait for notification
//                pool.condition.wait(lock);
//            }
//
//            if(pool.stop) // exit if the pool is stopped
//                return;
//
//            // get the task from the queue
//            task = pool.tasks.front();
//            pool.tasks.pop_front();
//
//        }   // release lock
//
//        // execute the task
//        task();
//    }
//}
//
//// the constructor just launches some amount of workers
//ThreadPool::ThreadPool(size_t threads)
//        :   stop(false)
//{
//    for(size_t i = 0;i<threads;++i)
//        workers.push_back(std::thread(Worker(*this)));
//}
//
//// the destructor joins all threads
//ThreadPool::~ThreadPool()
//{
//    // stop all threads
//    stop = true;
//    condition.notify_all();
//
//    // join them
//    for(size_t i = 0;i<workers.size();++i)
//        workers[i].join();
//}
//
//// add new work item to the pool
////template<class F>
//void ThreadPool::enqueue(std::function<void()> func)
//{
//    { // acquire lock
//        std::unique_lock<std::mutex> lock(queue_mutex);
//        // add the task
//        tasks.push_back(func);
//    } // release lock
//
//    // wake up one thread
//    condition.notify_one();
//}
//
