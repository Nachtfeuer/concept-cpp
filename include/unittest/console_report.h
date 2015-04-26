///
/// @author  Thomas Lehmann
/// @file    console_report.h
/// @brief   console report printing results to stdout.
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
#ifndef INCLUDE_UNITTEST_CONSOLE_REPORT_H_
#define INCLUDE_UNITTEST_CONSOLE_REPORT_H_

#include <unittest/report.h>
#include <unittest/test.h>

#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <algorithm>

namespace unittest {

/// @class report
/// @brief report interface which allows you to implement custom reports.
class console_report : public report {
    public:
        /// container type with test results for one suite
        using tests_container_type = std::vector<std::shared_ptr<test>>;
        /// type for one suite
        using suite_type = std::pair<std::string, tests_container_type>;
        /// container type for suites
        using suite_container_type = std::vector<suite_type>;

        /// class creator
        static report* creator() noexcept {
            return new console_report;
        }

        /// to be overwritten by a derived class
        /// @param suite_name name of the relating test suite
        /// @param finished_test the finished test
        void test_done(const std::string& suite_name,
                       std::shared_ptr<test> finished_test) override {
            auto it_suite = std::find_if(m_suites.begin(), m_suites.end(), [suite_name](const suite_type& suite) {
                return suite.first == suite_name;
            });

            if (it_suite == m_suites.end()) {
                auto suite = suite_type(suite_name, tests_container_type());
                suite.second.push_back(finished_test);
                m_suites.push_back(suite);
            } else {
                it_suite->second.push_back(finished_test);
            }
        }

        /// dumping results to stdout
        void dump() const override {
            bool success = true;
            for (const auto& suite: m_suites) {
                std::cout << std::endl << "Finished suite '" << suite.first << "'" << std::endl;
                for (const auto& test: suite.second) {
                    std::cout << "  ... test '" << test->get_name() << "'"
                              << (test->has_succeeded() ? " [succeeded]" : " [failed]")
                              << std::endl;
                    if (!test->has_succeeded()) {
                        success = false;
                        std::cout << "  ...... " << test->get_error_message() << std::endl;
                    }
                }
            }

            if (success) {
                std::cout << std::endl << "All tests have passed!" << std::endl;
            }
        }

    private:
        /// test results
        suite_container_type m_suites;
};

}  //namespace report

#endif  // INCLUDE_UNITTEST_CONSOLE_REPORT_H_
