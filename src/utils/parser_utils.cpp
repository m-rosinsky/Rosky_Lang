
/******************************************************************************/
//
//  Source Name:                parser_utils.cpp
//
//  Description:                This file contains a number of type
//                              definitions and helper functions for
//                              the parser to leverage.
//
//  Dependencies:               lexer_utils.hpp
//                              variable_handler.hpp
//                              rosky_interface.hpp
//                              rosky_int.hpp
//
//  Classes:                    ParseNode
//
//  Inherited Subprograms:      None
//
//  Exported Subprograms:       get_precedence
//                              insert_right
//                              insert_op
//                              is_expr_op
//                              is_literal
//                              is_assignment_op
//                              is_right_assoc
//                              is_left_assoc
//                              find_nextof
//                              find_matching_ctrl
//                              form_object
//                              
/******************************************************************************/

#include "../../includes/utils/parser_utils.hpp"

/******************************************************************************/

void insert_right(std::shared_ptr<ParseNode>& __root,
                  const std::shared_ptr<RoskyInterface>& __obj,
                  const std::string& __sym_string,
                  size_t __col, size_t __lin) {

    // Create the new node.
    std::shared_ptr<ParseNode> new_node = std::make_shared<ParseNode>(__obj, __sym_string, PARSE_OPERAND, __col, __lin);

    // If the root node is null, replace it with the new node.
    if (__root == nullptr) {
        __root = new_node;
        return;
    }

    // Create a pointer to move down the tree.
    std::shared_ptr<ParseNode> cur = __root;

    // Continue moving right.
    while (cur->_right != nullptr) {
        cur = cur->_right;
    }

    // Insert the new node as the right child of cur.
    cur->_right = new_node;

    // Set the new node's parent to cur.
    new_node->_parent = cur;

}

/******************************************************************************/

void insert_op(std::shared_ptr<ParseNode>& __root,
               const std::string& __op,
               size_t __col, size_t __lin) {

    // Create the new node.
    std::shared_ptr<ParseNode> new_node = std::make_shared<ParseNode>(nullptr, __op, PARSE_OPERATOR, __col, __lin);

    // Create a pointer to navigate the tree.
    std::shared_ptr<ParseNode> cur = __root;

    // while the current node is an operator.
    while (cur->_type == PARSE_OPERATOR) {

        // If the current node's operator precedence is less than the
        // new operators precedence, move right.
        // Or if the operator's precedence is equal and the operator
        // is right-left associative.
        if ((get_precedence(cur->_op) < get_precedence(__op)) ||
            (get_precedence(cur->_op) == get_precedence(__op) &&
             is_right_assoc(__op))) {
            cur = cur->_right;
            continue;
        }

        // If the current node's precedence is greater than or equal to
        // the new operator's precedence, make the current node the left
        // child of the new node and assign the root if needed.

        // If the node we are shifting down is the root, ensure
        // we reassign the root.
        if (__root.get() == cur.get()) {
            __root = new_node;
        }

        // Set the current node as the left child of the new node.
        new_node->_parent = cur->_parent;
        cur->_parent = new_node;
        new_node->_left = cur;

        // If the parent is not null, set it's right child as the new node.
        if (new_node->_parent.lock() != nullptr) {
            new_node->_parent.lock()->_right = new_node;
        }

        // Work's done.
        return;

    }

    // The node must be a symbol or integer, so make the new node
    // the current node's parent, and make the current node the left
    // child of the new node.

    // If the current node is the root, ensure we reassign the root.
    if (__root.get() == cur.get()) {
        __root = new_node;
    }

    // Set the current node as the left child of the new node.
    new_node->_parent = cur->_parent;
    cur->_parent = new_node;
    new_node->_left = cur;

    // If the parent is not null, set its right child as the new node.
    if (new_node->_parent.lock() != nullptr) {
        new_node->_parent.lock()->_right = new_node;
    }

}

/******************************************************************************/

void print_inorder(const std::shared_ptr<ParseNode>& __root) {

    if (__root == nullptr) { return; }

    print_inorder(__root->_left);

    if (__root->_type == PARSE_OPERAND) {
        std::cout << __root->_obj->to_string() << std::endl;
    } else {
        std::cout << __root->_op << std::endl;
    }

    print_inorder(__root->_right);

}

/******************************************************************************/

size_t find_nextof(const std::deque<std::shared_ptr<Token_T>>& __tokens,
                    size_t __start_idx, const std::string& __token) {

    // Iterate through the token table.
    for (size_t idx = __start_idx; idx < __tokens.size(); idx++) {

        // If the token matches, return the index.
        if (__tokens[idx]->_token == __token) {
            return idx;
        }

    }

    // Not found, return 0
    return 0;

}

/******************************************************************************/

size_t find_matching_ctrl(const std::deque<std::shared_ptr<Token_T>>& __tokens,
                            size_t __start_idx, const std::string& __token) {

    // This holds the number of open tokens.
    size_t open_count = 0;

    // Mark the close token based on the provided token.
    std::string close_token;
    close_token = __token == "(" ? ")" : __token == "[" ? "]" : "}";

    // Iterate through the table.
    for (size_t idx = __start_idx; idx < __tokens.size(); idx++) {

        // If open structure, increment the count.
        if (__tokens[idx]->_token == __token) {
            open_count++;
            continue;
        }

        // If close structure, check if found match, otherwise,
        // decrement the count.
        if (__tokens[idx]->_token == close_token) {
            open_count--;
            if (open_count == 0) {
                return idx;
            }
            continue;
        }

    }

    // No match found, return 0.
    return 0;

}

/******************************************************************************/

std::shared_ptr<RoskyInterface> form_object(const std::shared_ptr<Token_T>& __token,
                                            const VariableTable_T& __var_table) {

    // Literals
    if (__token->_type == TOKEN_LIT_INT) {
        return std::make_shared<RoskyInt>(std::stoi(__token->_token));
    }

    // Symbols
    if (__token->_type == TOKEN_SYMBOL) {
        return __var_table.get_entry(__token->_token);
    }

    return nullptr;

}

/******************************************************************************/