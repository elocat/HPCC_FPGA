/*
Copyright (c) 2019 Marius Meyer

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is furnished to do
so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef SRC_HOST_RANDOM_ACCESS_BENCHMARK_H_
#define SRC_HOST_RANDOM_ACCESS_BENCHMARK_H_

/* C++ standard library headers */
#include <complex>
#include <memory>

/* Project's headers */
#include "hpcc_benchmark.hpp"
#include "parameters.h"

/**
 * @brief Contains all classes and methods needed by the STREAM benchmark
 * 
 */
namespace random_access {

/**
 * @brief The random access specific program settings
 * 
 */
class RandomAccessProgramSettings : public hpcc_base::BaseSettings {

public:
    /**
     * @brief The size of the data array
     * 
     */
    size_t dataSize;

    /**
     * @brief The number of used kernel replications
     * 
     */
    uint kernelReplications;

    /**
     * @brief Construct a new random access Program Settings object
     * 
     * @param results the result map from parsing the program input parameters
     */
    RandomAccessProgramSettings(cxxopts::ParseResult &results);

    /**
     * @brief Construct a new random access Program Settings object
     * 
     * @return a map of program parameters. keys are the name of the parameter.
     */
    std::map<std::string, std::string> getSettingsMap() override;

};

/**
 * @brief Data class cotnaining the data the kernel is exeucted with
 * 
 */
class RandomAccessData {

public:
    HOST_DATA_TYPE *data;
    RandomAccessData(HOST_DATA_TYPE *data_) : data(data_) {}

};

/**
 * @brief Measured execution timing from the kernel execution
 * 
 */
class RandomAccessExecutionTimings {
public:
    /**
     * @brief A vector containing the timings for all repetitions
     * 
     */
    std::vector<double> times;

};

/**
 * @brief Implementation of the random access benchmark
 * 
 */
class RandomAccessBenchmark : public hpcc_base::HpccFpgaBenchmark<RandomAccessProgramSettings, RandomAccessData, RandomAccessExecutionTimings> {

protected:

    /**
     * @brief Additional input parameters of the random access benchmark
     * 
     * @param options 
     */
    void
    addAdditionalParseOptions(cxxopts::Options &options) override;

public:

    /**
     * @brief Random access specific implementation of the data generation
     * 
     * @param settings 
     * @return std::shared_ptr<RandomAccessData> 
     */
    std::shared_ptr<RandomAccessData>
    generateInputData(const hpcc_base::ExecutionSettings<RandomAccessProgramSettings> &settings) override;

    /**
     * @brief RandomAccess specific implementation of the kernel execution
     * 
     * @param settings 
     * @param data 
     * @return std::shared_ptr<RandomAccessExecutionTimings> 
     */
    std::shared_ptr<RandomAccessExecutionTimings>
    executeKernel(const hpcc_base::ExecutionSettings<RandomAccessProgramSettings> &settings, RandomAccessData &data) override;

    /**
     * @brief RandomAccess specific implementation of the execution validation
     * 
     * @param settings 
     * @param data 
     * @param output 
     * @return true 
     * @return false 
     */
    bool
    validateOutputAndPrintError(const hpcc_base::ExecutionSettings<RandomAccessProgramSettings> &settings ,RandomAccessData &data, const RandomAccessExecutionTimings &output) override;

    /**
     * @brief RandomAccess specific implementation of printing the execution results
     * 
     * @param settings 
     * @param output 
     */
    void
    printResults(const hpcc_base::ExecutionSettings<RandomAccessProgramSettings> &settings, const RandomAccessExecutionTimings &output) override;

    /**
     * @brief Construct a new RandomAccess Benchmark object
     * 
     * @param argc the number of program input parameters
     * @param argv the program input parameters as array of strings
     */
    RandomAccessBenchmark(int argc, char* argv[]);

        /**
     * @brief Construct a new RandomAccess Benchmark object
     */
    RandomAccessBenchmark();

};

} // namespace stream


#endif // SRC_HOST_STREAM_BENCHMARK_H_
