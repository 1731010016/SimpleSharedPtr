#pragma once

#include <iostream>
#include <atomic>


template<typename T>
class SimpleSharedPtr {
private:
    T *ptr;
    std::atomic<int> *count;  // 引用计数

    void release() {
        if (ptr && --(*count) == 0) {
            delete ptr;
            delete count;
            std::cout << "Resource destroyed." << std::endl;
        }
    }


public:
    explicit SimpleSharedPtr(T *p = nullptr) : ptr(p), count(p ? new std::atomic<int>(1) : nullptr) {
        if (p == nullptr) {
            std::cout << "Warning: SimpleSharedPtr constructed with a null pointer." << std::endl;
        }
    }

    SimpleSharedPtr(const SimpleSharedPtr &other) : ptr(other.ptr), count(other.count) {
        if (ptr) {
            (*count)++;
        }
        std::cout << "MySharedPtr copy-constructed, count = " << *count << std::endl;
    }

    SimpleSharedPtr &operator=(const SimpleSharedPtr &other) {
        if (this != &other) {
            release();
            ptr = other.ptr;
            count = other.count;
            (*count)++;
        }
        return *this;
    };

    // 移动构造函数
    SimpleSharedPtr(SimpleSharedPtr &&other) noexcept: ptr(other.ptr), count(other.count) {
        other.ptr = nullptr;
        other.count = nullptr;
        std::cout << "Moved SimpleSharedPtr." << std::endl;
    }

    // 移动赋值操作符
    SimpleSharedPtr &operator=(SimpleSharedPtr &&other) noexcept {
        if (this != &other) {
            release();
            ptr = other.ptr;
            count = other.count;
            other.ptr = nullptr;
            other.count = nullptr;
            std::cout << "Move-assigned SimpleSharedPtr." << std::endl;
        }
        return *this;
    }

    // 析构函数
    ~SimpleSharedPtr() {
        release();
    }

    // 解引用操作符
    T &operator*() const {
        return *ptr;
    }

    // 箭头操作符
    T *operator->() const {
        return ptr;
    }

    // 获取引用计数
    [[nodiscard]] int use_count() const {
        return *count;
    }

};