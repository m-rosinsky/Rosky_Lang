
/******************************************************************************/
//
//  Source Name:                function_handler.hpp
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
//                              native_functions.hpp
//                              native_member_functions.hpp
//
//  Classes:                    FunctionTable_T
//
//  Inherited Subprograms:      None
//
//  Exported Subprograms:       ctor
//                              is_function
//                              
/******************************************************************************/

#ifndef FUNCTION_HANDLER
#define FUNCTION_HANDLER

/******************************************************************************/

#include <string>                           // std::string
#include <map>                              // std::map
#include <functional>                       // std::function
#include <vector>                           // std::vector
#include <utility>                          // std::pair
#include <memory>                           // std::shared_ptr

#include "objects/rosky_interface.hpp"

#include "functions/native_functions.hpp"
#include "functions/native_member_functions.hpp"

/******************************************************************************/

// This is the definition for the function table class.
class FunctionTable_T {

public:

    // Type definitions.
    typedef std::shared_ptr<RoskyInterface>     obj;
    typedef obj*                                obj_ptr;
    typedef std::pair<obj*, obj>                obj_pair;

private:

    // This is the built-in function table, which is a mapping of the name
    // of the function to the function pointer along with the function
    // call's metadata.
    std::map<std::string, std::function<obj_pair(const std::vector<obj>&, size_t, size_t)>> _native_table;

    // This is the built-in member function table, which contains member
    // functions such as .append() or .size(). It takes in an object
    // pair as an argument so it knows the object that the member
    // function acts on.
    std::map<std::string, std::function<obj_pair(obj_pair&, const std::vector<obj>&, size_t, size_t)>> _native_member_table;

public:

    // Ctor.
    FunctionTable_T() {

        // Populate the function table with the built-in function pointers.
        _native_table["out"] = out_func;
        _native_table["outln"] = outln_func;
        _native_table["assert"] = assert_func;

        // Populate the native function table with the built-in member funciton pointers.
        _native_member_table["size"] = size_func;
        _native_member_table["append"] = append_func;

    }

    // This function returns true if a specified string is in the function
    // table.
    bool is_function(const std::string& __func) const noexcept;

    // This function calls a function from the table and returns the return value.
    obj_pair call_function(const std::string& __func, const std::vector<obj>& __func_args,
                           size_t __colnum, size_t __linenum);

    // This function returns true if a specified string is in the member function
    // table.
    bool is_member_function(const std::string& __func) const noexcept;

    // This function calls a function from the member function table and returns
    // the value.
    obj_pair call_member_function(const std::string& __func,
                                  obj_pair& __obj,
                                  const std::vector<obj>& __func_args,
                                  size_t __colnum, size_t __linenum);

};

/******************************************************************************/

#endif // FUNCTION_HANDLER

/******************************************************************************/
