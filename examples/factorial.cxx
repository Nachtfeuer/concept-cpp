///
/// @author  Thomas Lehmann
/// @file    factorial.cxx
/// @brief   factorial function
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
#include <generator/select.h>
#include <math/big_integer.h>
#include <math/big_integer_configurator.h>
#include <performance/measurement.h>

#include <boost/program_options.hpp>
#include <vector>
#include <cstdint>

/// @struct options
/// @brief parsed command line options
struct Options {
    uint64_t max_n; ///! factorial: n!
    bool all;       ///! when true showing each factorial
};

/// @param argc number of parameters
/// @param argv array of parameters
/// @param options where to store the parsed command line options
/// @return true when all is fine and application can use the option(s).
static bool parse(int argc, char** argv, Options& options) {
    namespace po = boost::program_options;
    po::options_description description("Allowed options for tool 'factorial'");
    description.add_options()
        ("help", "print this help")
        ("n", po::value<uint64_t>(&options.max_n)->default_value(100),
         "Calculating factorial: n! (default: 100)")
        ("all", po::value<bool>(&options.all)->default_value(true),
         "showing each factorials until 'n!' (default: true)")
        ;

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, description), vm);
    po::notify(vm);

    if (vm.count("help")) {
        std::cout << description << std::endl;
        return false;
    }

    return true;
}

/// Simple example demonstrating how to generate factorials.
///
/// @param argc number of parameters
/// @param argv array of parameters
/// @return 0 when succeeded, 1 when failed or when used the help
int main(int argc, char** argv) {
    std::cout << "factorial tool (version " << VERSION << ")" << std::endl;

    Options options;
    // parsing command line options
    if (!parse(argc, argv, options)) {
        return 1;
    }

    // registering implementations
    math::big_integer_configurator bic;
    bic.configure();

    math::big_integer bi = 1;
    std::cout << options.max_n << "!" << std::endl << std::endl;

    std::vector<math::big_integer> results;

    const auto duration = performance::measure<std::milli>([&options, &bi, &results]() {
        for (auto n = static_cast<uint64_t>(2); n <= options.max_n; ++n) {
            bi *= math::big_integer(n);
            if (options.all) {
                results.push_back(bi);
            }
        }
    });

    if (!options.all) {
        results.push_back(bi);
    }

    for (const auto& result: results) {
        std::cout << result.to_string() << std::endl;
    }

    std::cout << std::endl;
    std::cout << " ... " << bi.size() << " digits." << std::endl;
    std::cout << " ... Calculation only took " << duration << "ms." << std::endl;
    return 0;
}
