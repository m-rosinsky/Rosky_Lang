
/******************************************************************************/
//
//  Source Name:                rosky_int.hpp
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
//
//  Exported Subprograms:       None
//                              
/******************************************************************************/

#ifndef ROSKY_INT
#define ROSKY_INT

/******************************************************************************/

#include <string>                           // std::string

#include "rosky_interface.hpp"

/******************************************************************************/

// This is the class defintion for the RoskyInt class.
class RoskyInt : public RoskyInterface {

private:

    // The underlying data type is a long.
    long _data;

public:

    // Constructors.
    RoskyInt() : _data(0) {}
    RoskyInt(long __data) : _data(__data) {}

    // Type information.
    OBJ_TYPES get_type_id() const noexcept override;
    std::string get_type_string() const noexcept override;

    // Casting.
    long to_int() const noexcept override;
    std::string to_string() const noexcept override;

    // Arithmetic operators.
    std::shared_ptr<RoskyInterface> add_op(const std::shared_ptr<RoskyInterface>& __r) const noexcept override;
    std::shared_ptr<RoskyInterface> mul_op(const std::shared_ptr<RoskyInterface>& __r) const noexcept override;

};

/******************************************************************************/

#endif // ROSKY_INT
