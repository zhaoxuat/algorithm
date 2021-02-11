#include <iostream>
#include <cassert>
#include <string>
#include <functional>
#include "hash_function.h"


class HashTable{
public:
    struct hashElems {
        hashElems(std::string val) : value_(val) {
             hash_ = TableHash(val);
        }
        struct hashElems* hashNext_;
        std::string value_;
        uint32_t hash_;
    };
    HashTable(): list_(nullptr), length_(0), elems_(0) {
        resize();
    }
    ~HashTable() {
        delete []list_;
    }
    hashElems* Insert(hashElems* h) {
        auto ptr = findPoint(h->value_, h->hash_);
        auto old = *ptr;
        h->hashNext_ = (old == nullptr) ? nullptr : old->hashNext_;
        *ptr = h;
        if(old == nullptr) {
            ++elems_;
            if(elems_ > length_) {
                 resize();
            }
        }
        return old;
    }

     hashElems* Remove(const std::string& val, uint32_t hash) {
        auto ptr = findPoint(val, hash);
        auto result = *ptr;
        if (result != nullptr) {
            *ptr = result->hashNext_;
            --elems_;
        }
        return result;
     }
     
    hashElems* LookUp(const std::string& val, uint32_t hash) {
        return *findPoint(val, hash);
    }

    void Debug(const std::function<void (HashTable::hashElems* val)>& val) {
        std::cout << "HashTable Debug info: " << std::endl;
        std::cout << "Length: " << length_ << ", Elems: " << elems_ << ", all Elem: " << std::endl;
        for(uint32_t i = 0; i < length_; i++) {
            auto h = list_[i];
            while(h != nullptr) {
                auto next = h->hashNext_;
                val(h);
                h = next;
            }
        }
        std::cout << std::endl;
    }
private:
    hashElems** list_;
    uint32_t length_;
    uint32_t elems_;
    hashElems** findPoint(const std::string& value, uint32_t hash) {
        auto h = &list_[hash & (length_ -1)];
        while(*h != nullptr && ((*h)->hash_ != hash || (*h)->value_ != value)){
            h = &(*h)->hashNext_;
        }
        return h;
    }

    void resize() {
        uint32_t newLegth = 4;
        while(newLegth < elems_) {
            newLegth *= 2;
        }
        auto newList = new hashElems*[newLegth];
        for (int index = 0; index <newLegth; index++) { // mac must nullptr
            newList[index] = nullptr;
        }
        uint32_t count = 0;
        for(uint32_t index = 0; index < length_; index++) {
            auto h = list_[index];
            while(h != nullptr) {
                auto hash = h->hash_;
                auto nextNode = h->hashNext_;
                auto ptr = &newList[hash & (newLegth -1)];
                h->hashNext_ = *ptr;
                *ptr = h;
                h = nextNode;
                count++;
            } 
        }
        assert(elems_ == count);
        delete []list_;
        list_ = newList;
        length_ = newLegth;
    }
};


int main() {
    HashTable table;
    auto a =  new HashTable::hashElems("xuzhao");
    table.Insert(a);
    a =  new HashTable::hashElems("xu");
    table.Insert(a);
    a =  new HashTable::hashElems("zhao");
    table.Insert(a);
    a =  new HashTable::hashElems("zo");
    table.Insert(a);
    a =  new HashTable::hashElems("zao");
    table.Insert(a);
    table.Debug([](HashTable::hashElems* val){ std::cout << "," << val->value_; });
}