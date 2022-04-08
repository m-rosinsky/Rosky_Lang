
/******************************************************************************/
//
//  Source Name:                rosky_float.cpp
//
//  Description:                This file contains the class definition for
//                              the built in float type.
// 
//                              The underlying data type is a double, rather
//                              than a float.
//
//  Dependencies:               RoskyInterface
//
//  Classes:                    RoskyFloat
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
//                              ctor(double)
//                              
/******************************************************************************/

#include "../../includes/objects/rosky_float.hpp"

/******************************************************************************/

// Type information.
OBJ_TYPES RoskyFloat::get_type_id() const noexcept {
    return OBJ_FLOAT;
}

std::string RoskyFloat::get_type_string() const noexcept {
    return "float";
}

/******************************************************************************/

// Iterable information.
bool RoskyFloat::is_iterable() const noexcept {
    return false;
}

bool RoskyFloat::is_addressable() const noexcept {
    return false;
}

/******************************************************************************/

// Casting.
long RoskyFloat::to_int() const noexcept {
    return (long)_data;
}

double RoskyFloat::to_float() const noexcept {
    return _data;
}

std::string RoskyFloat::to_string() const noexcept {
    std::string s = std::to_string(_data);
    size_t last_idx = 0;
    size_t deci_idx = 0;
    for (size_t i = 0; i < s.size(); i++) {
        if (s[i] != '0') {
            last_idx = i;
        }
        if (s[i] == '.') {
            deci_idx = i;
        }
    }
    return s.substr(0, last_idx > deci_idx + 1 ? last_idx + 1 : deci_idx + 2);
}

bool RoskyFloat::to_bool() const noexcept {
    return _data != 0.0;
}

/******************************************************************************/

// Arithmetic operators.
std::shared_ptr<RoskyInterface> RoskyFloat::add_op(const std::shared_ptr<RoskyInterface>& __r) const noexcept {

    if (__r->get_type_id() == OBJ_INT || __r->get_type_id() == OBJ_FLOAT) {
        return std::make_shared<RoskyFloat>(_data + __r->to_float());
    }

    return nullptr;

}

std::shared_ptr<RoskyInterface> RoskyFloat::sub_op(const std::shared_ptr<RoskyInterface>& __r) const noexcept {

    if (__r->get_type_id() == OBJ_INT || __r->get_type_id() == OBJ_FLOAT) {
        return std::make_shared<RoskyFloat>(_data - __r->to_float());
    }

    return nullptr;

}

std::shared_ptr<RoskyInterface> RoskyFloat::mul_op(const std::shared_ptr<RoskyInterface>& __r) const noexcept {

    if (__r->get_type_id() == OBJ_INT || __r->get_type_id() == OBJ_FLOAT) {
        return std::make_shared<RoskyFloat>(_data * __r->to_float());
    }

    return nullptr;

}

std::shared_ptr<RoskyInterface> RoskyFloat::div_op(const std::shared_ptr<RoskyInterface>& __r) const noexcept {

    if (__r->get_type_id() == OBJ_INT || __r->get_type_id() == OBJ_FLOAT) {
        return std::make_shared<RoskyFloat>(_data / __r->to_float());
    }

    return nullptr;

}

/******************************************************************************/

// String operators.
std::shared_ptr<RoskyInterface> RoskyFloat::concat_op(const std::shared_ptr<RoskyInterface>& __r) const noexcept {

    return std::make_shared<RoskyString>(to_string() + __r->to_string());

}

/******************************************************************************/

// Comparison operators.
std::shared_ptr<RoskyInterface> RoskyFloat::eq_op(const std::shared_ptr<RoskyInterface>& __r) const noexcept {

    if (__r->get_type_id() == OBJ_INT || __r->get_type_id() == OBJ_FLOAT) {
        return std::make_shared<RoskyBool>(_data == __r->to_float());
    } else if (__r->get_type_id() == OBJ_NULL) {
        return std::make_shared<RoskyBool>(false);
    }

    return nullptr;

}

std::shared_ptr<RoskyInterface> RoskyFloat::neq_op(const std::shared_ptr<RoskyInterface>& __r) const noexcept {

    if (__r->get_type_id() == OBJ_INT || __r->get_type_id() == OBJ_FLOAT) {
        return std::make_shared<RoskyBool>(_data != __r->to_float());
    } else if (__r->get_type_id() == OBJ_NULL) {
        return std::make_shared<RoskyBool>(true);
    }

    return nullptr;

}

std::shared_ptr<RoskyInterface> RoskyFloat::gt_op(const std::shared_ptr<RoskyInterface>& __r) const noexcept {

    if (__r->get_type_id() == OBJ_INT || __r->get_type_id() == OBJ_FLOAT) {
        return std::make_shared<RoskyBool>(_data > __r->to_float());
    }

    return nullptr;

}

std::shared_ptr<RoskyInterface> RoskyFloat::lt_op(const std::shared_ptr<RoskyInterface>& __r) const noexcept {

    if (__r->get_type_id() == OBJ_INT || __r->get_type_id() == OBJ_FLOAT) {
        return std::make_shared<RoskyBool>(_data < __r->to_float());
    }

    return nullptr;

}

std::shared_ptr<RoskyInterface> RoskyFloat::geq_op(const std::shared_ptr<RoskyInterface>& __r) const noexcept {

    if (__r->get_type_id() == OBJ_INT || __r->get_type_id() == OBJ_FLOAT) {
        return std::make_shared<RoskyBool>(_data >= __r->to_float());
    }

    return nullptr;

}

std::shared_ptr<RoskyInterface> RoskyFloat::leq_op(const std::shared_ptr<RoskyInterface>& __r) const noexcept {

    if (__r->get_type_id() == OBJ_INT || __r->get_type_id() == OBJ_FLOAT) {
        return std::make_shared<RoskyBool>(_data <= __r->to_float());
    }

    return nullptr;

}

/******************************************************************************/
