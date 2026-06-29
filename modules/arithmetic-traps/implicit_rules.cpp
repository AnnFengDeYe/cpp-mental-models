#include <type_traits>

int main() {
    // === Stage 1: Integral Promotion ===

    // Script Case: short + short -> int
    {
        short a = 1;
        short b = 2;
        auto c = a + b;
        static_assert(std::is_same_v<decltype(c), int>, "short + short promotes to int");
    }

    // Script Case: char + bool -> int
    {
        char a = 'A';
        bool b = true;
        auto c = a + b;
        static_assert(std::is_same_v<decltype(c), int>, "char + bool promotes to int");
    }

    // === Stage 2: Usual Arithmetic Conversions ===

    // Principle 1: Float Priority (Script: long long + float)
    {
        long long a = 100;
        float b = 3.14f;
        auto c = a + b;
        static_assert(std::is_same_v<decltype(c), float>, "long long aligns to float");
    }

    // Principle 2: Width Priority (Script: int + long long)
    {
        int a = 10;
        long long b = 20;
        auto c = a + b;
        static_assert(std::is_same_v<decltype(c), long long>, "int aligns to long long");
    }

    // Principle 3: Unsigned > Signed (Script: int + unsigned int)
    {
        int a = -5;
        unsigned int b = 10;
        auto c = a + b;
        static_assert(std::is_same_v<decltype(c), unsigned int>, "signed int aligns to unsigned int");
    }

    // === Exception: Shift Operator (<<) ===

    // Example A: short << long long -> int
    {
        short a = 1;
        long long b = 2;
        auto c = a << b;
        static_assert(std::is_same_v<decltype(c), int>, "right operand is ignored, short promotes to int");
    }

    // Example B: long long << char -> long long
    {
        long long a = 1;
        char b = 2;
        auto c = a << b;
        static_assert(std::is_same_v<decltype(c), long long>, "right operand is ignored, long long remains long long");
    }
}