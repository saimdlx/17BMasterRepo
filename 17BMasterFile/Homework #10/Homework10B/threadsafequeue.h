// ================================================================
// Programmer: Saim Ahmed
// Class: CIS17B
// Instructor: Med Mogasemi
// ================================================================
// Program: HW10B - Producer-Consumer Task Processor
// ================================================================
// Program Description:
// Thread-Safe Queue Header File
// - Template class for a blocking concurrent queue.
// - Uses mutexes and condition variables for synchronization.
// ================================================================
#ifndef THREADSAFEQUEUE_H
#define THREADSAFEQUEUE_H

#include <queue>
#include <mutex>
#include <condition_variable>

// ================================================================
// Class: ThreadSafeQueue
// - Manages concurrent access to an underlying std::queue.
// ================================================================
template<typename T>
class ThreadSafeQueue {
public:
    // ================================================================
    // Function: push
    // - Adds an item to the queue and notifies waiting threads.
    // ================================================================
    void push(const T &item) {
        std::lock_guard<std::mutex> lock(mutex_);
        queue_.push(item);
        cv_.notify_one();
    }

    // ================================================================
    // Function: pop
    // - Blocking call that retrieves an item from the queue.
    // - Returns false if the queue is shut down and empty.
    // ================================================================
    bool pop(T &item) {
        std::unique_lock<std::mutex> lock(mutex_);
        cv_.wait(lock, [this]() { return !queue_.empty() || shutdown_; });
        
        if (queue_.empty() && shutdown_) {
            return false;
        }
        
        item = std::move(queue_.front());
        queue_.pop();
        return true;
    }

    // ================================================================
    // Function: shutdown
    // - Signals all waiting threads to wake up and exit.
    // ================================================================
    void shutdown() {
        {
            std::lock_guard<std::mutex> lock(mutex_);
            shutdown_ = true;
        }
        cv_.notify_all();
    }

    // ================================================================
    // Function: size
    // - Returns the current number of items in the queue.
    // ================================================================
    size_t size() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return queue_.size();
    }

private:
    std::queue<T> queue_;
    mutable std::mutex mutex_;
    std::condition_variable cv_;
    bool shutdown_ = false;
};

#endif // THREADSAFEQUEUE_H
