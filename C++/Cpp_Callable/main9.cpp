#include <iostream>
#include <vector>

template <typename Handler>
void process_data(const std::vector<int>& data, Handler&& handler) {
    std::cout << "[Library] Starting data processing (Universal Reference version)..." << std::endl;

    for (int value : data) {
        handler(value);
    }

    std::cout << "[Library] Processing complete." << std::endl;
}

int main() {
    std::vector<int> dataset = {10, 5, 8, 3, 12};

    int sum = 0;
    int count_even = 0;

    process_data(dataset, [&, count = 0](int value) mutable {
        count++;

        sum += value;

        if (value % 2 == 0) {
            count_even++;
            std::cout << "  [Lambda] Found even number: " << value << std::endl;
        }
    });

    std::cout << "\n--- Final Statistics ---" << std::endl;
    std::cout << "Sum: " << sum << std::endl;
    std::cout << "Even Count: " << count_even << std::endl;
}

