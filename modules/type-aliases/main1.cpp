#include <iostream>
#include <functional>

using IntPredicate = bool(int);

IntPredicate* p;               // traditional pointer
std::function<IntPredicate> f; // modern capacity

int main () {

}
