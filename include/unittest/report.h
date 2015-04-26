///
/// @author  Thomas Lehmann
/// @file    report.h
/// @brief   report interface
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
#ifndef INCLUDE_UNITTEST_REPORT_H_
#define INCLUDE_UNITTEST_REPORT_H_

#include <unittest/test.h>

namespace unittest {

/// @class report
/// @brief report interface which allows you to implement custom reports.
class report {
    public:
        /// providing default d'tor
        virtual ~report() = default;
        /// to be overwritten by a derived class
        /// @param suite_name name of the relating test suite
        /// @param finished_test the finished test
        virtual void test_done(const std::string& suite_name,
                               std::shared_ptr<test> finished_test) = 0;
        /// dumping the report (stdout, file, or whatever the derived class implements)
        virtual void dump() const = 0;
};

}  //namespace report

#endif  // INCLUDE_UNITTEST_REPORT_H_
