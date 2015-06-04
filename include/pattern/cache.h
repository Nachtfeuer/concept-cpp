///
/// @author  Thomas Lehmann
/// @file    cache.h
/// @brief   key/value cache
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
#ifndef INCLUDE_PATTERN_CACHE_H_
#define INCLUDE_PATTERN_CACHE_H_

#include <unordered_map>
#include <functional>
#include <stdexcept>

namespace pattern {

/// @class cache
/// @brief key/value cache
template <class TKey, class TValue>
class cache final {
    /// type for the container of the cached entries
    using container_type = std::unordered_map<TKey, TValue>;
    /// when the cache does not contain the key the value
    /// can be automatically retrieved by this function.
    using retrieve_function_type = std::function<TValue (const TKey&)>;

    public:
        /// initializing defaults
        /// @param retrieve the function to be called to retrieve a value for
        ///        a key that is not yet stored in the cache.
        cache(retrieve_function_type retrieve)
            : m_entries(), m_retrieve(retrieve) {
            if (nullptr == m_retrieve) {
                throw std::runtime_error("Missing cache retrieve function!");
            }
        }

        /// @return value for given key
        const TValue& get(const TKey& key) {
            auto result = m_entries.insert(typename container_type::value_type(key, TValue()));
            if (result.second) {
                result.first->second = m_retrieve(key);
            }

            return result.first->second;
        }

    private:
        /// caches entries
        container_type m_entries;
        /// general function to retrieve a function for a given key
        retrieve_function_type m_retrieve;
};

}  // namespace pattern

#endif  // INCLUDE_PATTERN_CACHE_H_
