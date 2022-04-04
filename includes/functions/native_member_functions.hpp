
/******************************************************************************/
//
//  Source Name:                native_member_functions.hpp
//
//  Description:                This file contains the native member functions
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
//                              
/******************************************************************************/

#include <string>                           // std::string
#include <vector>                           // std::vector
#include <utility>                          // std::pair
#include <memory>                           // std::shared_ptr

#include "../objects/rosky_interface.hpp"
#include "../objects/rosky_null.hpp"
#include "../objects/rosky_int.hpp"

#include "../error_handler.hpp"

/******************************************************************************/

// This function returns the size of an iterable.
std::pair<std::shared_ptr<RoskyInterface>*, std::shared_ptr<RoskyInterface>>
    size_func(std::pair<std::shared_ptr<RoskyInterface>*, std::shared_ptr<RoskyInterface>>& __obj,
               const std::vector<std::shared_ptr<RoskyInterface>>& __func_args,
               size_t __colnum, size_t __linenum);

/******************************************************************************/

// This function appends an object to an iterable.
std::pair<std::shared_ptr<RoskyInterface>*, std::shared_ptr<RoskyInterface>>
    append_func(std::pair<std::shared_ptr<RoskyInterface>*, std::shared_ptr<RoskyInterface>>& __obj,
               const std::vector<std::shared_ptr<RoskyInterface>>& __func_args,
               size_t __colnum, size_t __linenum);

/******************************************************************************/
