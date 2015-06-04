///
/// @author  Thomas Lehmann
/// @file    test_cache.cxx
/// @brief   testing of @ref pattern::cache
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
#include <unittest/unittest.h>
#include <pattern/cache.h>

/// @struct custom_key
/// @brief  represents math operation for two numbers to be cached
struct custom_key {
    using value_type = int;

    value_type m_value_a;  ///! first value to use with given operation with second one
    int m_operation;       ///! 0:+, 1:-, 2:*
    value_type m_value_b;  ///! second value to use with given operation with first one

    /// init c'tor for key
    custom_key(const value_type value_a, const int operation, const value_type value_b)
        : m_value_a(value_a), m_operation(operation), m_value_b(value_b) {}

    /// comparing two keys to be equal (note: std::equal_to of has container asks for it)
    friend bool operator == (const custom_key& key_a, const custom_key& key_b)  {
        return key_a.m_value_a == key_b.m_value_a &&
               key_a.m_operation == key_b.m_operation &&
               key_a.m_value_b == key_b.m_value_b;
    }
};

namespace std {

/// @class hash<custom_key>
/// @brief hash function for cache with custom key
template <>
struct hash<custom_key> {
    /// does calculation of the hash key value for given key
    /// @return hash key
    inline size_t operator ()(const custom_key& key) const {
        return std::hash<custom_key::value_type>()(key.m_value_a) ^
               std::hash<int>()(key.m_operation) ^
               std::hash<custom_key::value_type>()(key.m_value_b);
    }
};

}  // namespace std

using namespace unittest;
using namespace matcher;

/// testing of class @ref pattern::cache
describe_suite("testing pattern::cache", [](){
    describe_test("testing cache function, example: square cache", []() {
        pattern::cache<int, int> squares([](const int& n) {return n*n;});
        assert_that(16, is_equal(squares.get(4)));
        assert_that(1024, is_equal(squares.get(32)));
    });

    describe_test("testing cache fails", []() {
        int counter = 0;
        pattern::cache<int, int> squares([&counter](const int& n) {++counter; return n*n;});

        for (auto n = 0; n < 100; ++n) {
            squares.get(n);
            squares.get(n);
        }
        assert_that(100, is_equal(counter));
    });

    describe_test("testing cache with custom key", []() {
        pattern::cache<custom_key, custom_key::value_type> cache([](const custom_key& key) {
            switch (key.m_operation) {
                case 0: return key.m_value_a + key.m_value_b;
                case 1: return key.m_value_a - key.m_value_b;
                case 2: return key.m_value_a * key.m_value_b;
                default:
                    throw std::runtime_error("Not supported operation!");
            }
        });

        assert_that(50, is_equal(cache.get(custom_key(10, 0, 40))));
        assert_that(15, is_equal(cache.get(custom_key(40, 1, 25))));
        assert_that(1024, is_equal(cache.get(custom_key(32, 2, 32))));
    });
});

