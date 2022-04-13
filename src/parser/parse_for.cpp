
/******************************************************************************/
//
//  Source Name:                parse_for.cpp
//
//  Description:                This file is responsible for parsing
//                              for loops. Nothing is returned
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
//  Exported Subprograms:       parse_for
//                              
/******************************************************************************/

#include "../../includes/parser.hpp"

/******************************************************************************/

void Parser_T::parse_for(size_t& __idx, size_t __end_idx, size_t __scope) {

    // The next token will be the variable name, so it must be a symbol.
    if (__end_idx == __idx + 1) {
        throw_error(ERR_UNEXP_EOF, "for", _tokens[__idx]->_colnum, _tokens[__idx]->_linenum);
    }

    __idx++;

    if (_tokens[__idx]->_type != TOKEN_SYMBOL) {
        throw_error(ERR_SYNTAX, _tokens[__idx]->_token, _tokens[__idx]->_colnum, _tokens[__idx]->_linenum);
    }

    // Bookmark the symbol
    std::string symbol_name = _tokens[__idx]->_token;

    // The next token must be the 'in' keyword.
    if (__end_idx == __idx + 1) {
        throw_error(ERR_UNEXP_EOF, "expected 'in' keyword", _tokens[__idx]->_colnum, _tokens[__idx]->_linenum);
    }

    __idx++;

    if (_tokens[__idx]->_type != TOKEN_KW || _tokens[__idx]->_token != "in") {
        throw_error(ERR_SYNTAX, _tokens[__idx]->_token, _tokens[__idx]->_colnum, _tokens[__idx]->_linenum);
    }

    // Find the next "{" token.
    size_t open_index = find_nextof(_tokens, __idx, "{");

    // If not found, throw error.
    if (open_index == 0 || open_index > __end_idx) {
        throw_error(ERR_MISSING_BODY, "", _tokens[__idx]->_colnum, _tokens[__idx]->_linenum);
    }

    __idx++;

    // If the open "{" is the next token, throw error.
    if (__idx == open_index) {
        throw_error(ERR_MISSING_COND, "", _tokens[__idx]->_colnum, _tokens[__idx]->_linenum);
    }

    // Evaluate the object between the idx and the open bracket.
    auto iter_obj_pair = parse_expr(__idx, open_index, __scope);

    // The object must be an iterable.
    if (iter_obj_pair.second->is_iterable() == false) {
        throw_error(ERR_NON_ITERABLE, iter_obj_pair.second->to_string(), _tokens[open_index-1]->_colnum, _tokens[open_index-1]->_linenum);
    }

    // Find the closing bracket.
    size_t close_index = find_matching_ctrl(_tokens, open_index, "{");

    // If not found, throw error.
    if (close_index == 0 || close_index > __end_idx) {
        throw_error(ERR_UNCLOSED_BRACE, "", _tokens[open_index]->_colnum, _tokens[open_index]->_linenum);
    }

    // Grab the size of the iterable object.
    size_t iter_sz = iter_obj_pair.second->get_size();

    // Assign a local variable to track the index.
    size_t iter_index = 0;

    // Bookmark the previous state of the loop flag.
    bool loop_flag = _loop_flag;

    // Assert the loop flag.
    _loop_flag = true;

    // Loop.
    while (iter_index < iter_sz) {
    
        // Create the index object.
        auto index_obj = std::make_shared<RoskyInt>((long)iter_index);

        // Assign the symbol.
        _var_table->set_entry(symbol_name,
                              iter_obj_pair.second->index_op(index_obj).second,
                              __scope, _recursive_index);

        // Increment the index.
        iter_index++;

        // Set the index to the opening brace.
        __idx = open_index;

        // Parse the body.
        parse(__idx, close_index, __scope);

        // If the break flag has been asserted, deassert and break.
        if (_break_flag == true) {
            _break_flag = false;
            break;
        }

        // If the continue flag has been asserted, deassert and continue.
        if (_cont_flag == true) {
            _cont_flag = false;
            continue;
        }

    }

    // Reset the loop flag to its previous state.
    _loop_flag = loop_flag;

    // Release above the current scope.
    _var_table->release_above_scope(__scope);

    // Set the index to close index and return.
    __idx = close_index;
    return;

}
