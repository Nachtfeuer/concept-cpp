///
/// @author  Thomas Lehmann
/// @file    text.h
/// @brief   text document with some useful functions.
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
#ifndef INCLUDE_DOCUMENT_TEXT_H_
#define INCLUDE_DOCUMENT_TEXT_H_

#include <boost/regex.hpp>
#include <string>

namespace document {

/// @class text_document
/// @brief text document with some useful functions.
class text_document {
    public:
        using count_type = uint32_t;

        /// initializing document with a some text
        text_document(const std::string& text)
            : m_text(text) {}

        /// @return number of words in current document
        count_type count_words() const noexcept {
            const auto pattern = boost::regex("\\w+");
            return std::distance(boost::sregex_iterator(m_text.begin(), m_text.end(), pattern),
                                 boost::sregex_iterator());
        }

    private:
        /// some text
        std::string m_text;
};

}  // namespace document

#endif  // INCLUDE_DOCUMENT_TEXT_H_
