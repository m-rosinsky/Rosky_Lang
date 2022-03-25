
/******************************************************************************/
//
//  Source Name:                evaluator.cpp
//
//  Description:                This file is responsible for evaluating
//                              a parse tree generated by the parser and
//                              returning the resulting object.
//
//  Dependencies:               parser_utils.hpp
//                              lexer_utils.hpp
//                              error_handler.hpp
//                              variable_handler.hpp
//                              rosky_interface.hpp
//                              rosky_int.hpp
//
//  Classes:                    None
//
//  Inherited Subprograms:      None
//
//  Exported Subprograms:       evaluate
//                              
/******************************************************************************/

#include "../includes/evaluator.hpp"

/******************************************************************************/

std::shared_ptr<RoskyInterface> evaluate(const std::shared_ptr<ParseNode>& __root, bool __top) {

    /***********************************************/
    /* Create the object based off the token type. */
    /***********************************************/

    // Literals
    if (__root->_value->_type == TOKEN_LIT_INT) {
        return std::make_shared<RoskyInt>(std::stoi(__root->_value->_token));
    }

    // Symbols
    if (__root->_value->_type == TOKEN_SYMBOL) {
        auto ret = get_entry(__root->_value->_token);

        // If this is the top level evaluation and the entry was nullptr,
        // this is an error for unrecognized symbol.
        if (__top && ret == nullptr) {
            throw_error(ERR_UNREC_SYM, __root->_value->_token, __root->_value->_colnum, __root->_value->_linenum);
        }
        return ret;
    }

    /********************************************/
    /*          Evaluate the operators.         */
    /********************************************/

    // Double left-right associative operators.
    if (__root->_value->_type == TOKEN_OP_DLR) {

        // Create a temp storage for the return value and the left and right operands.
        std::shared_ptr<RoskyInterface> ret_obj = nullptr;

        std::shared_ptr<RoskyInterface> left = evaluate(__root->_left, false);
        std::shared_ptr<RoskyInterface> right = evaluate(__root->_right, false);

        // The right side of an op is never allowed to be nullptr. This means
        // a symbol was unrecognized. Throw an error.
        if (right == nullptr) {
            throw_error(ERR_UNREC_SYM, __root->_right->_value->_token, __root->_right->_value->_colnum, __root->_right->_value->_linenum);
        }

        // The left side of the op is allowed to be nullptr on assignments,
        // so check those first.
        if (is_assignment_op(__root->_value->_token)) {

            // Simple Assignment.
            if (__root->_value->_token == "=") {
                set_entry(__root->_left->_value->_token, right);
            }

            // ***DEBUG***
            std::cout << __root->_left->_value->_token << " = " << right->to_string() << std::endl;
            // ***DEBUG***

            // Return the right-side object.
            return right;

        }

        // Now if the left side of the op is a nullptr, throw an error.
        if ((!is_assignment_op(__root->_value->_token)) && left == nullptr) {
            throw_error(ERR_UNREC_SYM, __root->_left->_value->_token, __root->_left->_value->_colnum, __root->_left->_value->_linenum);
        }

        if (__root->_value->_token == "+") {
            ret_obj = left->add_op(right);
        }
        if (__root->_value->_token == "*") {
            ret_obj = left->mul_op(right);
        }

        // If the ret_obj is nullptr, the operator was incompat.
        if (ret_obj == nullptr) {

            // Construct the error message.
            std::string err_msg = "'" + __root->_value->_token + "' with types: '";
            err_msg += left->get_type_string() + "' and '";
            err_msg += right->get_type_string() + "'";
            throw_error(ERR_OP_INCOMPAT, err_msg, __root->_value->_colnum, __root->_value->_linenum);
        }

        // std::cout << ret_obj->to_string() << std::endl;

        // Return the object.
        return ret_obj;

    }

    // Should never reach here, but for safety.
    throw_error(ERR_UNEXP_OP, __root->_value->_token, __root->_value->_colnum, __root->_value->_linenum);

}

/******************************************************************************/
