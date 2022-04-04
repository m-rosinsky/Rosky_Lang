
/******************************************************************************/
//
//  Source Name:                native_functions.cpp
//
//  Description:                This file contains the native functions
//                              for rosky. All function return an object pair
//                              and take in a vector of objects.
//
//  Dependencies:               all object definition files
//
//  Classes:                    None
//
//  Inherited Subprograms:      None
//
//  Exported Subprograms:       out
//                              
/******************************************************************************/

#include "../../includes/functions/native_functions.hpp"

/******************************************************************************/

std::pair<std::shared_ptr<RoskyInterface>*, std::shared_ptr<RoskyInterface>>
    out_func(const std::vector<std::shared_ptr<RoskyInterface>>& __func_args,
        size_t __colnum, size_t __linenum) {

    // Check the number of arguments.
    if (__func_args.size() != 1) {
        throw_error(ERR_BAD_FUNC_ARGS, "'out' expects 1 argument, received " +
                    std::to_string(__func_args.size()), __colnum, __linenum);
    }

    // Print the arg to stdout.
    std::cout << __func_args.front()->to_string() << std::flush;

    // Return a null object.
    return {nullptr, std::make_shared<RoskyNull>()};

}

/******************************************************************************/

std::pair<std::shared_ptr<RoskyInterface>*, std::shared_ptr<RoskyInterface>>
    outln_func(const std::vector<std::shared_ptr<RoskyInterface>>& __func_args,
        size_t __colnum, size_t __linenum) {

    // Check the number of arguments.
    if (__func_args.size() != 1) {
        throw_error(ERR_BAD_FUNC_ARGS, "'outln' expects 1 argument, received " +
                    std::to_string(__func_args.size()), __colnum, __linenum);
    }

    // Print the arg to stdout with a new line.
    std::cout << __func_args.front()->to_string() << std::endl;

    // Return a null object.
    return {nullptr, std::make_shared<RoskyNull>()};

}

/******************************************************************************/

std::pair<std::shared_ptr<RoskyInterface>*, std::shared_ptr<RoskyInterface>>
    assert_func(const std::vector<std::shared_ptr<RoskyInterface>>& __func_args,
        size_t __colnum, size_t __linenum) {

    // Check the number of arguments.
    if (__func_args.size() != 1 && __func_args.size() != 2) {
        throw_error(ERR_BAD_FUNC_ARGS, "'assert' expects 1 or 2 arguments, received " +
                    std::to_string(__func_args.size()), __colnum, __linenum);
    }

    // First argument must be a boolean.
    if (__func_args.front()->get_type_id() != OBJ_BOOL) {
        throw_error(ERR_BAD_FUNC_ARGS, "'assert' expects argument of type 'bool', received '" +
                    __func_args.front()->get_type_string() + "'",
                    __colnum, __linenum);
    }

    std::string err_message = "";

    // Get the second argument.
    if (__func_args.size() == 2) {
        err_message = __func_args.back()->to_string();
    }

    // If the argument is false, throw an assertion error.
    if (__func_args.front()->to_bool() == false) {
        throw_error(ERR_ASSERT, err_message, __colnum, __linenum);
    }

    // Return a null object.
    return {nullptr, std::make_shared<RoskyNull>()};

}

/******************************************************************************/
