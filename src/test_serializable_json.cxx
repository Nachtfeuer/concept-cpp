///
/// @author  Thomas Lehmann
/// @file    test_serializable_json.cxx
/// @brief   testing of @ref serializable::json_dumper
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
#include <serializable/json.h>

using namespace unittest;

/// testing of class @ref serializable::object
describe_suite("testing serializable::json_dumper", [](){
    describe_test("testing object JSON dumper - default", []() {
        serializable::object the_object("test");
        
        serializable::json_dumper dumper;
        std::stringstream stream;
        dumper.dump(the_object, stream);
        assert_that(std::string("{\"test\":{}}"), is_equal(stream.str()));
    });

    describe_test("testing object JSON dumper - one member", []() {
        serializable::object the_object("test");
        serializable::member<int> age("age", 45, the_object);
        
        serializable::json_dumper dumper;
        std::stringstream stream;
        dumper.dump(the_object, stream);
        assert_that(std::string("{\"test\":{\"age\":45}}"), is_equal(stream.str()));
    });

    describe_test("testing object JSON dumper - two member", []() {
        serializable::object the_object("test");
        serializable::member<int> age("age", 45, the_object);
        serializable::member<std::string> hobby("hobby", "reading books", the_object);
        
        serializable::json_dumper dumper;
        std::stringstream stream;
        dumper.dump(the_object, stream);
        assert_that(std::string("{\"test\":{\"hobby\":\"reading books\",\"age\":45}}"),
                    is_equal(stream.str()));
    });
});

