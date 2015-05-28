///
/// @author  Thomas Lehmann
/// @file    options.h
/// @brief   options for the unittesting framework.
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
#ifndef INCLUDE_UNTTEST_OPTIONS_H_
#define INCLUDE_UNTTEST_OPTIONS_H_

#include <iostream>
#include <boost/program_options.hpp>

namespace unittest {

/// @struct options
/// @brief options for the unittesting framework.
struct options {
    /// initializing defaults
    options()
        : shuffle_tests(false)
        , shuffle_suites(false)
        , filter()
        , format("default") {}

    /// when true then shuffle the test functions otherwise
    /// execute them ordered by name (which is the default).
    bool shuffle_tests;
    /// when true then shuffle the suites otherwise
    /// execute them ordered by name (which is the default).
    bool shuffle_suites;
    /// when not empty used to filter for individual
    /// unittests to be executed.
    std::string filter;
    /// output format of the unit tests
    std::string format;
};

/// @class option_parser
/// @brief does parse the command line options storing the values into the options.
class option_parser {
    public:
        /// @return when the application should continue with the parsed
        ///         options other the help is shown or something was wrong
        ///         with the provided parameters.
        static bool parse(int argc, char** argv, options& the_options) {
            namespace po = boost::program_options;
            po::options_description description("options");
            description.add_options()
                ("help", "print this help")
                ("shuffle-suites",
                 po::value<bool>(&the_options.shuffle_suites)->default_value(false),
                 "running registered suites in random order otherwise sorted by name.")
                ("shuffle-tests",
                 po::value<bool>(&the_options.shuffle_tests)->default_value(false),
                 "running registered tests per suite in random order otherwise sorted by name.")
                ("filter",
                 po::value<std::string>(&the_options.filter)->default_value(""),
                 "filtering for individual unittests that are executed")
                ("format",
                 po::value<std::string>(&the_options.format)->default_value("default"),
                 "output format for unit tests results (default: internal format)")
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
};

}  // namespace unittest

#endif  // INCLUDE_UNTTEST_OPTIONS_H_
