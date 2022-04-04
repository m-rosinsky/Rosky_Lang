
/******************************************************************************/
//
//  Source Name:                rosky_pointer.hpp
//
//  Description:                This file contains the class definition for
//                              the built in pointer type.
// 
//                              The underlying data type is a pointer
//                              to a shared_ptr instance of an object.
//
//  Dependencies:               RoskyInterface
//
//  Classes:                    RoskyPointer
//
//  Inherited Subprograms:      get_type_id
//                              get_type_string
//                              to_int
//                              to_string
//                              add_op
//                              mul_op
//
//  Exported Subprograms:       ctor
//                              ctor(ptr)
//                              
/******************************************************************************/

#ifndef ROSKY_POINTER
#define ROSKY_POINTER

/******************************************************************************/

#include <string>                       // std::string
#include <sstream>                      // std::stringstream    
#include <memory>                       // std::shared_ptr
#include <utility>                      // std::pair

#include "rosky_interface.hpp"
#include "rosky_string.hpp"
#include "rosky_bool.hpp"

/******************************************************************************/

// This is the class defintion for the RoskyInt class.
class RoskyPointer : public RoskyInterface {

private:

    // The underlying data type is a pointer to a shared_ptr
    // instance of an object.
    std::shared_ptr<RoskyInterface>* _data;

public:

    // Constructors.
    RoskyPointer() : _data(nullptr) {}
    RoskyPointer(std::shared_ptr<RoskyInterface>* __data)
        : _data(__data) {}

    // Destructor.
    ~RoskyPointer() {}

    // Type information.
    OBJ_TYPES get_type_id() const noexcept override;
    std::string get_type_string() const noexcept override;

    // Iterable information.
    bool is_iterable() const noexcept override;
    bool is_addressable() const noexcept override;

    // Casting.
    long to_int() const noexcept override;
    std::string to_string() const noexcept override;
    std::shared_ptr<RoskyInterface>* to_pointer() const noexcept override;
    bool to_bool() const noexcept override;

    // Pointer operators.
    std::pair<std::shared_ptr<RoskyInterface>*, std::shared_ptr<RoskyInterface>> deref_op() const noexcept override;

    // String operators.
    std::shared_ptr<RoskyInterface> concat_op(const std::shared_ptr<RoskyInterface>& __r) const noexcept override;

    // Boolean operators.
    std::shared_ptr<RoskyInterface> eq_op(const std::shared_ptr<RoskyInterface>& __r) const noexcept override;

};

/******************************************************************************/

#endif // ROSKY_POINTER
