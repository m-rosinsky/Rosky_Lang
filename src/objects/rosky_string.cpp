
/******************************************************************************/
//
//  Source Name:                rosky_string.cpp
//
//  Description:                This file contains the class definition for
//                              the built in string type.
// 
//                              The underlying data type is an std::string
//
//  Dependencies:               RoskyInterface
//
//  Classes:                    RoskyString
//
//  Inherited Subprograms:      get_type_id
//                              get_type_string
//                              to_int
//                              to_string
//                              add_op
//                              mul_op
//
//  Exported Subprograms:       ctor
//                              ctor(const std::string&)
//                              
/******************************************************************************/

#include "../../includes/objects/rosky_string.hpp"

/******************************************************************************/

// Type information.
OBJ_TYPES RoskyString::get_type_id() const noexcept {
    return OBJ_STRING;
}

std::string RoskyString::get_type_string() const noexcept {
    return "string";
}

/******************************************************************************/

// Casting.
long RoskyString::to_int() const noexcept {
    return 0;
}

std::string RoskyString::to_string() const noexcept {
    return _data;
}

/******************************************************************************/

// Arithmetic operators.
std::shared_ptr<RoskyInterface> RoskyString::add_op(const std::shared_ptr<RoskyInterface>& __r) const noexcept {

    // Strings can only be added with other strings.
    if (__r->get_type_id() == OBJ_STRING) {
        return std::make_shared<RoskyString>(_data + __r->to_string());
    }

    return nullptr;

}

/******************************************************************************/

// String operators.
std::shared_ptr<RoskyInterface> RoskyString::concat_op(const std::shared_ptr<RoskyInterface>& __r) const noexcept {

    return std::make_shared<RoskyString>(to_string() + __r->to_string());

}

/******************************************************************************/