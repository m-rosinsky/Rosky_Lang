
/******************************************************************************/
//
//  Source Name:                rosky_group.hpp
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

#ifndef ROSKY_GROUP
#define ROSKY_GROUP

/******************************************************************************/

#include <string>                           // std::string

#include "rosky_interface.hpp"
#include "rosky_string.hpp"
#include "rosky_bool.hpp"

/******************************************************************************/

// This is the class defintion for the RoskyGroup class.
class RoskyGroup : public RoskyInterface {

private:

    // The underlying data type is a deque.
    std::deque<std::shared_ptr<RoskyInterface>> _data;

public:

    // Constructors.
    RoskyGroup() : _data(0) {}
    RoskyGroup(const std::deque<std::shared_ptr<RoskyInterface>>& __data) : _data(__data) {}

    // Destrcutor.
    ~RoskyGroup() {}

    // Type information.
    OBJ_TYPES get_type_id() const noexcept override;
    std::string get_type_string() const noexcept override;

    // Iterable information.
    bool is_iterable() const noexcept override;
    bool is_addressable() const noexcept override;

    // Casting.
    long to_int() const noexcept override;
    std::string to_string() const noexcept override;
    bool to_bool() const noexcept override;
    std::deque<std::shared_ptr<RoskyInterface>> to_group() const noexcept override;

    // Arithmetic operators.
    std::shared_ptr<RoskyInterface> add_op(const std::shared_ptr<RoskyInterface>& __r) const noexcept override;
    std::shared_ptr<RoskyInterface> mul_op(const std::shared_ptr<RoskyInterface>& __r) const noexcept override;

    // String operators.
    std::shared_ptr<RoskyInterface> concat_op(const std::shared_ptr<RoskyInterface>& __r) const noexcept override;

    // Boolean operators.
    std::shared_ptr<RoskyInterface> eq_op(const std::shared_ptr<RoskyInterface>& __r) const noexcept override;

    // Iterable functionality.
    size_t get_size() const noexcept override;
    std::pair<std::shared_ptr<RoskyInterface>*, std::shared_ptr<RoskyInterface>> index_op(const std::shared_ptr<RoskyInterface>& __r) noexcept override;
    void append_func(const std::shared_ptr<RoskyInterface>& __r) noexcept override;

};

/******************************************************************************/

#endif // ROSKY_GROUP

