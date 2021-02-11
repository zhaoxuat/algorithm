#include <iostream>
#include <stdexcept>
template <typename T>
class Stack {
public:
    explicit Stack(int lenghth= 15) : length_(lenghth), tail_(0) {
        array_ = new T[lenghth];
    }
    ~Stack() {delete[] array_;}
    Stack(const Stack& ) = delete;
    Stack& operator=(const Stack& ) = delete;
    void Degug(){
        std::cout << "Array Address: " << array_ << ", Array tail: " << tail_ << ", Array lenth: " << length_ << std::endl;
        std::cout << "[";
        for(int i = 0; i < tail_; i++) {
            std::cout << array_[i] << ",";
        }
        std::cout << "]" << std::endl;
    }
    void Push(const T& val) {
        if(tail_ >= length_) {
            std::string exp("Push Stak overflow_error");
            exp += "tail length: ";
            exp += std::to_string(tail_);
            throw std::overflow_error(exp);
        }
        array_[tail_++] = val;
    }
    T Pop() {
        if (tail_ <= 0) {
            std::string exp("Pop Stak overflow_error");
            exp += "tail length: ";
            exp += tail_;
            throw std::overflow_error(exp);
        }
        return array_[tail_--];
    }
private:
    T* array_;
    int length_;
    int tail_; 
};

int main() {
    Stack<int> a;
    for (int index = 0; index < 10; index++) {
        a.Push(index);
    }
    a.Degug();
    try {
        std::cout << "begin pop: ";
        for (int index = 0; index < 10; index++) {
            std::cout << a.Pop() << ", ";
        }
        std::cout <<"end pop" << std::endl;
    }catch(const std::exception& e) {
        std::cout << "exception: " << e.what() << std::endl;
        return 1;
    }
    a.Degug();
}


