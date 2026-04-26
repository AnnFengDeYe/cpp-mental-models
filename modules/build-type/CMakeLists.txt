# ==========================================
# Eigen & Benchmark
# ==========================================
include(FetchContent)

# Eigen
FetchContent_Declare(
        eigen
        GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git
        GIT_TAG        3.4.0
)
FetchContent_MakeAvailable(eigen)

# Google Benchmark
set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "Disable benchmark tests" FORCE)
set(BENCHMARK_ENABLE_INSTALL OFF CACHE BOOL "Disable benchmark install" FORCE)

FetchContent_Declare(
        benchmark
        GIT_REPOSITORY https://github.com/google/benchmark.git
        GIT_TAG        v1.8.3
)
FetchContent_MakeAvailable(benchmark)

target_compile_options(benchmark PRIVATE -O3)
target_compile_definitions(benchmark PRIVATE NDEBUG)
target_compile_options(benchmark_main PRIVATE -O3)
target_compile_definitions(benchmark_main PRIVATE NDEBUG)

# ------------------------------------------
# Debug vs Release
# ------------------------------------------
add_executable(matrix_bench_debug matrix_bench.cpp)
target_link_libraries(matrix_bench_debug PRIVATE eigen benchmark::benchmark benchmark::benchmark_main)
target_compile_options(matrix_bench_debug PRIVATE -O0 -g -UNDEBUG)

add_executable(matrix_bench_release matrix_bench.cpp)
target_link_libraries(matrix_bench_release PRIVATE eigen benchmark::benchmark benchmark::benchmark_main)
target_compile_options(matrix_bench_release PRIVATE -O3 -march=native)
target_compile_definitions(matrix_bench_release PRIVATE NDEBUG)


# ------------------------------------------
# Profiles
# ------------------------------------------
set(MATRIX_PROFILE_SOURCE matrix_build_profiles.cpp)

# 1) Profile
add_executable(matrix_profiles_profile ${MATRIX_PROFILE_SOURCE})
target_link_libraries(matrix_profiles_profile PRIVATE eigen benchmark::benchmark benchmark::benchmark_main)
target_compile_options(matrix_profiles_profile PRIVATE
        -Wall -Wextra -Wpedantic
        -O2 -g -march=native
)
target_compile_definitions(matrix_profiles_profile PRIVATE
        NDEBUG
        BUILD_PROFILE_NAME="Profile"
)

# 2) FastRelease
add_executable(matrix_profiles_fast ${MATRIX_PROFILE_SOURCE})
target_link_libraries(matrix_profiles_fast PRIVATE eigen benchmark::benchmark benchmark::benchmark_main)
target_compile_options(matrix_profiles_fast PRIVATE
        -Wall -Wextra -Wpedantic
        -O3 -march=native
)
target_compile_definitions(matrix_profiles_fast PRIVATE
        NDEBUG
        BUILD_PROFILE_NAME="FastRelease"
)

# 3) MinSizeRelCustom
add_executable(matrix_profiles_size ${MATRIX_PROFILE_SOURCE})
target_link_libraries(matrix_profiles_size PRIVATE eigen benchmark::benchmark benchmark::benchmark_main)
target_compile_options(matrix_profiles_size PRIVATE
        -Wall -Wextra -Wpedantic
        -Os
)
target_compile_definitions(matrix_profiles_size PRIVATE
        NDEBUG
        BUILD_PROFILE_NAME="MinSizeRelCustom"
)