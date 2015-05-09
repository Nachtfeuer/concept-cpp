///
/// @author  Thomas Lehmann
/// @file    test_performance.cxx
/// @brief   testing time functions.
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
#include <performance/measurement.h>

#include <thread>

using namespace unittest;

describe_suite("testing performance functions", [](){
    describe_test("testing performance::measure (milliseconds)", []() {
        const auto duration = performance::measure<std::milli>([]() {
            // sleeping for 100ms ...
            std::this_thread::sleep_for(std::chrono::duration<double, std::milli>(100));
        });

        assert_that(duration, is_range(100.0, 103.0));
    });

    describe_test("testing performance::measure (microseconds)", []() {
        const auto duration = performance::measure<std::micro>([]() {
            // sleeping for 100ms ...
            std::this_thread::sleep_for(std::chrono::duration<double, std::milli>(100));
        });

        assert_that(duration, is_range(100000.0, 103000.0));
    });

    describe_test("testing performance::measure (seconds)", []() {
        const auto duration = performance::measure<std::ratio<1>>([]() {
            // sleeping for 100ms ...
            std::this_thread::sleep_for(std::chrono::duration<double, std::milli>(100));
        });

        assert_that(duration, is_range(0.100, 0.103));
    });
});

