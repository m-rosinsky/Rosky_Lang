
/******************************************************************************/
//
//  Source Name:                rosky_bool.cpp
//
//  Description:                This file contains the class definition for
//                              the built in boolean type.
// 
//                              The underlying data type is a bool
//
//  Dependencies:               RoskyInterface
//
//  Classes:                    RoskyBool
//
//  Inherited Subprograms:      get_type_id
//                              get_type_string
//                              to_int
//                              to_string
//                              add_op
//                              mul_op
//
//  Exported Subprograms:       ctor
//                              ctor(bool)
//                              
/******************************************************************************/

#include "../../includes/objects/rosky_bool.hpp"

/******************************************************************************/

// Type information.
OBJ_TYPES RoskyBool::get_type_id() const noexcept {
    return OBJ_BOOL;
}

std::string RoskyBool::get_type_string() const noexcept {
    return "bool";
}

/******************************************************************************/

// Iterable information.
bool RoskyBool::is_iterable() const noexcept {
    return false;
}

bool RoskyBool::is_addressable() const noexcept {
    return false;
}

/******************************************************************************/

// Casting.
long RoskyBool::to_int() const noexcept {
    return _data ? 1 : 0;
}

std::string RoskyBool::to_string() const noexcept {
    return _data ? "true" : "false";
}

bool RoskyBool::to_bool() const noexcept {
    return _data;
}

/******************************************************************************/

// String operators
std::shared_ptr<RoskyInterface> RoskyBool::concat_op(const std::shared_ptr<RoskyInterface>& __r) const noexcept {

    return std::make_shared<RoskyString>(to_string() + __r->to_string());

}

/******************************************************************************/

// Boolean operators.
std::shared_ptr<RoskyInterface> RoskyBool::eq_op(const std::shared_ptr<RoskyInterface>& __r) const noexcept {

    if (__r->get_type_id() != OBJ_NULL) {
        return std::make_shared<RoskyBool>(_data == __r->to_bool());
    }

    // If compared to null, always return false.
    return std::make_shared<RoskyBool>(false);

} 

/******************************************************************************/