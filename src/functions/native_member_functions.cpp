
/******************************************************************************/
//
//  Source Name:                native_member_functions.cpp
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

#include "../../includes/functions/native_member_functions.hpp"

/******************************************************************************/

std::pair<std::shared_ptr<RoskyInterface>*, std::shared_ptr<RoskyInterface>>
    size_func(std::pair<std::shared_ptr<RoskyInterface>*, std::shared_ptr<RoskyInterface>>& __obj,
               const std::vector<std::shared_ptr<RoskyInterface>>& __func_args,
               size_t __colnum, size_t __linenum) {

    // Check the number of arguments.
    if (__func_args.size() != 0) {
        throw_error(ERR_BAD_FUNC_ARGS, "'size' expects 0 arguments, received " +
                    std::to_string(__func_args.size()), __colnum, __linenum);
    }

    // Ensure we have a string type as an object.
    if (__obj.second->is_iterable() == false) {
        throw_error(ERR_NONMEMBER, "'size' is not a member function for type '" +
                    __obj.second->get_type_string() + "'", __colnum, __linenum);
    }

    // return the new obj.
    return {nullptr, std::make_shared<RoskyInt>(__obj.second->get_size())};

}

/******************************************************************************/

std::pair<std::shared_ptr<RoskyInterface>*, std::shared_ptr<RoskyInterface>>
    append_func(std::pair<std::shared_ptr<RoskyInterface>*, std::shared_ptr<RoskyInterface>>& __obj,
               const std::vector<std::shared_ptr<RoskyInterface>>& __func_args,
               size_t __colnum, size_t __linenum) {

    // Check the number of arguments.
    if (__func_args.size() != 1) {
        throw_error(ERR_BAD_FUNC_ARGS, "'append' expects 1 argument, received " +
                    std::to_string(__func_args.size()), __colnum, __linenum);
    }

    // Check if the object is a group.
    if (__obj.second->get_type_id() != OBJ_GROUP) {
        throw_error(ERR_NONMEMBER, "'append' is not a member function for type '" +
                    __obj.second->get_type_string() + "'", __colnum, __linenum);
    }

    // Perform the function.
    if (__obj.first != nullptr) {
        (*__obj.first)->append_func(__func_args.front());
    } else {
        __obj.second->append_func(__func_args.front());
    }

    // Return null, since this is a void function.
    return {nullptr, std::make_shared<RoskyNull>()};

}

/******************************************************************************/

