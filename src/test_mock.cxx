///
/// @author  Thomas Lehmann
/// @file    test_mock.cxx
/// @brief   testing of @ref pattern::mock class.
///
/// Copyright (c) 2020 Thomas Lehmann
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
#include <pattern/factory.h>
#include <pattern/mock.h>

#include <vector>
#include <memory>

using namespace unittest;
using namespace matcher;
using namespace pattern;

/// testing of class @ref pattern:mock
describe_suite("testing pattern::mock", [](){
    const auto creator = []() { return std::unique_ptr<int>(new int(123)); };

    describe_test("testing mocking", [creator]() {
        /// we cannot rely that the singelton does not contain yet registered entries
        factory<int, int>::get().clear();
        /// first registration should succeed
        factory<int, int>::get().register_creator(1, creator);

        std::cout << "mock::before enter scope" << std::endl;
        { /// enter scope
            const auto anotherCreator = []() { return std::unique_ptr<int>(new int(456)); };
            std::cout << "mock::before mocked" << std::endl;
            mock<int, int> mockIt(1, anotherCreator);
            std::cout << "mock::after mocked" << std::endl;
            assert_that(*factory<int, int>::get().create_instance(1), is_equal(456));
        } /// leaving scope
        std::cout << "mock::after left scope" << std::endl;

        /// destructor of the mocking should have restored the original creator
        assert_that(*factory<int, int>::get().create_instance(1), is_equal(123));
    });

    describe_test("testing mocking with decoration", [creator]() {
        /// we cannot rely that the singelton does not contain yet registered entries
        factory<int, int>::get().clear();
        /// first registration should succeed
        factory<int, int>::get().register_creator(1, creator);

        std::cout << "mock decoration::before enter scope" << std::endl;
        { /// enter scope
            /// decoration
            const auto originalCreator = factory<int, int>::get().find_creator(1);
            const auto anotherCreator = [originalCreator]() {
                auto value = originalCreator();
                *value *= 2;
                return value;
            };

            std::cout << "mock decoration::before mocked" << std::endl;
            mock<int, int> mockIt(1, anotherCreator);
            std::cout << "mock decoration::after mocked" << std::endl;
            assert_that(*factory<int, int>::get().create_instance(1), is_equal(246));
        } /// leaving scope
        std::cout << "mock decoration::after left scope" << std::endl;

        /// destructor of the mocking should have restored the original creator
        assert_that(*factory<int, int>::get().create_instance(1), is_equal(123));
    });
});
