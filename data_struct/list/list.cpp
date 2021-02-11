#include <iostream>

template <typename T>
class List {
public:
    List(): len_(0){
        head_ = tail_ = nullptr;
    }
    ~List() {
        struct ListNode* tempNode;
        while(len_) {
            tempNode = head_;
            head_ = head_->next;
            delete tempNode;
            len_--;
        }
        head_ = nullptr;
        tail_ = nullptr; 
    }
    List(const List& ) = delete;
    List& operator=(const List&) = delete;

    void AddNodeHead(const T& value) {
        auto newNode = new (struct ListNode);
        newNode->value = value;
        if (len_ == 0) {
            head_ = tail_ = newNode;
            newNode->prev = nullptr;
            newNode->next = nullptr;
        } else {
            newNode->prev = nullptr;
            newNode->next = head_;
            head_->prev = newNode;
            head_ = newNode;
        }
        len_++;
    }
    void Debug() {
        std::cout << "list len: " << len_ << ", ";
        auto tempNode = head_;
        std::cout << "[ ";
        while(tempNode != nullptr) {
            std::cout << tempNode->value << ", ";
            tempNode = tempNode->next;
        }
        std::cout << "]" << std::endl;
    }
private:
    struct ListNode {
        T value;
        struct ListNode* prev;
        struct ListNode* next;
    };
    ListNode* head_;
    ListNode* tail_;
    int len_;
};

int main() {
    List<int> a;
    a.Debug();
    a.AddNodeHead(6);
    a.AddNodeHead(7);
    a.AddNodeHead(7);
    a.AddNodeHead(7);
    a.AddNodeHead(7);
    a.AddNodeHead(7);
    a.Debug();
    a.~List();
    a.Debug();
}