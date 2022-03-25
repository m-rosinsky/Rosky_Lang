
/******************************************************************************/
//
//  Source Name:                rosky_int.cpp
//
//  Description:                This file contains the class definition for
//                              the built in integer type.
// 
//                              The underlying data type is a long, rather
//                              than an int.
//
//  Dependencies:               RoskyInterface
//
//  Classes:                    RoskyInt
//
//  Inherited Subprograms:      get_type_id
//                              get_type_string
//                              to_int
//                              to_string
//                              add_op
//                              mul_op
//
//  Exported Subprograms:       ctor
//                              ctor(long)
//                              
/******************************************************************************/

#include "../../includes/objects/rosky_int.hpp"

/******************************************************************************/

// Type information.
OBJ_TYPES RoskyInt::get_type_id() const noexcept {
    return OBJ_INT;
}

std::string RoskyInt::get_type_string() const noexcept {
    return "int";
}

/******************************************************************************/

// Casting.
long RoskyInt::to_int() const noexcept {
    return _data;
}

std::string RoskyInt::to_string() const noexcept {
    return std::to_string(_data);
}

/******************************************************************************/

// Arithmetic operators.
std::shared_ptr<RoskyInterface> RoskyInt::add_op(const std::shared_ptr<RoskyInterface>& __r) const noexcept {

    if (__r->get_type_id() == OBJ_INT) {
        return std::make_shared<RoskyInt>(_data + __r->to_int());
    }

    return nullptr;

}

std::shared_ptr<RoskyInterface> RoskyInt::mul_op(const std::shared_ptr<RoskyInterface>& __r) const noexcept {

    if (__r->get_type_id() == OBJ_INT) {
        return std::make_shared<RoskyInt>(_data * __r->to_int());
    }

    return nullptr;

}

/******************************************************************************/
