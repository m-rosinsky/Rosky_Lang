
/******************************************************************************/
//
//  Source Name:                parse_if.cpp
//
//  Description:                This file is responsible for parsing
//                              if statements. Nothing is returned
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
//  Exported Subprograms:       parse_if
//                              
/******************************************************************************/

#include "../../includes/parser.hpp"

#include <iostream>

/******************************************************************************/

void Parser_T::parse_if(size_t& __idx, size_t __end_idx, size_t __scope) {

    // This holds the indices for the conditions.
    std::vector<std::pair<size_t, size_t>> conds;

    // This holds the indices for the bodies.
    std::vector<std::pair<size_t, size_t>> bods;

    // Loop.
    while (true) {

        __idx++;

        // Mark the start index of the condition.
        size_t cond_start_idx = __idx;

        // Mark the end index of the condition.
        size_t cond_end_idx = find_nextof(_tokens, __idx, "{");

        // If the token was not found, throw error.
        if (cond_end_idx == 0 || cond_end_idx > __end_idx) {
            throw_error(ERR_MISSING_BODY, "", _tokens[cond_start_idx-1]->_colnum, _tokens[cond_start_idx-1]->_linenum);
        }

        // If the token is the current index, throw error.
        if (cond_start_idx == cond_end_idx) {
            throw_error(ERR_MISSING_COND, "", _tokens[__idx]->_colnum, _tokens[__idx]->_linenum); 
        }

        // Find the closing bracket.
        __idx = cond_end_idx;
        size_t body_end_idx = find_matching_ctrl(_tokens, __idx, "{");

        // If not found, throw error.
        if (body_end_idx == 0 || body_end_idx > __end_idx) {
            throw_error(ERR_UNCLOSED_BRACE, "", _tokens[cond_end_idx]->_colnum, _tokens[cond_end_idx]->_linenum);
        }

        // Add the condition indices and body indices to the vector.
        conds.push_back({cond_start_idx, cond_end_idx});
        bods.push_back({cond_end_idx, body_end_idx});

        // If the next token is "elsif", loop.
        if (body_end_idx + 1 < __end_idx) {

            if (_tokens[body_end_idx+1]->_token == "elsif") {
                __idx = body_end_idx + 1;
                continue;
            }

        }

        // If the next token is "else", add body and break.
        if (body_end_idx + 1 < __end_idx) {

            if (_tokens[body_end_idx+1]->_token == "else") {

                __idx = body_end_idx + 1;

                // Find the next "{"
                size_t else_start_idx = find_nextof(_tokens, __idx, "{");

                // If not found, throw error.
                if (else_start_idx == 0 || else_start_idx > __end_idx) {
                    throw_error(ERR_MISSING_BODY, "", _tokens[body_end_idx+1]->_colnum, _tokens[body_end_idx+1]->_linenum);
                }

                // If not the next token throw error.
                if (body_end_idx + 2 != else_start_idx) {
                    throw_error(ERR_SYNTAX, _tokens[body_end_idx+2]->_token, _tokens[body_end_idx+2]->_colnum, _tokens[body_end_idx+1]->_linenum);
                }

                // Find the closing bracket.
                __idx = else_start_idx;
                size_t else_end_idx = find_matching_ctrl(_tokens, __idx, "{");

                // If not found, throw error.
                if (else_end_idx == 0 || else_end_idx > __end_idx) {
                    throw_error(ERR_UNCLOSED_BRACE, "", _tokens[else_start_idx]->_colnum, _tokens[else_start_idx]->_linenum);
                }

                // Append the body to the vector.
                bods.push_back({else_start_idx, else_end_idx});

                // Break.
                break;

            }

        }

        // Neither "elseif", nor "else", break.
        break;

    }

    // Iterate through the vector of conditions, and execute the body
    // of the true statement. If none of the statements are true and there
    // is an extra statement in the body, this signifies the else, so execute it.
    auto cond_it = conds.begin();
    auto bod_it = bods.begin();

    while (cond_it != conds.end()) {

        // Set the index to the start of the condition.
        __idx = cond_it->first;

        // Evaluate the condition.
        auto obj_pair = parse_expr(__idx, cond_it->second, __scope);

        // If the condition is not a boolean, throw error.
        if (obj_pair.second->get_type_id() != OBJ_BOOL) {
            throw_error(ERR_BAD_COND_TYPE, "received '" + obj_pair.second->get_type_string() + "'",
                        _tokens[cond_it->second]->_colnum, _tokens[cond_it->second]->_linenum);
        }

        // If the condition is true, evaluate the respective body and break this loop.
        if (obj_pair.second->to_bool() == true) {

            __idx = bod_it->first;

            parse(__idx, bod_it->second, __scope);

            break;

        }

        // Increment the iterators.
        cond_it++;
        bod_it++;
        
        // If the condition iterator is at its end, but the bod_it is not,
        // execute the else block.
        if (cond_it == conds.end() && bod_it != bods.end()) {

            __idx = bod_it->first;

            parse(__idx, bod_it->second, __scope);

            break;

        }

    }

    // Set the index.
    __idx = bods.back().second;

    // Release above scope.
    _var_table->release_above_scope(__scope);

}

/******************************************************************************/
