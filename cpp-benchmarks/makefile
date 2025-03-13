CXX = g++
CXXFLAGS = -std=c++14 -O3 -Wall -Wextra
LDFLAGS = -lpthread

# Path to SoftPosit library
SOFTPOSIT_PATH = ../softposit-cpp
INCLUDE_PATHS = -I$(SOFTPOSIT_PATH)/source/include

# Path to the softposit.a library
SOFTPOSIT_LIB = $(SOFTPOSIT_PATH)/build/Linux-x86_64-GCC/softposit.a

# Source files - using the existing files in the source directory
BENCHMARK_SRC = google_posit_benchmark_p16.cpp
SIMPLE_SRC = simple_benchmark_p16.cpp
COMPARE_SRC = posit_vs_fp_bench_p16.cpp

# The name of the benchmark executables
BENCHMARK_TARGET = build/google_posit_benchmark_p16
SIMPLE_TARGET = build/simple_benchmark_p16
COMPARE_TARGET = build/posit_vs_fp_bench_p16

all: $(BENCHMARK_TARGET) $(SIMPLE_TARGET) $(COMPARE_TARGET)

# For benchmarks that require Google Benchmark library
benchmark: $(BENCHMARK_TARGET)

# For simple benchmarks
simple: $(SIMPLE_TARGET)

# For compareision benchmarks (FP vs POSIT)
simple: $(COMPARE_TARGET)

# Rule for standard benchmark (requires Google Benchmark library)
$(BENCHMARK_TARGET): $(BENCHMARK_SRC)
	$(CXX) $(CXXFLAGS) $(INCLUDE_PATHS) -o $@ $< $(SOFTPOSIT_LIB) -lbenchmark $(LDFLAGS)


# Rule for Simple Benchmark
$(SIMPLE_TARGET): $(SIMPLE_SRC)
	$(CXX) $(CXXFLAGS) $(INCLUDE_PATHS) -o $@ $< $(SOFTPOSIT_LIB) $(LDFLAGS)

# Rule for Comparison Benchmark
$(COMPARE_TARGET): $(COMPARE_SRC)
	$(CXX) $(CXXFLAGS) $(INCLUDE_PATHS) -o $@ $< $(SOFTPOSIT_LIB) $(LDFLAGS)

clean:
	rm -f $(BENCHMARK_TARGET) $(SIMPLE_TARGET) $(COMPARE_TARGET)

.PHONY: all benchmark clean
