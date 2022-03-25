
/******************************************************************************/
//
//  Source Name:                parser_utils.cpp
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
//                              is_literal
//                              is_assignment_op
//                              
/******************************************************************************/

#include "../../includes/utils/parser_utils.hpp"

/******************************************************************************/

void insert_right(std::shared_ptr<ParseNode>& __root,
                  const std::shared_ptr<Token_T>& __token) {

    // Create the new node.
    std::shared_ptr<ParseNode> new_node = std::make_shared<ParseNode>(__token);

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
               const std::shared_ptr<Token_T>& __token) {

    // Create the new node.
    std::shared_ptr<ParseNode> new_node = std::make_shared<ParseNode>(__token);

    // Create a pointer to navigate the tree.
    std::shared_ptr<ParseNode> cur = __root;

    // while the current node is an operator.
    while (cur->_value->_type == TOKEN_OP_DLR) {

        // If the current node's operator precedence is less than the
        // new operators precedence, move right.
        // Or if the operator's precedence is equal and the operator
        // is right-left associative.
        if ((get_precedence(cur->_value->_token) < get_precedence(__token->_token)) ||
            (get_precedence(cur->_value->_token) == get_precedence(__token->_token) &&
             is_right_assoc(__token->_token))) {
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

    std::cout << __root->_value->_token << std::endl;

    print_inorder(__root->_right);

}

/******************************************************************************/


