///
/// @author  Thomas Lehmann
/// @file    test_number.cxx
/// @brief   testing of @ref math::number
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
#include <math/number.h>
#include <generator/select.h>

using namespace unittest;
using namespace matcher;

/// testing of struct @ref math::number
describe_suite("testing math::number", [](){
    describe_test("testing is_perfect", []() {
        // see here: oeis.org/A000396
        const std::vector<int> some_perfect_numbers = {6, 28, 496, 8128};
        auto results = generator::select(1, 10000, 1)
            .where([](int number){return math::number<int>::is_perfect(number);})
            .to_vector();

        assert_that(some_perfect_numbers, is_equal(results));
    });

    describe_test("testing is_abundant", []() {
        const std::vector<int> some_abundant_numbers = {
            12, 18, 20, 24, 30, 36, 40, 42, 48, 54, 56, 60, 66, 70, 72, 78, 80, 84, 88, 90, 96, 100
        };

        auto results = generator::select(1, 100, 1)
            .where([](int number){return math::number<int>::is_abundant(number);})
            .to_vector();

        assert_that(some_abundant_numbers, is_equal(results));
    });

    describe_test("testing is_square", []() {
        // positiv check (probe):
        assert_that(true, is_equal(math::number<int>::is_square(1)));
        assert_that(true, is_equal(math::number<int>::is_square(4)));
        assert_that(true, is_equal(math::number<int>::is_square(121)));

        // negativ check (probe):
        assert_that(true, is_not(is_equal(math::number<int>::is_square(5))));
        assert_that(true, is_not(is_equal(math::number<int>::is_square(11))));
        assert_that(true, is_not(is_equal(math::number<int>::is_square(17))));
    });

    describe_test("testing triangle", []() {
        const std::vector<int> some_triangle_numbers = {
            1, 3, 6, 10, 15, 21, 28, 36, 45, 55, 66, 78, 91, 105, 120, 136, 153, 171, 190, 210
        };

        auto results = generator::select(1, 20, 1)
            .transform([](int& number){number = math::number<int>::triangle(number);})
            .to_vector();

        assert_that(some_triangle_numbers, is_equal(results));
    });

    describe_test("testing is_triangle", []() {
        // positiv check (probe):
        assert_that(true, is_equal(math::number<int>::is_triangle(6)));
        assert_that(true, is_equal(math::number<int>::is_triangle(91)));
        assert_that(true, is_equal(math::number<int>::is_triangle(153)));

        // negativ check (probe):
        assert_that(true, is_not(is_equal(math::number<int>::is_triangle(2))));
        assert_that(true, is_not(is_equal(math::number<int>::is_triangle(54))));
        assert_that(true, is_not(is_equal(math::number<int>::is_triangle(200))));
    });

    describe_test("testing pentagonal", []() {
        const std::vector<int> some_pentagonal_numbers = {
            1, 5, 12, 22, 35, 51, 70, 92, 117, 145, 176, 210, 247, 287, 330, 376, 425, 477, 532, 590
        };

        auto results = generator::select(1, 20, 1)
            .transform([](int& number){number = math::number<int>::pentagonal(number);})
            .to_vector();

        assert_that(some_pentagonal_numbers, is_equal(results));
    });

    describe_test("testing is_pentagonal", []() {
        // positiv check (probe):
        assert_that(true, is_equal(math::number<int>::is_pentagonal(5)));
        assert_that(true, is_equal(math::number<int>::is_pentagonal(117)));
        assert_that(true, is_equal(math::number<int>::is_pentagonal(425)));

        // negativ check (probe):
        assert_that(true, is_not(is_equal(math::number<int>::is_pentagonal(2))));
        assert_that(true, is_not(is_equal(math::number<int>::is_pentagonal(50))));
        assert_that(true, is_not(is_equal(math::number<int>::is_pentagonal(200))));
    });

    describe_test("testing hexagonal", []() {
        const std::vector<int> some_hexagonal_numbers = {
            1, 6, 15, 28, 45, 66, 91, 120, 153, 190, 231, 276, 325, 378, 435, 496, 561, 630, 703, 780
        };

        auto results = generator::select(1, 20, 1)
            .transform([](int& number){number = math::number<int>::hexagonal(number);})
            .to_vector();

        assert_that(some_hexagonal_numbers, is_equal(results));
    });

    describe_test("testing is_hexagonal", []() {
        // positiv check (probe):
        assert_that(true, is_equal(math::number<int>::is_hexagonal(6)));
        assert_that(true, is_equal(math::number<int>::is_hexagonal(120)));
        assert_that(true, is_equal(math::number<int>::is_hexagonal(703)));

        // negativ check (probe):
        assert_that(true, is_not(is_equal(math::number<int>::is_hexagonal(2))));
        assert_that(true, is_not(is_equal(math::number<int>::is_hexagonal(50))));
        assert_that(true, is_not(is_equal(math::number<int>::is_hexagonal(200))));
    });

    describe_test("testing is_pandigital", []() {
        // positive check
        assert_that(true, is_equal(math::number<int>::is_pandigital(123456789)));
        assert_that(true, is_equal(math::number<int>::is_pandigital(12345)));
        assert_that(true, is_equal(math::number<int>::is_pandigital(1230)));

        // negtive check
        assert_that(false, is_equal(math::number<int>::is_pandigital(123445)));
        assert_that(false, is_equal(math::number<int>::is_pandigital(123445)));
        assert_that(false, is_equal(math::number<int>::is_pandigital(123005)));
    });

    describe_test("testing is_palindrome", []() {
        // positive check
        assert_that(true, is_equal(math::number<int>::is_palindrome(12321)));
        assert_that(true, is_equal(math::number<int>::is_palindrome(123454321)));
        assert_that(true, is_equal(math::number<int>::is_palindrome(55)));

        // negtive check
        assert_that(false, is_equal(math::number<int>::is_palindrome(12345)));
        assert_that(false, is_equal(math::number<int>::is_palindrome(54321)));
        assert_that(false, is_equal(math::number<int>::is_palindrome(32233)));
    });

    describe_test("testing reverse", []() {
        assert_that(123456789, is_equal(math::number<int>::reverse(987654321)));
        assert_that(987654321, is_equal(math::number<int>::reverse(123456789)));
        assert_that(12300456, is_equal(math::number<int>::reverse(65400321)));
    });
});

