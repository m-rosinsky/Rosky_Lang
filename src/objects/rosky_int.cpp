
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

// Iterable information.
bool RoskyInt::is_iterable() const noexcept {
    return false;
}

bool RoskyInt::is_addressable() const noexcept {
    return false;
}

/******************************************************************************/

// Casting.
long RoskyInt::to_int() const noexcept {
    return _data;
}

double RoskyInt::to_float() const noexcept {
    return (double)_data;
}

std::string RoskyInt::to_string() const noexcept {
    return std::to_string(_data);
}

bool RoskyInt::to_bool() const noexcept {
    return _data != 0;
}

/******************************************************************************/

// Arithmetic operators.
std::shared_ptr<RoskyInterface> RoskyInt::add_op(const std::shared_ptr<RoskyInterface>& __r) const noexcept {

    if (__r->get_type_id() == OBJ_INT) {
        return std::make_shared<RoskyInt>(_data + __r->to_int());
    } else if (__r->get_type_id() == OBJ_FLOAT) {
        return std::make_shared<RoskyFloat>(to_float() + __r->to_float());
    }

    return nullptr;

}

std::shared_ptr<RoskyInterface> RoskyInt::sub_op(const std::shared_ptr<RoskyInterface>& __r) const noexcept {

    if (__r->get_type_id() == OBJ_INT) {
        return std::make_shared<RoskyInt>(_data - __r->to_int());
    } else if (__r->get_type_id() == OBJ_FLOAT) {
        return std::make_shared<RoskyFloat>(to_float() - __r->to_float());
    }

    return nullptr;

}

std::shared_ptr<RoskyInterface> RoskyInt::mul_op(const std::shared_ptr<RoskyInterface>& __r) const noexcept {

    if (__r->get_type_id() == OBJ_INT) {
        return std::make_shared<RoskyInt>(_data * __r->to_int());
    } else if (__r->get_type_id() == OBJ_FLOAT) {
        return std::make_shared<RoskyFloat>(to_float() * __r->to_float());
    } else if (__r->get_type_id() == OBJ_STRING) {
        return __r->mul_op(std::make_shared<RoskyInt>(_data));
    } else if (__r->get_type_id() == OBJ_GROUP) {
        return __r->mul_op(std::make_shared<RoskyInt>(_data));
    }

    return nullptr;

}

std::shared_ptr<RoskyInterface> RoskyInt::div_op(const std::shared_ptr<RoskyInterface>& __r) const noexcept {

    if (__r->get_type_id() == OBJ_INT || __r->get_type_id() == OBJ_FLOAT) {
        return std::make_shared<RoskyFloat>(to_float() / __r->to_float());
    }

    return nullptr;

}

std::shared_ptr<RoskyInterface> RoskyInt::idiv_op(const std::shared_ptr<RoskyInterface>& __r) const noexcept {

    if (__r->get_type_id() == OBJ_INT) {
        return std::make_shared<RoskyInt>((long)(_data / __r->to_int()));
    }

    return nullptr;

}

std::shared_ptr<RoskyInterface> RoskyInt::mod_op(const std::shared_ptr<RoskyInterface>& __r) const noexcept {

    if (__r->get_type_id() == OBJ_INT) {
        return std::make_shared<RoskyInt>(_data % __r->to_int());
    }

    return nullptr;

}

/******************************************************************************/

// String operators.
std::shared_ptr<RoskyInterface> RoskyInt::concat_op(const std::shared_ptr<RoskyInterface>& __r) const noexcept {

    return std::make_shared<RoskyString>(to_string() + __r->to_string());

}

/******************************************************************************/

// Comparison operators.
std::shared_ptr<RoskyInterface> RoskyInt::eq_op(const std::shared_ptr<RoskyInterface>& __r) const noexcept {

    if (__r->get_type_id() == OBJ_INT) {
        return std::make_shared<RoskyBool>(_data == __r->to_int());
    } else if (__r->get_type_id() == OBJ_FLOAT) {
        return std::make_shared<RoskyBool>(to_float() == __r->to_float());
    } else if (__r->get_type_id() == OBJ_NULL) {
        return std::make_shared<RoskyBool>(false);
    }

    return nullptr;

}

std::shared_ptr<RoskyInterface> RoskyInt::neq_op(const std::shared_ptr<RoskyInterface>& __r) const noexcept {

    if (__r->get_type_id() == OBJ_INT) {
        return std::make_shared<RoskyBool>(_data != __r->to_int());
    } else if (__r->get_type_id() == OBJ_FLOAT) {
        return std::make_shared<RoskyBool>(to_float() != __r->to_float());
    } else if (__r->get_type_id() == OBJ_NULL) {
        return std::make_shared<RoskyBool>(true);
    }

    return nullptr;

}

std::shared_ptr<RoskyInterface> RoskyInt::gt_op(const std::shared_ptr<RoskyInterface>& __r) const noexcept {

    if (__r->get_type_id() == OBJ_INT) {
        return std::make_shared<RoskyBool>(_data > __r->to_int());
    } else if (__r->get_type_id() == OBJ_FLOAT) {
        return std::make_shared<RoskyBool>(to_float() > __r->to_float());
    }

    return nullptr;

}

std::shared_ptr<RoskyInterface> RoskyInt::lt_op(const std::shared_ptr<RoskyInterface>& __r) const noexcept {

    if (__r->get_type_id() == OBJ_INT) {
        return std::make_shared<RoskyBool>(_data < __r->to_int());
    } else if (__r->get_type_id() == OBJ_FLOAT) {
        return std::make_shared<RoskyBool>(to_float() < __r->to_float());
    }

    return nullptr;

}

std::shared_ptr<RoskyInterface> RoskyInt::geq_op(const std::shared_ptr<RoskyInterface>& __r) const noexcept {

    if (__r->get_type_id() == OBJ_INT) {
        return std::make_shared<RoskyBool>(_data >= __r->to_int());
    } else if (__r->get_type_id() == OBJ_FLOAT) {
        return std::make_shared<RoskyBool>(to_float() >= __r->to_float());
    }

    return nullptr;

}

std::shared_ptr<RoskyInterface> RoskyInt::leq_op(const std::shared_ptr<RoskyInterface>& __r) const noexcept {

    if (__r->get_type_id() == OBJ_INT) {
        return std::make_shared<RoskyBool>(_data <= __r->to_int());
    } else if (__r->get_type_id() == OBJ_FLOAT) {
        return std::make_shared<RoskyBool>(to_float() <= __r->to_float());
    }

    return nullptr;

}

/******************************************************************************/