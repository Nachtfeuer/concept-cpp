///
/// @author  Thomas Lehmann
/// @file    json.h
/// @brief   implements a JSON dumper. FIXME: impl. a parser
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
#ifndef INCLUDE_SERIALIZABLE_JSON_H_
#define INCLUDE_SERIALIZABLE_JSON_H_

#include <serializable/abstract_dumper.h>
#include <serializable/member.h>

namespace serializable {

/// @class json_dumper
/// @brief implements a JSON dumper.
/// @note member names are prefixed with "m:"
/// @note object names are prefixed with "o:"
class json_dumper : public abstract_dumper {
    public:
        /// dumping of an object (depends on impl.)
        virtual void dump(const object& the_object, std::ostream& stream) const override {
            stream << "{\"o:" << the_object.get_name() << "\":{";
            auto countdown = the_object.size();
            for (const auto& it: the_object) {
                stream << "\"m:" << it.first << "\":";
                dump(*it.second, stream);
                if (--countdown > 0) {
                    stream << ",";
                }
            }
            stream << "}}";
        }

        /// dumping of a member (depends on impl.)
        virtual void dump(const abstract_member& the_member, std::ostream& stream) const override {
            if (the_member.is_string()) {
                stream << "\"" << the_member.to_string() << "\"";
            } else if (the_member.is_object()) {
                auto obj = dynamic_cast<const member<abstract_object>&>(the_member).get_value();
                dump(*dynamic_cast<const object*>(obj), stream);
            } else {
                stream << the_member.to_string();
            }
        }
};

}  // namespace serializable

#endif  // INCLUDE_SERIALIZABLE_JSON_H_
