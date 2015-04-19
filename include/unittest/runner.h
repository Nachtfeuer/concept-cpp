///
/// @author  Thomas Lehmann
/// @file    runner.h
/// @brief   runner for registered test suoites.
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
#ifndef INCLUDE_RUNNER_H_
#define INCLUDE_RUNNER_H_

#include <unittest/suite.h>

#include <functional>
#include <string>
#include <map>
#include <memory>

namespace unittest {

/// @class runner
/// @brief runner of registered suites
class runner final {
    public:
        /// suite "runner"
        using suite_function_type = std::function<void()>;
        /// each suite has a name and a function ("runner")
        using suites_type = std::map<std::string, std::shared_ptr<suite>>;

        /// providing singleton instance of runner
        static runner& get() {
            return get_runner_instance();
        }

        /// registering a suite function ("runner") und given name
        /// @name name of the suite
        /// @suite_function the suite function ("runner") executing individual tests.
        bool register_suite(const std::string& name,
                            suite_function_type suite_function) {
            auto result = m_suites.insert(suites_type::value_type(name, nullptr));
            if (result.second) {
                result.first->second.reset(new suite);
                m_suite_name = name;
                suite_function();
                m_suite_name = "";
                return true;
            }
            return false;
        }

        /// delegates registration of a test function to a suite.
        bool register_test(const std::string& name,
                           suite::test_function_type test_function) {
            auto it = m_suites.find(m_suite_name);
            if (it != m_suites.end()) {
                return it->second->register_test(name, test_function);
            }
            return false;
        }


        /// running all registered suites
        void run() {
            for (auto& it: m_suites) {
                std::cout  << "Running suite " << it.first << std::endl;
                it.second->run();
            }
        }

    private:
        /// initializing the 
        runner() : m_suites() {}

        /// @return providing singleton instance of runner
        static runner& get_runner_instance() {
            static runner instance;
            return instance;
        }

        /// disable copy c'tor
        runner(const runner&) = delete;
        /// disable assignment
        const runner& operator = (const runner&) = delete;

        /// container for registered suites.
        suites_type m_suites;
        /// current suite name
        std::string m_suite_name;
};

}  // namespace unittest

#endif  // INCLUDE_RUNNER_H_

