#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <unistd.h>


template <typename T>
class SafeQueue {
public:
    SafeQueue(int lowWater = 0, int hightWater = 20) : lowWater_(lowWater), hightWater_(hightWater) {
        lowWaterCallBackFunc_ = [](){std::cout << "lowWater Call Function" << std::endl;};
        highWaterCallBackFunc_ = [](){std::cout << "hightWater Call Function" << std::endl;};
    }
    void Push(const T& value) {
        std::unique_lock<std::mutex> lck(queueMutex_);
        if(queue_.size() == lowWater_) {
            queue_low_cv_.notify_all();
        } else if(queue_.size() == hightWater_) {
            highWaterCallBackFunc_();
            queue_high_cv_.wait(lck, [this]{return !(queue_.size() == hightWater_);});
        }
        queue_.emplace(value);
    }


    T Pop() {
        std::unique_lock <std::mutex> lck(queueMutex_);
        if(queue_.size() == lowWater_) {
            lowWaterCallBackFunc_();
            queue_low_cv_.wait(lck, [this]{return !(queue_.size() == lowWater_);});
        } else if(queue_.size() == hightWater_) {
            queue_high_cv_.notify_all();
        }
        
        auto temp = queue_.back();
        queue_.pop();
        return temp;
    }
private:
    std::queue<T> queue_;
    mutable std::mutex queueMutex_;

    int lowWater_;
    std::condition_variable queue_low_cv_;
    std::function<void()>lowWaterCallBackFunc_;
    
    int hightWater_;
    std::condition_variable queue_high_cv_;
    std::function<void ()> highWaterCallBackFunc_;
};

int main() {
    SafeQueue<int> a;
    std::thread threads[2];
    threads[0] = std::thread([&](){
        auto value  = a.Pop();
        std::cout << value << std::endl;        
    });
    threads[1] = std::thread([&](){
        sleep(1);
        a.Push(5);
    });
    for (auto & th:threads)
        th.join();
}