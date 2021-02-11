#include <iostream>
#include <vector>
using std::cout;
using std::vector;
using std::endl;


template<typename T>
class Queue {
public:
    Queue(int limit = 15) : limit_(limit), head_(0), tail_(0), length_(0){
        elems_ = new T[limit_];
    }
    ~Queue() {
        delete[] elems_;
        elems_ = nullptr;
    }
    Queue(const Queue<T>& copy) noexcept:  limit_(copy.limit_) ,length_(copy.length_), head_(copy.head_), tail_(copy.tail_){
        if (elems_ != nullptr) {
            delete[] elems_;
            elems_ = nullptr;
        }
        elems_ = new T[this->limit_];
        this->copy(copy.elems_, copy.length_);
    }
    Queue(Queue<T>&& copy) noexcept:  limit_(copy.limit_) ,length_(copy.length_), head_(copy.head_), tail_(copy.tail_){
        std::cout << "Debug && copy" << std::endl;
        this->elems_ = copy.elems_;
        copy.elems_ = nullptr;
        copy.limit_ = copy.length_ = copy.head_ = copy.tail_ = 0; 
    }
    Queue& operator=(const Queue& copy){
        if (this == &copy) {
            return *this;
        }
        delete[]elems_;
        elems_ = nullptr;
        this->limit_ = copy.limit_;
        this->length_ = copy.length_;
        this->head_ = copy.head_;
        this->tail_ = copy.tail_;
        elems_ = new T[this->limit_];
        this->copy(copy.elems_, copy.length_);
        return *this;
    }
    Queue& operator=(Queue&& copy){
        std::cout << "Debug &&==" << std::endl;
        if (this == &copy) {
            return *this;
        }
        delete[]elems_;
        this->limit_ = copy.limit_;
        this->length_ = copy.length_;
        this->head_ = copy.head_;
        this->tail_ = copy.tail_;
        this->elems_ = copy.elems_;
        copy.elems_ = nullptr;
        copy.limit_ =  copy.length_ = copy.head_ = copy.tail_ = 0; 
        return *this;
    }
    void Push(const T& value) {
        if(length_ == limit_) {
            std::string exp("Push Queue erflow_error, info: ");
            exp += debugInfo();
            throw std::overflow_error(exp);
        }
        if (tail_ == limit_) {
            tail_ = 0;
        }
        elems_[tail_] = value;
        length_++;
        tail_++;
    }

    T Pop(){
      if(length_ == 0) {
            std::string exp("Pop Queue erflow_error, info: ");
            exp += debugInfo();
            throw std::overflow_error(exp);
        }  
        T temp = elems_[head_];
        head_++;
        length_--;
        if (head_ == limit_) {
            head_ = 0;
        }
        return temp;
    }

    void Degug(){
        std::cout << "Elem Address: " << elems_ << ", Array Head: " << head_ << ", Array Tail: " << tail_
                << ", Array lenth: " << length_ << std::endl;
        std::cout << "[";
        auto tempLength = length_;
        auto tempHead = head_;
        while(tempLength != 0) {
            if(tempHead == limit_) {
                tempHead = 0;
            }
            std::cout << elems_[tempHead] << ",";
            tempHead++;
            tempLength--;
        }
        std::cout << "]" << std::endl;
    }
private:
    std::string debugInfo(){
        std:: string exp = "tail length: ";
        exp += std::to_string(length_);
        exp += ", head_: ";
        exp += std::to_string(head_);
        exp += ", tail_: ";
        exp += std::to_string(tail_);
        return exp;
    }
    void copy(T* array, int length) {
        for(int i = 0; i < length; i++) {
            this->elems_[i] = array[i];
        }
    }

    T *elems_;
    int head_;
    int tail_;
    int length_;
    int limit_;
};


int main() {
    Queue<int> a;
    try{
        for(int index = 0; index < 15; index++) {
            int temp = index + 1;
            a.Push(temp);
        }
        a.Degug();
        std::cout << "Pop:";
        for(int index = 0; index < 7; index++) {
           std::cout << a.Pop() << ",";
        }
        a.Degug();
        std::cout << std::endl;
        for(int index = 0; index < 7; index++) {
            int temp = index + 1;
            a.Push(temp);
        }
        a.Degug();
    } catch(const std::exception& e) {
        std::cout << "catch exception: "<< e.what() << std::endl;
    }

}