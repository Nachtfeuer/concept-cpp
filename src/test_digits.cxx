///
/// @author  Thomas Lehmann
/// @file    test_digits.cxx
/// @brief   testing of @ref math::digits
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
#include <math/digits.h>
#include <generator/select.h>

using namespace unittest;
using namespace matcher;

/// testing of class @ref math::digits
describe_suite("testing math::digits", [](){
    /// testing @ref math::digits::sum
    describe_test("testing sum", []() {
        const auto digit_sums = generator::select(1, 20, 1)
            .transform([](int& n){n = math::digits<int>::sum(n);})
            .to_vector();

        const auto expected = std::vector<int>({
            1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 2});

        assert_that(expected, is_equal(digit_sums));
        assert_that(45, is_equal(math::digits<int>::sum(123456789)));
    });

    /// testing @ref math::digits::count
    describe_test("testing count", []() {
        assert_that(9, is_equal(math::digits<int>::count(123456789)));
        assert_that(1, is_equal(math::digits<int>::count(0)));
        assert_that(9, is_equal(math::digits<int>::count(-123456789)));
    });

    describe_test("testing is_pandigital", []() {
        // positive check
        assert_that(true, is_equal(math::digits<int>::is_pandigital(123456789)));
        assert_that(true, is_equal(math::digits<int>::is_pandigital(12345)));
        assert_that(true, is_equal(math::digits<int>::is_pandigital(1230)));

        // negtive check
        assert_that(false, is_equal(math::digits<int>::is_pandigital(123445)));
        assert_that(false, is_equal(math::digits<int>::is_pandigital(123445)));
        assert_that(false, is_equal(math::digits<int>::is_pandigital(123005)));
    });
});

