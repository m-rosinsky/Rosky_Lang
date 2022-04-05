
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
                  std::shared_ptr<RoskyInterface>* __obj_adr,
                  const std::shared_ptr<RoskyInterface>& __obj,
                  const std::string& __sym_string,
                  size_t __col, size_t __lin) {

    // Create the new node.
    std::shared_ptr<ParseNode> new_node = std::make_shared<ParseNode>(__obj_adr, __obj, __sym_string, PARSE_OPERAND, __col, __lin);

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
    std::shared_ptr<ParseNode> new_node = std::make_shared<ParseNode>(nullptr, nullptr, __op, PARSE_OPERATOR, __col, __lin);

    // Create a pointer to navigate the tree.
    std::shared_ptr<ParseNode> cur = __root;

    // If the root is empty, insert the operator as root.
    if (cur == nullptr) {
        __root = new_node;
        return;
    }

    // while the current node is an operator.
    while (cur->_type == PARSE_OPERATOR) {

        // If the current node's operator precedence is less than the
        // new operators precedence, move right.
        // Or if the operator's precedence is equal and the operator
        // is right-left associative.
        if ((get_precedence(cur->_op) < get_precedence(__op)) ||
            (get_precedence(cur->_op) == get_precedence(__op) &&
             is_right_assoc(__op))) {

            // If the right child is nullptr (only applies to unary ops),
            // insert the operator to the right and return, otherwise
            // continue.
            if (cur->_right == nullptr) {

                new_node->_parent = cur;
                cur->_right = new_node;
                return;

            }
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

void replace_right(std::shared_ptr<ParseNode>& __root,
                   std::shared_ptr<RoskyInterface>* __obj_adr,
                   const std::shared_ptr<RoskyInterface>& __obj) {

    // Create a pointer to traverse the tree.
    std::shared_ptr<ParseNode> cur = __root;

    // Move while right is not nullptr.
    while (cur->_right != nullptr) {
        cur = cur->_right;
    }

    // Replace cur's contents with the provided objects.
    cur->_obj_adr = __obj_adr;
    cur->_obj = __obj;
    cur->_op = "";

}

/******************************************************************************/

std::shared_ptr<ParseNode> get_last_obj(const std::shared_ptr<ParseNode>& __root) {

    // Create a pointer to traverse the tree.
    std::shared_ptr<ParseNode> cur = __root;

    // Move while right is not nullptr.
    while (cur->_right != nullptr) {
        cur = cur->_right;
    }

    // Return cur.
    return cur;

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

        // The token can't be in a closure, so if we find start
        // start of a closure, skip over it.
        if (__tokens[idx]->_type != TOKEN_LIT_STRING) {

            if (__tokens[idx]->_token == "[" ||
                __tokens[idx]->_token == "{" ||
                __tokens[idx]->_token == "(") {

                if (__tokens[idx]->_token == __token) {
                    return idx;
                }

                size_t match_idx = find_matching_ctrl(__tokens, idx, __tokens[idx]->_token);

                idx = match_idx == 0 ? idx : match_idx;
                continue;

            }

        }

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

std::pair<std::shared_ptr<RoskyInterface>*, std::shared_ptr<RoskyInterface>>
    form_object(const std::shared_ptr<Token_T>& __token,
                std::unique_ptr<VariableTable_T>& __var_table,
                size_t __scope) {

    // Literals
    if (__token->_type == TOKEN_LIT_INT) {
        return {nullptr, std::make_shared<RoskyInt>(std::stoi(__token->_token))};
    }
    if (__token->_type == TOKEN_LIT_STRING) {
        return {nullptr, std::make_shared<RoskyString>(__token->_token)};
    }

    // Symbols
    if (__token->_type == TOKEN_SYMBOL) {

        auto ret = __var_table->get_entry(__token->_token, __scope);
        if (ret != nullptr) {
            return {ret, *ret};
        }
    }

    // Keywords
    if (__token->_type == TOKEN_KW) {

        if (__token->_token == "null") {
            return {nullptr, std::make_shared<RoskyNull>()};
        }
        if (__token->_token == "nullptr") {
            return {nullptr, std::make_shared<RoskyPointer>(nullptr)};
        }
        if (__token->_token == "true") {
            return {nullptr, std::make_shared<RoskyBool>(true)};
        }
        if (__token->_token == "false") {
            return {nullptr, std::make_shared<RoskyBool>(false)};
        }

    }

    return {nullptr, nullptr};

}

/******************************************************************************/
