///
/// @author  Thomas Lehmann
/// @file    test_is_prime.cxx
/// @brief   testing of @ref math::prime::is_prime
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
#include <math/prime/is_prime.h>

using namespace unittest;
using namespace matcher;

/// testing of class @ref math::prime::is_prime
describe_suite("testing math::prime::is_prime", []() {
    /// some numbers tested:
    describe_test("testing is_prime (int)", []() {
        assert_that(false, is_equal(math::prime::is_prime(0)));
        assert_that(false, is_equal(math::prime::is_prime(1)));
        assert_that(true,  is_equal(math::prime::is_prime(2)));
        assert_that(true,  is_equal(math::prime::is_prime(3)));
        assert_that(false, is_equal(math::prime::is_prime(4)));
        assert_that(true,  is_equal(math::prime::is_prime(5)));
        assert_that(false, is_equal(math::prime::is_prime(6)));
        assert_that(true,  is_equal(math::prime::is_prime(7)));
        assert_that(false, is_equal(math::prime::is_prime(8)));
        assert_that(false, is_equal(math::prime::is_prime(9)));
        assert_that(false, is_equal(math::prime::is_prime(10)));
        assert_that(true,  is_equal(math::prime::is_prime(11)));
    });

    /// some numbers tested:
    describe_test("testing is_prime matcher (int)", []() {
        assert_that(0, is_not(is_prime<int>()));
        assert_that(1, is_not(is_prime<int>()));
        assert_that(2, is_prime<int>());
        assert_that(3, is_prime<int>());
        assert_that(4, is_not(is_prime<int>()));
        assert_that(5, is_prime<int>());
        assert_that(6, is_not(is_prime<int>()));
        assert_that(7, is_prime<int>());
        assert_that(8, is_not(is_prime<int>()));
        assert_that(9, is_not(is_prime<int>()));
        assert_that(10, is_not(is_prime<int>()));
        assert_that(11, is_prime<int>());

        const is_prime_matcher<int> the_matcher;
        assert_that(std::string("is_prime()"), is_equal(the_matcher.get_expression()));
    });
});
