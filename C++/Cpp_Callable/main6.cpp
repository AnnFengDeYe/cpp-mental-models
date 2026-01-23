#include <iostream>
#include <vector>

template <typename Handler>
void process_data(const std::vector<int>& data, Handler& handler) {
    std::cout << "[Library] Starting data processing (Lambda version)..." << std::endl;

    for (int value : data) {
        handler(value);
    }

    std::cout << "[Library] Processing complete." << std::endl;
}

int main() {
    std::vector<int> dataset = {10, 5, 8, 3, 12};

    int sum = 0;
    int count_even = 0;

    auto lambda_logic = [&](int value)  {
        sum += value;

        if (value % 2 == 0) {
            count_even++;
            std::cout << "  [Lambda] Found even number: " << value << std::endl;
        }
    };

    process_data(dataset, lambda_logic);

    std::cout << "\n--- Final Statistics ---" << std::endl;
    std::cout << "Sum: " << sum << std::endl;
    std::cout << "Even Count: " << count_even << std::endl;
}