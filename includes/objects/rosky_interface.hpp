
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

/******************************************************************************/

// This enum defines the built-in object types.
enum OBJ_TYPES {

    OBJ_INT,
    OBJ_STRING,

};

/******************************************************************************/

// This is the class definition for the RoskyInterface class.
class RoskyInterface {

public:

    // Type information.
    virtual OBJ_TYPES get_type_id() const noexcept = 0;
    virtual std::string get_type_string() const noexcept = 0;

    // Casting.
    virtual long to_int() const noexcept { return 0; }
    virtual std::string to_string() const noexcept { return ""; } 
    
    // Arithmetic operators.
    virtual std::shared_ptr<RoskyInterface> add_op(const std::shared_ptr<RoskyInterface>& __r) const noexcept { return nullptr; }
    virtual std::shared_ptr<RoskyInterface> mul_op(const std::shared_ptr<RoskyInterface>& __r) const noexcept { return nullptr; }

};

/******************************************************************************/

#endif // ROSKY_INTERFACE
