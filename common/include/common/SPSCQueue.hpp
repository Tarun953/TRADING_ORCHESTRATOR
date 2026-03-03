#ifndef COMMON_SPSC_QUEUE_HPP
#define COMMON_SPSC_QUEUE_HPP

#include <vector>
#include <atomic>
#include <cstdint>

template <typename T>
class SPSCQueue
{
private:
    std::vector<T> data_;
    std::size_t capacity_;
    std::atomic<std::int64_t> head_;
    std::atomic<std::int64_t> tail_;

public:
    explicit SPSCQueue(std::size_t capacity) : capacity_(capacity), head_(0), tail_(0), data_(capacity)
    {
        assert(capacity_ & (capacity_ - 1) == 0);
    }

    SPSCQueue() = delete;
    SPSCQueue(const SPSCQueue &) = delete;
    SPSCQueue(SPSCQueue &&) = delete;
    SPSCQueue &operator=(const SPSCQueue &) = delete;
    SPSCQueue &operator=(SPSCQueue &&) = delete;

    bool try_enqueue(T &&item)
    {
        std::int64_t head = head_.load(std::memory_order_relaxed);
        std::int64_t next_head = (head + 1) & (capacity_ - 1);

        if (next_head == tail_.load(std::memory_order_acquire))
            return false;
        data_[head] = std::forward<T>(item);
        head_.store(std::memory_order_release);
        return true;
    }

    bool try_dequeue(T &item)
    {
        std::int64_t tail = tail_.load(std::memory_order_relaxed);
        if (tail == head_.load(std::memory_order_acquire))
            return false;

        item = std::move(data_[tail]);
        std::int64_t next_tail = (tail + 1) & (capacity_ - 1);
        tail_.store(std::memory_order_release);
        return true;
    }

    bool is_empty() const
    {
        return tail_.load(std::memory_order_acquire) == head_.load(std::memory_order_acquire);
    }

    bool is_full() const
    {
        return ((head_.load(std::memory_order_acquire) + 1) & (capacity_ - 1)) == tail_.load(std::memory_order_acquire);
    }

    ~SPSCQueue()
    {
        data_.clear();
        head_ = 0;
        tail_ = 0;
    }
};

#endif