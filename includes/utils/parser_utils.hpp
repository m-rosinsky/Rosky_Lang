
/******************************************************************************/
//
//  Source Name:                parser_utils.hpp
//
//  Description:                This file contains a number of type
//                              definitions and helper functions for
//                              the parser to leverage.
//
//  Dependencies:               lexer_utils.hpp
//
//  Classes:                    ParseNode
//
//  Inherited Subprograms:      None
//
//  Exported Subprograms:       get_precedence
//                              insert_right
//                              is_expr_op
//                              
/******************************************************************************/

#ifndef PARSER_UTILS
#define PARSER_UTILS

/******************************************************************************/

#include <string>                       // std::string
#include <memory>                       // std::shared_ptr, std::weak_ptr
#include <iostream>

#include "lexer_utils.hpp"

/******************************************************************************/

// This function allows us to get operator precedence.
inline size_t get_precedence(const std::string& op) {
    if (op == "=") { return 1; }
    if (op == "+") { return 2; }
    if (op == "*") { return 3; }
    return 0;
}

/******************************************************************************/

// This struct defines the parse tree node structure. The pointer
// to the parent node must be a weak_ptr to avoid cyclic referencing
// which would not allow memory to be freed from the shared_ptr's
// when the stack is unwound.
struct ParseNode {

    std::shared_ptr<Token_T> _value;

    std::shared_ptr<ParseNode> _left;
    std::shared_ptr<ParseNode> _right;
    std::weak_ptr<ParseNode> _parent;

    // Ctor.
    ParseNode(const std::shared_ptr<Token_T>& __token)
        : _value(__token) {}

};

/******************************************************************************/

// This function is a tree helper function that inserts a child node
// as far right down the tree as possible.
void insert_right(std::shared_ptr<ParseNode>& __root,
                  const std::shared_ptr<Token_T>& __token);

// This function is a tree helper function for inserting operators
// into the tree.
void insert_op(std::shared_ptr<ParseNode>& __root,
               const std::shared_ptr<Token_T>& __token);

// This is a debug function for displaying the parse tree.
void print_inorder(const std::shared_ptr<ParseNode>& __root);

/******************************************************************************/

// This function determines if an operator is valid in starting
// an expression. (i.e. *p = 2;)
inline bool is_expr_op(const std::string& op) noexcept {
    return op == "*";
}

// This function determines if a token type is a literal
inline bool is_literal(TOKEN_TYPE __type) noexcept {
    return (__type == TOKEN_LIT_INT) ||
           (__type == TOKEN_LIT_FLOAT) ||
           (__type == TOKEN_LIT_STRING);
}

inline bool is_assignment_op(const std::string& op) noexcept {
    return op == "=";
}

/******************************************************************************/

#endif // PARSER_UTILS
