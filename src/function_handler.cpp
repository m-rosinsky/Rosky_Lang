
/******************************************************************************/
//
//  Source Name:                function_handler.cpp
//
//  Description:                This file contains the function table class
//                              which holds the table of both built-in and
//                              user-defined functions.
// 
//                              The class contains functions to
//                              operate on the function table, as well
//                              as call functions within the table.
//
//  Dependencies:               all object definition files
//
//  Classes:                    FunctionTable_T
//
//  Inherited Subprograms:      None
//
//  Exported Subprograms:       ctor
//                              is_function
//                              
/******************************************************************************/

#include "../includes/function_handler.hpp"

/******************************************************************************/

bool FunctionTable_T::is_function(const std::string& __func) const noexcept {

    return _native_table.count(__func) > 0;

}

/******************************************************************************/

FunctionTable_T::obj_pair FunctionTable_T::call_function(const std::string& __func,
                                                         const std::vector<obj>& __func_args,
                                                         size_t __colnum, size_t __linenum) {

    // Check if the provided function name is in the table.
    if (!is_function(__func)) { return {nullptr, nullptr}; }
    
    // Call the appropriate function with the given args.
    return _native_table[__func](__func_args, __colnum, __linenum);

}

/******************************************************************************/

bool FunctionTable_T::is_member_function(const std::string& __func) const noexcept {

    return _native_member_table.count(__func) > 0;

}

/******************************************************************************/

FunctionTable_T::obj_pair FunctionTable_T::call_member_function
    (const std::string& __func,
     obj_pair& __obj,
     const std::vector<obj>& __func_args,
     size_t __colnum, size_t __linenum) {

    // Check if the provided function name is in the member table.
    if (!is_member_function(__func)) { return {nullptr, nullptr}; }
    
    // Call the appropriate function with the given args.
    return _native_member_table[__func](__obj, __func_args, __colnum, __linenum);

}

/******************************************************************************/
