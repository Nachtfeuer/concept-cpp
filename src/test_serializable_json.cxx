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
using namespace matcher;

/// testing of class @ref serializable::object
describe_suite("testing serializable::json_dumper", [](){
    describe_test("testing object JSON dumper - default", []() {
        serializable::object the_object("test");
        
        serializable::json_dumper dumper;
        std::stringstream stream;
        dumper.dump(the_object, stream);
        assert_that(std::string("{\"o:test\":{}}"), is_equal(stream.str()));
    });

    describe_test("testing object JSON dumper - one member", []() {
        serializable::object the_object("test");
        serializable::member<int> age("age", 45, the_object);
        
        serializable::json_dumper dumper;
        std::stringstream stream;
        dumper.dump(the_object, stream);
        assert_that(std::string("{\"o:test\":{\"m:age\":45}}"), is_equal(stream.str()));
    });

    describe_test("testing object JSON dumper - two member", []() {
        serializable::object the_object("test");
        serializable::member<int> age("age", 45, the_object);
        serializable::member<std::string> hobby("hobby", "reading books", the_object);
        
        serializable::json_dumper dumper;
        std::stringstream stream;
        dumper.dump(the_object, stream);
        assert_that(std::string("{\"o:test\":{\"m:hobby\":\"reading books\",\"m:age\":45}}"),
                    is_equal(stream.str()));
    });

    describe_test("testing object JSON dumper - one object member", []() {
        serializable::object the_object("test");
        serializable::object_member<serializable::object> sub_object(
            "sub-test", new serializable::object("sub-test"), the_object);
        
        serializable::json_dumper dumper;
        std::stringstream stream;
        dumper.dump(the_object, stream);
        assert_that(std::string("{\"o:test\":{\"m:sub-test\":{\"o:sub-test\":{}}}}"),
                    is_equal(stream.str()));
    });

    describe_test("testing object JSON dumper - one object member with one member", []() {
        serializable::object the_object("test");
        auto sub_test = new serializable::object("sub-test");
        serializable::object_member<serializable::object> sub_object(
            "sub-test", sub_test, the_object);
        serializable::member<int> age("age", 45, *sub_test);
        
        serializable::json_dumper dumper;
        std::stringstream stream;
        dumper.dump(the_object, stream);
        assert_that(std::string("{\"o:test\":{\"m:sub-test\":{\"o:sub-test\":{\"m:age\":45}}}}"),
                    is_equal(stream.str()));
    });

    /// testing to write a custom serializable class with two members.
    describe_test("testing object JSON dumper - custom class", []() {
        // a custom serializable test class
        class Foo : public serializable::object {
            public:
                Foo()
                    : serializable::object("Bar")
                    , m_ivalue("ivalue", 123, *this)
                    , m_strvalue("strvalue", "hello", *this) {
                }

            private:
                serializable::member<int> m_ivalue;           ///! simple integer value
                serializable::member<std::string> m_strvalue; ///! simple string value
        };

        Foo foo;

        serializable::json_dumper dumper;
        std::stringstream stream;
        dumper.dump(foo, stream);
        assert_that(std::string("{\"o:Bar\":{\"m:strvalue\":\"hello\",\"m:ivalue\":123}}"),
                    is_equal(stream.str()));
    });
});

