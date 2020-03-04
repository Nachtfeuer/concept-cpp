///
/// @author  Thomas Lehmann
/// @file    mock.h
/// @brief   mocking of objects created via abstract factory.
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
#ifndef INCLUDE_PATTERN_MOCK_H_
#define INCLUDE_PATTERN_MOCK_H_

#include <pattern/factory.h>

namespace pattern {

/// @class mock
/// @brief mocking of objects created via abstract factory.
template <typename TKey, typename TClass>
class mock final {
    public:
        /// type for creator function
        using creator_function_type = std::function<std::unique_ptr<TClass> ()>;

        /// The c'tor replaces the original creator with the one defined
        /// in the parameter keeping it in mind. In d'tor it will be restored.
        ///
        /// @param  key unique key that may not exist
        /// @param  creator the creator function providing instance of type TClass (may not be nullptr)
        mock(const TKey& key, creator_function_type creator)
            : m_key(key), m_mock_creator(creator),
              m_original_creator(factory<TKey, TClass>::get().replace_creator(key, creator)) {}

        /// restore the original creator
        ~mock() {
            if (m_original_creator != nullptr) {
                factory<TKey, TClass>::get().replace_creator(m_key, m_original_creator);
            }
        }

    private:
        /// The key under which the creator is stored
        const TKey m_key;
        /// the created used as mock
        const creator_function_type m_mock_creator;
        /// the original creator stored in the abstract factory
        const creator_function_type m_original_creator;
};

}  // namespace pattern

#endif  // INCLUDE_PATTERN_MOCK_H_
