
/******************************************************************************/
//
//  Source Name:                rosky_interface.hpp
//
//  Description:                This file contains the interface for all
//                              built-in objects to inherit from.
//
//  Dependencies:               None
//
//  Classes:                    RoskyInterface
//
//  Inherited Subprograms:      None
//
//  Exported Subprograms:       get_type_id
//                              get_type_string
//                              to_int
//                              to_string
//                              add_op
//                              mul_op
//                              
/******************************************************************************/

#ifndef ROSKY_INTERFACE
#define ROSKY_INTERFACE

/******************************************************************************/

#include <memory>                   // std::shared_ptr
#include <string>                   // std::string
#include <utility>                  // std::pair
#include <deque>                    // std::deque

/******************************************************************************/

// This enum defines the built-in object types.
enum OBJ_TYPES {

    OBJ_INT,
    OBJ_POINTER,
    OBJ_NULL,
    OBJ_STRING,
    OBJ_BOOL,
    OBJ_GROUP,

};

/******************************************************************************/

// This is the class definition for the RoskyInterface class.
class RoskyInterface {

public:

    // Virtual desctructor.
    virtual ~RoskyInterface() {}

    // Type information.
    virtual OBJ_TYPES get_type_id() const noexcept = 0;
    virtual std::string get_type_string() const noexcept = 0;

    // Iterable information.
    virtual bool is_iterable() const noexcept = 0;
    virtual bool is_addressable() const noexcept = 0;

    // Casting.
    virtual long to_int() const noexcept { return 0; }
    virtual std::string to_string() const noexcept = 0;
    virtual std::shared_ptr<RoskyInterface>* to_pointer() const noexcept { return nullptr; }
    virtual bool to_bool() const noexcept = 0;
    virtual std::deque<std::shared_ptr<RoskyInterface>> to_group() const noexcept { return {}; }
    
    // Arithmetic operators.
    virtual std::shared_ptr<RoskyInterface> add_op(const std::shared_ptr<RoskyInterface>& __r) const noexcept { return nullptr; }
    virtual std::shared_ptr<RoskyInterface> mul_op(const std::shared_ptr<RoskyInterface>& __r) const noexcept { return nullptr; }

    // Pointer operators.
    virtual std::pair<std::shared_ptr<RoskyInterface>*, std::shared_ptr<RoskyInterface>> deref_op() const noexcept { return {nullptr, nullptr}; }

    // String operators.
    virtual std::shared_ptr<RoskyInterface> concat_op(const std::shared_ptr<RoskyInterface>& __r) const noexcept { return nullptr; }

    // Boolean operators.
    virtual std::shared_ptr<RoskyInterface> eq_op(const std::shared_ptr<RoskyInterface>& __r) const noexcept { return nullptr; }

    // Iterable functionality.
    virtual size_t get_size() const noexcept { return 0; }
    virtual std::pair<std::shared_ptr<RoskyInterface>*, std::shared_ptr<RoskyInterface>> index_op(const std::shared_ptr<RoskyInterface>& __r) noexcept { return {nullptr, nullptr}; }
    virtual void append_func(const std::shared_ptr<RoskyInterface>& __r) noexcept {}

};

/******************************************************************************/

#endif // ROSKY_INTERFACE
