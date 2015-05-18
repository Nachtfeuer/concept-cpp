///
/// @author  Thomas Lehmann
/// @file    test_type_traits.cxx
/// @brief   testing of type traits.
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
#include <types/type_traits.h>

using namespace unittest;
using namespace matcher;

/// testing of @ref types::is_container
describe_suite("testing types::is_container", []() {
    describe_test("testing different types for is_container", []() {
        auto value = types::is_container<int>::value;
        assert_that(false, is_equal(value));
        value = types::is_container<std::vector<int>>::value;
        assert_that(true, is_equal(value));
        value = types::is_container<std::deque<int>>::value;
        assert_that(true, is_equal(value));
        value = types::is_container<std::list<int>>::value;
        assert_that(true, is_equal(value));
        value = types::is_container<std::queue<int>>::value;
        assert_that(true, is_equal(value));
        value = types::is_container<std::stack<int>>::value;
        assert_that(true, is_equal(value));
        value = types::is_container<std::set<int>>::value;
        assert_that(true, is_equal(value));
        value = types::is_container<std::unordered_set<int>>::value;
        assert_that(true, is_equal(value));
    });
});

