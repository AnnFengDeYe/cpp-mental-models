#include <iostream>
#define NUM 10
#define SQUARE(x) ((x)*(x))
#define DEBUG

int main() {
    int result = SQUARE(NUM);

#ifdef DEBUG
    std::cout << "Debug" << std::endl;
#endif
}
