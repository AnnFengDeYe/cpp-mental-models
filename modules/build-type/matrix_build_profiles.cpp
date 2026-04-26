#include <iostream>
#include <benchmark/benchmark.h>
#include <Eigen/Dense>

static void PrintBuildInfo() {
#ifdef BUILD_PROFILE_NAME
    std::cout << "[build] profile = " << BUILD_PROFILE_NAME << std::endl;
#endif

#ifdef NDEBUG
    std::cout << "[build] NDEBUG defined" << std::endl;
#else
    std::cout << "[build] NDEBUG NOT defined" << std::endl;
#endif

#ifdef __OPTIMIZE__
    std::cout << "[build] optimization enabled" << std::endl;
#else
    std::cout << "[build] optimization NOT enabled" << std::endl;
#endif
}

struct BuildInfoPrinter {
    BuildInfoPrinter() { PrintBuildInfo(); }
} g_build_info_printer;

static Eigen::MatrixXd MakeSPDMatrix(int n) {
    Eigen::MatrixXd a = Eigen::MatrixXd::Random(n, n);
    return a * a.transpose() + Eigen::MatrixXd::Identity(n, n) * n;
}

static void BM_MatrixLLT(benchmark::State& state) {
    const int n = static_cast<int>(state.range(0));
    const Eigen::MatrixXd spd = MakeSPDMatrix(n);

    for (auto _ : state) {
        Eigen::LLT<Eigen::MatrixXd> llt(spd);
        benchmark::DoNotOptimize(llt.matrixLLT().data());
        benchmark::ClobberMemory();
    }

    state.counters["FLOPs"] = benchmark::Counter(
            state.iterations() * (1.0 / 3.0) * n * n * n,
            benchmark::Counter::kIsRate
    );
}

BENCHMARK(BM_MatrixLLT)
        ->Arg(500)
        ->Arg(1000)
        ->Arg(2000)
        ->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();