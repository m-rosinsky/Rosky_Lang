
/******************************************************************************/
//
//  Source Name:                parse_while.cpp
//
//  Description:                This file is responsible for parsing
//                              while statements. Nothing is returned
//                              from this function.
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
//  Exported Subprograms:       parse_while
//                              
/******************************************************************************/

#include "../../includes/parser.hpp"

/******************************************************************************/

void Parser_T::parse_while(size_t& __idx, size_t __end_idx, size_t __scope) {

    // Bookmark the index starting the condition.
    size_t cond_start_index = __idx + 1;

    // Find the next "{" token.
    size_t open_index = find_nextof(_tokens, __idx, "{");

    // If not found, throw error.
    if (open_index == 0 || open_index > __end_idx) {
        throw_error(ERR_MISSING_BODY, "", _tokens[__idx]->_colnum, _tokens[__idx]->_linenum);
    }

    // If next token, throw error.
    if (__idx + 1 == open_index) {
        throw_error(ERR_MISSING_COND, "", _tokens[__idx+1]->_colnum, _tokens[__idx]->_linenum);
    }

    // Find the closing bracket.
    size_t close_index = find_matching_ctrl(_tokens, open_index, "{");

    // If not found, throw error.
    if (close_index == 0 || close_index > __end_idx) {
        throw_error(ERR_UNCLOSED_BRACE, "", _tokens[__idx]->_colnum, _tokens[__idx]->_linenum);
    }

    // Loop
    while (true) {

        // Set the index to the start of the condition.
        __idx = cond_start_index;

        // evaluate the condition.
        auto cond_obj_pair = parse_expr(__idx, open_index, __scope);

        // The condition must be a boolean statement, otherwise throw error.
        if (cond_obj_pair.second->get_type_id() != OBJ_BOOL) {

            throw_error(ERR_BAD_COND_TYPE, "received '" + cond_obj_pair.second->get_type_string() + "'", _tokens[__idx-1]->_colnum, _tokens[__idx-1]->_linenum);

        }

        // If the condition is false, break this loop.
        if (cond_obj_pair.second->to_bool() == false) {
            break;
        }

        // Set the index to the opening brace.
        __idx = open_index;

        // Parse the body.
        parse(__idx, close_index, __scope);

    }

    // Release above the current scope.
    _var_table->release_above_scope(__scope);

    // Set the index to close index and return.
    __idx = close_index;
    return;

}

/******************************************************************************/