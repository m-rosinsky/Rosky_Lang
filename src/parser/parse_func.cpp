
/******************************************************************************/
//
//  Source Name:                parse_func.cpp
//
//  Description:                This file is responsible for parsing
//                              function calls. It will create
//                              a vector of argument objects and
//                              call the function handler to evaluate
//                              the given function if it is formatted
//                              correctly.
//
//  Dependencies:               lexer_utils.hpp
//                              parser_utils.hpp
//                              error_handler.hpp
//                              evaluator.hpp
//                              variable_handler.hpp
//                              function_handler.hpp
//                              rosky_interface.hpp
//
//  Classes:                    Parser_T
//
//  Inherited Subprograms:      None
//
//  Exported Subprograms:       parse_func
//                              parse_member_func
//                              
/******************************************************************************/

#include "../../includes/parser.hpp"

/******************************************************************************/

// This is a helper function that parses function arguments into a vector
// of objects.
std::vector<std::shared_ptr<RoskyInterface>> Parser_T::parse_func_args(
    size_t& __idx, size_t __end_idx, size_t __scope) {

    // Create a vector to hold the function argument objects.
    std::vector<std::shared_ptr<RoskyInterface>> func_args;

    // Collect function arguments until no more commas.
    size_t comma_idx = find_nextof(_tokens, ++__idx, ",");

    // This flag marks if we have a comma.
    bool has_comma = false;

    // While the comma comes before the end idx.
    while (comma_idx != 0 && comma_idx < __end_idx) {

        // Mark the flag.
        has_comma = true;
        
        // If the comma is the next index, throw an error for an empty arg.
        if (comma_idx == __idx) {
            throw_error(ERR_EMPTY_ARG, "", _tokens[__idx]->_colnum, _tokens[__idx]->_linenum);
        }

        // Parse the expression from this index, to the comma index.
        auto obj_pair = parse_expr(__idx, comma_idx, __scope);

        // Add the object to the argument table.
        func_args.push_back(obj_pair.second);

        // Find the next comma.
        comma_idx = find_nextof(_tokens, ++__idx, ",");

    }

    // If the next index is the closing parentheses and no comma, return empty.
    if (__idx == __end_idx && !has_comma) {
        return func_args;
    }

    // If next index is closing parentheses and comma, empty arg.
    if (__idx == __end_idx) {
        throw_error(ERR_EMPTY_ARG, "", _tokens[__idx]->_colnum, _tokens[__idx]->_linenum);
    }

    // Parse the expression between this index and the end idx.
    auto obj_pair = parse_expr(__idx, __end_idx, __scope);

    // Add the object to the argument table.
    func_args.push_back(obj_pair.second);

    // Return the table.
    return func_args;

}

/******************************************************************************/

std::pair<std::shared_ptr<RoskyInterface>*, std::shared_ptr<RoskyInterface>>
    Parser_T::parse_func(size_t& __idx, size_t __end_idx, size_t __scope) {

    // Create a vector to hold the function argument objects.
    std::vector<std::shared_ptr<RoskyInterface>> func_args;

    // Bookmark the token metadata for the function call.
    size_t func_col = _tokens[__idx]->_colnum;
    size_t func_lin = _tokens[__idx]->_linenum;

    // This holds the function name.
    std::string func_name = _tokens[__idx++]->_token;

    // The next token must be a left paren.
    if (_tokens[__idx]->_token != "(") {
        throw_error(ERR_SYNTAX, "Illegal use of reserved function name '" + func_name + "'",
                    _tokens[__idx-1]->_colnum, _tokens[__idx-1]->_linenum);
    }

    // Find the matching parentheses.
    size_t match_idx = find_matching_ctrl(_tokens, __idx, "(");

    // If matching paren not found, throw error.
    if (match_idx == 0) {
        throw_error(ERR_UNCLOSED_PAREN, "", _tokens[__idx]->_colnum, _tokens[__idx]->_linenum);
    }

    // If matching paren is past the end idx, throw error.
    if (match_idx > __end_idx) {
        throw_error(ERR_TERM_BEFORE_CLOSURE, "", _tokens[__idx]->_colnum, _tokens[__idx]->_linenum);
    }

    // Parse the function arguments.
    func_args = parse_func_args(__idx, match_idx, __scope);

    // Create a temporary to hold the return object of the function.
    std::pair<std::shared_ptr<RoskyInterface>*, std::shared_ptr<RoskyInterface>> ret_obj = {nullptr, nullptr};

    // Check if the function is a native function.
    if (_func_table->is_function(func_name)) {

        // Call the native function
        ret_obj = _func_table->call_function(func_name, func_args, func_col, func_lin);

    }

    // Check if the function is user-defined.
    if (_func_table->is_user_function(func_name)) {

        // Get the user function entry.
        std::shared_ptr<UserFunction_T> user_func_entry = _func_table->get_user_function(func_name);

        if (user_func_entry != nullptr) {

            // Ensure the parameter counts match.
            if (func_args.size() != user_func_entry->_func_params.size()) {
                throw_error(ERR_BAD_FUNC_ARGS, "'" + func_name + "' expects " +
                            std::to_string(user_func_entry->_func_params.size()) +
                            " arguments, received " + std::to_string(func_args.size()),
                            func_col, func_lin);
            }

            // Assign the function parameters at a +1 scope and +1 recursive
            // index.
            for (size_t param_idx = 0; param_idx < func_args.size(); param_idx++) {

                _var_table->set_entry(user_func_entry->_func_params[param_idx],
                                      func_args[param_idx],
                                      __scope + 1, _recursive_index + 1);

            }

            // Bookmark the in function flag.
            bool func_flag = _func_flag;

            // Assert the function flag.
            _func_flag = true;

            // Bookmark the recursive index.
            size_t recursive_index = _recursive_index;

            // Increment the recursive index.
            _recursive_index++;

            // Check if the maximum recursion depth has been exceeded.
            if (_recursive_index > 999) {
                throw_error(ERR_MAX_RECURSION_DEPTH, "", func_col, func_lin);
            }

            // Parse the function body.
            parse(user_func_entry->_start_idx, user_func_entry->_end_idx, __scope + 1);

            // If the return object has been set, set the return object to that.
            // Otherwise, set the return object to a null object.
            if (_parser_ret_obj != nullptr) {

                ret_obj = {nullptr, _parser_ret_obj};

            } else {

                ret_obj = {nullptr, std::make_shared<RoskyNull>()};

            }

            // Reset the _parser_ret_obj.
            _parser_ret_obj = nullptr;

            // Reset the function flag.
            _func_flag = func_flag;

            // Reset the return flag.
            _return_flag = false;

            // Reset the recursive index.
            _recursive_index = recursive_index;

            // Release above scope.
            _var_table->release_above_scope(__scope + 1);

        }

    }

    // If ret_obj is null, throw an error.
    if (ret_obj.first == nullptr && ret_obj.second == nullptr) {
        throw_error(ERR_UNREC_FUNC, "'" + func_name + "'", func_col, func_lin);
    }

    return ret_obj;

}

/******************************************************************************/

std::pair<std::shared_ptr<RoskyInterface>*, std::shared_ptr<RoskyInterface>>
        Parser_T::parse_member_func(std::pair<std::shared_ptr<RoskyInterface>*, std::shared_ptr<RoskyInterface>> __obj,
                          size_t& __idx, size_t __end_idx, size_t __scope) {

    // Create a vector to hold the function argument objects.
    std::vector<std::shared_ptr<RoskyInterface>> func_args;

    // Bookmark the token metadata for the function call.
    size_t func_col = _tokens[__idx]->_colnum;
    size_t func_lin = _tokens[__idx]->_linenum;

    // This holds the function name.
    std::string func_name = _tokens[__idx++]->_token;

    // The next token must be a left paren.
    if (_tokens[__idx]->_token != "(") {
        throw_error(ERR_NO_FUNC_ARGS, "'" + _tokens[__idx-1]->_token + "'",
                    _tokens[__idx-1]->_colnum, _tokens[__idx-1]->_linenum);
    }

    // Find the matching parentheses.
    size_t match_idx = find_matching_ctrl(_tokens, __idx, "(");

    // If matching paren not found, throw error.
    if (match_idx == 0) {
        throw_error(ERR_UNCLOSED_PAREN, "", _tokens[__idx]->_colnum, _tokens[__idx]->_linenum);
    }

    // If matching paren is past the end idx, throw error.
    if (match_idx > __end_idx) {
        throw_error(ERR_TERM_BEFORE_CLOSURE, "", _tokens[__idx]->_colnum, _tokens[__idx]->_linenum);
    }

    // Parse the function arguments.
    func_args = parse_func_args(__idx, match_idx, __scope);

     // Call the function with the args and return the value.
     auto ret_obj = _func_table->call_member_function(func_name, __obj, func_args, func_col, func_lin);

     // If ret_obj is null, throw an error.
     if (ret_obj.first == nullptr && ret_obj.second == nullptr) {
         throw_error(ERR_UNREC_FUNC, "'" + func_name + "'", func_col, func_lin);
     }

     return ret_obj;

}

/******************************************************************************/
