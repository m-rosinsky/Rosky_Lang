
/******************************************************************************/
//
//  Source Name:                rosky_string.hpp
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

#ifndef ROSKY_STRING
#define ROSKY_STRING

/******************************************************************************/

#include <string>                       // std::string
#include <memory>                       // std::shared_ptr

#include "rosky_interface.hpp"
#include "rosky_bool.hpp"

/******************************************************************************/

// This is the class definition for the built-in string type.
class RoskyString : public RoskyInterface {

private:

    // The underlying data type is an std::string
    std::string _data;

public:

    // Ctors.
    RoskyString() : _data("") {}
    RoskyString(const std::string& __data) : _data(__data) {}

    // Dtor.
    ~RoskyString() {}

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

    // Arithmetic operators.
    std::shared_ptr<RoskyInterface> add_op(const std::shared_ptr<RoskyInterface>& __r) const noexcept override;

    // String operators.
    std::shared_ptr<RoskyInterface> concat_op(const std::shared_ptr<RoskyInterface>& __r) const noexcept override;
    
    // Boolean operators.
    std::shared_ptr<RoskyInterface> eq_op(const std::shared_ptr<RoskyInterface>& __r) const noexcept override;

    // Iterable functionality.
    size_t get_size() const noexcept override;
    std::pair<std::shared_ptr<RoskyInterface>*, std::shared_ptr<RoskyInterface>> index_op(const std::shared_ptr<RoskyInterface>& __r, bool __addr) noexcept override;

};

/******************************************************************************/

#endif // ROSKY_STRING