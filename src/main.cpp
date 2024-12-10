#include <iostream>
#include "SimpleSharedPtr.h"


class MyClass {
public:
    MyClass(int value) : value(value) {}
    void show() const { std::cout << "Value: " << value << std::endl; }

private:
    int value;
};

int main() {
    // 创建一个SimpleSharedPtr对象，指向一个MyClass对象
    SimpleSharedPtr<MyClass> ptr1(new MyClass(10));
    std::cout << "ptr1 use_count = " << ptr1.use_count() << std::endl;

    // 使用拷贝构造函数
    SimpleSharedPtr<MyClass> ptr2 = ptr1;
    std::cout << "After copy, ptr1 use_count = " << ptr1.use_count() << std::endl;
    std::cout << "After copy, ptr2 use_count = " << ptr2.use_count() << std::endl;

    // 使用移动构造函数
    SimpleSharedPtr<MyClass> ptr3 = std::move(ptr1);
    std::cout << "After move, ptr3 use_count = " << ptr3.use_count() << std::endl;

    // 使用拷贝赋值运算符
    SimpleSharedPtr<MyClass> ptr4(new MyClass(20));
    ptr4 = ptr2;
    std::cout << "After copy assignment, ptr2 use_count = " << ptr2.use_count() << std::endl;
    std::cout << "After copy assignment, ptr4 use_count = " << ptr4.use_count() << std::endl;

    // 使用移动赋值运算符
    SimpleSharedPtr<MyClass> ptr5(new MyClass(30));
    ptr5 = std::move(ptr3);
    std::cout << "After move assignment, ptr5 use_count = " << ptr5.use_count() << std::endl;

    // 显示对象内容
    ptr4->show(); // 调用 MyClass 的 show 方法
    ptr5->show();

    // 程序结束时会触发析构函数
    return 0;
}