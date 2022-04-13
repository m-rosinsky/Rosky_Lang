
/******************************************************************************/
//
//  Source Name:                parse_func_def.cpp
//
//  Description:                This file is responsible for parsing
//                              user defined function definitions started
//                              with the keyword 'func' and adding the
//                              functions to the function table.
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
//  Exported Subprograms:       parse_func_def
//                              
/******************************************************************************/

#include "../../includes/parser.hpp"

#include <iostream>

/******************************************************************************/

void Parser_T::parse_func_def(size_t& __idx, size_t __end_idx, size_t __scope) {

    // Increment the index.
    if (__idx + 1 >= __end_idx || __idx + 1 >= _tokens.size()) {
        throw_error(ERR_UNEXP_EOF, "", _tokens[__idx]->_colnum, _tokens[__idx]->_linenum);
    }

    __idx++;

    // Bookmark the function name and token column and linenum.
    std::string func_name = _tokens[__idx]->_token;
    size_t func_col = _tokens[__idx]->_colnum;
    size_t func_lin = _tokens[__idx]->_linenum;

    // Check if the function name is a native function or a keyword.
    if (is_reserved(func_name)) {
        throw_error(ERR_RESERVED_USE, func_name, func_col, func_lin);
    }

    // Find the opening parentheses.
    size_t open_index = find_nextof(_tokens, __idx, "(");

    // The opening parentheses must be the next token.
    if (open_index == 0 || open_index != __idx + 1) {
        throw_error(ERR_NO_FUNC_ARGS, "", func_col, func_lin);
    }

    // Set index to opening parentheses.
    __idx = open_index;

    // Find the closing parentheses.
    size_t close_index = find_matching_ctrl(_tokens, __idx, "(");

    // Check if the close index was not found.
    if (close_index == 0 || close_index > __end_idx) {
        throw_error(ERR_UNCLOSED_PAREN, "", _tokens[open_index]->_colnum, _tokens[open_index]->_linenum);
    }

    // Create a vector to hold the parameter symbols.
    std::vector<std::string> func_params;

    // If the close_index is directly after the open_index, skip param collection.
    if (open_index + 1 != close_index) {

        // This flag marks if we have a comma.
        bool has_comma = false;

        // Collect symbols until no more commas.
        size_t comma_idx = find_nextof(_tokens, ++__idx, ",");

        // While the comma comes before the close paren index.
        while (comma_idx != 0 && comma_idx < close_index) {

            // Mark the flag.
            has_comma = true;

            // If the comma index is the next index, throw an error for empty arg.
            if (comma_idx == __idx) {
                throw_error(ERR_EMPTY_ARG, "", _tokens[__idx]->_colnum, _tokens[__idx]->_linenum);
            }

            // If the token is reserved, throw error.
            if (is_reserved(_tokens[__idx]->_token)) {
                throw_error(ERR_RESERVED_USE, _tokens[__idx]->_token, _tokens[__idx]->_colnum, _tokens[__idx]->_linenum);
            }

            // If the current token is not a symbol, throw error.
            if (_tokens[__idx]->_type != TOKEN_SYMBOL) {
                throw_error(ERR_SYNTAX, _tokens[__idx]->_token, _tokens[__idx]->_colnum, _tokens[__idx]->_linenum);
            }

            // The comma must be the next index, otherwise throw syntax.
            if (comma_idx != __idx + 1) {
                throw_error(ERR_SYNTAX, _tokens[__idx+1]->_token, _tokens[__idx+1]->_colnum, _tokens[__idx+1]->_linenum);
            }

            // Push the symbol into the parameter list.
            func_params.push_back(_tokens[__idx]->_token);

            // Increment the index.
            __idx++;

            // Find the next comma.
            comma_idx = find_nextof(_tokens, ++__idx, ",");

        }

        // If has comma and next index is the closing paren, throw empty arg.
        if (has_comma && __idx == close_index) {
            throw_error(ERR_EMPTY_ARG, "", _tokens[__idx]->_colnum, _tokens[__idx]->_linenum);
        }

        // If the token is reserved, throw error.
        if (is_reserved(_tokens[__idx]->_token)) {
            throw_error(ERR_RESERVED_USE, _tokens[__idx]->_token, _tokens[__idx]->_colnum, _tokens[__idx]->_linenum);
        }

        // If the current token is not a symbol, throw error.
        if (_tokens[__idx]->_type != TOKEN_SYMBOL) {
            throw_error(ERR_SYNTAX, _tokens[__idx]->_token, _tokens[__idx]->_colnum, _tokens[__idx]->_linenum);
        }

        // The close index must be next, otherwise throw syntax.
        if (close_index != __idx + 1) {
            throw_error(ERR_SYNTAX, _tokens[__idx+1]->_token, _tokens[__idx+1]->_colnum, _tokens[__idx+1]->_linenum);
        }

        // Push the symbol into the parameter list.
        func_params.push_back(_tokens[__idx]->_token);

    }

    // Put the index on the close index.
    __idx = close_index;

    // Find the open body bracket.
    size_t open_body_index = find_nextof(_tokens, __idx, "{");

    // If not found, throw error.
    if (open_body_index == 0 || open_body_index > __end_idx) {
        throw_error(ERR_MISSING_BODY, "", _tokens[close_index]->_colnum, _tokens[close_index]->_linenum);
    }

    // Find the closing body bracket.
    size_t close_body_index = find_matching_ctrl(_tokens, open_body_index, "{");

    // If not found, throw error.
    if (close_body_index == 0 || close_body_index > __end_idx) {
        throw_error(ERR_UNCLOSED_BRACKET, "", _tokens[open_body_index]->_colnum, _tokens[open_body_index]->_linenum);
    }

    // Push the user function into the table at current scope.
    _func_table->add_user_function(func_name, func_params, __scope, open_body_index, close_body_index);

    // Set the index to the close body index.
    __idx = close_body_index;

}

/******************************************************************************/

void Parser_T::parse_return(size_t& __idx, size_t __end_idx, size_t __scope) {

    // If we are not in a function, throw error.
    if (_func_flag == false) {
        throw_error(ERR_RESERVED_USE, "'return' not in function", _tokens[__idx]->_colnum, _tokens[__idx]->_linenum);
    }

    // Find the next ';'.
    size_t end_token = find_nextof(_tokens, __idx, ";");
    
    // If not found, throw error.
    if (end_token == 0 || end_token > __end_idx) {
        throw_error(ERR_MISSING_TERM, "", _tokens[__end_idx - 1]->_colnum, _tokens[__end_idx - 1]->_linenum);
    }

    // Increment index.
    __idx++;

    // If the end index is the next index, set the return object to a null type.
    if (__idx == end_token) {

        _parser_ret_obj = std::make_shared<RoskyNull>();
        
    } else {

        // Parse the expression.
        auto ret_obj = parse_expr(__idx, end_token, __scope);

        // Set the return object to the ret_obj.
        _parser_ret_obj = ret_obj.second;

    }

    // Assert the return flag.
    _return_flag = true;

}

/******************************************************************************/
