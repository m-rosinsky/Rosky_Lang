
/******************************************************************************/
//
//  Source Name:                rosky_null.hpp
//
//  Description:                This file contains the class definition for
//                              the built in null type.
// 
//                              There is no underlying data type for this
//                              class.
//
//  Dependencies:               RoskyInterface
//
//  Classes:                    RoskyNull
//
//  Inherited Subprograms:      get_type_id
//                              get_type_string
//                              to_int
//                              to_string
//
//  Exported Subprograms:       ctor
//                              
/******************************************************************************/

#ifndef ROSKY_NULL
#define ROSKY_NULL

/******************************************************************************/

#include <string>                       // std::string

#include "rosky_interface.hpp"
#include "rosky_string.hpp"

/******************************************************************************/

// This is the class defintion for the RoskyNull class.
class RoskyNull : public RoskyInterface {

public:

    // Constructors.
    RoskyNull() {}
    
    // Destructor.
    ~RoskyNull() {}
    
    // Type information.
    OBJ_TYPES get_type_id() const noexcept override;
    std::string get_type_string() const noexcept override;

    // Casting.
    long to_int() const noexcept override;
    std::string to_string() const noexcept override;

    // String operators.
    std::shared_ptr<RoskyInterface> concat_op(const std::shared_ptr<RoskyInterface>& __r) const noexcept override;

};

/******************************************************************************/

#endif // ROSKY_NULL
