///
/// @author  Thomas Lehmann
/// @file    primes.cxx
/// @brief   generating primes
///
/// Copyright (c) 2015 Thomas Lehmann
///
/// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
/// documentation files (the "Software"), to deal in the Software without restriction, including without limitation
/// the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
/// and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
///
/// The above copyright notice and this permission notice shall be included in all copies
/// or substantial portions of the Software.
///
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
/// INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
/// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
/// IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
/// DAMAGES OR OTHER LIABILITY,
/// WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
/// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
#include <math/prime/sieve_of_eratosthenes.h>
#include <generator/select.h>
#include <performance/measurement.h>

#include <boost/program_options.hpp>
#include <cstdint>

/// @struct options
/// @brief parsed command line options
struct Options {
    uint64_t max_number; ///! the biggest number that should be checked to be a prime.
};

/// @param argc number of parameters
/// @param argv array of parameters
/// @param options where to store the parsed command line options
/// @return true when all is fine and application can use the option(s).
static bool parse(int argc, char** argv, Options& options) {
    namespace po = boost::program_options;
    po::options_description description("Allowed options for tool 'primes'");
    description.add_options()
        ("help", "print this help")
        ("max-number",
         po::value<uint64_t>(&options.max_number)->default_value(1000),
         "generating primes up to this limit (default: 1000)")
        ;

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, description), vm);
    po::notify(vm);

    if (vm.count("help")) {
        std::cout << description << std::endl;
        return false;
    }

    if (options.max_number < 2) {
        std::cout << "No primes possible with a limit of "
                  << options.max_number << std::endl;
    }

    return true;
}

/// Simple example demonstrating how to generate primes.
///
/// @param argc number of parameters
/// @param argv array of parameters
/// @return 0 when succeeded, 1 when failed or when used the help
int main(int argc, char** argv) {
    Options options;
    // parsing command line options
    if (!parse(argc, argv, options)) {
        return 1;
    }

    /// initializing maximum 'size' of sieve
    math::prime::sieve_of_eratosthenes<std::vector<bool>> sieve(options.max_number);

    const auto duration = performance::measure<std::milli>([&sieve]() {
        /// calculating the primes and none primes
        sieve.calculate();
    });

    /// printing out all primes
    constexpr auto one = static_cast<uint64_t>(1);
    const auto primes =  generator::select(one, options.max_number, one)
           .where([&sieve](const int n){return sieve.is_prime(n);})
           .to_vector();

    auto first = false;
    for (const auto& prime: primes) {
        if (first) {
            std::cout << " ";
        }
        std::cout << prime;
        first = true;
    }
    std::cout << std::endl;
    std::cout << " ... " << primes.size() << " primes found." << std::endl;
    std::cout << " ... Calculation took " << duration << "ms." << std::endl;
    return 0;
}
