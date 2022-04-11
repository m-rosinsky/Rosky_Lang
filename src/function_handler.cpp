
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

void FunctionTable_T::add_user_function(const std::string& __func,
                                        const std::vector<std::string>& __func_params,
                                        size_t __scope, size_t __start_idx ,size_t __end_idx) noexcept {

    // Create a shared_ptr to the new entry.
    std::shared_ptr<UserFunction_T> new_func =
        std::make_shared<UserFunction_T>(__func, __func_params, __scope, __start_idx, __end_idx);

    // Push the function in the front of the user table, so it is found first.
    _user_func_table.push_front(new_func);

}

/******************************************************************************/

bool FunctionTable_T::is_user_function(const std::string& __func) const noexcept {

    // Iterate through the user function table.
    for (auto& func : _user_func_table) {

        if (func->_func_name == __func) {
            return true;
        }

    }

    return false;

}

/******************************************************************************/

std::shared_ptr<UserFunction_T> FunctionTable_T::get_user_function(const std::string& __func) const noexcept {

    // Iterate through the function table.
    for (auto& func : _user_func_table) {

        if (func->_func_name == __func) {
            return func;
        }

    }

    return nullptr;

}

/******************************************************************************/

void FunctionTable_T::release_above_scope(size_t __scope) noexcept {

    std::deque<size_t> deletion;

    size_t idx = 0;
    for (auto& func : _user_func_table) {
        if (func->_scope >= __scope) {
            deletion.push_front(idx);
        }
        idx++;
    }

    for (auto it = deletion.begin(); it != deletion.end(); it++) {
        _user_func_table.erase(_user_func_table.begin() + *it);
    }

}

/******************************************************************************/
