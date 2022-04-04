
/******************************************************************************/
//
//  Source Name:                rosky_bool.hpp
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

#ifndef ROSKY_BOOL
#define ROSKY_BOOL

/******************************************************************************/

#include <string>                       // std::string
#include <memory>                       // std::shared_ptr

#include "rosky_interface.hpp"
#include "rosky_string.hpp"

/******************************************************************************/

// This is the class definition for the built-in boolean type.
class RoskyBool : public RoskyInterface {

private:

    // The underlying data type is a bool.
    bool _data;

public:

    // Ctors.
    RoskyBool() : _data("") {}
    RoskyBool(bool __data) : _data(__data) {}

    // Dtor.
    ~RoskyBool() {}

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

    // String operators.
    std::shared_ptr<RoskyInterface> concat_op(const std::shared_ptr<RoskyInterface>& __r) const noexcept override;
    
    // Boolean operators.
    std::shared_ptr<RoskyInterface> eq_op(const std::shared_ptr<RoskyInterface>& __r) const noexcept override;

};

/******************************************************************************/

#endif // ROSKY_BOOL