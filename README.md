# Posits Benchmarking

This repository contains benchmarks for Posit number format implementations, comparing performance between Posit and IEEE floating-point operations.

## About Posits

Posits are a floating-point number alternative proposed by John L. Gustafson, offering potential advantages in accuracy, dynamic range, and simplicity compared to IEEE 754 floating-point.

## Dependencies

This project uses the following repositories as submodules:

- **SoftPosit C/C++ Library**: A C/C++ implementation of the posit standard

  - Repository: [https://gitlab.com/cerlane/SoftPosit](https://gitlab.com/cerlane/SoftPosit)
  - License: BSD 3-Clause License

- **SoftPosit Rust Library**: A Rust implementation of the posit standard

  - Repository: [https://gitlab.com/burrbull/softposit-rs](https://gitlab.com/burrbull/softposit-rs)
  - License: MIT/Apache-2.0 dual license

- **Google Benchmark**: A microbenchmarking framework for C++
  - Repository: [https://github.com/google/benchmark](https://github.com/google/benchmark)
  - License: Apache-2.0 License

## Building and Running the Benchmarks

### 1. Set up Google Benchmark

First, build and install the Google Benchmark library:

```bash
git clone https://github.com/google/benchmark.git
cd benchmark
cmake -E make_directory "build"
cmake -DCMAKE_BUILD_TYPE=Release -DBENCHMARK_ENABLE_GTEST_TESTS=OFF -S . -B "build"
cmake --build "build" --config Release
sudo cmake --install "build"
```

### 2. Build SoftPosit C/C++ Library

Next, build the SoftPosit C/C++ library:

```bash
cd softposit-cpp/build/Linux-x86_64-GCC
make -j$(nproc) all  # Linux || make -j$(sysctl -n hw.ncpu) all  # macOS
```

### 3. Build and Run the C++ Benchmarks

The benchmarks are organized in the `cpp-benchmarks` directory. Build them using the provided makefile:

```bash
cd cpp-benchmarks
mkdir -p build
make all
```

This will create three benchmark executables:

- `build/google_posit_benchmark_p16`: Uses Google Benchmark framework
- `build/simple_benchmark_p16`: Simple timing benchmarks
- `build/posit_vs_fp_bench_p16`: Comparison between posits and floating-point

To run a specific benchmark:

```bash
# Run Google benchmarks
./build/google_posit_benchmark_p16

# Run simple timing benchmarks
./build/simple_benchmark_p16

# Run posit vs floating-point comparison
./build/posit_vs_fp_bench_p16
```

## Current Status

This is a work in progress. Currently, only 16-bit posit (`p16`) operations have been implemented and benchmarked:

- Basic operations:

  - Addition
  - Subtraction
  - Multiplication
  - Division

- Mathematical operations:

  - Square root
  - Rounding

- Quire operations:
  - Fused multiply-add (qma)
  - Add posit to quire
  - Convert quire to posit

Support for other posit sizes (p8, p32, p64) and additional operations will be added in future releases.

## License

This benchmarking code is released under the MIT License.

Note that the submodule libraries have their own licenses as mentioned above.

## Acknowledgements

Special thanks to:

- The SoftPosit C/C++ Library team (led by Cerlane Leong)
- The SoftPosit Rust Library developers
- The Google Benchmark team
