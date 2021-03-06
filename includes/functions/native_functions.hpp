
/******************************************************************************/
//
//  Source Name:                native_functions.hpp
//
//  Description:                This file contains the native functions
//                              for rosky. All function return an object pair
//                              and take in a vector of objects.
//
//  Dependencies:               all object definition files
//                              error_handler.hpp
//
//  Classes:                    None
//
//  Inherited Subprograms:      None
//
//  Exported Subprograms:       out
//                              outln
//                              scan
//                              assert
//                              
/******************************************************************************/

#ifndef NATIVE_FUNCTIONS
#define NATIVE_FUNCTIONS

/******************************************************************************/

#include <string>                           // std::string
#include <vector>                           // std::vector
#include <utility>                          // std::pair
#include <memory>                           // std::shared_ptr
#include <iostream>                         // std::cout, std::cerr, std::endl

#include "../objects/rosky_interface.hpp"
#include "../objects/rosky_null.hpp"
#include "../objects/rosky_group.hpp"
#include "../objects/rosky_int.hpp"
#include "../objects/rosky_string.hpp"

#include "../error_handler.hpp"

/******************************************************************************/

// This function outputs an object to the standard output.
std::pair<std::shared_ptr<RoskyInterface>*, std::shared_ptr<RoskyInterface>>
    out_func(const std::vector<std::shared_ptr<RoskyInterface>>& __func_args,
             size_t __colnum, size_t __linenum);

/******************************************************************************/

// This function outputs an object to the standard output and inserts
// a new line after.
std::pair<std::shared_ptr<RoskyInterface>*, std::shared_ptr<RoskyInterface>>
    outln_func(const std::vector<std::shared_ptr<RoskyInterface>>& __func_args,
               size_t __colnum, size_t __linenum);

/******************************************************************************/

// This function gets a string from stdin.
std::pair<std::shared_ptr<RoskyInterface>*, std::shared_ptr<RoskyInterface>>
    scan_func(const std::vector<std::shared_ptr<RoskyInterface>>& __func_args,
               size_t __colnum, size_t __linenum);

/******************************************************************************/

// This function takes in a boolean expression and throws an assertion error
// if the condition is false.
std::pair<std::shared_ptr<RoskyInterface>*, std::shared_ptr<RoskyInterface>>
    assert_func(const std::vector<std::shared_ptr<RoskyInterface>>& __func_args,
                size_t __colnum, size_t __linenum);

/******************************************************************************/

// This function generates a group of integers in a given range.
std::pair<std::shared_ptr<RoskyInterface>*, std::shared_ptr<RoskyInterface>>
    range_func(const std::vector<std::shared_ptr<RoskyInterface>>& __func_args,
                size_t __colnum, size_t __linenum);

/******************************************************************************/

// This function returns a string of the provided object type.
std::pair<std::shared_ptr<RoskyInterface>*, std::shared_ptr<RoskyInterface>>
    type_func(const std::vector<std::shared_ptr<RoskyInterface>>& __func_args,
                size_t __colnum, size_t __linenum);

/******************************************************************************/

#endif // NATIVE_FUNCTIONS
