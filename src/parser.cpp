
/******************************************************************************/
//
//  Source Name:                parser.cpp
//
//  Description:                This file is responsible for parsing a
//                              token table that is generated by the
//                              lexer. Parsing decisions are made
//                              in the main 'parse' function and subsequent
//                              parsing is handled in specific parse functions
//                              pertaining to the tokens needing to be parsed.
// 
//                              The parser will catch logical as well as
//                              syntactical errors.
//
//  Dependencies:               lexer_utils.hpp
//                              parser_utils.hpp
//                              error_handler.hpp
//                              evaluator.hpp
//                              variable_handler.hpp
//                              rosky_interface.hpp
//
//  Classes:                    Parser_T
//
//  Inherited Subprograms:      None
//
//  Exported Subprograms:       parse
//                              parse_expr
//                              
/******************************************************************************/

#include "../includes/parser.hpp"

/******************************************************************************/

void Parser_T::parse(size_t __start_idx, size_t __end_idx, size_t __scope) {

    // Create an index iterator. The reason this is
    // chosen over a traditional std::iterator is
    // because it may potentially go past the .end() point
    // and memory leak. The index can be checked against the max
    // size.
    size_t idx = __start_idx;

    // Check if the default was provided for the end index.
    __end_idx = __end_idx == 0 ? _tokens.size() : __end_idx;

    // Iterate through the token table.
    for (; idx < __end_idx; idx++) {

        // token is a literal.
        if (is_literal(_tokens[idx]->_type)) {

            // Parse as expression.
            size_t end_idx = find_nextof(_tokens, idx, ";");
            if (end_idx == 0 || end_idx > __end_idx) {
                throw_error(ERR_UNEXP_EOF, "", _tokens[__end_idx]->_colnum, _tokens[__end_idx]->_linenum);
            }
            auto ignore = parse_expr(idx, end_idx, __scope);
            continue;

        }

        // Token is a keyword.
        if (_tokens[idx]->_type == TOKEN_KW) {

            // Check keyword and parse accordingly.
            if (_tokens[idx]->_token == "if") {
                parse_if(idx, __end_idx, __scope + 1);
                continue;
            }
            if (_tokens[idx]->_token == "while") {
                parse_while(idx, __end_idx, __scope+1);
                continue;
            }

            // Keyword will be parsed as expression.
            size_t end_idx = find_nextof(_tokens, idx, ";");
            if (end_idx == 0 || end_idx > __end_idx) {
                throw_error(ERR_UNEXP_EOF, "", _tokens[__end_idx]->_colnum, _tokens[__end_idx]->_linenum);
            }
            auto ignore = parse_expr(idx, end_idx, __scope);
            continue;

        }

        // Token is a symbol.
        if (_tokens[idx]->_type == TOKEN_SYMBOL) {

            // Token must be an expression.
            size_t end_idx = find_nextof(_tokens, idx, ";");
            if (end_idx == 0 || end_idx > __end_idx) {
                throw_error(ERR_UNEXP_EOF, "", _tokens[__end_idx]->_colnum, _tokens[__end_idx]->_linenum);
            }
            auto ignore = parse_expr(idx, end_idx, __scope);
            continue;

        }

        // Token is an operator.
        if (_tokens[idx]->_type == TOKEN_OP) {

            // Only select prefix ops can be considered starters
            // of an expression, otherwise this check fails.
            if (is_expr_op(_tokens[idx]->_token)) {
                size_t end_idx = find_nextof(_tokens, idx, ";");
                if (end_idx == 0 || end_idx > __end_idx) {
                    throw_error(ERR_UNEXP_EOF, "", _tokens[__end_idx]->_colnum, _tokens[__end_idx]->_linenum);
                }
                auto ignore = parse_expr(idx, end_idx, __scope);
                continue;
            }

        }

        // Token is a control structure.
        if (_tokens[idx]->_type == TOKEN_CTRL) {

            // If left paren, parse as expression.
            if (_tokens[idx]->_token == "(") {
                size_t end_idx = find_nextof(_tokens, idx, ";");
                if (end_idx == 0 || end_idx > __end_idx) {
                    throw_error(ERR_UNEXP_EOF, "", _tokens[__end_idx]->_colnum, _tokens[__end_idx]->_linenum);
                }
                auto ignore = parse_expr(idx, end_idx, __scope);
                continue;
            }

            // Left curly brace.
            if (_tokens[idx]->_token == "{") {

                // Find the matching brace.
                size_t match_idx = find_matching_ctrl(_tokens, idx, "{");

                // If the match is not found, throw an error.
                if (match_idx == 0) {
                    throw_error(ERR_UNCLOSED_BRACE, "", _tokens[idx]->_colnum, _tokens[idx]->_linenum);
                }

                // Increment the scope.
                __scope++;
                continue;

            }

            // Right curly brace.
            if (_tokens[idx]->_token == "}") {
                
                // If the scope is already zero, throw an error.
                if (__scope == 0) {
                    throw_error(ERR_SYNTAX, "}", _tokens[idx]->_colnum, _tokens[idx]->_linenum);
                }

                // Release variables off the table above scope.
                _var_table->release_above_scope(__scope);

                // Decrement the scope.
                __scope--;
                continue;
            }

        }

        // Anything reaching here is considered a syntax error.
        throw_error(ERR_SYNTAX, _tokens[idx]->_token, _tokens[idx]->_colnum, _tokens[idx]->_linenum);

    }

}

/******************************************************************************/
