#include <iostream>
#include <vector>
#include <algorithm>


struct Sorter {
    bool is_ascending;
    explicit Sorter(bool mode) : is_ascending(mode) {}

    bool operator()(int a, int b) const {
        if (is_ascending) {
            return a < b;
        } else {
            return a > b;
        }
    }
};

int main() {
    std::vector<int> dataset = {10, 5, 8, 3, 12};

    bool is_ascending = false;
    std::sort(dataset.begin(), dataset.end(), Sorter(is_ascending));

    for (int v : dataset) std::cout << v << " ";
}