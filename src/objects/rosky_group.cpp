
/******************************************************************************/
//
//  Source Name:                rosky_group.cpp
//
//  Description:                This file contains the class definition for
//                              the built in group type.
// 
//                              The underlying data type is a deque.
//
//  Dependencies:               RoskyInterface
//
//  Classes:                    RoskyGroup
//
//  Inherited Subprograms:      get_type_id
//                              get_type_string
//                              to_int
//                              to_string
//                              add_op
//                              mul_op
//
//  Exported Subprograms:       ctor
//                              ctor(deque)
//                              
/******************************************************************************/

#include "../../includes/objects/rosky_group.hpp"

/******************************************************************************/

// Type information.
OBJ_TYPES RoskyGroup::get_type_id() const noexcept {
    return OBJ_GROUP;
}

std::string RoskyGroup::get_type_string() const noexcept {
    return "group";
}

/******************************************************************************/

// Iterable information.
bool RoskyGroup::is_iterable() const noexcept {
    return true;
}

bool RoskyGroup::is_addressable() const noexcept {
    return true;
}

/******************************************************************************/

// Casting.
long RoskyGroup::to_int() const noexcept {
    return 0;
}

std::string RoskyGroup::to_string() const noexcept {

    std::string ret = "[";
    for (auto it = _data.begin(); it != _data.end(); it++) {

        if ((*it)->get_type_id() == OBJ_STRING) {
            ret += ('"' + (*it)->to_string() + '"'); 
        } else {
            ret += (*it)->to_string();
        }

        if (it + 1 != _data.end()) {
            ret += ", ";
        }

    }
    ret += "]";

    return ret;

}

bool RoskyGroup::to_bool() const noexcept {
    return _data.size() != 0;
}

std::deque<std::shared_ptr<RoskyInterface>> RoskyGroup::to_group() const noexcept {
    return _data;
}

/******************************************************************************/

// Arithmetic operators.
std::shared_ptr<RoskyInterface> RoskyGroup::add_op(const std::shared_ptr<RoskyInterface>& __r) const noexcept {

    // Only able to add other groups.
    if (__r->get_type_id() == OBJ_GROUP) {
        auto d = _data;
        for (auto& data : __r->to_group()) {
            d.push_back(data);
        }
        return std::make_shared<RoskyGroup>(d);
    }

    return nullptr;

}

std::shared_ptr<RoskyInterface> RoskyGroup::mul_op(const std::shared_ptr<RoskyInterface>& __r) const noexcept {

    // Can only be multiplied by integers.
    if (__r->get_type_id() == OBJ_INT) {
        std::deque<std::shared_ptr<RoskyInterface>> d;
        for (long i = 0; i < __r->to_int(); i++) {
            
            for (auto& data : _data) {
                d.push_back(data);
            }

        }
        return std::make_shared<RoskyGroup>(d);
    }

    return nullptr;

}

/******************************************************************************/

// String operators.
std::shared_ptr<RoskyInterface> RoskyGroup::concat_op(const std::shared_ptr<RoskyInterface>& __r) const noexcept {
    return std::make_shared<RoskyString>(to_string() + __r->to_string());
}

/******************************************************************************/

// Boolean operators.
std::shared_ptr<RoskyInterface> RoskyGroup::eq_op(const std::shared_ptr<RoskyInterface>& __r) const noexcept {

    // Can only be compared to other groups.
    if (__r->get_type_id() == OBJ_GROUP) {
        
        if (_data.size() != __r->get_size()) {
            return std::make_shared<RoskyBool>(false);
        }

        auto it1 = _data.begin();
        auto it2 = __r->to_group().begin();

        while (it1 != _data.end()) {
            if (((*it1)->eq_op(*it2))->to_bool() == false) {
                return std::make_shared<RoskyBool>(false);
            }
            it1++;
            it2++;
        }

        return std::make_shared<RoskyBool>(true);

    }

    return nullptr;

}

/******************************************************************************/

// Iterable functionality.
size_t RoskyGroup::get_size() const noexcept {
    return _data.size();
}

std::pair<std::shared_ptr<RoskyInterface>*, std::shared_ptr<RoskyInterface>>
    RoskyGroup::index_op(const std::shared_ptr<RoskyInterface>& __r) noexcept {

    if (__r->get_type_id() != OBJ_INT) {
        return {nullptr, nullptr};
    }

    if (__r->to_int() < _data.size() && __r->to_int() >= 0) {
        return { &(_data[__r->to_int()]), _data[__r->to_int()] };
    }

    return {nullptr, nullptr};

}

void RoskyGroup::append_func(const std::shared_ptr<RoskyInterface>& __r) noexcept {

    _data.push_back(__r);

}

/******************************************************************************/
