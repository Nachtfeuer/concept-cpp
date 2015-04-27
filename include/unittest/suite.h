///
/// @author  Thomas Lehmann
/// @file    suite.h
/// @brief   suite for registered tests.
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
#ifndef INCLUDE_SUITE_H_
#define INCLUDE_SUITE_H_

#include <unittest/assert.h>
#include <unittest/test.h>
#include <unittest/report.h>
#include <algorithm/shuffled.h>

#include <functional>
#include <string>
#include <map>
#include <memory>

namespace unittest {

/// @class suite
/// @brief suite of registered tests.
class suite final {
    public:
        /// each test has a name and a function ("runner")
        using container_type = std::map<std::string, std::shared_ptr<test>>;

        /// initializing the 
        suite(const std::string& name) : m_name(name), m_tests() {}

        /// registering a suite function ("runner") und given name
        /// @param name of the suite (must be unique per suite)
        /// @param suite_function the suite function ("runner") executing individual tests.
        /// @return true when successfully registered a test function under a given name.
        bool register_test(const std::string& name,
                           test::function_type test_function) noexcept {
            if (nullptr == test_function || name.empty()) {
                return false;
            }
            auto result = m_tests.insert(container_type::value_type(name, nullptr));
            if (result.second) {
                result.first->second.reset(new test(name, test_function));
            }
            return result.second;
        }

        /// running all registered suites
        bool run(const options& the_options, report* the_report) {
            std::vector<std::shared_ptr<test>> tests;

            for (auto& it: m_tests) {
                tests.push_back(it.second);
            }

            if (the_options.shuffle_tests) {
                tests = algorithm::shuffled(tests);
            }

            bool succeeded = true;
            for (auto& it: tests) {
                try {
                    it->run();
                } catch (const assertion& e) {
                    succeeded = false;
                }
                the_report->test_done(m_name, it);
            }
            return succeeded;
        }

        /// @return number of registered tests
        container_type::size_type size() const noexcept {
            return m_tests.size();
        }

        /// @return true when there is no registered test
        bool empty() const noexcept {
            return m_tests.empty();
        }

        /// name of the suite
        std::string get_name() const noexcept {
            return m_name;
        }

    private:
        /// disable copy c'tor
        suite(const suite&) = delete;
        /// disable assignment
        const suite& operator = (const suite&) = delete;

        /// name of the suite
        const std::string m_name;
        /// container for registered tests.
        container_type m_tests;
};

}  // namespace unittest

#endif  // INCLUDE_SUITE_H_

