///
/// @author  Thomas Lehmann
/// @file    test_assertion.cxx
/// @brief   testing of @ref unittest::assertion
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
#include <math/power_of_two.h>

#include <vector>
#include <sstream>
#include <cstdint>

using namespace unittest;

/// testing of class @ref unittest::suite
describe_suite("testing math::power_of_two", [](){
    describe_test("testing different values", []() {
        const std::vector<uint32_t> results = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048};
        for (uint32_t exponent = 0; exponent < results.size(); ++exponent) {
            std::stringstream expected;
            expected << results[exponent];

            math::power_of_two pot;
            pot.calculate(exponent);
            std::stringstream given;
            given << pot;

            assert_that(expected.str(), is_equal(given.str()));
        }
    });

    describe_test("testing bigger exponent", []() {
        // tested using: python -c "2**300"
        const std::string expected
            = "2037035976334486086268445688409378161051468393665936250636140449354381299763336706183397376";

        math::power_of_two pot;
        pot.calculate(300);
        std::stringstream given;
        given << pot;

        assert_that(expected, is_equal(given.str()));
    });
});

