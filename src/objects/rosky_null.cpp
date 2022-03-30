
/******************************************************************************/
//
//  Source Name:                rosky_null.cpp
//
//  Description:                This file contains the class definition for
//                              the built in null type.
// 
//                              There is no underlying data type for this
//                              class.
//
//  Dependencies:               RoskyInterface
//
//  Classes:                    RoskyNull
//
//  Inherited Subprograms:      get_type_id
//                              get_type_string
//                              to_int
//                              to_string
//
//  Exported Subprograms:       ctor
//                              
/******************************************************************************/

#include "../../includes/objects/rosky_null.hpp"

/******************************************************************************/

// Type information.
OBJ_TYPES RoskyNull::get_type_id() const noexcept {
    return OBJ_NULL;
}

std::string RoskyNull::get_type_string() const noexcept {
    return "null";
}

/******************************************************************************/

// Casting.
long RoskyNull::to_int() const noexcept {
    return 0;
}

std::string RoskyNull::to_string() const noexcept {
    return "null";
}

/******************************************************************************/

// String operators.
std::shared_ptr<RoskyInterface> RoskyNull::concat_op(const std::shared_ptr<RoskyInterface>& __r) const noexcept {

    return std::make_shared<RoskyString>(to_string() + __r->to_string());

}

/******************************************************************************/
