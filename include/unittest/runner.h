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

#include <unittest/options.h>
#include <unittest/suite.h>
#include <unittest/console_report.h>

#include <algorithm/shuffled.h>
#include <pattern/factory.h>

#include <functional>
#include <string>
#include <map>
#include <vector>
#include <memory>

namespace unittest {

/// @class runner
/// @brief runner of registered suites
class runner final {
    public:
        /// suite "runner"
        using suite_function_type = std::function<void()>;
        /// each suite has a name and a function ("runner")
        using container_type = std::map<std::string, std::shared_ptr<suite>>;
        /// type for report factory
        using report_factory = pattern::factory<std::string, report>;

        /// providing singleton instance of runner
        static runner& get() noexcept {
            return get_runner_instance();
        }

        /// registering a suite function ("runner") und given name
        /// @name name of the suite
        /// @suite_function the suite function ("runner") executing individual tests.
        bool register_suite(const std::string& name,
                            suite_function_type suite_function) noexcept {
            if (nullptr == suite_function || name.empty()) {
                return false;
            }

            auto result = m_suites.insert(container_type::value_type(name, nullptr));
            if (result.second) {
                result.first->second.reset(new suite(name));
                m_suite_name = name;
                suite_function();
                m_suite_name = "";
                return true;
            }
            return false;
        }

        /// delegates registration of a test function to a suite.
        bool register_test(const std::string& name,
                           test::function_type test_function) noexcept {
            auto it = m_suites.find(m_suite_name);
            if (it != m_suites.end()) {
                return it->second->register_test(name, test_function);
            }
            return false;
        }


        /// running all registered suites
        bool run(int argc, char** argv) noexcept {
            if (!option_parser::parse(argc, argv, m_options)) {
                return false;
            }

            m_report.reset(report_factory::get().create_instance("default"));

            std::vector<suite*> suites;

            for (auto& it: m_suites) {
                if (m_options.filter.empty() ||
                    it.second->get_name().find(m_options.filter) != std::string::npos) {
                    suites.push_back(it.second.get());
                }
            }

            if (m_options.shuffle_suites) {
                suites = algorithm::shuffled(suites);
            }

            bool succeeded = true;
            for (auto& it: suites) {
                if (!it->run(m_options, m_report.get())) {
                    succeeded = false;
                }
            }

            if (m_report) {
                m_report->dump();
            }

            return succeeded;
        }

        /// @return number of registered suites
        container_type::size_type size() const noexcept {
            return m_suites.size();
        }

        /// @return true when there is no registered suite
        bool empty() const noexcept {
            return m_suites.empty();
        }

    private:
        /// initializing the 
        runner() : m_options(), m_suites(), m_report(nullptr) {
            report_factory::get().register_creator("default", console_report::creator);
        }

        /// @return providing singleton instance of runner
        static runner& get_runner_instance() noexcept {
            static runner instance;
            return instance;
        }

        /// disable copy c'tor
        runner(const runner&) = delete;
        /// disable assignment
        const runner& operator = (const runner&) = delete;

        /// options for the unittest framework
        options m_options;
        /// container for registered suites.
        container_type m_suites;
        /// current suite name (only valid via run)
        std::string m_suite_name;
        /// report to dump the results
        std::unique_ptr<report> m_report;
};

}  // namespace unittest

#endif  // INCLUDE_RUNNER_H_

