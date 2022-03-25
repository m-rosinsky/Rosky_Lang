
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
//                              rosky_interface.hpp
//
//  Classes:                    None
//
//  Inherited Subprograms:      None
//
//  Exported Subprograms:       parse_expr
//                              
/******************************************************************************/

#include "../../includes/parser.hpp"

/******************************************************************************/

std::shared_ptr<RoskyInterface> parse_expr(const std::deque<std::shared_ptr<Token_T>>& __tokens,
                                           size_t& __idx) {

    // This flag determines if we are expecting an operator or not.
    bool expecting_op = false;

    // This flag determines if we have reached an expression terminator.
    bool has_terminator = false;

    // This holds the root node of the final parse tree.
    std::shared_ptr<ParseNode> root = nullptr;

    // Capture the first token's linenum and colnum for potential error reporting.
    size_t err_linenum = __tokens[__idx]->_linenum;
    size_t err_colnum = __tokens[__idx]->_colnum;

    // Iterate through the token table.
    for (; __idx < __tokens.size(); __idx++) {

        // Literal token type or symbol.
        if (is_literal(__tokens[__idx]->_type) ||
            __tokens[__idx]->_type == TOKEN_SYMBOL) {

            // If we are expecting an op, throw an error (exits program).
            if (expecting_op) {
                throw_error(ERR_SYNTAX, __tokens[__idx]->_token, __tokens[__idx]->_colnum, __tokens[__idx]->_linenum);
            }

            // Continue down the right side of the tree until right child is null,
            // then insert self as right child.
            insert_right(root, __tokens[__idx]);

            // Now expecting an operator.
            expecting_op = true;
            continue;

        }

        // Operator token type.
        if (__tokens[__idx]->_type == TOKEN_OP_DLR) {

            // If not expecting an op, throw an error (exits program).
            if (!expecting_op) {
                throw_error(ERR_SYNTAX, __tokens[__idx]->_token, __tokens[__idx]->_colnum, __tokens[__idx]->_linenum);
            }

            // Insert the operator.
            insert_op(root, __tokens[__idx]);

            // Now not expecting an operator.
            expecting_op = false;
            continue;

        }

        // Operator is a delimiter.
        if (__tokens[__idx]->_type == TOKEN_DELIM) {

            // If not expecting an op, throw an error (exits program).
            if (!expecting_op) {
                throw_error(ERR_SYNTAX, __tokens[__idx]->_token, __tokens[__idx]->_colnum, __tokens[__idx]->_linenum);
            }

            // A semicolon marks the end of parsing, and the tree
            // will be handed off to the evaluator.
            if (__tokens[__idx]->_token == ";") {

                // Set the flag.
                has_terminator = true;

                // Break out of the loop.
                break;

            }

        }

        // Anything else should be considered unexpected.
        throw_error(ERR_SYNTAX, __tokens[__idx]->_token, __tokens[__idx]->_colnum, __tokens[__idx]->_linenum);

    }

    // If we did not receive a terminator, throw an error.
    if (!has_terminator) {
        throw_error(ERR_UNEXP_EOF, "", err_colnum, err_linenum);
    }

    // print_inorder(root);

    // Send parse tree to evaluator.
    return evaluate(root);

}

/******************************************************************************/
