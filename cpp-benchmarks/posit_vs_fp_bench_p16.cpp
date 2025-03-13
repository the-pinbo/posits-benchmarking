#include "include/softposit_cpp.h"
#include <chrono>
#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <iomanip>
#include <cmath>
#include <random>
#include <fstream>

// Benchmark utility that compares SoftPosit with standard floating-point types
class ComparativeBenchmark
{
private:
    template <typename T>
    static double runTimed(const std::function<T()> &fn, size_t iterations)
    {
        // Warmup
        for (size_t i = 0; i < iterations / 10; ++i)
        {
            volatile T result = fn();
            (void)result; // Prevent optimization
        }

        // Actual timing
        auto start = std::chrono::high_resolution_clock::now();
        for (size_t i = 0; i < iterations; ++i)
        {
            volatile T result = fn();
            (void)result; // Prevent optimization
        }
        auto end = std::chrono::high_resolution_clock::now();

        return static_cast<double>(
                   std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count()) /
               iterations;
    }

public:
    template <typename T1, typename T2>
    static void compare(const std::string &name,
                        const std::function<T1()> &fn1,
                        const std::function<T2()> &fn2,
                        const std::string &type1Name = "posit16",
                        const std::string &type2Name = "float",
                        size_t iterations = 1000000)
    {

        std::cout << "Comparing: " << name << std::endl;

        double time1 = runTimed<T1>(fn1, iterations);
        double time2 = runTimed<T2>(fn2, iterations);
        double ratio = time1 / time2;

        std::cout << std::fixed << std::setprecision(2);
        std::cout << "  " << type1Name << ": " << time1 << " ns per iteration ("
                  << 1e9 / time1 << " ops/sec)" << std::endl;
        std::cout << "  " << type2Name << ": " << time2 << " ns per iteration ("
                  << 1e9 / time2 << " ops/sec)" << std::endl;
        std::cout << "  Ratio (" << type1Name << "/" << type2Name << "): " << ratio
                  << "x" << std::endl;
        std::cout << std::endl;
    }

    // Generate comparative results in CSV format
    static void generateCSV(const std::string &filename)
    {
        std::ofstream file(filename);
        if (!file)
        {
            std::cerr << "Failed to open " << filename << " for writing" << std::endl;
            return;
        }

        // Header
        file << "Operation,posit16 (ns),float (ns),Ratio (posit16/float)" << std::endl;

        // Generate random values for testing
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(1.0, 100.0);

        // Create arrays of test values
        std::vector<posit16> posits;
        std::vector<float> floats;
        const size_t TEST_SIZE = 1000;
        const size_t ITERATIONS = 100000;

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            double val = dis(gen);
            posits.push_back(posit16(val));
            floats.push_back(static_cast<float>(val));
        }

        // Test addition
        double positTime = runTimed<posit16>([&]()
                                             {
            posit16 sum(0);
            for (size_t i = 0; i < TEST_SIZE; ++i) {
                sum += posits[i];
            }
            return sum; }, ITERATIONS);

        double floatTime = runTimed<float>([&]()
                                           {
            float sum = 0;
            for (size_t i = 0; i < TEST_SIZE; ++i) {
                sum += floats[i];
            }
            return sum; }, ITERATIONS);

        file << "Addition," << positTime << "," << floatTime << "," << (positTime / floatTime) << std::endl;

        // Test multiplication
        positTime = runTimed<posit16>([&]()
                                      {
            posit16 product(1);
            for (size_t i = 0; i < TEST_SIZE; ++i) {
                product *= posits[i % 10];
            }
            return product; }, ITERATIONS);

        floatTime = runTimed<float>([&]()
                                    {
            float product = 1;
            for (size_t i = 0; i < TEST_SIZE; ++i) {
                product *= floats[i % 10];
            }
            return product; }, ITERATIONS);

        file << "Multiplication," << positTime << "," << floatTime << "," << (positTime / floatTime) << std::endl;

        // Test division
        positTime = runTimed<posit16>([&]()
                                      {
            posit16 result(100);
            for (size_t i = 0; i < TEST_SIZE; ++i) {
                if (i % 10 != 0) // Avoid division by values close to zero
                    result /= posits[i % 10];
            }
            return result; }, ITERATIONS);

        floatTime = runTimed<float>([&]()
                                    {
            float result = 100;
            for (size_t i = 0; i < TEST_SIZE; ++i) {
                if (i % 10 != 0) // Avoid division by values close to zero
                    result /= floats[i % 10];
            }
            return result; }, ITERATIONS);

        file << "Division," << positTime << "," << floatTime << "," << (positTime / floatTime) << std::endl;

        // Test square root
        positTime = runTimed<posit16>([&]()
                                      {
            posit16 result = posits[0];
            result.sqrt();
            return result; }, ITERATIONS);

        floatTime = runTimed<float>([&]()
                                    { return std::sqrt(floats[0]); }, ITERATIONS);

        file << "Square Root," << positTime << "," << floatTime << "," << (positTime / floatTime) << std::endl;

        std::cout << "Benchmark results saved to " << filename << std::endl;
    }
};

int main()
{
    std::cout << "SoftPosit vs Float Comparison Benchmark" << std::endl;
    std::cout << "=======================================" << std::endl
              << std::endl;

    // Constants for benchmark
    const posit16 pX(12.5);
    const posit16 pY(117.334);
    const float fX = 12.5f;
    const float fY = 117.334f;

    // Compare basic operations
    ComparativeBenchmark::compare<posit16, float>(
        "Addition",
        [=]()
        { return pX + pY; },
        [=]()
        { return fX + fY; });

    ComparativeBenchmark::compare<posit16, float>(
        "Subtraction",
        [=]()
        { return pX - pY; },
        [=]()
        { return fX - fY; });

    ComparativeBenchmark::compare<posit16, float>(
        "Multiplication",
        [=]()
        { return pX * pY; },
        [=]()
        { return fX * fY; });

    ComparativeBenchmark::compare<posit16, float>(
        "Division",
        [=]()
        { return pX / pY; },
        [=]()
        { return fX / fY; });

    // Compare mathematical operations
    ComparativeBenchmark::compare<posit16, float>(
        "Square Root",
        [=]()
        {
            posit16 temp = pX;
            temp.sqrt();
            return temp;
        },
        [=]()
        { return std::sqrt(fX); });

    ComparativeBenchmark::compare<posit16, float>(
        "Rounding",
        [=]()
        {
            posit16 temp = pY;
            temp.rint();
            return temp;
        },
        [=]()
        { return std::round(fY); });

    // Generate CSV
    ComparativeBenchmark::generateCSV("posit_vs_float_benchmark.csv");

    return 0;
}