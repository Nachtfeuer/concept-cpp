///
/// @author  Thomas Lehmann
/// @file    test_serializable_member.cxx
/// @brief   testing of @ref serializable::member
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

#include <serializable/object.h>
#include <serializable/member.h>

using namespace unittest;

/// testing of class @ref serializable::member
describe_suite("testing serializable::member", [](){
    describe_test("testing string member - default", []() {
        serializable::object dummy_object("dummy");
        const serializable::member<std::string> string_member("test", "hello world", dummy_object);

        assert_that(std::string("test"), is_equal(string_member.get_name()));
        assert_that(std::string("hello world"), is_equal(string_member.to_string()));
        assert_that(true, is_equal(string_member.is_string()));
    });

    describe_test("testing string member - set/get value", []() {
        serializable::object dummy_object("dummy");
        serializable::member<std::string> string_member("test", "hello world", dummy_object);

        string_member.set_value("it's a wonderful world");
        assert_that(std::string("it's a wonderful world"), is_equal(string_member.get_value()));
        assert_that(std::string("it's a wonderful world"), is_equal(string_member.to_string()));
    });
});

