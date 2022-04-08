
/******************************************************************************/
//
//  Source Name:                rosky_float.hpp
//
//  Description:                This file contains the class definition for
//                              the built in float type.
// 
//                              The underlying data type is a double, rather
//                              than a float.
//
//  Dependencies:               RoskyInterface
//
//  Classes:                    RoskyFloat
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
//                              ctor(double)
//                              
/******************************************************************************/

#ifndef ROSKY_FLOAT
#define ROSKY_FLOAT

/******************************************************************************/

#include <string>                           // std::string

#include "rosky_interface.hpp"
#include "rosky_string.hpp"
#include "rosky_bool.hpp"

/******************************************************************************/

// This is the class defintion for the RoskyFloat class.
class RoskyFloat : public RoskyInterface {

private:

    // The underlying data type is a double.
    double _data;

public:

    // Constructors.
    RoskyFloat() : _data(0) {}
    RoskyFloat(long __data) : _data(__data) {}
    RoskyFloat(double __data) : _data(__data) {}

    // Destrcutor.
    ~RoskyFloat() {}

    // Type information.
    OBJ_TYPES get_type_id() const noexcept override;
    std::string get_type_string() const noexcept override;

    // Iterable information.
    bool is_iterable() const noexcept override;
    bool is_addressable() const noexcept override;

    // Casting.
    long to_int() const noexcept override;
    double to_float() const noexcept override;
    std::string to_string() const noexcept override;
    bool to_bool() const noexcept override;

    // Arithmetic operators.
    std::shared_ptr<RoskyInterface> add_op(const std::shared_ptr<RoskyInterface>& __r) const noexcept override;
    std::shared_ptr<RoskyInterface> sub_op(const std::shared_ptr<RoskyInterface>& __r) const noexcept override;
    std::shared_ptr<RoskyInterface> mul_op(const std::shared_ptr<RoskyInterface>& __r) const noexcept override;
    std::shared_ptr<RoskyInterface> div_op(const std::shared_ptr<RoskyInterface>& __r) const noexcept override;

    // String operators.
    std::shared_ptr<RoskyInterface> concat_op(const std::shared_ptr<RoskyInterface>& __r) const noexcept override;

    // Comparison operators.
    std::shared_ptr<RoskyInterface> eq_op(const std::shared_ptr<RoskyInterface>& __r) const noexcept override;
    std::shared_ptr<RoskyInterface> neq_op(const std::shared_ptr<RoskyInterface>& __r) const noexcept override;
    std::shared_ptr<RoskyInterface> gt_op(const std::shared_ptr<RoskyInterface>& __r) const noexcept override;
    std::shared_ptr<RoskyInterface> lt_op(const std::shared_ptr<RoskyInterface>& __r) const noexcept override;
    std::shared_ptr<RoskyInterface> geq_op(const std::shared_ptr<RoskyInterface>& __r) const noexcept override;
    std::shared_ptr<RoskyInterface> leq_op(const std::shared_ptr<RoskyInterface>& __r) const noexcept override;

};

/******************************************************************************/

#endif // ROSKY_FLOAT
