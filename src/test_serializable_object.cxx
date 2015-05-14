///
/// @author  Thomas Lehmann
/// @file    test_serializable_object.cxx
/// @brief   testing of @ref serializable::object
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
using namespace matcher;

/// testing of class @ref serializable::object
describe_suite("testing serializable::object", [](){
    describe_test("testing object - default", []() {
        serializable::object the_object("test");

        assert_that(std::string("test"), is_equal(the_object.get_name()));
        assert_that(serializable::object::member_container_type::size_type(0),
                    is_equal(the_object.size()));
        assert_that(true, is_equal(the_object.empty()));
        assert_that(true, is_equal(the_object.begin() == the_object.end()));
    });

    describe_test("testing object - one member", []() {
        serializable::object the_object("test");
        serializable::member<int> age("age", 45, the_object);

        assert_that(serializable::object::member_container_type::size_type(1),
                    is_equal(the_object.size()));
        assert_that(false, is_equal(the_object.empty()));
        assert_that(true, is_equal(the_object.begin() != the_object.end()));
        // checking the ONE member.
        auto it = the_object.begin();
        assert_that(std::string("age"), is_equal(it->second->get_name()));
        assert_that(std::string("45"), is_equal(it->second->to_string()));
        assert_that(false, is_equal(it->second->is_string()));
    });
});

