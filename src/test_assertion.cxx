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

using namespace unittest;
using namespace matcher;

/// testing of class @ref unittest::suite
describe_suite("testing unittest::assertion", [](){
    describe_test("testing assertion", []() {
        const assertion test_assertion("test assertion");

        assert_that(std::string("test assertion"),
                    is_equal(std::string(test_assertion.what())));
    });

    describe_test("testing assert_that", []() {
        try {
            assert_that(true, is_equal(false));
        } catch (assertion& catched_assertion) {
            return;
        }
        assert_that(std::string("assert_that has failed"), is_equal(std::string("")));
    });

    /// ensure that right exception is thrown
    describe_test("testing assert_raise (default)", []() {
        assert_raise<std::runtime_error>("expecting runtime exception", []() {
                throw std::runtime_error("catch me if you can");
        });
    });

    /// ensure that we handle the wrong exception scenario
    describe_test("testing assert_raise for wrong exception", []() {
        try {
            assert_raise<std::runtime_error>("expecting runtime exception", []() {
                    throw "catch me if you can";
            });
        } catch (const assertion& e) {
            assert_that(true, is_equal(
                std::string(e.what()).find("wrong exception") != std::string::npos));
        }
    });
});

