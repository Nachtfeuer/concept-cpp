///
/// @author  Thomas Lehmann
/// @file    test_to_stream.cxx
/// @brief   testing of @ref types::to_stream<T>
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
#include <sstream>

using namespace unittest;
using namespace matcher;

/// testing of class @ref types::to_stream<T>
describe_suite("testing types::to_stream<T>", [](){
    describe_test("testing to_stream<bool>(true)", []() {
        std::stringstream stream;
        types::to_stream<bool>::dump(stream, true);
        assert_that(std::string("true"), is_equal(stream.str()));
    });

    describe_test("testing to_stream<bool>(false)", []() {
        std::stringstream stream;
        types::to_stream<bool>::dump(stream, false);
        assert_that(std::string("false"), is_equal(stream.str()));
    });

    describe_test("testing to_stream<unsigned char>", []() {
        std::stringstream stream;
        types::to_stream<unsigned char>::dump(stream, 7);
        assert_that(std::string("7"), is_equal(stream.str()));
    });

    describe_test("testing to_stream<std::vector<int>>", []() {
        const std::vector<int> values = {2, 4, 6, 8};
        std::stringstream stream;
        types::to_stream<std::vector<int>>::dump(stream, values);
        assert_that(std::string("[2, 4, 6, 8]"), is_equal(stream.str()));
    });

    describe_test("testing to_stream<std::list<int>>", []() {
        const std::list<int> values = {2, 4, 6, 8};
        std::stringstream stream;
        types::to_stream<std::list<int>>::dump(stream, values);
        assert_that(std::string("[2, 4, 6, 8]"), is_equal(stream.str()));
    });

    describe_test("testing to_stream<std::set<int>>", []() {
        const std::set<int> values = {2, 4, 6, 8};
        std::stringstream stream;
        types::to_stream<std::set<int>>::dump(stream, values);
        assert_that(std::string("[2, 4, 6, 8]"), is_equal(stream.str()));
    });
});

