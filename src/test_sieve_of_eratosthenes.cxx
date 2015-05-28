///
/// @author  Thomas Lehmann
/// @file    test_sieve_of_eratosthenes.cxx
/// @brief   testing of @ref math::primes::sieve_of_eratosthenes
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
#include <math/prime/sieve_of_eratosthenes.h>
#include <math/prime/is_prime.h>
#include <generator/select.h>

#include <vector>

using namespace unittest;
using namespace matcher;

/// testing of class @ref math::primes::sieve_of_eratosthenes
describe_suite("testing math::prime::sieve_of_eratosthenes", [](){
    // keeping the calculation of sieve outside of the
    // test function to be excluded from the time measurement
    constexpr auto max_number = 5000;
    math::prime::sieve_of_eratosthenes<std::vector<bool>> sieve(max_number);
    sieve.calculate();

    describe_test("testing sieve 5000 (compared with is_prime)", []() {
        constexpr auto max_number = 5000;
        math::prime::sieve_of_eratosthenes<std::vector<bool>> sieve(max_number);
        sieve.calculate();

        for (auto number = 0; number <= max_number; ++number) {
            assert_that(math::prime::is_prime(number), is_equal(sieve.is_prime(number)));
        }
    });

    describe_test("testing sieve (captured) 5000 (compared with is_prime)", [sieve]() {
        for (auto number = 0; number <= max_number; ++number) {
            assert_that(math::prime::is_prime(number), is_equal(sieve.is_prime(number)));
        }
    });

    describe_test("testing sieve 100000 (max prime: 99991)", []() {
        constexpr auto max_number = 100000;
        math::prime::sieve_of_eratosthenes<std::vector<bool>> sieve(max_number);
        sieve.calculate();
        assert_that(true, is_equal(sieve.is_prime(99991)));
    });

    describe_test("testing prime generator (first ten)", [sieve]() {
        auto primes = generator::select(1, 25, 1)
            .where([&sieve](int number) {return sieve.is_prime(number);})
            .to_vector();

        const std::vector<int> expected = {2, 3, 5, 7, 11, 13, 17, 19, 23};
        assert_that(expected, is_equal(primes));
    });
});

