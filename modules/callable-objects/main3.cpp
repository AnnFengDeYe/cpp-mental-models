#include <iostream>
#include <vector>
using namespace std;

using CallbackHandler = void(*)(int value, void* context);

void process_data(const std::vector<int>& data, CallbackHandler handler, void* context) {
    std::cout << "[Library] Starting to process data stream..." << std::endl;

    for (int value : data) {
        handler(value, context);
    }

    std::cout << "[Library] Processing finished." << std::endl;
}

struct MyStatsContext {
    int sum = 0;
    int count_even = 0;
};

void specific_logic(int value, void* env_ptr) {
    auto* ctx = static_cast<MyStatsContext*>(env_ptr);

    ctx->sum += value;

    if (value % 2 == 0) {
        ctx->count_even++;
        std::cout << "  [Logic] Found even number: " << value
                  << " (Current even count: " << ctx->count_even << ")" << std::endl;
    }
}

int main() {
    std::vector<int> dataset = {10, 5, 8, 3, 12};

    MyStatsContext env;

    process_data(dataset, specific_logic, &env);

    std::cout << "\n--- Final Statistics ---" << std::endl;
    std::cout << "Total Sum: " << env.sum << std::endl;
    std::cout << "Even Count: " << env.count_even << std::endl;
}

