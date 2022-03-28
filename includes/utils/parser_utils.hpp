
/******************************************************************************/
//
//  Source Name:                parser_utils.hpp
//
//  Description:                This file contains a number of type
//                              definitions and helper functions for
//                              the parser to leverage.
//
//  Dependencies:               lexer_utils.hpp
//                              variable_handler.hpp
//                              
//                              all object definition files
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
//                              is_unary_op
//                              find_nextof
//                              find_matching_ctrl
//                              form_object
//                              
/******************************************************************************/

#ifndef PARSER_UTILS
#define PARSER_UTILS

/******************************************************************************/

#include <string>                       // std::string
#include <memory>                       // std::shared_ptr, std::weak_ptr
#include <iostream>                     // std::cout, std::endl;
#include <deque>                        // std::deque
#include <utility>                      // std::pair

#include "lexer_utils.hpp"
#include "../variable_handler.hpp"
#include "../objects/rosky_interface.hpp"
#include "../objects/rosky_int.hpp"
#include "../objects/rosky_pointer.hpp"
#include "../objects/rosky_null.hpp"

/******************************************************************************/

// This function allows us to get operator precedence.
inline size_t get_precedence(const std::string& op) {
    if (op == "=") { return 1; }
    if (op == "+") { return 2; }
    if (op == "*") { return 3; }
    if (op == "de" || op == "@") { return 4; }
    return 0;
}

/******************************************************************************/

// This defines the type of node the parse node is.
enum PARSE_NODE_TYPE {
    PARSE_OPERATOR,
    PARSE_OPERAND,
};

/******************************************************************************/

// This struct defines the parse tree node structure. The pointer
// to the parent node must be a weak_ptr to avoid cyclic referencing
// which would not allow memory to be freed from the shared_ptr's
// when the stack is unwound.
struct ParseNode {

    std::shared_ptr<RoskyInterface>* _obj_adr;  // For pointer referencing
    std::shared_ptr<RoskyInterface> _obj;
    std::string _op;
    PARSE_NODE_TYPE _type;
    size_t _colnum;
    size_t _linenum;

    std::shared_ptr<ParseNode> _left;
    std::shared_ptr<ParseNode> _right;
    std::weak_ptr<ParseNode> _parent;

    // Ctor.
    ParseNode(std::shared_ptr<RoskyInterface>* __obj_adr,
              const std::shared_ptr<RoskyInterface>& __obj,
              const std::string __op, PARSE_NODE_TYPE __type,
              size_t __col, size_t __lin)
        : _obj_adr(__obj_adr), _obj(__obj), _op(__op),
          _type(__type), _colnum(__col), _linenum(__lin) {}

    // Compare to nullptr
    inline bool is_nullptr() const noexcept {
        return _obj_adr == nullptr && _obj == nullptr;
    }

};

/******************************************************************************/

// This function is a tree helper function that inserts a child node
// as far right down the tree as possible.
void insert_right(std::shared_ptr<ParseNode>& __root,
                  std::shared_ptr<RoskyInterface>* __obj_adr,
                  const std::shared_ptr<RoskyInterface>& __obj,
                  const std::string& __sym_string,
                  size_t __col, size_t __lin);

// This function is a tree helper function for inserting operators
// into the tree.
void insert_op(std::shared_ptr<ParseNode>& __root,
               const std::string& __op,
               size_t __col, size_t __lin);

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

// This function determines if a token type is an assignment operator.
inline bool is_assignment_op(const std::string& op) noexcept {
    return op == "=";
}

// This function determines if an operator is left associative.
inline bool is_left_assoc(const std::string& op) noexcept {
    return (op == "+") || (op == "*");
}

// This function determines if an operator is right associative.
inline bool is_right_assoc(const std::string& op) noexcept {
    return (op == "=") ||
           (op == "@") || (op == "de");
}

// This function determines if an operator is unary.
inline bool is_unary_op(const std::string& op) noexcept {
    return (op == "*") || (op == "@");
}

// This function determines if an evaluator op is unary.
inline bool is_unary_eval_op(const std::string& op) noexcept {
    return (op == "de") || (op == "@");
}

/******************************************************************************/

// This function returns the index of the next occurence of a given
// token.
size_t find_nextof(const std::deque<std::shared_ptr<Token_T>>& __tokens,
                    size_t __start_idx, const std::string& __token);

// This function finds the corredsponding bracket, paren, brace, etc.
size_t find_matching_ctrl(const std::deque<std::shared_ptr<Token_T>>& __tokens,
                            size_t __start_idx, const std::string& __token);

/******************************************************************************/

// This function forms objects out of a token.
std::pair<std::shared_ptr<RoskyInterface>*, std::shared_ptr<RoskyInterface>>
    form_object(const std::shared_ptr<Token_T>& __token,
                std::unique_ptr<VariableTable_T>& __var_table,
                size_t __scope);

/******************************************************************************/

#endif // PARSER_UTILS
