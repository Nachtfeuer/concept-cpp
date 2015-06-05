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
#include <math/number.h>
#include <generator/select.h>
#include <performance/measurement.h>

#include <boost/program_options.hpp>
#include <string>
#include <iomanip>
#include <cstdint>

/// @struct options
/// @brief parsed command line options
struct Options {
    /// type of filter function
    using filter_function_type = std::function<bool (const uint64_t&)>;

    uint64_t max_number;         ///! the biggest number that should be checked to be a prime.
    uint64_t max_columns;        ///! number of columns for printing primes
    filter_function_type filter; ///! additional filter function

    /// default c'tor initializing defaults
    Options()
        : max_number(1000), max_columns(10), filter(nullptr) {}
};

/// Providing filter as configured.
/// @param filter_name name of the filter
/// @return concrete filter function or true function.
Options::filter_function_type resolve_filter(const std::string& filter_name) noexcept {
    if (filter_name == "pandigital") {
        std::cout << " ... applying 'pandigital' filter" << std::endl;
        return [](const uint64_t number) {return math::number<uint64_t>::is_pandigital(number);};
    }
    if (filter_name == "palindrome") {
        std::cout << " ... applying 'palindrome' filter" << std::endl;
        return [](const uint64_t number) {return math::number<uint64_t>::is_palindrome(number);};
    }
    std::cout << " ... no additional filter" << std::endl;
    return [](const uint64_t) {return true;};
} 

/// @param argc number of parameters
/// @param argv array of parameters
/// @param options where to store the parsed command line options
/// @return true when all is fine and application can use the option(s).
static bool parse(int argc, char** argv, Options& options) {
    namespace po = boost::program_options;
    std::string filter_name;
    po::options_description description("Allowed options for tool 'primes'");
    description.add_options()
        ("help", "print this help")
        ("max-number", po::value<uint64_t>(&options.max_number)->default_value(1000),
         "generating primes up to this limit (default: 1000)")
        ("columns", po::value<uint64_t>(&options.max_columns)->default_value(10),
         "number of columns (default: 10)")
        ("filter", po::value<std::string>(&filter_name)->default_value(""),
         "providing filter name (default: none).")
        ;

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, description), vm);
    po::notify(vm);

    if (vm.count("help")) {
        std::cout << description << std::endl;
        return false;
    }

    options.filter = resolve_filter(filter_name);

    if (options.max_columns < 1) {
        std::cout << "error: You cannot have 0 columns" << std::endl;
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
    std::cout << "prime tool" << std::endl;

    Options options;
    // parsing command line options
    if (!parse(argc, argv, options)) {
        return 1;
    }

    std::cout << " ... creating sieve up to max. number: " << options.max_number << std::endl;
    /// initializing maximum 'size' of sieve
    math::prime::sieve_of_eratosthenes<std::vector<bool>> sieve(options.max_number);

    const auto sieve_duration = performance::measure<std::milli>([&sieve]() {
        /// calculating the primes and none primes
        sieve.calculate();
    });

    std::cout << " ... collecting primes" << std::endl;
    std::cout << std::endl;

    /// printing out all primes
    constexpr auto one = static_cast<uint64_t>(1);
    const auto primes = generator::select(one, options.max_number, one)
           .where([&sieve](const int n){return sieve.is_prime(n);})
           .where(options.filter)
           .to_vector();

    const auto width = math::digits<int>::count(*(primes.end()-1)) + 1;

    auto column = static_cast<uint64_t>(0);
    for (const auto& prime: primes) {
        std::cout << std::setw(width) << prime;
        ++column;
        if (column % options.max_columns == 0) {
            std::cout << std::endl;
        }
    }
    std::cout << std::endl << std::endl;
    std::cout << " ... " << primes.size() << " primes found." << std::endl;
    std::cout << " ... Sieve calculation took " << sieve_duration << "ms." << std::endl;
    return 0;
}
