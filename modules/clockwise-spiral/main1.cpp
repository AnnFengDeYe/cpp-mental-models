#include <iostream>

int main() {
    int a = 10, b = 20, c = 30, d = 40, e = 50;

    int *foo[5];

    foo[0] = &a;
    foo[1] = &b;
    foo[2] = &c;
    foo[3] = &d;
    foo[4] = &e;

    std::cout << "The value pointed to by foo[1] is: " << *foo[1] << std::endl; // 输出 20

    *foo[0] = 100;
    std::cout << "The new value of a is: " << a << std::endl; // 输出 100
}