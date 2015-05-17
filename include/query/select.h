///
/// @author  Thomas Lehmann
/// @file    select.h
/// @brief   select/selector takes a container.
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

#ifndef INCLUDE_QUERY_SELECT_H_
#define INCLUDE_QUERY_SELECT_H_

#include <matcher/matcher.h>

#include <vector>
#include <list>
#include <functional>
#include <numeric>
#include <algorithm>
#include <stdexcept>

namespace query {

/// @class selector<T>
/// @brief provides a query for a container
template <typename T>
class selector final {
    public:
        /// type for container
        using container_type = T;
        /// type of value for given container
        using value_type = typename T::value_type;

        /// type for the filter function
        using filter_function_type = std::function<bool (const value_type&)>;
        /// type for container of registered filter functions
        using filter_container_type = std::vector<filter_function_type>;

        /// type for the transform function
        using transform_function_type = std::function<void (value_type&)>;
        /// type for container of registered transform functions
        using transform_container_type = std::vector<transform_function_type>;

        /// "selecting" a container keeping the reference
        selector(const container_type& container)
            : m_container(container), m_filters(), m_transforms() {}

        /// @return number of entries in the container
        typename container_type::size_type size() const noexcept {
            return m_container.size();
        }

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
        selector& where(const matcher::matcher<value_type>& matcher) noexcept {
            m_filters.push_back([&matcher](const value_type& value) {
                    return matcher.check(value);
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
        std::vector<value_type> to_vector() const noexcept {
            std::vector<value_type> filtered;
            for (const auto& entry: m_container) {
                auto ignore = false;
                for (auto filter: m_filters) {
                    if (!filter(entry)) {
                        ignore = true;
                        break;
                    }
                }

                if (!ignore) {
                    auto value = entry;
                    for (const auto& transform: m_transforms) {
                        transform(value);
                    }

                    filtered.push_back(value);
                }
            }
            return filtered;
        }

        /// @return provides count of selected values.
        typename std::vector<value_type>::size_type count() const noexcept {
            return to_vector().size();
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

    private:
        /// reference to selected container
        const container_type& m_container;
        /// container of registered filters
        filter_container_type m_filters;
        /// container of registered transforms
        transform_container_type m_transforms;
};

template <typename Container>
selector<Container> select(const Container& container) noexcept {
    return selector<Container>(container);
}

}  // namespace query

#endif  // INCLUDE_QUERY_SELECT_H_
