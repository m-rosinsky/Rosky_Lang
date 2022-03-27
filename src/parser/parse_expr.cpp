
/******************************************************************************/
//
//  Source Name:                parse_expr.cpp
//
//  Description:                This file is responsible for parsing
//                              expressions. It will form a parse tree
//                              from a token table and a given start
//                              iterator.
// 
//                              Upon failure, an error will be thrown.
// 
//                              Upon success, it will call the evaluator
//                              to evaluate the parse tree.
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
//  Exported Subprograms:       parse_expr
//                              
/******************************************************************************/

#include "../../includes/parser.hpp"

/******************************************************************************/

std::shared_ptr<RoskyInterface> Parser_T::parse_expr(size_t& __idx, size_t __end_idx, size_t __scope) {

    // This flag determines if we are expecting an operator or not.
    bool expecting_op = false;

    // This holds the root node of the final parse tree.
    std::shared_ptr<ParseNode> root = nullptr;

    // Capture the first token's linenum and colnum for potential error reporting.
    size_t err_linenum = _tokens[__idx]->_linenum;
    size_t err_colnum = _tokens[__idx]->_colnum;

    // Iterate through the token table.
    for (; __idx < __end_idx; __idx++) {

        // Literal token type or symbol.
        if (is_literal(_tokens[__idx]->_type) ||
            _tokens[__idx]->_type == TOKEN_SYMBOL) {

            // If we are expecting an op, throw an error (exits program).
            if (expecting_op) {
                throw_error(ERR_SYNTAX, _tokens[__idx]->_token, _tokens[__idx]->_colnum, _tokens[__idx]->_linenum);
            }

            // Form the object.
            std::shared_ptr<RoskyInterface> obj = form_object(_tokens[__idx], _var_table, __scope);

            // Continue down the right side of the tree until right child is null,
            // then insert self as right child.
            insert_right(root, obj, _tokens[__idx]->_token, _tokens[__idx]->_colnum, _tokens[__idx]->_linenum);

            // Now expecting an operator.
            expecting_op = true;
            continue;

        }

        // Parentheses.
        if (_tokens[__idx]->_type == TOKEN_CTRL) {

            // Left paren and not expecting op.
            if (_tokens[__idx]->_token == "(" && !expecting_op) {
                // Find matching paren.
                size_t match_idx = find_matching_ctrl(_tokens, __idx, "(");

                // If no matching paren, throw an error.
                if (match_idx == 0) {
                    throw_error(ERR_UNCLOSED_PAREN, "", _tokens[__idx]->_colnum, _tokens[__idx]->_linenum);
                }

                // If the matching paren is the next token, throw an error.
                if (__idx + 1 == match_idx) {
                    throw_error(ERR_EMPTY_PARENS, "", _tokens[__idx]->_colnum, _tokens[__idx]->_linenum);
                }

                // If the matching paren is at a higher index than our stop
                // point, throw an error.
                if (match_idx > __end_idx) {
                    throw_error(ERR_UNCLOSED_PAREN, "", _tokens[__idx]->_colnum, _tokens[__idx]->_linenum);
                }

                // Recursively call the parse_expr function with the new bounds.
                std::shared_ptr<RoskyInterface> obj = parse_expr(++__idx, match_idx, __scope);

                // Insert the result to the right.
                // The token metadata doesn't matter because errors pertaining
                // to evaluation of this object would have been caught already.
                insert_right(root, obj, "", 0, 0);

                // Now expecting an operator.
                expecting_op = true;
                continue;

            }

        }

        // Operator token type.
        if (_tokens[__idx]->_type == TOKEN_OP_BIN) {

            // If not expecting an op, throw an error (exits program).
            if (!expecting_op) {
                throw_error(ERR_SYNTAX, _tokens[__idx]->_token, _tokens[__idx]->_colnum, _tokens[__idx]->_linenum);
            }

            // Insert the operator.
            insert_op(root, _tokens[__idx]->_token, _tokens[__idx]->_colnum, _tokens[__idx]->_linenum);

            // Now not expecting an operator.
            expecting_op = false;
            continue;

        }

        // Anything else should be considered unexpected.
        throw_error(ERR_SYNTAX, _tokens[__idx]->_token, _tokens[__idx]->_colnum, _tokens[__idx]->_linenum);

    }

    // If we are not expecting an operation, throw.
    if (!expecting_op) {
        throw_error(ERR_SYNTAX, _tokens[__end_idx]->_token, _tokens[__end_idx]->_colnum, _tokens[__end_idx]->_linenum);
    }

    // print_inorder(root);

    // Send parse tree to evaluator.
    return evaluate(root, _var_table, true, __scope);

}

/******************************************************************************/
