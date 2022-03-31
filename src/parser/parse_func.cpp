
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
//                              
/******************************************************************************/

#include "../../includes/parser.hpp"

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

    // Special case where the matching paren is the next token, send the
    // empty arg list.
    if (__idx + 1 == match_idx) {

         // Call the function with the empty args and return the value.
        return _func_table->call_function(func_name, func_args, func_col, func_lin);

    }

    // If matching paren not found, throw error.
    if (match_idx == 0) {
        throw_error(ERR_UNCLOSED_PAREN, "", _tokens[__idx]->_colnum, _tokens[__idx]->_linenum);
    }

    // If matching paren is past the end idx, throw error.
    if (match_idx > __end_idx) {
        throw_error(ERR_TERM_BEFORE_CLOSURE, "", _tokens[__idx]->_colnum, _tokens[__idx]->_linenum);
    }

    // Collect function arguments until no more commas.
    size_t comma_idx = find_nextof(_tokens, ++__idx, ",");
    
    // While the comma comes before the closing paren.
    while (comma_idx != 0 && comma_idx < match_idx) {

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

    // If the next index is the closing parentheses, empty arg.
    if (__idx == match_idx) {
        throw_error(ERR_EMPTY_ARG, "", _tokens[__idx]->_colnum, _tokens[__idx]->_linenum);
    }

    // Parse the expression between this index and the match idx.
    auto obj_pair = parse_expr(__idx, match_idx, __scope);

    // Add the object to the argument table.
    func_args.push_back(obj_pair.second);

    // Call the function with the args and return the value.
    return _func_table->call_function(func_name, func_args, func_col, func_lin);

}

/******************************************************************************/
