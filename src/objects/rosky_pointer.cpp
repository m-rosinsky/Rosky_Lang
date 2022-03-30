
/******************************************************************************/
//
//  Source Name:                rosky_pointer.cpp
//
//  Description:                This file contains the class definition for
//                              the built in pointer type.
// 
//                              The underlying data type is a pointer
//                              to a shared_ptr instance of an object.
//
//  Dependencies:               RoskyInterface
//
//  Classes:                    RoskyPointer
//
//  Inherited Subprograms:      get_type_id
//                              get_type_string
//                              to_int
//                              to_string
//                              add_op
//                              mul_op
//
//  Exported Subprograms:       ctor
//                              ctor(ptr)
//                              
/******************************************************************************/

#include "../../includes/objects/rosky_pointer.hpp"

/******************************************************************************/

// Type information.
OBJ_TYPES RoskyPointer::get_type_id() const noexcept {
    return OBJ_POINTER;
}

std::string RoskyPointer::get_type_string() const noexcept {
    return "pointer";
}

/******************************************************************************/

// Casting.
long RoskyPointer::to_int() const noexcept {
    return 0;
}

std::string RoskyPointer::to_string() const noexcept {

    // Special case for nullptr.
    if (_data == nullptr) {
        return "0x0";
    }

    // Cast the address the data pointer is holding to a string
    std::stringstream ss;
    ss << _data;
    return ss.str();
}

/******************************************************************************/

// Pointer operators.
std::pair<std::shared_ptr<RoskyInterface>*, std::shared_ptr<RoskyInterface>> RoskyPointer::deref_op() const noexcept {

    if (_data == nullptr) {
        return {nullptr, nullptr};
    }

    return {_data, *_data};

}

/******************************************************************************/

// String operators.
std::shared_ptr<RoskyInterface> RoskyPointer::concat_op(const std::shared_ptr<RoskyInterface>& __r) const noexcept {

    return std::make_shared<RoskyString>(to_string() + __r->to_string());

}

/******************************************************************************/
