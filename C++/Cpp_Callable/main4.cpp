#include <iostream>
#include <vector>

class MyStatsFunctor {
public:
    int sum = 0;
    int count_even = 0;

    void operator()(int value) {
        this->sum += value;

        if (value % 2 == 0) {
            this->count_even++;
            std::cout << "  [Functor] Found even number: " << value << std::endl;
        }
    }
};

void process_data(const std::vector<int>& data, MyStatsFunctor& handler) {
    std::cout << "[Library] Starting to process data stream..." << std::endl;

    for (int value : data) {
        handler(value);
    }

    std::cout << "[Library] Processing finished." << std::endl;
}

int main() {
    std::vector<int> dataset = {10, 5, 8, 3, 12};

    MyStatsFunctor stats_obj;

    process_data(dataset, stats_obj);

    std::cout << "\n--- Final Statistics ---" << std::endl;
    std::cout << "Total Sum: " << stats_obj.sum << std::endl;
    std::cout << "Even Count: " << stats_obj.count_even << std::endl;
}