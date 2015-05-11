///
/// @author  Thomas Lehmann
/// @file    test.h
/// @brief   represents one test (name and function)
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
#ifndef INCLUDE_TEST_H_
#define INCLUDE_TEST_H_

#include <performance/measurement.h>
#include <string>

namespace unittest {

/// @class test
/// @brief represents one test (name and function)
class test final {
    public:
        /// function type for test "runner"
        using function_type = std::function<void()>;

        /// initializing the fields
        test(const std::string& name, function_type function)
            : m_name(name)
            , m_function(function)
            , m_succeeded(false)
            , m_error_message()
            , m_duration(-1.0) {}

        /// running all registered suites
        void run() {
            const performance::measure_scope<std::milli> measurement;
            try {
                m_function();
                m_duration = measurement.get_duration();
                m_succeeded = true;
            } catch (const assertion& test_assertion) {
                m_duration = measurement.get_duration();
                m_succeeded = false;
                m_error_message = test_assertion.what();
                m_duration = measurement.get_duration();
                throw test_assertion;
            }
        }

        /// @return true when test has succeeded
        bool has_succeeded() const noexcept {
            return m_succeeded;
        }

        /// @return name of the test
        std::string get_name() const noexcept {
            return m_name;
        }

        /// @return message of asssertion - if thrown - otherwise empty
        std::string get_error_message() const noexcept {
            return m_error_message;
        }

        /// @return duration of last test.
        double get_duration() const noexcept {
            return m_duration;
        }

    private:
        /// disable copy c'tor
        test(const test&) = delete;
        /// disable assignment
        const test& operator = (const test&) = delete;

        /// name of the test
        const std::string m_name;
        /// test function
        function_type m_function;
        /// when true then the test has succeeded
        bool m_succeeded;
        /// error message when test has failed
        std::string m_error_message;
        /// duration of test function in milliseconds.
        double m_duration;
};

}  // namespace unittest

#endif  // INCLUDE_TEST_H_

