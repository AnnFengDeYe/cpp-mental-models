#include <iostream>
#include <benchmark/benchmark.h>
#include <Eigen/Dense>

static void PrintBuildInfo() {
#ifdef NDEBUG
    std::cout << "[build] NDEBUG defined\n";
#else
    std::cout << "[build] NDEBUG NOT defined\n";
#endif

#ifdef __OPTIMIZE__
    std::cout << "[build] optimization enabled\n";
#else
    std::cout << "[build] optimization NOT enabled\n";
#endif
}

struct BuildInfoPrinter {
    BuildInfoPrinter() { PrintBuildInfo(); }
} build_info_printer;

static void BM_MatrixDecomposition(benchmark::State& state) {
    const int N = state.range(0);

    Eigen::MatrixXd A = Eigen::MatrixXd::Random(N, N);
    Eigen::MatrixXd SPD = A * A.transpose() + Eigen::MatrixXd::Identity(N, N) * N;

    for (auto _ : state) {
        Eigen::LLT<Eigen::MatrixXd> lltOfA(SPD);

        benchmark::DoNotOptimize(lltOfA.matrixLLT().data());

        benchmark::ClobberMemory();
    }

    state.counters["FLOPs"] = benchmark::Counter(
            state.iterations() * (1.0 / 3.0) * N * N * N,
            benchmark::Counter::kIsRate
    );
}

BENCHMARK(BM_MatrixDecomposition)
        ->Arg(500)
        ->Arg(1000)
        ->Arg(2000)
        ->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();