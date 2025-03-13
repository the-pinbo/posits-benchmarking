#include "include/softposit_cpp.h"
#include <chrono>
#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include <numeric>

// Simple benchmark utility for environments without Google Benchmark
class SimpleBenchmark
{
public:
    static void run(const std::string &name, const std::function<void()> &fn, size_t iterations = 1e7)
    {
        std::cout << "Running benchmark: " << name << std::endl;

        // Warmup
        for (size_t i = 0; i < iterations / 10; ++i)
        {
            fn();
        }

        // Actual timing
        std::vector<double> times;
        times.reserve(10);

        for (int run = 0; run < 10; ++run)
        {
            auto start = std::chrono::high_resolution_clock::now();

            for (size_t i = 0; i < iterations; ++i)
            {
                fn();
            }

            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

            times.push_back(static_cast<double>(duration) / iterations);
        }

        // Calculate statistics
        std::sort(times.begin(), times.end());
        double median = (times[4] + times[5]) / 2.0;
        double sum = std::accumulate(times.begin(), times.end(), 0.0);
        double mean = sum / times.size();

        double variance = 0.0;
        for (double time : times)
        {
            variance += (time - mean) * (time - mean);
        }
        variance /= times.size();
        double stddev = std::sqrt(variance);

        // Print results
        std::cout << std::fixed << std::setprecision(2);
        std::cout << "  Median time: " << median << " ns per iteration" << std::endl;
        std::cout << "  Mean time:   " << mean << " ns per iteration" << std::endl;
        std::cout << "  Std dev:     " << stddev << " ns" << std::endl;
        std::cout << "  Operations:  " << std::setprecision(2) << 1e9 / median << " ops/sec" << std::endl;
        std::cout << std::endl;
    }
};

// Constants matching the Rust benchmark
const posit16 X(12.5);    // 0x6c80 in hex
const posit16 Y(117.334); // 0x79ab in hex

// Create a PI constant for the quire16
quire16 createQuire16PI()
{
    quire16 q;
    q.clr();
    posit16 pi_posit(3.14159265358979323846);
    q.qma(pi_posit, posit16(1.0));
    return q;
}

int main()
{
    std::cout << "SoftPosit C++ Benchmark" << std::endl;
    std::cout << "======================" << std::endl
              << std::endl;

    // Basic operations
    SimpleBenchmark::run("p16_add", []()
                         { posit16 result = X + Y; });
    SimpleBenchmark::run("p16_sub", []()
                         { posit16 result = X - Y; });
    SimpleBenchmark::run("p16_mul", []()
                         { posit16 result = X * Y; });
    SimpleBenchmark::run("p16_div", []()
                         { posit16 result = X / Y; });

    // Mathematical operations
    SimpleBenchmark::run("p16_sqrt", []()
                         { 
        posit16 temp = X;
        temp.sqrt(); });

    SimpleBenchmark::run("p16_round", []()
                         {
        posit16 temp = Y;
        temp.rint(); });

    // * NOTE:Transcendental functions for now :)
    SimpleBenchmark::run("p16_exp", []()
                         {
        double value = X.toDouble();
        double result = std::exp(value);
        posit16 posit_result(result); });

    SimpleBenchmark::run("p16_exp2", []()
                         {
        double value = X.toDouble();
        double result = std::exp2(value);
        posit16 posit_result(result); });

    SimpleBenchmark::run("p16_ln", []()
                         {
        double value = X.toDouble();
        double result = std::log(value);
        posit16 posit_result(result); });

    SimpleBenchmark::run("p16_log2", []()
                         {
        double value = X.toDouble();
        double result = std::log2(value);
        posit16 posit_result(result); });

    SimpleBenchmark::run("p16_sin_pi", []()
                         {
        double value = X.toDouble() * M_PI;
        double result = std::sin(value);
        posit16 posit_result(result); });

    SimpleBenchmark::run("p16_cos_pi", []()
                         {
        double value = X.toDouble() * M_PI;
        double result = std::cos(value);
        posit16 posit_result(result); });

    SimpleBenchmark::run("p16_tan_pi", []()
                         {
        double value = X.toDouble() * M_PI;
        double result = std::tan(value);
        posit16 posit_result(result); }, 1e5);

    // Quire operations
    SimpleBenchmark::run("q16_add_product", []()
                         {
        quire16 q = createQuire16PI();
        q.qma(X, Y); });

    SimpleBenchmark::run("q16_add_posit", []()
                         {
        quire16 q = createQuire16PI();
        q.qma(X, posit16(1.0)); });

    SimpleBenchmark::run("q16_to_posit", []()
                         {
        quire16 q = createQuire16PI();
        posit16 result = q.toPosit(); });

    return 0;
}