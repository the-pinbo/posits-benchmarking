# Posits Benchmarking

This repository contains benchmarks for Posit number format implementations, comparing performance between Posit and IEEE floating-point operations.

## About

This repository provides benchmarks for the Posit number format, a floating-point alternative proposed by John L. Gustafson. The benchmarks measure performance of Posit operations compared to traditional IEEE-754 floating-point operations across different implementations and languages.

## Dependencies

This project includes the following repositories as submodules:

- **SoftPosit C/C++ Library**: C/C++ implementation of the posit standard

  - Repository: [https://gitlab.com/cerlane/SoftPosit](https://gitlab.com/cerlane/SoftPosit)
  - License: BSD 3-Clause "New" or "Revised" License

- **SoftPosit Rust Library**: Rust implementation of the posit standard

  - Repository: [https://gitlab.com/burrbull/softposit-rs](https://gitlab.com/burrbull/softposit-rs)
  - License: BSD 3-Clause "New" or "Revised" License

- **Google Benchmark**: Microbenchmarking framework for C++
  - Repository: [https://github.com/google/benchmark](https://github.com/google/benchmark)
  - License: Apache-2.0 License

## Getting Started

### Clone the Repository with Submodules

```bash
git clone --recursive https://github.com/the-pinbo/posits-benchmarking.git
cd posits-benchmarking
```

If you've already cloned the repository without the `--recursive` flag:

```bash
git submodule update --init --recursive
```

### Building and Running C++ Benchmarks

1. **Build SoftPosit C/C++ Library**:

   ```bash
    cd softposit-cpp/build/Linux-x86_64-GCC
    make -j$(nproc) all  # Linux || make -j$(sysctl -n hw.ncpu) all  # macOS
   ```

2. **Build Google Benchmark** (already included as a submodule):

   ```bash
   cd google-benchmark
   cmake -E make_directory "build"
   cmake -DCMAKE_BUILD_TYPE=Release -DBENCHMARK_ENABLE_GTEST_TESTS=OFF -S . -B "build"
   cmake --build "build" --config Release
   cd ..
   ```

3. **Build C++ Benchmarks**:

   ```bash
   cd cpp-benchmarks
   mkdir -p build
   make all
   ```

4. **Run C++ Benchmarks**:

   ```bash
   # Run Google benchmarks
   ./build/google_posit_benchmark_p16

   # Run simple timing benchmarks
   ./build/simple_benchmark_p16

   # Run posit vs floating-point comparison
   ./build/posit_vs_fp_bench_p16
   ```

### Running Rust Benchmarks

The Rust benchmarks are already implemented in the SoftPosit Rust library:

1. **Ensure Rust is installed**:
   If you don't have Rust installed, follow the instructions at [https://www.rust-lang.org/tools/install](https://www.rust-lang.org/tools/install)

2. **Run Rust benchmarks**:

   ```bash
   cd softposit-rs
   cargo bench
   ```

   This will run all benchmarks defined in the `benches` directory.

## Current Status

This is a work in progress. Currently, the following operations have been benchmarked:

### C++ Benchmarks (P16 only)

- Basic operations: addition, subtraction, multiplication, division
- Mathematical operations: square root, rounding
- Quire operations: fused multiply-add (qma), add posit to quire, convert quire to posit

## License

This benchmarking code is released under the MIT License.

Note that the submodule libraries have their own licenses as mentioned above.

## Acknowledgements

Special thanks to:

- The SoftPosit C/C++ Library team (led by Cerlane Leong)
- The SoftPosit Rust Library developers
- The Google Benchmark team
