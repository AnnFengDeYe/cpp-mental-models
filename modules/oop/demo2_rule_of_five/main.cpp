#include "Shape.h"
#include <iostream>

int main() {
    std::cout << "========== 🎬 Runtime Destiny ==========\n\n";

    std::cout << "--- 0. Construction ---\n";
    Circle c1(5.0, nullptr);
    std::cout << c1 << "\n\n";

    std::cout << "--- 1. Copy Construction ---\n";
    Circle c2 = c1;
    std::cout << c2 << "\n\n";

    std::cout << "--- 2. Copy Assignment ---\n";
    Circle c3(10.0, "Temp_C3");
    c3 = c1;
    std::cout << c3 << "\n\n";

    std::cout << "--- 3. Move Construction ---\n";
    Circle c4 = std::move(c1);
    std::cout << "After Move Construction:\n";
    std::cout << "c4 (Thief)   : " << c4 << "\n";
    std::cout << "c1 (Victim)  : " << c1 << "\n\n";

    std::cout << "--- 4. Move Assignment ---\n";
    Circle c5(20.0, "Target_C5");
    c5 = std::move(c2);
    std::cout << "After Move Assignment:\n";
    std::cout << "c5 (Thief)   : " << c5 << "\n";
    std::cout << "c2 (Victim)  : " << c2 << "\n\n";

    std::cout << "--- 5. Destruction ---\n";
    std::cout << "Main function ending. Objects are going out of scope...\n";
    // do sth ...
}