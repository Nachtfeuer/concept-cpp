///
/// @author  Thomas Lehmann
/// @file    select.h
/// @brief   select/selector takes a range definition.
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

#ifndef INCLUDE_GENERATOR_SELECT_H_
#define INCLUDE_GENERATOR_SELECT_H_

#include <matcher/matcher.h>

#include <vector>
#include <list>
#include <functional>
#include <numeric>
#include <algorithm>
#include <stdexcept>

namespace generator {

/// @class selector<T>
/// @brief provides a query for a container
template <typename T>
class selector final {
    public:
        /// type for container
        using container_type = std::vector<T>;
        /// type of value for given container
        using value_type = T;

        /// type for the filter function
        using filter_function_type = std::function<bool (const value_type&)>;
        /// type for container of registered filter functions
        using filter_container_type = std::vector<filter_function_type>;

        /// type for the transform function
        using transform_function_type = std::function<void (value_type&)>;
        /// type for container of registered transform functions
        using transform_container_type = std::vector<transform_function_type>;

        /// "selecting" a range
        selector(const T& from_value, const T& to_value, const T& step_value)
            : m_from_value(from_value)
            , m_to_value(to_value)
            , m_step_value(step_value)
            , m_filters()
            , m_transforms() {}

        /// register a filter function
        /// @param filter a filter function that returns true when a value should be included
        /// @return selector to continue with further operations on it.
        /// @note all registrations are working like a "and" filter.
        selector& where(filter_function_type filter) noexcept {
            m_filters.push_back(filter);
            return *this;
        }

        /// register a filter functions (closure) that captures provided matcher
        /// @param matcher a matcher that returns true when a value should be included
        /// @return selector to continue with further operations on it.
        /// @note all registrations are working like a "and" filter.
        selector& where(matcher::shared_matcher<value_type> matcher) noexcept {
            m_filters.push_back([&matcher](const value_type& value) {
                    return matcher->check(value);
            });
            return *this;
        }

        /// register a transform function
        /// @return selector to continue with further operations on it.
        /// @note all transformations are done in order of executions
        selector& transform(transform_function_type transform) noexcept {
            m_transforms.push_back(transform);
            return *this;
        }

        /// @return provides entries reflecting the provided filters.
        container_type to_vector() const noexcept {
            container_type results;

            auto condition = (m_step_value > 0)
                ? [](const T& current, const T& to_value) {return current <= to_value;}
                : [](const T& current, const T& to_value) {return current >= to_value;};

            for (auto it = m_from_value; condition(it, m_to_value); it += m_step_value) {
                auto ignore = false;
                for (auto filter: m_filters) {
                    if (!filter(it)) {
                        ignore = true;
                        break;
                    }
                }

                if (!ignore) {
                    auto value = it;
                    for (const auto& transform: m_transforms) {
                        transform(value);
                    }

                    results.push_back(value);
                }
            }
            return results;
        }

        /// @return sum of values
        value_type sum() const noexcept {
            const auto values = to_vector();
            return std::accumulate(values.begin(), values.end(), static_cast<value_type>(0));
        }

        /// @return smallest of values
        value_type min() const {
            const auto values = to_vector();
            if (values.empty()) {
                throw std::range_error("no elements to find min value in");
            }
            return *std::min_element(values.begin(), values.end());
        }

        /// @return biggest of values
        value_type max() const {
            const auto values = to_vector();
            if (values.empty()) {
                throw std::range_error("no elements to find max value in");
            }
            return *std::max_element(values.begin(), values.end());
        }

        /// @return average of all values
        double average() const noexcept {
            const auto values = to_vector();
            return std::accumulate(values.begin(), values.end(), static_cast<value_type>(0))
                 / static_cast<double>(values.size());
        }

        /// @return median of all values
        double median() const noexcept {
            auto values = to_vector();
            if (values.empty()) {
                return 0.0;
            }

            std::sort(values.begin(), values.end());
            if (values.size() % 2 == 0) {
                auto pos = values.size() / 2 - 1;
                return (values[pos] + values[pos+1]) / 2.0;
            } else {
                auto pos = values.size() / 2;
                return values[pos];
            }
        }

    private:
        /// start value of the range
        const T m_from_value;
        /// end value of the range
        const T m_to_value;
        /// step value of the range
        const T m_step_value;
        /// container of registered filters
        filter_container_type m_filters;
        /// container of registered transforms
        transform_container_type m_transforms;
};

template <typename T>
selector<T> select(const T& from_value, const T& to_value, const T& step_value) noexcept {
    return selector<T>(from_value, to_value, step_value);
}

}  // namespace generator

#endif  // INCLUDE_GENERATOR_SELECT_H_
