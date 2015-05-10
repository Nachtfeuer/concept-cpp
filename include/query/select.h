///
/// @author  Thomas Lehmann
/// @file    select.h
/// @brief   select does take a container.
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

#include <vector>
#include <list>
#include <functional>

namespace query {

/// @class selector<std::vector>
/// @brief provides a query for a std::vector container.
template <typename T>
class selector final {
    public:
        /// type for container
        using container_type = T;
        /// type of value for given container
        using value_type = typename T::value_type;
        /// type for the filter function
        using filter_function_type = std::function<bool (const value_type&)>;
        /// type for container of registered filters
        using filter_container_type = std::vector<filter_function_type>;

        /// "selecting" a container keeping the reference
        selector(const container_type& container)
            : m_container(container) {}

        /// @return number of entries in the container
        typename container_type::size_type size() const noexcept {
            return m_container.size();
        }

        /// @return container with values only defined by given filter.
        selector& where(filter_function_type filter) noexcept {
            m_filters.push_back(filter);
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
                    filtered.push_back(entry);
                }
            }
            return filtered;
        }

        /// @return provides count of selected values.
        typename std::vector<value_type>::size_type count() const noexcept {
            return to_vector().size();
        }

    private:
        /// reference to selected container
        const container_type& m_container;
        /// container of registered filters
        filter_container_type m_filters;
};

template <typename Container>
selector<Container> select(const Container& container) noexcept {
    return selector<Container>(container);
}

}  // namespace query

#endif  // INCLUDE_QUERY_SELECT_H_
